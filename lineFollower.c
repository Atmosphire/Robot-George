#include <msp430g2553.h>
#include "moveRobot.h"
#include "ADC.h"

/*** Global Variable ***/
int IncDec_PWM = 1;

void main(void){

    /*** Watchdog timer and clock Set-Up ***/
    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
    DCOCTL = 0;                     // Select lowest DCOx and MODx
    BCSCTL1 = CALBC1_1MHZ;          // Set range
    DCOCTL = CALDCO_1MHZ;           // Set DCO step + modulation


    /*** Left line sensor init ***/
    P1DIR &= ~(BIT4);

    /*** Left line sensor init ***/
    P1DIR &= ~(BIT5);

    P1DIR |= (BIT0);

    settingUp();
    setForward();


    //__enable_interrupt();

    while(1){

        lineFollower();

    }

}

void lineFollower(void){

    //Disk case
    if(!(( P1IN | ~BIT4) == ~BIT4) && !(( P1IN | ~BIT5) == ~BIT5)){
        setForward();
    }else{
        setStop();
    }

    //Left turn case
    if((( P1IN | ~BIT4) == ~BIT4) && !(( P1IN | ~BIT5) == ~BIT5)){
        setLeft();
    }

    //Right turn case
    if(!(( P1IN | ~BIT4) == ~BIT4) && (( P1IN | ~BIT5) == ~BIT5)){
        setRight();
    }

}


/**
#pragma vector=PORT1_VECTOR
__interrupt void detect (void) {
    setStop();
}

**/

