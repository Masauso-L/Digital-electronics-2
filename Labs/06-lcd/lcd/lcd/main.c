/*
 * lcd.c
 *
 * Created: 11/4/2020 11:08:05
 * Author : masau
 */ 

/***********************************************************************
 * 
 * Stopwatch with LCD display output.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2017-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Includes ----------------------------------------------------------*/
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC
#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function

/* Variables ---------------------------------------------------------*/
// Custom character definition using https://omerk.github.io/lcdchargen/
uint8_t customChar[] = {
	// addr 0: .....
	0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000, 0b00000,
	// addr 1: |....
	0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000, 0b10000,
	// addr 2: ||...
	0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000, 0b11000,
	// addr 3: |||..
	0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100, 0b11100,
	// addr 4: ||||.
	0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110, 0b11110,
	// addr 5: |||||
	0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111, 0b11111,
};


/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Update stopwatch
 * value on LCD display when 8-bit Timer/Counter2 overflows.
 */
int main(void)
{
    // Initialize LCD display
    lcd_init(LCD_DISP_ON);

    // Set pointer to beginning of CGRAM memory
    lcd_command(1 << LCD_CGRAM);
    for (uint8_t i = 0; i < 48; i++)
    {
	    // Store all new chars to memory line by line
	    lcd_data(customChar[i]);
    }
    // Set DDRAM address
    lcd_command(1 << LCD_DDRAM);
    
    // Put string(s) at LCD display
    lcd_gotoxy(1, 0);
    lcd_puts("00:00.0");
	lcd_gotoxy(11, 1);
	lcd_puts("DE2");

    // Configure 8-bit Timer/Counter2 for Stopwatch
    // Set prescaler and enable overflow interrupt every 16 ms
	TIM2_overflow_16ms();
	TIM2_overflow_interrupt_enable();
	
	// Configure 8-bit Timer/Counter0 for status bar
	// Set prescaler and enable overflow interrupt every 16 ms
	TIM0_overflow_16ms();
	TIM0_overflow_interrupt_enable();

    // Enables interrupts by setting the global interrupt mask
    sei();

    // Infinite loop
    while (1)
    {
        /* Empty loop. All subsequent operations are performed exclusively 
         * inside interrupt service routines ISRs */
    }

    // Will never reach this
    return 0;
}

/* Interrupt service routines ----------------------------------------*/
/**
 * ISR starts when Timer/Counter2 overflows. Update the stopwatch on
 * LCD display every sixth overflow, ie approximately every 100 ms
 * (6 x 16 ms = 100 ms).
 */
ISR(TIMER2_OVF_vect)
{
    static uint8_t number_of_overflows = 0;
    static uint8_t tens = 0;        // Tenths of a second
    static uint8_t secs = 0;        // Seconds
	static uint8_t mins = 0;        // Minutes
    char lcd_string[] = "  ";       // String for converting numbers by itoa()
	uint16_t secs_sq = secs*secs;    // Square of seconds

    number_of_overflows++;
    if (number_of_overflows >= 6)
    {
        // Do this every 6 x 16 ms = 100 ms
        number_of_overflows = 0;

		tens++;
		if (tens > 9)
		{
			tens = 0;
			secs++;
			if (secs > 59)
			{
				secs = 0;
				mins++;
				if (mins > 59)
				{
					mins = 0;
				}
			}
		}
		
		itoa(tens, lcd_string, 10);
		lcd_gotoxy(7, 0);
		lcd_putc(lcd_string[0]);
		
		// Displaying Seconds
		itoa(secs, lcd_string, 10);
		lcd_gotoxy(4, 0);
		if (secs < 10)
		{
			lcd_putc('0');
			lcd_putc(lcd_string[0]);
		}
		else
		{
			lcd_puts(lcd_string);
		}
		
		//Displaying minutes
		itoa(mins, lcd_string, 10);
		lcd_gotoxy(1, 0);
		if (mins < 10)
		{
			lcd_putc('0');
			lcd_putc(lcd_string[0]);
		}
		else
		{
			lcd_puts(lcd_string);
		}
		
		//Displaying square of seconds
		itoa(secs_sq, lcd_string, 10);
		lcd_gotoxy(11, 0);
		lcd_puts(lcd_string);
		if (secs == 0)
		{
			// Clears the position and reset square of secs back to 0
			secs_sq = 0;
			lcd_puts("       ");  
		}
		

    }
	
}

/*--------------------------------------------------------------------*/
/**
 * ISR starts when Timer/Counter0 overflows. Update the progress bar on
 * LCD display every 16 ms.
 */
ISR(TIMER0_OVF_vect)
{   
	static uint8_t number_of_overflows = 0;
    static uint8_t symbol = 0;
    static uint8_t position = 0;
    
	number_of_overflows++;
	if (number_of_overflows >=12)
	{
		number_of_overflows = 0;
		symbol++;
		if(symbol > 5)
		{
			symbol = 0;
			position++;
			if ((position > 7))
			{
				position = 0;
				lcd_gotoxy(1, 1);
				lcd_puts("         ");
			
			}
		}
	}
	
	lcd_gotoxy(1 + position, 1);
	lcd_putc(symbol);
}
