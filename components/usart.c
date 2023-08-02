#include "usart.h"

static FILE USART_stream = FDEV_SETUP_STREAM(usart_printf, NULL, _FDEV_SETUP_WRITE);
void usart_init(uint32_t ubrr)
{
    // Set baud rate
	UBRR0H = (uint8_t)(ubrr >> 8);
	UBRR0L = (uint8_t)ubrr;
	
	UCSR0A = (1 << U2X0);

	// Enable receiver and transmitter
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);
	// Set frame format: 8 data, 1 stop bit
	UCSR0C = (3 << UCSZ00);
	
	// Enable rx interrupt
	UCSR0B |= (1 << RXCIE0);\
	stdout = &USART_stream;    
}

int usart_printf(char byte, FILE *stream)
{
	if (byte == '\n')
	usart_printf('\r', stream);
	// Wait for empty transmit buffer
	while (!(UCSR0A & (1 << UDRE0)));
	// Put data into buffer, sends the data
	UDR0 = byte;
	return 0;
}

void usart_transmit_byte(uint8_t data)
{
	while (!(UCSR0A & (1 << UDRE0)));
	// Put data into buffer, sends the data
	UDR0 = data;
	return;
}

void usart_transmit_data(uint8_t *data, uint16_t data_len)
{
	while(data_len)
	{
		usart_transmit_byte(*data++);
		data_len--;
	}
	return;
}