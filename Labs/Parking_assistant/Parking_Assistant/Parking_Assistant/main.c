/*
 * Parking assistant.c
 *
 * Created: 11/25/2020 20:43:55
 * Author : masau
 */ 

//LIBRARIES NECCESSARY FOR THE APPLICATION
#include <avr/io.h>         // AVR device-specific IO definitions
#include <avr/interrupt.h>  // Interrupts standard C library for AVR-GCC

#include "timer.h"          // Timer library for AVR-GCC
#include "lcd.h"            // Peter Fleury's LCD library
#include <stdlib.h>         // C library. Needed for conversion function
#include "uart.h"           // Peter Fleury's UART library
#include "gpio.h"


#ifndef F_CPU
#define F_CPU 16000000		// CPU frequency
#endif
#include <util/delay.h>     // Functions for busy-wait delay loops

//Pin definition and variables
#define trigPin1     PD0       // Sensor Trip pin connected to arduino uno pin RX<-0
#define echoPin1     PD2       // Sensor Echo pin connected to arduino uno pin 2
#define trigPin2     PD1
#define echoPin2     PD3
#define LED_GREEN   PB4       // Red LED connected to arduino uno pin 12
#define LED_YELLOW  PB3       // Yellow LED connected to arduino uno pin 11
#define LED_RED     PB2       // Green LED connected to arduino uno pin 10
#define buzzer      PC0       // Buzzer connected to arduino uno Analogue pin A0
long Distance, Distance_Front, Distance_Back;       // A variable to store the distance 
//int16_t counter = 0;          // Counter value to check if the object has stopped moving 
static volatile int pulse = 0;
static volatile int i = 0;


int main(void)
{ 
	
	//Initialize LCD display.
	lcd_init(LCD_DISP_ON);
	lcd_gotoxy(0,0);						
	lcd_puts("Front:");
	lcd_gotoxy(0,1);
	lcd_puts("Back:");
	lcd_gotoxy(13,0);					
	lcd_puts("cm");
	lcd_gotoxy(13,1);
	lcd_puts("cm");
	
	_delay_ms(50);
	GPIO_config_output(&DDRB, LED_GREEN);
	GPIO_write_low(&PORTB, LED_GREEN);
	
	GPIO_config_output(&DDRB, LED_YELLOW);
	GPIO_write_low(&PORTB, LED_YELLOW);
	
	GPIO_config_output(&DDRB, LED_RED);
	GPIO_write_low(&PORTB, LED_RED);
	
	GPIO_config_output(&DDRD, trigPin1);
	GPIO_write_low(&PORTD, trigPin1);
	
	GPIO_config_output(&DDRD, trigPin2);
	GPIO_write_low(&PORTD, trigPin2);
	
	GPIO_config_output(&DDRC, buzzer);
	GPIO_write_low(&PORTC, buzzer);
	
	GPIO_config_input_pullup(&DDRD, echoPin1);
	GPIO_config_input_pullup(&DDRD, echoPin2);
	
	
	EIMSK |= ((1<<INT0) | (1<<INT1));
	EICRA |= ((1<<ISC00) | (1<<ISC01) | (1<<ISC10) | (1<<ISC11));
	
	
    // Configure 16-bit Timer/Counter1 to start ADC conversion
    // Enable interrupt and set the overflow prescaler to 262 ms
	TIM1_overflow_262ms();
	TIM1_overflow_interrupt_enable();
	
	TIM2_overflow_2ms();
	TIM2_overflow_interrupt_enable();
	
    // Initialize UART to asynchronous, 8N1, 9600
	uart_init(UART_BAUD_SELECT(9600, F_CPU));
	
    // Enables interrupts by setting the global interrupt mask
    sei();
	
    while (1) 
    { 
		
    }
	return 0;
}
ISR(INT0_vect)
{
	char lcd_string[10];
	
	while(GPIO_read(&PIND, echoPin1))
	{
		pulse++;
	}
	
	Distance = pulse*0.017;
	
	if (i == 1)
	{
		Distance_Front = Distance;
		if (Distance > 400)
		{
			// send data to LCD display and UART
		    uart_puts("Clear \n");					
		    lcd_gotoxy(7,0);
		    lcd_puts("      ");
		    lcd_gotoxy(7,0);
		    lcd_puts("Clear");
			
			GPIO_write_low(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_YELLOW);
			GPIO_write_low(&PORTB, LED_RED);
			
		}
		
		if ((Distance > 100) && (Distance <= 400))
		{
			GPIO_write_high(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_YELLOW);
			GPIO_write_low(&PORTB, LED_RED);
			
			// send data to LCD display and UART
			itoa(Distance,lcd_string,10);				
	    	lcd_gotoxy(7,0);
		    lcd_puts("      ");
		    lcd_gotoxy(7,0);
		    lcd_puts(lcd_string);
		    uart_puts("Front: ");
		    uart_puts(lcd_string);
		    uart_puts(" cm");
			uart_puts(" Safe to go");
		    uart_puts("\n");
		}
		
		if ((Distance > 30) && (Distance <= 100))
		{
			GPIO_write_high(&PORTB, LED_YELLOW);
			GPIO_write_low(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_RED);
			
			// send data to LCD display and UART
			itoa(Distance,lcd_string,10);
			lcd_gotoxy(7,0);
			lcd_puts("      ");
			lcd_gotoxy(7,0);
			lcd_puts(lcd_string);
			uart_puts("Front: ");
			uart_puts(lcd_string);
			uart_puts(" cm");
			uart_puts(" Warning, getting close");
			uart_puts("\n");
		}
		
		
		if (Distance <= 30)
		{
			GPIO_write_high(&PORTB, LED_RED);
			GPIO_write_low(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_YELLOW);
			
			// send data to LCD display and UART
			itoa(Distance,lcd_string,10);
			lcd_gotoxy(7,0);
			lcd_puts("      ");
			lcd_gotoxy(7,0);
			lcd_puts(lcd_string);
			uart_puts("Front: ");
			uart_puts(lcd_string);
			uart_puts(" cm");
			uart_puts(" STOP!");
			uart_puts("\n");
		}
		
		
		if (Distance < 15)
		{
			GPIO_write_high(&PORTB, LED_RED);
			GPIO_write_low(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_YELLOW);
			
			// send data to LCD display and UART
			itoa(Distance,lcd_string,10);
			lcd_gotoxy(7,0);
			lcd_puts("      ");
			lcd_gotoxy(7,0);
			lcd_puts(lcd_string);
			uart_puts("Front: ");
			uart_puts(lcd_string);
			uart_puts(" cm");
			uart_puts(" STOP! parking rules broken");
			uart_puts("\n");
		}
	}

	
	
}

ISR(INT1_vect)
{
	char lcd_string[10];
	
	while(GPIO_read(&PIND, echoPin2))
	{
		pulse++;
	}
	
	Distance = pulse*0.017;
	
	if (i == 2)
	{
		Distance_Back = Distance;
		if (Distance > 400)
		{
			uart_puts("Clear \n");					// send data to LCD display and UART
			lcd_gotoxy(7,1);
			lcd_puts("      ");
			lcd_gotoxy(7,1);
			lcd_puts("Clear");
			
			GPIO_write_low(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_YELLOW);
			GPIO_write_low(&PORTB, LED_RED);
			GPIO_write_low(&PORTC, buzzer);
		}
		
		else if ((Distance > 100) && (Distance <= 400))
		{
			GPIO_write_high(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_YELLOW);
			GPIO_write_low(&PORTB, LED_RED);
			GPIO_write_low(&PORTC, buzzer);
			
			// send data to LCD display and UART
			itoa(Distance,lcd_string,10);
			lcd_gotoxy(7,1);
			lcd_puts("      ");
			lcd_gotoxy(7,1);
			lcd_puts(lcd_string);
			uart_puts("Front: ");
			uart_puts(lcd_string);
			uart_puts(" cm");
			uart_puts(" Safe to go");
			uart_puts("\n");
		}
		
		else if ((Distance > 30) && (Distance <= 100))
		{
			GPIO_write_high(&PORTB, LED_YELLOW);
			GPIO_write_low(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_RED);
			GPIO_write_low(&PORTC, buzzer);
			
			// send data to LCD display and UART
			itoa(Distance,lcd_string,10);
			lcd_gotoxy(7,1);
			lcd_puts("      ");
			lcd_gotoxy(7,1);
			lcd_puts(lcd_string);
			uart_puts("Front: ");
			uart_puts(lcd_string);
			uart_puts(" cm");
			uart_puts(" Warning, getting close");
			uart_puts("\n");
		}
		
		
		else if (Distance <= 30)
		{
			GPIO_write_high(&PORTB, LED_RED);
			GPIO_write_low(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_YELLOW);
			GPIO_write_low(&PORTC, buzzer);
			
			// send data to LCD display and UART
			itoa(Distance,lcd_string,10);
			lcd_gotoxy(7,1);
			lcd_puts("      ");
			lcd_gotoxy(7,1);
			lcd_puts(lcd_string);
			uart_puts("Front: ");
			uart_puts(lcd_string);
			uart_puts(" cm");
			uart_puts(" STOP!");
			uart_puts("\n");
		}
		
		
		else if (Distance < 15)
		{
			GPIO_write_high(&PORTB, LED_RED);
			GPIO_write_low(&PORTB, LED_GREEN);
			GPIO_write_low(&PORTB, LED_YELLOW);
			
			// send data to LCD display and UART
			itoa(Distance,lcd_string,10);
			lcd_gotoxy(7,1);
			lcd_puts("      ");
			lcd_gotoxy(7,1);
			lcd_puts(lcd_string);
			uart_puts("Front: ");
			uart_puts(lcd_string);
			uart_puts(" cm");
			uart_puts(" STOP! parking rules broken");
			uart_puts("\n");
		}
	}

}


ISR(TIMER1_OVF_vect)
{
	i++;
	if (i == 1)
	{
		GPIO_write_high(&PORTD, trigPin1);
		_delay_us(20);
		
		GPIO_write_low(&PORTD, trigPin1);  //set pin low
		
	}
	
	else if (i == 2)
	{
		GPIO_write_high(&PORTD, trigPin2);
		_delay_us(20);
		
		GPIO_write_low(&PORTD, trigPin2);  //set pin low
		
	}
	
}

ISR(TIMER2_OVF_vect)
{
	if ((Distance_Front <= 15) | (Distance_Back<= 15))
	{
		TIM2_overflow_512us()
		GPIO_write_high(&PORTC, buzzer);
	}
	else if ((Distance_Front >= 15) | (Distance_Back >= 15))
	{
		TIM2_overflow_2ms()
		GPIO_write_high(&PORTC, buzzer);
	}
}
