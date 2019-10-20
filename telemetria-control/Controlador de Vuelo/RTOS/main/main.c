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

void bmp180(void *pvParameters)
{
    bmp180_dev_t dev;
    memset(&dev, 0, sizeof(bmp180_dev_t)); // Zero descriptor

    ESP_ERROR_CHECK(bmp180_init_desc(&dev, 0, SDA_GPIO, SCL_GPIO));
    ESP_ERROR_CHECK(bmp180_init(&dev));

    while (1)
    {
        float temp;
        uint32_t pressure;

        printf("Current core: %d\n", xPortGetCoreID());

        esp_err_t res = bmp180_measure(&dev, &temp, &pressure, BMP180_MODE_STANDARD);
        if (res != ESP_OK)
            printf("Could not measure: %d\n", res);
        else
            printf("Temperature: %.2f degrees Celsius; Pressure: %d MPa\n", temp, pressure);

        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}

void app_main()
{
    static httpd_handle_t server = NULL;
    ESP_ERROR_CHECK(i2cdev_init());
    initialise_wifi(&server);
    xTaskCreatePinnedToCore(bmp180, "bmp180_test", configMINIMAL_STACK_SIZE * 15, NULL, 5, NULL, APP_CPU_NUM);
}
