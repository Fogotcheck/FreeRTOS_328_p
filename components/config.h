#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <avr/io.h>
#include <util\delay.h>
#include <stdint.h>

extern uint8_t c_sreg;
#define SREG_INTER 7
/*Функция инициализирует светодиод на PB5*/
void led_init(void);
void led_togle(void);

/*данные функции были написаны как альтернативные стандартным cli(), sei()
так как данные функции не сохраняют текущее значение регистра SREG,
что приводило к разрещению прерываний, кода ранее они были запрещены*/
/*Функция сохраняет текущее значение регистра SREG и разрешает
глобальные прерывания*/
void global_interrupts_init(void);
/*Функция сохраняет текущее значение SREG и
отключает глобальные прерывания*/
void interrupts_cli(void);
/*Функция возвращает текущее значение (ранее сохранённое) SREG*/
void interrupts_sei(void);
#endif //__CONFIG_H__