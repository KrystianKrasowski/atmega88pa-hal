#include <stdint.h>

#ifndef _AVR_IO_MOCK
#define _AVR_IO_MOCK

#define TIMER1_CAPT_vect __TIMER1_CAPT_vect
#define SPI_STC_vect __SPI_STC_vect

extern uint8_t DDRB;
extern uint8_t DDRC;
extern uint8_t DDRD;

extern uint8_t PORTB;
extern uint8_t PORTC;	
extern uint8_t PORTD;

extern uint8_t PINB;
extern uint8_t PINC;
extern uint8_t PIND;

extern uint8_t TCCR0A;
extern uint8_t TCCR0B;
extern uint8_t TCNT0;
extern uint8_t OCR0A;
extern uint8_t OCR0B;
extern uint8_t TIMSK0;
extern uint8_t TIFR0;
extern uint8_t WGM00;
extern uint8_t WGM01;
extern uint8_t WGM02;
extern uint8_t COM0A1;
extern uint8_t COM0A0;
extern uint8_t COM0B1;
extern uint8_t COM0B0;
extern uint8_t CS02;
extern uint8_t CS01;
extern uint8_t CS00;

extern uint8_t TCCR1A;
extern uint8_t WGM10;
extern uint8_t WGM11;
extern uint8_t COM1B0;
extern uint8_t COM1B1;
extern uint8_t COM1A0;
extern uint8_t COM1A1;
extern uint8_t TCCR1B;
extern uint8_t WGM12;
extern uint8_t TCCR1C;
extern uint16_t TCNT1;
extern uint8_t TIMSK1;
extern uint8_t CS12;
extern uint8_t CS11;
extern uint8_t CS10;
extern uint16_t ICR1;
extern uint8_t TOIE1;
extern uint8_t OCIE1A;
extern uint8_t OCIE1B;
extern uint8_t ICIE1;
extern uint16_t OCR1A;

extern uint8_t SPCR;
extern uint8_t SPIE;
extern uint8_t SPE;
extern uint8_t DORD;
extern uint8_t MSTR;
extern uint8_t CPOL;
extern uint8_t CPHA;
extern uint8_t SPR1;
extern uint8_t SPR0;
extern uint8_t SPSR;
extern uint8_t SPIF;
extern uint8_t WCOL;
extern uint8_t SPI2X;
extern uint8_t SPDR;
extern uint8_t SS_DDR;
extern uint8_t SS_PORT;
extern uint8_t SS_BIT;
extern uint8_t MOSI_DDR;
extern uint8_t MOSI_BIT;
extern uint8_t SCK_DDR;
extern uint8_t SCK_BIT;

void sei(void);

#endif
