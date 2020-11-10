# Digital electronics 2

The repository contains AVR lab exercises for bachelor course [*Digital Electronics 2*](https://www.vutbr.cz/en/students/courses/detail/224132) at Brno University of Technology, Czechia.

## Exercises

The Class exercises are located in the folder labs

* [Git version-control system, AVR tools](Labs/01-tools)
* [Control of GPIO, LED, push button](Labs/02-leds)
* [User library for GPIO control](Labs/03-gpio)
* [Interrupts, Timers](Labs/04-interrupts)
* [Display devices, 7-segment display](Labs/05-segment)
* [Display devices, LCD display](Labs/06-lcd)
* [ADC, serial communication, UART](Labs/07-uart)
* Serial communication, I2C/TWI

## Homework

Each exercise has a follow up homework to be submitted before the next lab. Homework tasks are contained in the folder Homeworks

* [Task 1:Blink(Morse code)](Homework/Task-1)
* [Task 2:Knight raider](Homework/Task-2)
* [Task 3:GPIO control ](Homework/Task-3)
* [Task 4:Interrupts](Homework/Task-4)
### Project
* General instructions


## Materials

The following hardware and software components are mainly used in the lab.

### Hardware

* [ATmega328P](https://www.microchip.com/wwwproducts/en/ATmega328P) 8-bit microcontroller: [instruction set](https://www.microchip.com/webdoc/avrassembler/avrassembler.wb_instruction_list.html)
* [Arduino Uno](https://arduino-shop.cz/arduino/1353-klon-arduino-uno-r3-atmega328p-ch340-mini-usb-1466635561.html) board: [schematic](Docs/arduino_shield.pdf)
* 24MHz 8-channel [logic analyzer](https://www.ebay.com/sch/i.html?LH_CAds=&_ex_kw=&_fpos=&_fspt=1&_mPrRngCbx=1&_nkw=24mhz%20logic%20analyzer&_sacat=&_sadis=&_sop=12&_udhi=&_udlo=): [software](https://www.saleae.com/)
* [Multi-function shield](https://www.gme.cz/experiment-shield-pro-arduino) with four LEDs, three push buttons, four seven-segment displays, and others: [schematic](Docs/arduino_shield.pdf)
* [LCD and keypad hield](https://arduino-shop.cz/en/arduino-platform/899-arduino-lcd-shield-1420670167.html) with LCD and five push buttons: [schematic](Docs/arduino_shield.pdf)
* Analog [joystick PS2](https://arduino-shop.cz/arduino/884-arduino-joystick-ps2.html)
* I2C humidity and temperature sensor [DHT12](https://arduino-shop.cz/arduino/1977-i2c-teplomer-a-vlhkomer-dht12-digitalni.html): [data sheet](Docs/dht12_manual.pdf)
* I2C real time clock [DS3231](https://arduino-shop.cz/hledani.php?q=DS3231&n_q=): [data sheet](Docs/ds3231_manual.pdf)
* [HC-SR04](https://components101.com/ultrasonic-sensor-working-pinout-datasheet) ultrasonic sensor
* [ESP8266](https://arduino-shop.cz/arduino/911-internet-veci-je-tady-tcp-ip-wifi-esp8266-1420990568.html) Wi-Fi module: [AT commands](Docs/esp8266_at_instruction_set.pdf)


### Software

* [Visual Studio Code](https://code.visualstudio.com/)
* [Saleae logic analyser](https://www.saleae.com/downloads/)
* [Atmel Studio 7](https://www.microchip.com/mplab/avr-support/atmel-studio-7)
* [SimulIDE](https://www.simulide.com/p/home.html), real time electronic circuit simulator. With PIC, AVR and Arduino simulation.
