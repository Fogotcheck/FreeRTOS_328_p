#include "config.h"
#include <avr\interrupt.h>
uint8_t c_sreg;

/*
 CKSEL0�CKSEL3 � ����� ��������� � ������� ������������ (������� � �������� �� ���� ��, ����� ������������ �� ��� ��������)
 SUT0�SUT1 � �������� ������ �� ����� ������������
 CKOUT � ������������ ������������ �� ���� �� ����� (��. � �������� �� �����)
 CKDIV8 � ����� �������� ������� �� 8
 BOOTRST � ���� �������, �� ����������� � ����������
 BOOTSZ0�BOOTSZ1 � ����� ������ ������� ����������
 EESAVE � ������ EEPROM �� �������� �� ����� ���������� ������ ������� ����
 WDTON � ���� ��������, �� Watchdog ����� ������������� ������� ��� ����������� ����������
 SPIEN � ������� ���, ��� ��� ���������� ��������� ����������� �������� ����� ISP, � ����������� ��������� ���� ��� � ��� �����*
 DWEN � ���/���� ���������� ��������� DebugWire. �� ������ ������� ������ � JTAG, � ��� ��� � JTAGEN
 RSTDISBL � ������� ���, ��� ��� ��������� ����� ������������ ���� RST ��� ������� �������� ���, �� ��������� ����������� �������� ����� ISP � ��������� ���� ��� ��� ���������*
 BODLEVEL0�BODLEVEL3 � ��������� �������� ���������� (�� ��������� ��� ������� ���� �������������� ����������)
FUSES = {.high = 0xff & FUSE_BOOTRST & FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_WDTON & FUSE_SPIEN & FUSE_DWEN & FUSE_RSTDISBL,

         .low = 0xff & FUSE_CKSEL0 & FUSE_CKSEL1 & FUSE_CKSEL2 & FUSE_CKSEL3 & FUSE_SUT0 & FUSE_SUT1 & FUSE_CKOUT & FUSE_CKDIV8,

         .extended = 0xff & FUSE_BODLEVEL0 & FUSE_BODLEVEL1 & FUSE_BODLEVEL2};


        !!!���� ���������!!!!
!!!� ������������ ���� �������� �� ���������!!!*/
#warning "!!!Check your fuses!!!!"
FUSES = {
    .high = 0xff & FUSE_EESAVE & FUSE_SPIEN,
    .low = 0xff,
    .extended = 0xff & FUSE_BODLEVEL0 & FUSE_BODLEVEL1};

void led_init(void)
{
    DDRB |= 1 << PB5;
    PORTB |= 1 << PB5;
}
void led_togle(void)
{
    PORTB ^= 1 << PB5;
}
void global_interrupts_init(void)
{
    sei();
    c_sreg = SREG;
}
void interrupts_cli(void)
{
    c_sreg = SREG;
    cli();
}
void interrupts_sei(void)
{
    SREG = c_sreg;
}