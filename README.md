# AVR PicoPower 
There are two power saving technics for AVR ATtiny chips
## Wake up on button interrupt
The `main.c` demonstrating how to possible use push button for wake up uC after long sleep
## Wake up on watchdog time.
The `main_wdt.c` shows technik how to use Watchdog timer (WDT) for wake up uC after some time of slleping.,
## Compile and upload script 
Included also. Please take `cu_avr.sh` to use.
The usage examples:
```cu_avr.sh main.c attiny85```
or 
```cu_avr.sh main_wdt.c attiny85```
