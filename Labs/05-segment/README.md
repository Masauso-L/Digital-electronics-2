## Preparation tasks (done before the lab at home)


   * Common Cathode 7-segment display (CC SSD): Have all of their segments' cathodes connected to a common ground, the respective anodes connected to individual pins i.e.  Active high
   
   * Common Anode 7-segment display (CA SSD): Have all of their segments' anodes connected to a common source, the respective cathodes connected to individual pins i.e.  Active low

Binary values of the segments for display 0 to 9 on a common anode 7-segment display.

   | **Digit** | **A** | **B** | **C** | **D** | **E** | **F** | **G** | **DP** |
   | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: | :-: |
   | 0 | 0  | 0  | 0  | 0  | 0  | 0  | 1  | 1  |
   | 1 | 1  | 0  | 0  | 1  | 1  | 1  | 1  | 1  |
   | 2 | 0  | 0  | 1  | 0  | 0  | 1  | 0  | 1  |
   | 3 | 0  | 0  | 0  | 0  | 1  | 1  | 0  | 1  |
   | 4 | 1  | 0  | 0  | 1  | 1  | 0  | 0  | 1  |
   | 5 | 0  | 1  | 0  | 0  | 1  | 0  | 0  | 1  |
   | 6 | 0  | 1  | 0  | 0  | 0  | 0  | 0  | 1  |
   | 7 | 0  | 0  | 0  | 1  | 1  | 1  | 1  | 1  |
   | 8 | 0  | 0  | 0  | 0  | 0  | 0  | 0  | 1  |
   | 9 | 0  | 0  | 0  | 0  | 1  | 0  | 0  | 1  |


   Use schematic of the [Multi-function shield](../../Docs/arduino_shield.pdf) and find out the connection of seven-segment display. What is the purpose of two shift registers 74HC595?

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;


According to the [ATmega328P datasheet](https://www.microchip.com/wwwproducts/en/ATmega328p) which I/O registers and which bits configure the Pin Change Interrupts (see External Interrupts)? What vector names have the PCINT [interrupt service routines](https://www.nongnu.org/avr-libc/user-manual/group__avr__interrupts.html)? Complete the table below.

| **Interrupt** | **Vector name** | **Pins** | **Operation** | **I/O register** | **Bit(s)** |
| :-: | :-: | :-: | :-- | :-: | :-: |
| Pin Change Interrupt 0 | `PCINT0_vect` | PB[7:0] | Interrupt enable<br>Select pins | PCICR<br>PCMSK0 | PCIE0<br>PCINT[7:0] |
| Pin Change Interrupt 1 | `PCINT1_vect`|  | Interrupt enable<br>Select pins | <br> | <br> |
| Pin Change Interrupt 2 | `PCINT2_vect`|  | Interrupt enable<br>Select pins | <br> | <br> |