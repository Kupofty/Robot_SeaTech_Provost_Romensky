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


int main (void){
/***************************************************************************************************/
//Initialisation de l?oscillateur
/****************************************************************************************************/
InitOscillator();

/****************************************************************************************************/
// Configuration des entrées sorties
/****************************************************************************************************/
InitIO();
InitTimer1();
InitTimer23();

LED_BLANCHE = 1;
LED_BLEUE = 1;
LED_ORANGE = 1;

/****************************************************************************************************/
// Boucle Principale
/****************************************************************************************************/
while(1){
    /*LED_BLANCHE = !LED_BLANCHE;*/
    /*  LED_BLEUE = !LED_BLEUE;*/
} // fin main
}