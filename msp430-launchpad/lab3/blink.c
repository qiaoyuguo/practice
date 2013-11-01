/* use button to control blinking LEDs */
/* modified from http://dbindner.freeshell.org/msp430/#_pushbutton_fun */
/* blink the LEDs, if button is pressed, no LED will flash, or else both
 * LEDs will flash. 
 */
#include <msp430g2221.h>
#define pin0mask  (0x01 << 0)
#define pin3mask  (0x01 << 3)
#define pin6mask  (0x01 << 6)

int main(void) {
    /* Hold the watchdog timer so it doesn't reset our chip */
    WDTCTL = WDTPW + WDTHOLD;

    /* Configure pins 0,6 on port 1 as output pins */
    P1DIR = pin0mask | pin6mask;

    /* Blink Pin 0 and Pin 6 led */
    P1OUT = pin6mask | pin0mask;
    /* infinite loop */
    for( ; ; ) {
        /* The following two lines implement a very crude delay loop.
         * The actual length of the delay can vary significantly.
         * This approach may not work with all compilers.
         */
        volatile int i;
        for( i = 0; i < 10000; i++ );

        /* Switch 2 is connected to pin 3.  If it is low, then change the
         * blinking behavior. 
         */
        if( pin3mask  == 0 ) {
            /* Toggle just pin 0. */
            P1OUT ^= pin0mask | pin6mask;
        } 
    }
}
