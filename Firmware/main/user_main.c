/* gpio example
   This example code is in the Public Domain (or CC0 licensed, at your option.)
   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "freertos/FreeRTOS.h"
#include "freertos/queue.h"
#include "freertos/task.h"
#include "freertos/event_groups.h"

#include "rom/ets_sys.h"
#include "esp_wifi.h"
#include "esp_event_loop.h"
#include "nvs_flash.h"

#include "esp_log.h"
#include "esp_system.h"

#include "hal.h"
#include "driver/uart.h"

#include "CdR_gpio.h"
#include "BMP180i2c.h"

#include "wifi.h"

#define BUF_SIZE (128)
static const int START_BIT = BIT0;
/* FreeRTOS event group to signal when we are connected*/
static EventGroupHandle_t wifi_event_group;

/* The event group allows multiple bits for each event,
   but we only care about one event - are we connected
   to the AP with an IP? */
const int WIFI_CONNECTED_BIT = BIT0;


static esp_err_t event_handler(void* ctx, system_event_t* event)
{
    switch (event->event_id) {
        case SYSTEM_EVENT_STA_START:
            xEventGroupSetBits(wifi_event_group, START_BIT);
            break;

        default:
            break;
    }

    return ESP_OK;
}


void InitializeUART0(void){
    // Configure parameters of an UART driver,
    // communication pins and install the driver
    uart_config_t uart_config = {
        .baud_rate = 115200,
        .data_bits = UART_DATA_8_BITS,
        .parity    = UART_PARITY_DISABLE,
        .stop_bits = UART_STOP_BITS_1,
        .flow_ctrl = UART_HW_FLOWCTRL_DISABLE
    };
    uart_param_config(UART_NUM_0, &uart_config);
    uart_driver_install(UART_NUM_0, BUF_SIZE * 2, 0, 0, NULL);
    uart_write_bytes(UART_NUM_0, (const char *)"UART OK", 4);
}

/*
 * Blinky para saber si el sistema esta funcionando ok
 */
void StayAliveTask( void * pvParameters )
{
	InitializeGPIO(BOARD_LED, GPIO_OUTPUT_PIN_SEL);
	ESP_LOGI("StayAliveTask", "Iniciado");
    for (;;) {
        gpio_set_level(BOARD_LED, 0);
        vTaskDelay(30 / portTICK_PERIOD_MS);
        gpio_set_level(BOARD_LED, 1);
        vTaskDelay(50 / portTICK_PERIOD_MS);
        gpio_set_level(BOARD_LED, 0);
        vTaskDelay(30 / portTICK_PERIOD_MS);
        gpio_set_level(BOARD_LED, 1);
        vTaskDelay(1910 / portTICK_PERIOD_MS);
    }
}

/*
 * Tarea de tesete de la uart, devuelve todos los caracteres que recive
 */
void UartTask( void * pvParameters )
{
    // Configure a temporary buffer for the incoming data
    uint8_t *data = (uint8_t *) malloc(BUF_SIZE);
    ESP_LOGI("UartTask", "Iniciado");
    while (1) {
        // Read data from the UART
        int len = uart_read_bytes(UART_NUM_0, data, BUF_SIZE, 20);
        // Write data back to the UART
        uart_write_bytes(UART_NUM_0, (const char *) data, len);
    }
}

void i2c_task_example(void *arg)
{
    uint8_t sensor_data[14];
    uint8_t who_am_i, i;
    double Temp;
    static uint32_t error_count = 0;
    int ret;

    i2c_example_master_mpu6050_init(I2C_EXAMPLE_MASTER_NUM);

    while (1) {
        who_am_i = 0;
        i2c_example_master_mpu6050_read(I2C_EXAMPLE_MASTER_NUM, WHO_AM_I, &who_am_i, 1);

        if (0x68 != who_am_i) {
            error_count++;
        }

        memset(sensor_data, 0, 14);
        ret = i2c_example_master_mpu6050_read(I2C_EXAMPLE_MASTER_NUM, ACCEL_XOUT_H, sensor_data, 14);

        if (ret == ESP_OK) {
            ESP_LOGI("I2C", "*******************\n");
            ESP_LOGI("I2C", "WHO_AM_I: 0x%02x\n", who_am_i);
            Temp = 36.53 + ((double)(int16_t)((sensor_data[6] << 8) | sensor_data[7]) / 340);
            ESP_LOGI("I2C", "TEMP: %d.%d\n", (uint16_t)Temp, (uint16_t)(Temp * 100) % 100);

            for (i = 0; i < 7; i++) {
                ESP_LOGI("I2C", "sensor_data[%d]: %d\n", i, (int16_t)((sensor_data[i * 2] << 8) | sensor_data[i * 2 + 1]));
            }

            ESP_LOGI("I2C", "error_count: %d\n", error_count);
        } else {
            ESP_LOGE("I2C", "No ack, sensor not connected...skip...\n");
        }

        vTaskDelay(100 / portTICK_RATE_MS);
    }

    i2c_driver_delete(I2C_EXAMPLE_MASTER_NUM);
}

void app_main()
{
	ESP_ERROR_CHECK(nvs_flash_init());
	InitializeUART0();
	//InitializeWIFI();
	Wifi_start();
	//xTaskCreate(&i2c_task_example, "i2c_task_example", 2048, NULL, 10, NULL);
    xTaskCreate(&UartTask, "uart_echo_task", 2048, NULL, 10, NULL);
    xTaskCreate(&StayAliveTask, "gpio_task_example", 2048, NULL, 10, NULL);
}
