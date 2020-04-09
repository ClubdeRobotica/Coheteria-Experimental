/***************************************************************************
  This is a library for the BMP085 pressure sensor

  Designed specifically to work with the Adafruit BMP085 or BMP180 Breakout
  ----> http://www.adafruit.com/products/391
  ----> http://www.adafruit.com/products/1603

  These displays use I2C to communicate, 2 pins are required to interface.

  Adafruit invests time and resources providing this open source code,
  please support Adafruit andopen-source hardware by purchasing products
  from Adafruit!

  Written by Kevin Townsend for Adafruit Industries.
  BSD license, all text above must be included in any redistribution
 ***************************************************************************/
#ifndef __BMP085_H__
#define __BMP085_H__

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "driver/i2c.h"
#include "CdR_gpio.h"
#include "hal.h"
#include "bmp180.h"
/*=========================================================================
    -----------------------------------------------------------------------*/
#define BMP180_ADDR		            (0x77)
#define I2C_SCL_IO     				BOARD_D7        /*!< gpio number for I2C master clock */
#define I2C_SDA_IO 	  				BOARD_D6 		/*!< gpio number for I2C master data  */
#define BMP180_RX_QUEUE_SIZE      	10
#define BMP180_TASK_PRIORITY     	9

#define BMP180_VERSION_REG        	0xD0
#define BMP180_CONTROL_REG        	0xF4
#define BMP180_RESET_REG          	0xE0
#define BMP180_OUT_MSB_REG        	0xF6
#define BMP180_OUT_LSB_REG        	0xF7
#define BMP180_OUT_XLSB_REG       	0xF8

#define BMP180_CALIBRATION_REG    	0xAA
#define BMP180_MEASURE_TEMP       	0x2E
#define BMP180_MEASURE_PRESS      	0x34

#define BMP180_CHIP_ID            	0x55

#define BMP180_RESET_VALUE 		  	0xB6


#define BMP180_TEMPERATURE 			(1<<0)
#define BMP180_PRESSURE 			(1<<1)

// Calibration constants
typedef struct
{
    int16_t  AC1;
    int16_t  AC2;
    int16_t  AC3;
    uint16_t AC4;
    uint16_t AC5;
    uint16_t AC6;
    int16_t  B1;
    int16_t  B2;
    int16_t  MB;
    int16_t  MC;
    int16_t  MD;
} bmp180_constants_t;


// temperature in °C
typedef float bmp180_temp_t;
// pressure in mPa (To get hPa divide by 100)
typedef uint32_t bmp180_press_t;
// BMP180_Event_Result
typedef struct
{
    uint8_t cmd;
    bmp180_temp_t  temperature;
    bmp180_press_t pressure;
} bmp180_result_t;


void i2c_master_init();
s8 BMP180_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);
s8 BMP180_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt);


// Returns true if the bmp180 is detected.
bool bmp180_is_available(u8 dev_addr);
// Reads all the internal constants, returning true on success.
bool bmp180_fillInternalConstants(u8 dev_addr, bmp180_constants_t *c);
// Reads an optional temperature and pressure. The over sampling
// setting, oss, may be 0 to 3. Returns true on success.
bool bmp180_measure(u8 dev_addr, bmp180_constants_t *c, int32_t *temperature,
uint32_t *pressure, uint8_t oss);

#endif
