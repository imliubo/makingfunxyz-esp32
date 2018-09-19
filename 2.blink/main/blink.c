/*
 * 包含相应的头文件
 * stdio.h -> C语言标准库 
 * FreeRTOS.h -> 实时操作系统相关 -> esp-idf/components/freertos/include/freertos/FreeRTOS.h
 * task.h -> 任务处理相关   -> esp-idf/components/freertos/include/freertos/tsak.h
 * gpio.h -> GPIO处理相关  -> esp-idf/components/esp32/include/rom/gpio.h
 * sdkconfig.h -> SDK相关  -> blink/build/include/sdkconfig.h
*/
#include <stdio.h>
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include "driver/gpio.h"
#include "sdkconfig.h"

/* Can run 'make menuconfig' to choose the GPIO to blink,
   or you can edit the following line and set a number here.
*/
/*
 * CONFIG_BLINK_GPIO -> 可以通过make menuconfig 指定管脚
 * 也可以将 >CONFIG_BLINK_GPIO<改成某个指定的管脚
*/
#define BLINK_GPIO CONFIG_BLINK_GPIO

void blink_task(void *pvParameter)                      //创建的任务
{
    /* Configure the IOMUX register for pad BLINK_GPIO (some pads are
       muxed to GPIO on reset already, but some default to other
       functions and need to be switched to GPIO. Consult the
       Technical Reference for a list of pads and their default
       functions.)
    */
    gpio_pad_select_gpio(BLINK_GPIO);                  //这句的作用是有些管脚会复用，这里选择管脚作为GPIO用
    /* Set the GPIO as a push/pull output */
    gpio_set_direction(BLINK_GPIO, GPIO_MODE_OUTPUT);  //设置管脚为输出模式
    while(1) {                                         //while循环 1 -> 条件在任何时候都成立，所以程序会一直在这个while循环里执行
        /* Blink off (output low) */
        gpio_set_level(BLINK_GPIO, 0);                 //让管脚输出低电平，0 -> 低电平
        vTaskDelay(1000 / portTICK_PERIOD_MS);         //延时任务 1s
        /* Blink on (output high) */
        gpio_set_level(BLINK_GPIO, 1);                 //让管脚输出低电平，1 -> 高电平          
        vTaskDelay(1000 / portTICK_PERIOD_MS);         //延时任务 1s
    }
}

void app_main()
{
	/* 函数原型 task.h -> 430L
	xTaskCreate(
			TaskFunction_t pvTaskCode,
			const char * const pcName,
			const uint32_t usStackDepth,
			void * const pvParameters,
			UBaseType_t uxPriority,
			TaskHandle_t * const pvCreatedTask)
	*/
    xTaskCreate(&blink_task,              //指向创建的任务的一个指针
    			"blink_task", 			  //创建的任务名称(函数名)
    			configMINIMAL_STACK_SIZE, //设置堆的大小
    			NULL,                     //任务参数的指针，这里为空
    			5,                        //任务的优先级
    			NULL);                    //创建任务的句柄
}
