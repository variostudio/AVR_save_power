#! /bin/bash

avrdude -p attiny85 -c usbasp -e -U flash:w:main.hex
