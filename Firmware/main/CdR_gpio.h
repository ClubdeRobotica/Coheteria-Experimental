/*
 * gpio.h
 *
 *  Created on: 23 mar. 2019
 *      Author: german
 */


#include "driver/gpio.h"

#ifndef MAIN_DRIVERS_CDR_GPIO_H_
#define MAIN_DRIVERS_CDR_GPIO_H_

/********	CAPA DE ABSTRACCION DE HARDWARE		******/
#define BOARD_D0			16
#define BOARD_D1			5
#define BOARD_D2			4
#define BOARD_D3			0
#define BOARD_D4			2
#define BOARD_D5			14
#define BOARD_D6			12
#define BOARD_D7			13

#define MASK_D0				GPIO_Pin_16
#define MASK_D1				GPIO_Pin_5
#define MASK_D2				GPIO_Pin_4
#define MASK_D3				GPIO_Pin_0
#define MASK_D4				GPIO_Pin_2
#define MASK_D5				GPIO_Pin_14
#define MASK_D6				GPIO_Pin_12
#define MASK_D7				GPIO_Pin_13

#define BOARD_LED			BOARD_D4
#define MASK_LED			MASK_D4
/********	********/

void	InitializeGPIO(char AGpioPin, char ABitMask);

#endif /* MAIN_DRIVERS_CDR_GPIO_H_ */
