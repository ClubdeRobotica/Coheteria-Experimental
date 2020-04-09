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
 ****************************************************************************
#include <math.h>
#include <limits.h>
#include <stdbool.h>

#include "BMP180i2c.h"

#include "driver/gpio.h"
#include "driver/i2c.h"
#include "esp_err.h"
#include "esp_log.h"
#include "freertos/task.h"
#include "bmp180.h"

#define I2C_MASTER_ACK 		0
#define I2C_MASTER_NACK 	1

void i2c_master_init()
{
	i2c_config_t i2c_config = {
		.mode = I2C_MODE_MASTER,
		.sda_io_num = I2C_SDA_IO,
		.scl_io_num = I2C_SCL_IO,
		.sda_pullup_en = GPIO_PULLUP_ENABLE,
		.scl_pullup_en = GPIO_PULLUP_ENABLE,
		//.master.clk_speed = 1000000
	};
	i2c_param_config(I2C_NUM_0, &i2c_config);
	i2c_driver_install(I2C_NUM_0, I2C_MODE_MASTER);
}

s8 BMP180_I2C_bus_write(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = ESP_OK;

	esp_err_t espRc;
	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);

	i2c_master_write_byte(cmd, reg_addr, true);
	i2c_master_write(cmd, reg_data, cnt, true);
	i2c_master_stop(cmd);

	espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
	if (espRc == ESP_OK) {
		iError = ESP_OK;
	} else {
		iError = ESP_FAIL;
	}
	i2c_cmd_link_delete(cmd);

	return (s8)iError;
}

s8 BMP180_I2C_bus_read(u8 dev_addr, u8 reg_addr, u8 *reg_data, u8 cnt)
{
	s32 iError = ESP_OK;
	esp_err_t espRc;

	i2c_cmd_handle_t cmd = i2c_cmd_link_create();

	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_WRITE, true);
	i2c_master_write_byte(cmd, reg_addr, true);

	i2c_master_start(cmd);
	i2c_master_write_byte(cmd, (dev_addr << 1) | I2C_MASTER_READ, true);

	if (cnt > 1) {
		i2c_master_read(cmd, reg_data, cnt-1, I2C_MASTER_ACK);
	}
	i2c_master_read_byte(cmd, reg_data+cnt-1, I2C_MASTER_NACK);
	i2c_master_stop(cmd);

	espRc = i2c_master_cmd_begin(I2C_NUM_0, cmd, 10/portTICK_PERIOD_MS);
	if (espRc == ESP_OK) {
		iError = ESP_OK;
	} else {
		iError = ESP_FAIL;
	}

	i2c_cmd_link_delete(cmd);

	return (s8)iError;
}


int bmp180_start_Messurement(u8 dev_addr, u8 reg_data)
{
    uint8_t reg = BMP180_CONTROL_REG;
    return BMP180_I2C_bus_write(dev_addr, reg, &reg_data, 1);
}

bool bmp180_get_uncompensated_temperature(u8 dev_addr, int32_t *ut)
{
    // Write Start Code into reg 0xF4.
    if (bmp180_start_Messurement(dev_addr, BMP180_MEASURE_TEMP))
        return false;

    // Wait 5ms, datasheet states 4.5ms
    vTaskDelay(5);

    int16_t v;
    if (BMP180_I2C_bus_read(dev_addr, BMP180_OUT_MSB_REG, &v, 2))
        return false;

    *ut = v;
    return true;
}

bool bmp180_get_uncompensated_pressure(u8 dev_addr, uint8_t oss, uint32_t *up)
{
    uint16_t us;

    // Limit oss and set the measurement wait time. The datasheet
    // states 4.5, 7.5, 13.5, 25.5ms for oss 0 to 3.
    switch (oss) {
      case 0: us = 5; break;
      case 1: us = 8; break;
      case 2: us = 14; break;
      default: oss = 3; us = 26; break;
    }

    // Write Start Code into reg 0xF4
    if (bmp180_start_Messurement(dev_addr, BMP180_MEASURE_PRESS | (oss << 6)))
        return false;

    vTaskDelay(us);

    uint8_t d[] = { 0, 0, 0 };
    uint8_t reg = BMP180_OUT_MSB_REG;
    if (BMP180_I2C_bus_read(dev_addr, reg, &d, 3))
        return false;

    uint32_t r = ((uint32_t)d[0] << 16) | ((uint32_t)d[1] << 8) | d[2];
    r >>= 8 - oss;
    *up = r;
    return true;
}


// Returns true of success else false.
bool bmp180_fillInternalConstants(u8 dev_addr, bmp180_constants_t *c)
{
    if (bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+0, &c->AC1) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+2, &c->AC2) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+4, &c->AC3) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+6, (int16_t *)&c->AC4) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+8, (int16_t *)&c->AC5) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+10, (int16_t *)&c->AC6) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+12, &c->B1) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+14, &c->B2) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+16, &c->MB) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+18, &c->MC) ||
        bmp180_readRegister16(dev_addr, BMP180_CALIBRATION_REG+20, &c->MD)) {
        return false;
    }

    // Error if any read as 0x0000 or 0xffff.
    return !(c->AC1 == 0x0000 || c->AC2 == 0x0000 || c->AC3 == 0x0000 ||
             c->AC4 == 0x0000 || c->AC5 == 0x0000 || c->AC6 == 0x0000 ||
             c->B1 == 0x0000 || c->B2 == 0x0000 ||
             c->MB == 0x0000 || c->MC == 0x0000 || c->MD == 0x0000 ||
             c->AC1 == 0xffff || c->AC2 == 0xffff || c->AC3 == 0xffff ||
             c->AC4 == 0xffff || c->AC5 == 0xffff || c->AC6 == 0xffff ||
             c->B1 == 0xffff || c->B2 == 0xffff ||
             c->MB == 0xffff || c->MC == 0xffff || c->MD == 0xffff);
}

//*/
