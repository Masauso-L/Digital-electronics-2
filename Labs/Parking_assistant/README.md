# Parking assistant

### Team members

Name: Masauso Lungu

ID: 209533

[Link to GitHub project folder](https://github.com/Masauso-L/Digital-electronics-2/tree/master/Labs/project)


### Project objectives

The aim of this project is to create an parking assistant aplication using several ultrasonic sensors HC-SR04. Implement LCD display showing distance of obstacles in cm, sound signaling with different frequencies according to distance, distance indication on LED bar and sending information to the UART.


## Hardware description

In this project, the following hardware was used: Arduino uno (based on atmega328p), an Ultrasonic sensor HC-SR04 for distance measuring, a buzzer for sound warning, LEDS for indication, LCD (16x2), resistors and jumper wires. 

![SimulIDE hardware implementation](images/circuit.png)

## Code description


![Application state diagram](images/Flow_Chart.jpeg)


### The source code is available in my github [reopsitory](https://github.com/Masauso-L/Digital-electronics-2/tree/master/Labs/project). 

The main program main.c is divided as follows:

* Import of Libraries
* Variable definitions
* Main function
* Interrupt service routine

Below is a summary of the sections of the program
### Imported libraries
 
 * This includes libraries bearing important functions to be used in the program and global parameters defined elsewhere.

### Main function
* In the main function, ports, UART protocol and LCD display are inicialized.
* Timer/counter configuration and enabling interrupt
* There is also an infinite loop to acertain stability of the program.

### Interrupt service routine (ISR)
Two timer/counter are used. Timer/counter1 is used for selecting an appropriate sensor to be active, either Front or Back and generation pulse for distance calculation

Timer/counter2 is used for generating the sound frequency.
LEDs are used to indicate the level of distance from the barrier: red when the distance is less than 30cm, yellow when in the range between  30 to 100 cm and green when in range of 100 to 400 cm.
The buzzer sound a warning, when the distance is less than or equal to 15cm.


## Video/animation
 
The implementation of the functionality of the program is demostrated here: [ Parking assistance](https://youtu.be/QUHA-yFgaHo)
or [Here with sound](https://youtu.be/lZ1OZvFWsUM)


## References

1. Tomáš Frýza, *Github*: [Digital-electronics-2](https://github.com/tomas-fryza/Digital-electronics-2)
2. DroneBot Workshop, *Using the HC-SR04 Ultrasonic Distance Sensor with Arduino*: [DroneBot](https://dronebotworkshop.com/hc-sr04-ultrasonic-distance-sensor-arduino/#1)
3. Ultrasonic module HC-SR04 [Datasheet](https://components101.com/ultrasonic-sensor-working-pinout-datasheet)