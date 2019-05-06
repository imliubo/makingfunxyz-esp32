/* Hello World Example

   This example code is in the Public Domain (or CC0 licensed, at your option.)

   Unless required by applicable law or agreed to in writing, this
   software is distributed on an "AS IS" BASIS, WITHOUT WARRANTIES OR
   CONDITIONS OF ANY KIND, either express or implied.
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "esp_system.h"
#include "esp_spi_flash.h"


void app_main()
{
    while(1){
        printf("www.makingfun.xyz\r\n");
        vTaskDelay(1000 / portTICK_PERIOD_MS);
        /*
            这是一个延时任务
            参数是需要延时的时间
            portTICK_PERIOD_MS 一个滴答周期的基准时间
            1000 / portTICK_PERIOD_MS = 1000ms = 1s
        */
    }
}
