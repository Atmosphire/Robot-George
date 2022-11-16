#include <msp430g2553.h>
#include "moveRobot.h"
#include "ultrasonicSensor.h"
#include "capteur_lumiere.h"
#include "ADC.h"

/*** Global Variable ***/
int IncDec_PWM = 1;
int i = 0;
int flagIsOnDisk = 0;
float initLight = 0;

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
    initUltrasonicSensor();

    initLight = init_lumiere_jour(6);

    setForward();


    //__enable_interrupt();

    while(1){


        for(i = 0; i<750; i++){
            lineFollower();
        }
        //setStop();
        while(isObstacle(18) == 1){
            setStop();
        }

        /*
        lineFollower();

        while(isObstacle(15) == 1){

            setStop();

        }
        */

    }

}

void lineFollower(void){

    //Disk case
    if(!(( P1IN | ~BIT4) == ~BIT4) && !(( P1IN | ~BIT5) == ~BIT5)){
        setForward();
    }

    if((( P1IN | ~BIT4) == ~BIT4) && (( P1IN | ~BIT5) == ~BIT5) && (flagIsOnDisk == 0)){


        /*
         * Center to disk
         */
        setForwardLow();
        __delay_cycles(3000000);
        flagIsOnDisk = 1;

        P2OUT |= BIT1;                         // Change direction of rotation for motor A
        P2OUT |= BIT5;                          // Change direction of rotation for motor B

        while(!(detecte_sortie(18, initLight, 6))){}

        setForward();
        settingUp();
        setForward();



    }

    /*
    if((( P1IN | ~BIT4) == ~BIT4) && (( P1IN | ~BIT5) == ~BIT5) && (flagIsOnDisk == 1)){
        setStop();
    }
    */

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
