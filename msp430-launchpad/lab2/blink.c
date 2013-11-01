/*
 * =====================================================================================
 *
 *       Filename:  blink.c
 *
 *    Description:  blink  red led and green led alternatively
 * modified from http://processors.wiki.ti.com/index.php/Blink_your_first_LED 
 * =====================================================================================
 */
#include <msp430g2211.h>

// Initilize variables, This will keep count of how many cycles between LED toggles
unsigned int i = 0;
void main(void)
{

    //Stop watching timer. This line of code is needed at the beginning of most MSP430 projects 
    //This lines of code turns off the watchdog timer, which can reset the device 
    WDTCTL = WDTPW + WDTHOLD; 

    //P1DIR is a register that configures the direction (DIR) of a port pin as an output of an input
    // To set a specific pin as output of input, we write a '1' or '0' on the appropriate bit of the register.
    // P1DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>
    // Since we want to blink the on-board red LED, we want to set the direction of Port 1, Pin 0(P1 0) as an output 
    // Since we want to blink the on-board green LED, we want to set the direction of Port 1, Pin 0(P1 6) as an output 
    // We do that by writing a 1 on the  PIN0 bit of the P1DIR register(red led)
    // We do that by writing a 1 on the  PIN6 bit of the P1DIR register(green led)
    // P1DIR = <PIN7><PIN6><PIN5><PIN4><PIN3><PIN2><PIN1><PIN0>
    // P1DIR = 0100 0001
    // P1DIR = 0x41 < this is the hexadecimal conversion of 0400 0001>
    P1DIR |= 0x41; 
    
    // This empty for-loop will cause the lines of code within to loop infinitely
    for(;;)
    {
        // Toggle P1.0 using exclusive-OR operation
        // P1OUT is another register which holds the status of LED
        // '1' specifies ithat it's ON or HIGH, while '0' specifies that 
        // it's OFF or LOW, Since our LED is tied to P1.0, we will toggle 
        // the 0 bit of the P1OUT register
        P1OUT ^= 0x01;

        //Delay between LED toggles, This for-loop will run until the conditions  is met.
        //In this case, it will loop until the variable i increments to 10000
        for(i = 0; i < 10000; i++) ;

        // similiar to the above code
        P1OUT ^= 0x40;
        for(i = 0; i < 10000; i++) ;
    }
}
