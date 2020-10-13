/*
 * File:   main.c
 * Author: TABLE 6
 *
 * Created on 29 septembre 2020, 09:31
 */
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "ChipConfig.h"
#include "timer.h"
#include "IO.h"
#include "Robot.h"
#include "PWM.h"
#include "ADC.h"


int main (void){
/***************************************************************************************************/
//Initialisation de l?oscillateur
/****************************************************************************************************/
InitOscillator();

/****************************************************************************************************/
// Configuration des entrées sorties
/****************************************************************************************************/
InitIO();
InitADC1();
InitTimer1();
InitTimer23();
InitPWM();

LED_BLANCHE = 1;
LED_BLEUE = 1;
LED_ORANGE = 1;

/****************************************************************************************************/
// Boucle Principale
/****************************************************************************************************/

//PWMSetSpeed(20, MOTEUR_DROIT) ;
// PWMSetSpeed(20 , MOTEUR_GAUCHE) ;

 
PWMSetSpeedConsigne(100, MOTEUR_GAUCHE);
        
        
while(1){
    LED_BLANCHE = !LED_BLANCHE;
    LED_BLEUE = !LED_BLEUE;
    if (ADCIsConversionFinished()==1)
    {  ADCClearConversionFinishedFlag(void);
        float ADCValue0=ADCGetResult[0];
        float ADCValue1=ADCGetResult[1];
        float ADCValue2=ADCGetResult[2];
}
}
}