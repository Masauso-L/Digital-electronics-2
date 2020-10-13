# Lab 4: Interrupts, timers

### Learning objectives

The purpose of the laboratory exercise is to understand the function of the interrupt, interrupt service routine, and the functionality of timer units. Another goal is to practice finding information in the MCU manual; specifically setting timer control registers

![Multi-function shield](images/arduino_uno_multi-shield.jpg)


## Preparation tasks (done before the lab at home)

Consider an n-bit number that we increment based on the clock signal. If we reach its maximum value and try to increase it, the value will be reset. We call this state an overflow. The overflow time depends on the frequency of the clock signal, the number of bits, and on the prescaler value:

&nbsp;
![Timer overflow](images/timer_overflow.png)
&nbsp;

Calculate the overflow times for three Timer/Counter modules that contain ATmega328P if CPU clock frequency is 16&nbsp;MHz. Complete the following table for given prescaler values. Note that, Timer/Counter2 is able to set 7 prescaler values, including 32 and 128.

| **Module** | **Number of bits** | **1** | **8** | **32** | **64** | **128** | **256** | **1024** |
| :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
| Timer/Counter0 | 8  | 16u | 128u | -- | 1.024m | -- |4.096m | 16.384m|
| Timer/Counter1 | 16 | 4.096m  | 32.768m    | -- | 262.144m | -- | 1.048576| 4.194304 |
| Timer/Counter2 | 8  | 16u | 128u|512u | 1.024m | 2.048m  | 4.096m| 16.384m|

Shields are boards that can be attached to an Arduino board, significantly expand its capabilities, and makes prototyping much faster. See schematic of [Multi-function shield](../../Docs/arduino_shield.pdf) and find out the connection of four LEDs (D1, D2, D3, D4) and three push buttons (S1-A1, S2-A2, S3-A3).

The LEDs are connected as follow: D1=PB5[13],  D2=PB4[12],  D3=PB3[~11],  D4=PB2[~10],

And the push buttons are connected as follows: S1-A1=PC1[A1],  S2-A2=PC2[A2],  S3-A3=PC3[A3].