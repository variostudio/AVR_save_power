#! /bin/bash

echo Compiling ${1%.*}.c...
avr-gcc -Wall -Os -fpack-struct -fshort-enums -funsigned-char -funsigned-bitfields -mmcu=$2 -c ${1%.*}.c 

avr-gcc -Os -mmcu=$2 -o main.elf ${1%.*}.o -lm

avr-objcopy -R .eeprom -O ihex main.elf ${1%.*}.hex

avr-size ${1%.*}.hex

if [ $? -eq 0 ]; then
    echo Compilaton done!
else
    exit 1
fi

rm *.o
rm *.elf

echo Uploading ${1%.*}.hex...
avrdude -p $2 -c usbasp -e -U flash:w:${1%.*}.hex 

if [ $? -eq 0 ]; then
	echo Upload done!
else 
	exit 1
fi
