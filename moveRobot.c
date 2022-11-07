#include "moveRobot.h"
#include <msp430g2553.h>

void settingUp(void)    /* Function definition */
{
    /*** GPIO Set-Up ***/
    P2DIR |= BIT2 | BIT4 | BIT1 |BIT5;      // Set P2X2.4.1.5 as Output
    P2SEL |= BIT2 | BIT4;                   // Set P2X2.4 as Output for Timer1

    P2OUT &= ~BIT1;                         // Change direction of rotation for motor A
    P2OUT |= BIT5;                          // Change direction of rotation for motor B
}

void setForward(void){
    /*** Timer1_A Set-Up ***/
    TA1CCR0 = 1000;                        // PWM period
    TA1CTL |= TASSEL_2 + MC_1;              // SMCLK, Up Mode (Counts to TA0CCR0)

    TA1CCR1 = 200;                         // TA0CCR1 PWM duty cycle for motor A
    TA1CCTL1 |= OUTMOD_7;                   // TA0CCR1 output mode = reset/set for motor A

    TA1CCR2 = 200;                         // TA0CCR1 PWM duty cycle for motor B
    TA1CCTL2 |= OUTMOD_7;                   // TA0CCR1 output mode = reset/set for motor B
}


void setRight(void){
    /*** Timer1_A Set-Up ***/
    TA1CCR0 = 1000;                        // PWM period
    TA1CTL |= TASSEL_2 + MC_1;              // SMCLK, Up Mode (Counts to TA0CCR0)

    TA1CCR1 = 250;                         // TA0CCR1 PWM duty cycle for motor A
    TA1CCTL1 |= OUTMOD_7;                   // TA0CCR1 output mode = reset/set for motor A

    TA1CCR2 = 0;                         // TA0CCR1 PWM duty cycle for motor B
    TA1CCTL2 |= OUTMOD_7;                   // TA0CCR1 output mode = reset/set for motor B
}

void setLeft(void){
    /*** Timer1_A Set-Up ***/
    TA1CCR0 = 1000;                        // PWM period
    TA1CTL |= TASSEL_2 + MC_1;              // SMCLK, Up Mode (Counts to TA0CCR0)

    TA1CCR1 = 0;                         // TA0CCR1 PWM duty cycle for motor A
    TA1CCTL1 |= OUTMOD_7;                   // TA0CCR1 output mode = reset/set for motor A

    TA1CCR2 = 450;                         // TA0CCR1 PWM duty cycle for motor B
    TA1CCTL2 |= OUTMOD_7;                   // TA0CCR1 output mode = reset/set for motor B
}

void setStop(void){
    /*** Timer1_A Set-Up ***/
    TA1CCR0 = 1000;                        // PWM period
    TA1CTL |= TASSEL_2 + MC_1;              // SMCLK, Up Mode (Counts to TA0CCR0)

    TA1CCR1 = 0;                         // TA0CCR1 PWM duty cycle for motor A

    TA1CCR2 = 0;                         // TA0CCR1 PWM duty cycle for motor B
}

