#include <stdint.h>
#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "./castoplug.c"
#include "uart.h"

int main(void)
{
    int state = 0;
    int counter = 0;
    int debounce_count = 30;
    int reading;

    DDRB &= ~_BV(0);
    uart_init(9600);

    castoplug_setup();

    while (1)
    {
        if(PINB & _BV(0)) {
            reading = 1;
        }
        if(!(PINB & _BV(0))) {
            reading = 0;
        }
        if((reading == state) && counter > 0)
            counter = counter - 1;
        if(reading != state)
            counter = counter + 1;
        if(counter >= debounce_count) {
            counter = 0;
            state = reading;
        }
        switch(state) {
            case 0:
                for (int j = 0; j != 5; ++j)
                {
                    castoplug_send(a, 3, off);
                    _delay_ms(10);
                }
                uart_println("off");
                //_delay_ms(1000);
                break;
            case 1:
                for (int i = 0; i != 5; ++i)
                {
                    castoplug_send(a, 3, on);
                    _delay_ms(10);
                }
                uart_println("on");
                //_delay_ms(1000);
                break;
        }
        /* turn off the a:3 wall outlet */
        /* send 5 consecutive frames for redundancy */
        /*for (int i = 0; i != 5; ++i)
          {
          castoplug_send(a, 3, off);
          _delay_ms(10);
          }*/

    }

    return 0;
}
