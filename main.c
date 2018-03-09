#define F_CPU 1000000UL  /* 1 MHz CPU clock */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/wdt.h>
#include <avr/sleep.h>

void powerSetup() {
    //Disable TIMER1, TIMER0, ADC
    PRR = (1<<PRTIM1)|(1<<PRTIM0)|(1<<PRADC);

    //Turn off WDT
    WDTCR &= (0<<WDIE) & (0<<WDE);

    //Enable Pin Change Interrupts
    GIMSK |= _BV(PCIE);

    //Wake up button on PB2
    PCMSK |= _BV(PCINT2);

    sei();

    //Sleepmode = powerdown
    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void powerDown() {
    sleep_enable();
    sleep_cpu();
}

int main(void) {
    // set PB3 to be output
    DDRB |= (1<<DDB3);
    powerSetup();

    while (1) {
        // set PB3 high
        PORTB |= (1<<PORTB3);
        //DelayNms();
        _delay_ms(200);

        // set PB3 low
        PORTB &= (0<<PORTB3);
        powerDown();
    }

    return 1;
}

ISR(PCINT0_vect) {
    // This is called when the interrupt occurs, but I don't need to do anything in it
}
