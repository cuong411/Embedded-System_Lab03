#include "driver/gpio.h"
#include "esp_spi_flash.h"
#include "esp_system.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "sdkconfig.h"
#include <stdio.h>
#include "FreeRTOSConfig.h"

int i = 0;
TaskHandle_t xHandle;

void task1(void *parameter)
{
    while (true)
    {
        printf("task1 is running\n");
        i++;
        if (i == 200)
            vTaskSuspend(xHandle);
    }
    vTaskDelete(NULL);
}

void task2(void *parameter)
{
    while (true)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
        printf("task2 starts\n");
        printf("task2 ends\n");
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void task3(void *parameter)
{
    while (true)
    {
        vTaskDelay(50 / portTICK_PERIOD_MS);
        printf("task3 starts\n");
        printf("task3 ends\n");
        vTaskDelay(200 / portTICK_PERIOD_MS);
    }
    vTaskDelete(NULL);
}

void app_main()
{
    xTaskCreate(task1, "task1", 2048, NULL, 1, &xHandle);
    xTaskCreate(task2, "task2", 2048, NULL, 2, NULL);
    xTaskCreate(task3, "task3", 2048, NULL, 3, NULL);
}