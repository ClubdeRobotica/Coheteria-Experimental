/*
 * hal.h
 *
 *  Created on: 19 oct. 2019
 *      Author: german
 */

#ifndef MAIN_HAL_H_
#define MAIN_HAL_H_
#include <stdint.h>

#define BMP_I2C_PORT						0
#define BUZZER_PIN							2	//TODO Cambiar este pin en la Rev2
#define SDA_GPIO 							4
#define SCL_GPIO 							5

#define STASSID 							"WiFi-Arnet-kxde"
#define STAPSK  							"dkfkchxbm4"
#define IP_PC     							"192.168.1.3"

#define PATH_DATA							"/spiffs/Data.txt"

#define BUZZER_CLOCK						10
#define BUZZER_TIME_INIT					10
#define BUZZER_PERIOD_INIT					90
#define BUZZER_TIME_READY					3
#define BUZZER_PERIOD_READY					200

typedef struct _QueueData{
	uint8_t SensorId;
	void*	SensorData;
}QueueData_t;

enum Sensores{
	Barometer_0,
	Acelerometer_0,
};

enum SystemStatus{
	sys_init,
	sys_calibration,
	sys_alert,
	sys_ready
};

#define ALTIMETER_BIT						( 1 << 0 )
#endif /* MAIN_HAL_H_ */
