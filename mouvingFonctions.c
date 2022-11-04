#include <msp430g2253.h>

/*** Global Variable ***/
int IncDec_PWM = 1;

void main(void){

    /*** Watchdog timer and clock Set-Up ***/
    WDTCTL = WDTPW + WDTHOLD;       // Stop watchdog timer
    DCOCTL = 0;                     // Select lowest DCOx and MODx
    BCSCTL1 = CALBC1_1MHZ;          // Set range
    DCOCTL = CALDCO_1MHZ;           // Set DCO step + modulation

    /*** GPIO Set-Up ***/
    P2DIR |= BIT2 | BIT4 | BIT1 |BIT5;      // Set P2X2.4.1.5 as Output
    P2SEL |= BIT2 | BIT4;                   // Set P2X2.4 as Output for Timer1

    P2OUT &= ~BIT1;                         // Change direction of rotation for motor A
    P2OUT |= BIT5;                          // Change direction of rotation for motor B


    /*** Timer1_A Set-Up ***/
    TA1CCR0 |= 1000;                        // PWM period
    TA1CTL |= TASSEL_2 + MC_1;              // SMCLK, Up Mode (Counts to TA0CCR0)

    TA1CCR1 |= 200;                         // TA0CCR1 PWM duty cycle for motor A
    TA1CCTL1 |= OUTMOD_7;                   // TA0CCR1 output mode = reset/set for motor A

    TA1CCR2 |= 200;                         // TA0CCR1 PWM duty cycle for motor B
    TA1CCTL2 |= OUTMOD_7;                   // TA0CCR1 output mode = reset/set for motor B


    _BIS_SR(LPM0_bits + GIE);       // Enter Low power mode 0 with interrupts enabled
}

/*
#pragma vector=TIMER1_A0_VECTOR     // Timer1 A0 interrupt service routine
   __interrupt void Timer1_A0 (void) {

}
*/
