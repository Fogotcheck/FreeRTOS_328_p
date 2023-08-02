#ifndef __MAIN_H__
#define __MAIN_H__
#include <avr/io.h>
#include <util\delay.h>
#include <stdint.h>
#include <avr\interrupt.h>
#include "components\config.h"
#include "components\usart.h"
#include "FreeRTOS\include\FreeRTOS.h"
#include "FreeRTOS\include\task.h"


#define mainLED_TASK_PRIORITY (tskIDLE_PRIORITY + 1)
#define mainCOM_TEST_PRIORITY (tskIDLE_PRIORITY + 2)
#define mainQUEUE_POLL_PRIORITY (tskIDLE_PRIORITY + 2)
#define mainCHECK_TASK_PRIORITY (tskIDLE_PRIORITY + 3)


#endif //__MAIN_H__