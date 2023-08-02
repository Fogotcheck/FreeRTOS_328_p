#ifndef __USART_H__
#define __USART_H__
#include <avr\io.h>
#include <stdio.h>

#define USART_BAUD 115200
#define USART_UBRR ((F_CPU / 8 / USART_BAUD) - 1)

/*Функция модифицирована для работы стандартной библиотеки stdio.h*/
void usart_init(uint32_t ubrr);
/*функция обеспечивает работу стандартной библиотеки stdio.h через usart*/
int usart_printf(char byte, FILE *stream);
void usart_transmit_byte(uint8_t data);
void usart_transmit_data(uint8_t *data, uint16_t data_len);
#endif //__USART_H__