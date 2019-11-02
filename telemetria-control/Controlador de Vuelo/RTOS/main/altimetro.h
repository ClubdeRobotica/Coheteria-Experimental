/*
 * altimetro.h
 *
 *  Created on: 27 oct. 2019
 *      Author: german
 */

#ifndef MAIN_ALTIMETRO_H_
#define MAIN_ALTIMETRO_H_

#include <stdint.h>
#include "hal.h"
#include <stdio.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/queue.h>
#include <esp_system.h>
#include <string.h>



enum BarometerStatus{
	bmpStInit,
	bmpStReady,
	bmpStSending,
};

typedef struct _bmpData_t{
	uint32_t time;				//!< El momento en que se tomo la medicion en ticks
	float temperature;		//!< Temperatura
	uint32_t pressure;			//!< Presion
}BmpData_t;

void bmp180(void *pvParameters);
void InicializarAltimetro(TaskHandle_t TaskHandler, QueueHandle_t Queue);

#endif /* MAIN_ALTIMETRO_H_ */
