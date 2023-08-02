#ifndef __CONFIG_H__
#define __CONFIG_H__
#include <avr/io.h>
#include <util\delay.h>
#include <stdint.h>

extern uint8_t c_sreg;
#define SREG_INTER 7
/*������� �������������� ��������� �� PB5*/
void led_init(void);
void led_togle(void);

/*������ ������� ���� �������� ��� �������������� ����������� cli(), sei()
��� ��� ������ ������� �� ��������� ������� �������� �������� SREG,
��� ��������� � ���������� ����������, ���� ����� ��� ���� ���������*/
/*������� ��������� ������� �������� �������� SREG � ���������
���������� ����������*/
void global_interrupts_init(void);
/*������� ��������� ������� �������� SREG �
��������� ���������� ����������*/
void interrupts_cli(void);
/*������� ���������� ������� �������� (����� ����������) SREG*/
void interrupts_sei(void);
#endif //__CONFIG_H__