#define F_CPU 1000000UL  /* 1 MHz CPU clock */

#include <util/delay.h>
#include <avr/io.h>
#include <avr/interrupt.h> 
#include <avr/wdt.h>
#include <avr/sleep.h>

void powerSetup() {
	//Disable TIMER1, TIMER0, ADC
	PRR = (1<<PRTIM1)|(1<<PRTIM0)|(1<<PRADC);

	//Set watchdog timer to 120ms
	wdt_reset();
	wdt_enable(WDTO_4S);
	WDTCR |= (1<<WDIE);

	sei();

	//Sleepmode = powerdown
	set_sleep_mode(SLEEP_MODE_PWR_DOWN);
}

void delayNms() {
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
    delayNms();
  }
 
	return 1;
}

ISR (WDT_vect) {
  WDTCR |= (1<<WDIE);
}
