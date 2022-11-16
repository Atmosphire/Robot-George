/*
 * capteur_lumiere.c
 *
 *  Created on: 14 nov. 2022
 *      Author: 35387315
 */
#include <msp430.h>
#include "capteur_lumiere.h"

int init_lumiere_jour(int pinLumiere) {

    float lumiereDuJour = 0;
    int i =0;
    ADC_init();
    ADC_Demarrer_conversion(pinLumiere);
    lumiereDuJour = ADC_Lire_resultat();

    while (i < 10) {

        ADC_Demarrer_conversion(pinLumiere);
        float tmp = ADC_Lire_resultat();
        lumiereDuJour = (lumiereDuJour + tmp) / 2;
        i++;
    }

    return lumiereDuJour;
}

int detecte_sortie(const int POURCENTAGE, float lumiereDuJour, int pinLumiere) {

    P1DIR |= BIT0;
    P1OUT &= ~(BIT0);

    float seuil = lumiereDuJour + (lumiereDuJour * (POURCENTAGE/100.0));

    ADC_Demarrer_conversion(pinLumiere);
    int lumiereActuel = ADC_Lire_resultat();
    if (lumiereActuel > seuil)   {
        P1OUT |= BIT0;
        return 1;
    } else {
        P1OUT &= ~(BIT0);
        return 0;
    }

}



