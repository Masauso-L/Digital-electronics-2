/*
 * Blink.c
 *
 * Created: 9/28/2020 18:23:26
 * Author : masau
 */ 
/***********************************************************************
 * 
 * Blink a LED and use the function from the delay library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2018-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czech
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
#define LED_GREEN   PB5      // AVR pin where green LED is connected
#define SHORT_DELAY 1000     // Delay in milliseconds for individual bits
#define LONG_DELAY  2000     // Delay between individual characters "DE2"
#ifndef F_CPU
#define F_CPU 16000000       // CPU frequency in Hz required for delay function
#endif

/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Variables ---------------------------------------------------------*/

/* Function prototypes -----------------------------------------------*/

/* Functions ---------------------------------------------------------*/
/**
 * Toggle one LED and use the function from the delay library.
 */
int main(void)
{
    // Set pin as output in Data Direction Register
    // DDRB = DDRB or 0010 0000
    DDRB = DDRB | (1<<LED_GREEN);

    // Set pin LOW in Data Register (LED off)
    // PORTB = PORTB and 1101 1111
    
    // DE2 in Morse Code : 1001(D),10(E),111100(2)
    // Infinite loop
    while (1)
    {
        //Sending "D" : 1001
		PORTB |=(1<<LED_GREEN);                //The LED is set on to 1 (High) i.e first 1 in D
                _delay_ms(SHORT_DELAY);                //There is delayed for few ms i.e 1000ms pause before the next bit is sent
		PORTB = PORTB & ~(1<<LED_GREEN);       //The LED is reset to 0 (Low) i.e first 0 in D
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB & ~(1<<LED_GREEN);       // The LED is kept Low to send the Second 0 in D 
		_delay_ms(SHORT_DELAY);
		PORTB |=(1<<LED_GREEN);                // The LED is set on to send the last 1 in D 
		_delay_ms(SHORT_DELAY);
		
		PORTB = PORTB & ~(1<<LED_GREEN);      //Reset LED to low and wait for 2000ms before next character  i.e "E"       
		_delay_ms(LONG_DELAY);
		
		// Sending "E" : 10
		PORTB |=(1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB & ~(1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		
		_delay_ms(LONG_DELAY);                //The output is delayed further for 2000ms to wait for the next character i.e "2"
		
		//Sending "2" : 111100
		PORTB |=(1<<LED_GREEN);               //The LED is set on and stay on for 1000ms..this is repeated 4x to send 1111
		_delay_ms(SHORT_DELAY);
		PORTB |=(1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB |=(1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB |=(1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB & ~(1<<LED_GREEN);      //The LED is reset to Low and delayed for a few ms. this repeated 2x to send 00
		_delay_ms(SHORT_DELAY);
		PORTB = PORTB & ~(1<<LED_GREEN);
		_delay_ms(SHORT_DELAY);

        // Invert LED in Data Register
        // PORTB = PORTB xor 0010 0000
        PORTB = PORTB ^ (1<<LED_GREEN);
    }

    // Will never reach this
    return 0;
}

/* Interrupt routines ------------------------------------------------*/
