/*
 * hal.h: La capa de abstraccion de Hardware, poner aca todos los defines necesarios
 *
 *  Created on: 13 ene. 2019
 *      Author: german
 */

#include "CdR_gpio.h"

#ifndef MAIN_HAL_H_
#define MAIN_HAL_H_

#define EXAMPLE_ESP_WIFI_MODE_AP   	false //TRUE:AP FALSE:STA
#define EXAMPLE_ESP_WIFI_SSID      	"Fibertel WiFi292 2.4GHz"
#define EXAMPLE_ESP_WIFI_PASS      	"0043192350"
#define EXAMPLE_MAX_STA_CONN 		1

#define GPIO_LED    		 BOARD_LED
#define GPIO_OUTPUT_PIN_SEL  MASK_LED

#endif /* MAIN_HAL_H_ */
