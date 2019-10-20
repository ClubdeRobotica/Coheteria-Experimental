#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <esp_system.h>
#include "bmp180.h"
#include "hal.h"
#include <string.h>
#include "wifi.h"

#define SDA_GPIO 4
#define SCL_GPIO 5

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
				printf("T0: %.2f C; P0: %d MPa\n", TempZero, PressureZero);
				bmp180status = bmpStSending;
			}
			break;

		case bmpStReady:
			res = bmp180_measure(&dev, &temp, &pressure, BMP180_MODE_STANDARD);
			if (res != ESP_OK)
				printf("Could not measure: %d\n", res);
			else
				printf(".");
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
			printf("Temperature: %.2f C; Pressure: %d MPa\n", TempAverage, PressAverage);
			bmp180status = bmpStReady;
			break;

		default:
			break;
		}
        // TODO: Enviar datos al main
    }
}

void app_main()
{
    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(i2cdev_init());
    initialise_wifi(&server);
    xTaskCreatePinnedToCore(bmp180, "bmp180_test", configMINIMAL_STACK_SIZE * 15, NULL, 5, NULL, APP_CPU_NUM);
}
