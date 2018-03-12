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

int high = 1;

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

void toggleLatch() {
    if (high == 1) {
        PORTB |= (1<<PORTB0);
    } else {
        PORTB &= (0<<PORTB0);
    }

    _delay_ms(5);
    PORTB |= (1<<PORTB2);
    _delay_ms(5);
    PORTB &= (0<<PORTB2);
    _delay_ms(5);
    PORTB &= (0<<PORTB0);
}

void flipHiLow() {
    if (high == 1) {
        high = 0;
    } else {
        high = 1;
    }
}

int main(void) {
    DDRB |= (1<<DDB2) | (1<<DDB1) | (1<<DDB0);
    powerSetup();

    while (1) {
        toggleLatch();
        flipHiLow();
        toggleLatch();

        PORTB |= (1<<PORTB1);
        _delay_ms(5);
        PORTB &= (0<<PORTB1);

        delayNms();
    }

    return 1;
}

ISR (WDT_vect) {
    WDTCR |= (1<<WDIE);
}
