#define F_CPU 16000000UL
#include "main.h"

static void taskFoo(void *arg)
{
    (void)arg;
    while (1)
    {
        printf("HI FOO\n");
        vTaskDelay(500);
    }
}
static void taskFunc(void *arg)
{
    (void)arg;
    while (1)
    {
        led_togle();
        printf("HI FUNC\n");
        vTaskDelay(1000);
    }
}

void vApplicationIdleHook(void)
{
}
int main(void)
{
    led_init();
    usart_init(USART_UBRR);
    printf("Init end\n");
    xTaskCreate(taskFoo, "taskFoo", configMINIMAL_STACK_SIZE, NULL, (mainCHECK_TASK_PRIORITY + 1), NULL);
    xTaskCreate(taskFunc, "taskFunc", configMINIMAL_STACK_SIZE, NULL, (mainCHECK_TASK_PRIORITY), NULL);
    vTaskStartScheduler();
    /*no START*/
    while (1)
    {
        /* code */
    }
}