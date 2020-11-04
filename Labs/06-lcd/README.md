# Lab 6: Display devices, LCD display

### Learning objectives

The purpose of the laboratory exercise is to understand the serial control of Hitachi HD44780-based LCD character display and how to define custom characters. Another goal is to learn how to read documentation for library functions and use them in your own project


## Preparation tasks (done before the lab at home)

Use schematic of the [LCD keypad shield](../../Docs/arduino_shield.pdf) and find out the connection of LCD display. What data and control signals are used? What is the meaning of these signals?

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;

&nbsp;
| **Signal(s)** | **Pin(s)** | **Purpose** |
| :-: | :-: | :-- |
| RS | PB0 | Register selection signal. Selection between *Instruction register* (0) and *Data register* (1) |
| R/W | GND | Selecting reading or writing. GND means only writing is enabled |
| E | PB1 | Enable signal for communication |
| D[3:0] | N/A | Data transfer in 8-bit mode. |
| D[7:4] | PD[7:4] | Data transfer in both 8 and 4-bit modes. |

| **Signal(s)** | **Value(s)** | **Purpose** |
| :-: | :-: | :-- |
| RS | 1 | Selects *Data register* |
| D[7:4] | 0100 | Higher four bits of sent word |
| D[7:4] | 0011 | ASCII code: C|


What is the ASCII table? What are the values for uppercase letters `A` to `Z`, lowercase letters `a` to `z`, and numbers `0` to `9` in this table?

&nbsp;


&nbsp;

&nbsp;

In the lab, we are using [LCD library for HD44780 based LCDs](http://www.peterfleury.epizy.com/avr-software.html) developed by Peter Fleury. Use online manual of LCD library and add the input parameters and description of the functions to the following table.

   | **Function name** | **Function parameters** | **Description** | **Example** |
   | :-- | :-- | :-- | :-- |
   | `lcd_init` | `LCD_DISP_OFF`<br>`LCD_DISP_ON`<br>`LCD_DISP_ON_CURSOR`<br>`LCD_DISP_ON_CURSOR_BLINK` | Display off<br>display on, cursor off<br>display on, cursor on<br>display on, cursor on flashing |`lcd_init(LCD_DISP_OFF);`<br>&nbsp;<br>&nbsp;<br>&nbsp; |
   | `lcd_clrscr` | `void` | Clear display and set cursor to home position. | `lcd_clrscr();` |
   | `lcd_gotoxy` | `uint8_t x`<br>`uint8_t y`|	Set cursor to specified position. | `lcd_gotxy(2,2);` |
   | `lcd_putc` |`char c` | Display character at current cursor position.   | `lcd_putc(c);` |
   | `lcd_puts` | `const char* s` | Display string without auto linefeed.   |`lcd_puts(s);` |
   | `lcd_command` | `uint8_t cmd` | Send LCD controller instruction command, | `lcd_command(cmd);` |
   | `lcd_data` | `uint8_t data` | Send data byte to LCD controller. |`lcd_data(data);` |