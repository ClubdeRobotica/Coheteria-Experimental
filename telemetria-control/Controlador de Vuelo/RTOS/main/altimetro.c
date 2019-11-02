/*
 * altimetro.c
 *
 *  Created on: 30 oct. 2019
 *      Author: german
 */

#include "altimetro.h"
#include "hal.h"
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include "bmp180.h"
#include <string.h>


#define NUM_OF_MESSURES		4				//!< Numero de mediciones
#define MESSURES_INTERVAL   20				//!< Tiempo entre mediciones

bmp180_dev_t dev;
TaskHandle_t *BayoTaskHand = NULL;
QueueHandle_t *BayoQueueReceiver = NULL;			//!< Cola para recibir datos desde las tareas secundarias
/*
 * @brief: Una vez configurado toma una medicion de temperatura y presion cada 10 ms y los envia al main_task
 * Tiene tres estados principales:
 * 	* StatusInit:	 El estado inicial, inicializa el modulo y queda a la espera de un comando de inicio de las mediciones o un comando de calibracion
 * 	* StatusReady:   En tiempo de ejecucion, toma una medicion cada 10 ms.
 * 	* StatusSending: En tiempo de ejecucion, cuando se han tomado 5 o 10 mediciones, se promedian
 */

int Bmp_InitAndCalibrate(BmpData_t *BufferToSave);			//!< Inicializa el bmp180 y lo calibra para que comience a tomar mediciones, devuelve los valores iniciales de T y P

void bmp180(void *pvParameters)
{
	static BmpData_t ValZero;
    static BmpData_t ValActual;
    float temp = 0;
    uint32_t press = 0;
    esp_err_t res = 0;
    portTickType xCurrentTick;
    uint8_t bmp180status = bmpStInit;
    xCurrentTick = xTaskGetTickCount();
    QueueData_t AltimeterData;
    AltimeterData.SensorId = Barometer_0;
    printf("\n____________Iniciando Bmp_Task_______________\n");
    ValZero.pressure = 2000;
    ValZero.temperature = 12.32;
    ValZero.time = xCurrentTick;
    while (1)
    {
        vTaskDelayUntil( &xCurrentTick, (MESSURES_INTERVAL));  // Antes de comenzar una medicion espero a que se cumplan los 10ms
        xCurrentTick = xTaskGetTickCount();
		switch(bmp180status){
		case bmpStInit:

			if(Bmp_InitAndCalibrate(&ValZero)==0){
				AltimeterData.SensorData = (void *)&ValZero;
				//printf("bmp180.c: Enviando notificacion T: %f, P:%d, time: %d", ValZero.temperature, ValZero.pressure, ValZero.time);
				if(xQueueSend(BayoQueueReceiver, (void *)&AltimeterData, portMAX_DELAY)!=pdPASS)
					printf("bmp180.c: Error al enviar los datos");
				bmp180status = bmpStReady;
			}
			else{
				printf("bmp180.c: Error al inicializar el sensor\n");
			}
			break;

		case bmpStReady:

			res = bmp180_measure(&dev, &temp, &press, BMP180_MODE_STANDARD);
			if (res != ESP_OK){
				//TODO enviar en la cola informacion sobre el error al medir
				printf("Could not measure: %d\n", res);
			}
			ValActual.temperature = temp;
			ValActual.pressure = press;
			ValActual.time = xTaskGetTickCount();
			AltimeterData.SensorData = (void *)&ValActual;
			xQueueSend(BayoQueueReceiver, &AltimeterData, portMAX_DELAY);
			break;

		case bmpStSending:
			printf("bmp180.c: bmpStSending\n");
			xQueueSend(BayoQueueReceiver, &AltimeterData, portMAX_DELAY);
			// Enviar notificacion a bayo
			bmp180status = bmpStReady;
			break;

		default:
			printf("bmp180.c: Status Unknown\n");
			break;
		}
    }
}



int Bmp_InitAndCalibrate(BmpData_t *BufferToSave){
    ESP_ERROR_CHECK(i2cdev_init());
    memset(&dev, 0, sizeof(bmp180_dev_t)); // Zero descriptor
    ESP_ERROR_CHECK(bmp180_init_desc(&dev, 0, SDA_GPIO, SCL_GPIO));
    ESP_ERROR_CHECK(bmp180_init(&dev));
    float temp;
    uint32_t pressure;
	esp_err_t res;
	res = bmp180_measure(&dev, &temp, &pressure, BMP180_MODE_STANDARD);
	if (res != ESP_OK){
		printf("Bmp_InitAndCalibrate: Could not measure: %d\n", res);
		return -1;
	}
	//TODO: Agregar filotro kalman para limpiar las medicionoes
	BufferToSave->temperature = temp;
	BufferToSave->pressure = pressure;
	BufferToSave->time = xTaskGetTickCount();
	return 0;
}

void InicializarAltimetro(TaskHandle_t TaskHandler, QueueHandle_t Queue){
	BayoTaskHand = TaskHandler;
	BayoQueueReceiver = Queue;
	//xTaskCreatePinnedToCore(bmp180, "bmp180_test", configMINIMAL_STACK_SIZE * 15, NULL, 5, NULL, 1);
    xTaskCreate(bmp180,   "Altimetro", configMINIMAL_STACK_SIZE+1500, NULL, 5, NULL);
}
