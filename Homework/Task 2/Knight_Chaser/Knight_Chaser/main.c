/*
 * Knight_Chaser.c
 *
 * Created: 10/6/2020 14:46:04
 * Author : masau
 */ 

/*Two different colors of the LED Green and Red are used to observe how the 
The toggle is alternating between the LEDS
*/

//Defines
#define LED_GREEN_5   PB5     
#define LED_RED_4     PB4  
#define LED_GREEN_3   PB3 
#define LED_RED_2     PB2  
#define LED_GREEN_1   PB1  
#define BTN           PD0 
#define BLINK_DELAY   50    //
#ifndef F_CPU
#define F_CPU 16000000      // CPU frequency in Hz required for delay
#endif

//Library inclusion
#include <util/delay.h>     // Functions for busy-wait delay loops
#include <avr/io.h>         // AVR device-specific IO definitions

/* Functions ---------------------------------------------------------*/
/**
 * Main function where the program execution begins. Toggle FIVE LEDs 
 * when a push button is pressed.
 */
int main(void)
{
    /* LEDS matching with ports and DDR*/
	
    	
    DDRB = DDRB | (1<<LED_GREEN_1);  // Set pins as output in Data Direction Register
    PORTB = PORTB & ~(1<<LED_GREEN_1); // ...and turn LED off in Data Register
		
    DDRB = DDRB | (1<<LED_RED_2); // Set pin as output in Data Direction Register
    PORTB = PORTB & ~(1<<LED_RED_2);  // ...and turn LED off in Data Register	
    	
    DDRB = DDRB | (1<<LED_GREEN_3); // Set pin as output in Data Direction Register
    PORTB = PORTB & ~(1<<LED_GREEN_3);	
    	
	DDRB = DDRB | (1<<LED_RED_4);     //Set pin as output in Data Direction Register
    PORTB = PORTB & ~(1<<LED_RED_4);  // ...and turn LED off in Data Register
	
    DDRB = DDRB | (1<<LED_GREEN_5);    //Set pin as output in Data Direction Register
   	PORTB = PORTB & ~(1<<LED_GREEN_5);  // ...and turn LED off in Data Register
	   	
	DDRD = DDRD & ~(1<<BTN);  //Set pin as input in Data Direction Register
	PORTD = PORTD | (1<<BTN);  //Set pull up resistor on
  
  
    // Infinite loop
    while (1)
    {    
		// Pause several milliseconds
		_delay_ms(BLINK_DELAY);
		
			if(bit_is_clear(PIND,BTN))
			{
			
			    //forward toggle
				PORTB = PORTB ^ (1<<LED_GREEN_1);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_1);
				PORTB = PORTB ^ (1<<LED_RED_2);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_RED_2);
				PORTB = PORTB ^ (1<<LED_GREEN_3);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_3);
				PORTB = PORTB ^ (1<<LED_RED_4);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_RED_4);
				PORTB = PORTB ^ (1<<LED_GREEN_5);
				_delay_ms(BLINK_DELAY);
				
				//backward toggle
				PORTB = PORTB ^ (1<<LED_GREEN_5);
				PORTB = PORTB ^ (1<<LED_RED_4);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_RED_4);
				PORTB = PORTB ^ (1<<LED_GREEN_3);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_GREEN_3);
				PORTB = PORTB ^ (1<<LED_RED_2);
				_delay_ms(BLINK_DELAY);
				PORTB = PORTB ^ (1<<LED_RED_2);
				PORTB = PORTB ^ (1<<LED_GREEN_1);
				
				
			}
    }
    // Will never reach this
    return 0;
}
