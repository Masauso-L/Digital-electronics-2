/*
 * gpio.c :m
 *
 * Created: 10/7/2020 11:13:50
 * Author : masau
 */ 

/***********************************************************************
 * 
 * Alternately toggle two LEDs when a push button is pressed. Use 
 * functions from GPIO library.
 * ATmega328P (Arduino Uno), 16 MHz, AVR 8-bit Toolchain 3.6.2
 *
 * Copyright (c) 2019-2020 Tomas Fryza
 * Dept. of Radio Electronics, Brno University of Technology, Czechia
 * This work is licensed under the terms of the MIT license.
 * 
 **********************************************************************/

/* Defines -----------------------------------------------------------*/
//Defines
#define LED_GREEN_5   PB5   // AVR pin where green LED is connected
#define LED_RED_4     PB4   // AVR pin where RED LED is connected
#define LED_GREEN_3   PB3   // AVR pin where green LED is connected
#define LED_RED_2     PB2   // AVR pin where RED LED is connected
#define LED_GREEN_1   PB1   // AVR pin where green LED is connected
#define BTN           PD0   // AVR pin where PUSH BUTTONis connected
#define BLINK_DELAY   50    // TIME DELAY IN MILISECONDS
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif


/* Includes ----------------------------------------------------------*/
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions
#include "gpio.h"           // GPIO library for AVR-GCC

/* Function definitions ----------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle FIVE LEDs 
 * when a push button is pressed.
 */


//This is the modified version of knight raider
int main(void)
{
    /* GREEN LED */
    GPIO_config_output(&DDRB, LED_GREEN_1);  //output configuration
    GPIO_write_low(&PORTB, LED_GREEN_1);     //port assignment
	
	GPIO_config_output(&DDRB, LED_GREEN_3);
	GPIO_write_low(&PORTB, LED_GREEN_3);
	
	GPIO_config_output(&DDRB, LED_GREEN_5);
	GPIO_write_low(&PORTB, LED_GREEN_5);



    /* RED LED */
	GPIO_config_output(&DDRB, LED_RED_2);
	GPIO_write_low(&PORTB, LED_RED_2);
	
	GPIO_config_output(&DDRB, LED_RED_4);
	GPIO_write_low(&PORTB, LED_RED_4);


    /* push button */
    GPIO_config_input_pullup(&DDRD, BTN);

   
 // Infinite loop
 while (1)
 {
	 // Pause several milliseconds
	 _delay_ms(BLINK_DELAY);
	 
	 if (!GPIO_read(&PIND, BTN))
	 {
		 
		 //forward toggle
		 GPIO_toggle(&PORTB, LED_GREEN_1);
		 _delay_ms(BLINK_DELAY);
		 GPIO_toggle(&PORTB, LED_GREEN_1);
		 GPIO_toggle(&PORTB, LED_RED_2);
		 _delay_ms(BLINK_DELAY);
		 GPIO_toggle(&PORTB, LED_RED_2);
		 GPIO_toggle(&PORTB, LED_GREEN_3);
		 _delay_ms(BLINK_DELAY);
		 GPIO_toggle(&PORTB, LED_GREEN_3);
		 GPIO_toggle(&PORTB, LED_RED_4);
		 _delay_ms(BLINK_DELAY);
		 GPIO_toggle(&PORTB, LED_RED_4);
		 GPIO_toggle(&PORTB, LED_GREEN_5);
		 _delay_ms(BLINK_DELAY);
		 
		 //backward toggle
		 GPIO_toggle(&PORTB, LED_GREEN_5);
		 GPIO_toggle(&PORTB, LED_RED_4);
		 _delay_ms(BLINK_DELAY);
		 GPIO_toggle(&PORTB, LED_RED_4);
		 GPIO_toggle(&PORTB, LED_GREEN_3);
		 _delay_ms(BLINK_DELAY);
		 GPIO_toggle(&PORTB, LED_GREEN_3);
		 GPIO_toggle(&PORTB, LED_RED_2);
		 _delay_ms(BLINK_DELAY);
		 GPIO_toggle(&PORTB, LED_RED_2);
		 GPIO_toggle(&PORTB, LED_GREEN_1);
		 
		 
	 }
 }
 // Will never reach this
 return 0;
 }



