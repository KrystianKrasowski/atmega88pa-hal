#include <stdint.h>

#ifndef _AVR_IO_MOCK
#define _AVR_IO_MOCK

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

#endif