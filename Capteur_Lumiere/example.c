#include <msp430.h>
#include "ADC.h"
#include "capteur_lumiere.h"

void main(void)
{

    WDTCTL = WDTPW | WDTHOLD;       // stop watchdog timer
    float lumiereDuJour = init_lumiere_jour(1);

    while(1)
    {
        detecte_sortie(15, lumiereDuJour, 1);
    }
}
