#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include "bmp180.h"
#include "hal.h"
#include <string.h>
#include "wifi.h"
#include "driver/gpio.h"
#include "filesystem.h"
#include "altimetro.h"

static char DataBuffer[64];
TaskHandle_t BayoTaskHandler = NULL;
QueueHandle_t BayoQueue = NULL;			//!< Cola para recibir datos desde las tareas secundarias
uint8_t SystemStatus = sys_init;

void buzzer_task( void * pvParameters )
{
    gpio_config_t io_conf;
    //disable interrupt
    io_conf.intr_type = GPIO_INTR_DISABLE;
    //set as output mode
    io_conf.mode = GPIO_MODE_OUTPUT;
    //bit mask of the pins that you want to set,e.g.GPIO15/16
    io_conf.pin_bit_mask = (1ULL<<BUZZER_PIN);
    //disable pull-down mode
    io_conf.pull_down_en = 0;
    //disable pull-up mode
    io_conf.pull_up_en = 0;
    //configure GPIO with the given settings
    gpio_config(&io_conf);
	gpio_set_level(BUZZER_PIN, 0);
    uint8_t BuzzerBip = 0, bips=0, times = 0;
    printf("\n____________Iniciando Buzzer_Task_______________\n");
    while (1) {
    	switch (SystemStatus){
    	case sys_init:
    		while(bips<8){
				if(BuzzerBip++ < (BUZZER_TIME_INIT)){
					gpio_set_level(BUZZER_PIN, 1);
				}
				else
					gpio_set_level(BUZZER_PIN, 0);
				if(BuzzerBip++ > (BUZZER_PERIOD_INIT-times)){
					BuzzerBip = 0;
					times+=10;
					bips++;
				}
		        vTaskDelay(50);
    		}
    		break;
    	case sys_ready:
    		if(BuzzerBip < BUZZER_TIME_READY){
    			gpio_set_level(BUZZER_PIN, 1);
    		}
    		else
    			gpio_set_level(BUZZER_PIN, 0);
    		if(BuzzerBip > BUZZER_PERIOD_READY){
    			BuzzerBip = 0;
    			printf(".");
    		}

    		break;
    	case sys_calibration:
    		break;
    	case sys_alert:
    		break;
    	default:
    		break;
    	}
    	BuzzerBip++;
        vTaskDelay(BUZZER_CLOCK);
    }
}

/*
 * Esta es la notificacion principal del sistema, se encarga de sincronizar las tareas
 * pide datos a las otras tareas por medio de los eventbits, lee por los valores desde un Queue
 */
void BayoTask( void * pvParameters )
{
	const TickType_t xBlockTime = 100;					//!< El tiempo maximo que se puede esperar por un sensor
	QueueData_t SensorData;
	BmpData_t *ReceivedBmpData;
	printf("\n____________Iniciando BayoTask_______________\n");
	while(1){
		switch (SystemStatus){
		case sys_init:
			printf("BayoTask: sys_init\n");
		    InicializarAltimetro(BayoTaskHandler, BayoQueue);
			// Primero espero a que se hayan inicializado todos los sensores
			// Tomo la presion y temperatura iniciales, lo mismo con los acelerometros
			// Genero un archivo nuevo y guardo todos los valores
			if(xQueueReceive(BayoQueue, &SensorData, portMAX_DELAY)==pdFAIL){
				printf("Error al recibir BayoQueue");
			}
			if(SensorData.SensorId == Barometer_0){
				ReceivedBmpData = SensorData.SensorData;
				printf("Iniciales: Temperature: %.2f C; Pressure: %d MPa\n", ReceivedBmpData->temperature, ReceivedBmpData->pressure);
				//sprintf(DataBuffer, "Iniciales: Temperature: %.2f C; Pressure: %d MPa\n", ReceivedBmpData->temperature, ReceivedBmpData->pressure);
				SystemStatus = sys_ready;
			}
			break;

		case sys_ready:
			xQueueReceive(BayoQueue, &SensorData, xBlockTime);
			if(SensorData.SensorId == Barometer_0){
				ReceivedBmpData = SensorData.SensorData;
				printf("Temperature: %.2f C; Pressure: %d MPa\n", ReceivedBmpData->temperature, ReceivedBmpData->pressure);
				//sprintf(DataBuffer, "Temperature: %.2f C; Pressure: %d MPa\n", ReceivedBmpData->temperature, ReceivedBmpData->pressure);
			}
			break;
		default:
			break;
		}
	}
}

void app_main()
{
    static httpd_handle_t server = NULL;
    initialise_wifi(&server);
    BayoQueue = xQueueCreate( 5, (sizeof(QueueData_t)) );
//    xTaskCreatePinnedToCore(buzzer_task, "buzzer_task", configMINIMAL_STACK_SIZE * 15, NULL, 5, NULL, APP_CPU_NUM);
    //xTaskCreatePinnedToCore(BayoTask, "Bayo_Main", configMINIMAL_STACK_SIZE *15 , 5, NULL, 5, APP_CPU_NUM);
    xTaskCreate(BayoTask,   "TareaPrincipalBayo", configMINIMAL_STACK_SIZE+500, NULL, 5, &BayoTaskHandler);
    xTaskCreate(buzzer_task, "Control de Estado", configMINIMAL_STACK_SIZE+500, NULL, 5, NULL);
    printf("\n____________Iniciando el sistema_______________\n");
}
