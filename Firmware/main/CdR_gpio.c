/*
 * CdR_gpio.c
 *
 *  Created on: 23 mar. 2019
 *      Author: german
 */

#include "CdR_gpio.h"


void	InitializeGPIO(char AGpioPin, char ABitMask){
    gpio_config_t io_conf;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.mode = AGpioPin;
    io_conf.pin_bit_mask = ABitMask;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
}
