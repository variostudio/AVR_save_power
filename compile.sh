#! /bin/bash

avr-gcc -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -mmcu=attiny85 -c main.c

avr-gcc -Os -mmcu=attiny85 -o main.elf main.o -lm

avr-objcopy -R .eeprom -O ihex main.elf main.hex

avr-size main.hex

rm *.o
rm *.elf
ls -l
