#include "config.h"
#include <avr\interrupt.h>
uint8_t c_sreg;

/*
 CKSEL0ЦCKSEL3 Ц выбор источника и частоты тактировани€ (уточн€й в даташите на свой ћ , кака€ конфигураци€ за что отвечает)
 SUT0ЦSUT1 Ц задержка старта ћ  после перезагрузки
 CKOUT Ц дублирование тактировани€ на один из пинов (см. в даташите на какой)
 CKDIV8 Ц делит тактовую частоту на 8
 BOOTRST Ц если включен, ћ  запускаетс€ с загрузчика
 BOOTSZ0ЦBOOTSZ1 Ц задаЄт размер сектора загрузчика
 EESAVE Ц защита EEPROM от стирани€ во врем€ выполнени€ полной очистки чипа
 WDTON Ц если включить, то Watchdog будет принудительно включен без возможности отключени€
 SPIEN Ц опасный бит, при его отключении пропадает возможность прошивки через ISP, и возможность выключить этот бит в том числе*
 DWEN Ц вкл/выкл отладочный интерфейс DebugWire. Ќа других модел€х бывает и JTAG, и его бит Ц JTAGEN
 RSTDISBL Ц опасный бит, при его включении можно использовать ногу RST как обычный цифровой пин, но пропадает возможность прошивки через ISP и выключить этот бит как следствие*
 BODLEVEL0ЦBODLEVEL3 Ц настройка контрол€ напр€жени€ (ћ  сброситс€ при падении ниже установленного напр€жени€)
FUSES = {.high = 0xff & FUSE_BOOTRST & FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_EESAVE & FUSE_WDTON & FUSE_SPIEN & FUSE_DWEN & FUSE_RSTDISBL,

         .low = 0xff & FUSE_CKSEL0 & FUSE_CKSEL1 & FUSE_CKSEL2 & FUSE_CKSEL3 & FUSE_SUT0 & FUSE_SUT1 & FUSE_CKOUT & FUSE_CKDIV8,

         .extended = 0xff & FUSE_BODLEVEL0 & FUSE_BODLEVEL1 & FUSE_BODLEVEL2};


        !!!Ѕ»“џ »Ќ¬≈–—Ќџ≈!!!!
!!!¬ ќѕ–≈ƒ≈Ћ≈Ќ»я’ ≈—“№ «Ќј„≈Ќ»я ѕќ ”ћќЋ„јЌ»ё!!!*/
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