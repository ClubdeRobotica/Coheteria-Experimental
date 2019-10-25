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

static char DataBuffer[64];

enum SystemStatus{
	sys_init,
	sys_calibration,
	sys_alert,
	sys_ready
};

static uint8_t SystemStatus = sys_init;
///////////////////////////////////////////////
// Barometros.c
// Todo esto se tendria que pasar a un nuevo documento para que quede mas ordenado


enum BarometerStatus{
	bmpStInit,
	bmpStReady,
	bmpStSending,
};

#define NUM_OF_MESSURES		4				//Numero de mediciones
#define MESSURES_INTERVAL   20				//Tiempo entre mediciones
/*
 * @brief: Una vez configurado toma una medicion de temperatura y presion cada 10 ms y los envia al main_task
 * Tiene tres estados principales:
 * 	* StatusInit:	 El estado inicial, inicializa el modulo y queda a la espera de un comando de inicio de las mediciones o un comando de calibracion
 * 	* StatusReady:   En tiempo de ejecucion, toma una medicion cada 10 ms.
 * 	* StatusSending: En tiempo de ejecucion, cuando se han tomado 5 o 10 mediciones, se promedian
 */
void bmp180(void *pvParameters)
{
    bmp180_dev_t dev;
    float temp, TempZero, SumTemp, TempAverage;
    uint32_t pressure, PressureZero, SumPressure, PressAverage;
    esp_err_t res = 0;
    portTickType xCurrentTick;
    uint8_t bmp180status = bmpStInit,
    		bmpMessuresCount = 0;
    memset(&dev, 0, sizeof(bmp180_dev_t)); // Zero descriptor

    ESP_ERROR_CHECK(bmp180_init_desc(&dev, 0, SDA_GPIO, SCL_GPIO));
    ESP_ERROR_CHECK(bmp180_init(&dev));
    xCurrentTick = xTaskGetTickCount();
	SumTemp = 0;
	SumPressure = 0;
    while (1)
    {
        vTaskDelayUntil( &xCurrentTick, (MESSURES_INTERVAL / portTICK_RATE_MS));  // Antes de comenzar una medicion espero a que se cumplan los 10ms
        xCurrentTick = xTaskGetTickCount();
		switch(bmp180status){
		case bmpStInit:// TODO reemplazar por una funcion de calbibracion
			SystemStatus = sys_init;
			res = bmp180_measure(&dev, &temp, &pressure, BMP180_MODE_STANDARD);
			if (res != ESP_OK)
				printf("Could not measure: %d\n", res);
			else
				printf(".");
			SumTemp += temp;
			SumPressure += pressure;
			bmpMessuresCount++;
			if(bmpMessuresCount == NUM_OF_MESSURES){
				TempZero = SumTemp / NUM_OF_MESSURES;
				PressureZero = SumPressure / NUM_OF_MESSURES;
				SumTemp = 0;
				SumPressure = 0;
				sprintf(DataBuffer, "T0: %.2f C; P0: %d MPa\n", TempZero, PressureZero);
				bmp180status = bmpStSending;
			}
			break;

		case bmpStReady:
			SystemStatus = sys_ready;
			res = bmp180_measure(&dev, &temp, &pressure, BMP180_MODE_STANDARD);
			if (res != ESP_OK)
				printf("Could not measure: %d\n", res);
			SumTemp += temp;
			SumPressure += pressure;
			bmpMessuresCount++;
			if(bmpMessuresCount == NUM_OF_MESSURES){
				TempAverage = SumTemp / NUM_OF_MESSURES;
				PressAverage = SumPressure / NUM_OF_MESSURES;
				SumTemp = 0;
				SumPressure = 0;
				bmp180status = bmpStSending;
			}
			break;

		case bmpStSending:
			bmpMessuresCount=0;
			SumTemp = 0;
			SumPressure = 0;
			sprintf(DataBuffer, "Temperature: %.2f C; Pressure: %d MPa\n", TempAverage, PressAverage);
			bmp180status = bmpStReady;
			break;

		default:
			break;
		}
        // TODO: Enviar datos al main
    }
}


void buzzer_task(void)
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
		        vTaskDelay(50 / portTICK_RATE_MS);
    		}
    		filesystem_main();
    		LoadData(PATH_DATA);
    		break;
    	case sys_ready:
    		if(BuzzerBip < BUZZER_TIME_READY){
    			gpio_set_level(BUZZER_PIN, 1);
    		}
    		else
    			gpio_set_level(BUZZER_PIN, 0);
    		if(BuzzerBip > BUZZER_PERIOD_READY){
    			SaveData (DataBuffer, PATH_DATA, EF_Append);
    			BuzzerBip = 0;
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

void app_main()
{
    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(i2cdev_init());
    initialise_wifi(&server);
    SystemStatus = 0;
    xTaskCreatePinnedToCore(bmp180, "bmp180_test", configMINIMAL_STACK_SIZE * 15, NULL, 5, NULL, APP_CPU_NUM);
    xTaskCreatePinnedToCore(buzzer_task, "buzzer_task", configMINIMAL_STACK_SIZE * 15, NULL, 5, NULL, APP_CPU_NUM);
    //xTaskCreate(buzzer_task, "buzzer_task", 512, NULL, 10, NULL);
}
