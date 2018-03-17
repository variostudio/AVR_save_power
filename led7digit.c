#define F_CPU 1000000UL  /* 1 MHz CPU clock */

/*
 * Pin configuration:
 * PORTB0 - to SER
 * PORTB1 - to RCLK
 * PORTB2 - to SRCLK
 */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

//Could be different. Depends on chematic.
short digits[] = {0b10111111, 0b00000011, 0b01011101, 0b01010111, 0b01100011, 0b01110110, 0b01111110, 0b00110011, 0b01111111, 0b01110111};

void powerSetup() {
    //Disable TIMER1, TIMER0, ADC
    PRR = (1<<PRTIM1)|(1<<PRTIM0)|(1<<PRADC);

    //Set watchdog timer
    wdt_reset();
    wdt_enable(WDTO_1S);
    WDTCR |= (1<<WDIE);

    sei();

    //Sleepmode = powerdown
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void delayNms() {
    sleep_enable();
    sleep_cpu();
}

void toggleLatch(short high) {
	PORTB &= (0<<PORTB0);
	PORTB &= (0<<PORTB2);
    _delay_ms(5);
	
    if (high == 1) {
        PORTB |= (1<<PORTB0);
    }

    _delay_ms(5);
    PORTB |= (1<<PORTB2);
    _delay_ms(5);
    PORTB &= (0<<PORTB2);
    _delay_ms(5);
    PORTB &= (0<<PORTB0);
}

void digitToShift(int digit) {
	short d = digits[digit];
	short high = 0;
	
	short i=0;
	for (i=0; i<8; i++) {
		high = d & (1<<i) ? 1 : 0;
					
		toggleLatch(high);
	}
}

void showDigit(int digit) {
	digitToShift(digit);
		
	PORTB |= (1<<PORTB1);
    _delay_ms(5);
    
    PORTB &= (0<<PORTB1);
}

int main(void) {
    DDRB |= (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
    //powerSetup();
    
    short i=0;

    while (1) {
		showDigit(i);
		//delayNms();
		_delay_ms(1000);

		i++;
		if (i>9) {
			i=0;
		}
    }

    return 1;
}

ISR (WDT_vect) {
    WDTCR |= (1<<WDIE);
}
