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
#include "main.h"
#include "UART.h"
#include "CB_TX1.h"



int main(void) {
    /***************************************************************************************************/
    //Initialisation de l?oscillateur
    /****************************************************************************************************/
    InitOscillator();

    /****************************************************************************************************/
    // Configuration des entr�es sorties
    /****************************************************************************************************/
    InitIO();
    InitADC1();
    InitTimer1(250);
    InitTimer4(1000);
    InitTimer23();
    InitPWM();
    InitUART();
//
    //LED_BLANCHE = 1;
    //LED_BLEUE = 1;
    //LED_ORANGE = 1;
//
//    /****************************************************************************************************/
//    // Boucle Principale
//    /****************************************************************************************************/
//
    //PWMSetSpeed(20, MOTEUR_DROIT) ;
   // PWMSetSpeed(20 , MOTEUR_GAUCHE) ;


    //PWMSetSpeedConsigne(100, MOTEUR_GAUCHE);
//
    unsigned int ADCValue0 = 0;
    unsigned int ADCValue1 = 0;
    unsigned int ADCValue2 = 0;
    unsigned int ADCValue3 = 0;
    unsigned int ADCValue4 = 0;
    int distmin = 20;

    while (1) {
        if (ADCIsConversionFinished()) {
            ADCClearConversionFinishedFlag();
            unsigned int * result = ADCGetResult();
            float volts = ((float) result [1]) * 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreDroit = 34 / volts - 5;
            volts = ((float) result [2]) * 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreCentre = 34 / volts - 5;
            volts = ((float) result [4]) * 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreGauche = 34 / volts - 5;
            volts = ((float) result [3]) * 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremeGauche = 34 / volts - 5;
            volts = ((float) result [0]) * 3.3 / 4096 * 3.2;
            robotState.distanceTelemetreExtremeDroit = 34 / volts - 5;

            if (robotState.distanceTelemetreExtremeGauche<=distmin)
                LED_BLANCHE = 1;
            else
                LED_BLANCHE=0;
            
            if (robotState.distanceTelemetreCentre <= distmin) 
                LED_BLEUE = 1;
            else
                LED_BLEUE = 0;
         
            if (robotState.distanceTelemetreExtremeDroit <= distmin) 
                LED_ORANGE = 1;
            else
                LED_ORANGE = 0;
        }
        
        
        
//        SendMessageDirect((unsigned char * ) "Bonjour", 7);
//        __delay32(4000000);
        SendMessage((unsigned char * ) "Bonjour", 7);
        
    }
}
unsigned char stateRobot;

void OperatingSystemLoop(void) {
    switch (stateRobot) {
        case STATE_ATTENTE:
            timestamp = 0;
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_ATTENTE_EN_COURS;

        case STATE_ATTENTE_EN_COURS:
            if (timestamp > 1000)
                stateRobot = STATE_AVANCE;
            break;

        case STATE_AVANCE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);   //20
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);  //20
            stateRobot = STATE_AVANCE_EN_COURS;
            break;
        case STATE_AVANCE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_GAUCHE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT); //20
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);
            stateRobot = STATE_TOURNE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);  //20
            stateRobot = STATE_TOURNE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_GAUCHE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT); //+15
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE); //-15
            stateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_GAUCHE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        case STATE_TOURNE_SUR_PLACE_DROITE:
            PWMSetSpeedConsigne(0, MOTEUR_DROIT);  //-15
            PWMSetSpeedConsigne(0, MOTEUR_GAUCHE);  //15
            stateRobot = STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS;
            break;
        case STATE_TOURNE_SUR_PLACE_DROITE_EN_COURS:
            SetNextRobotStateInAutomaticMode();
            break;

        default:
            stateRobot = STATE_ATTENTE;
            break;
    }
}

unsigned char nextStateRobot = 0;


void SetNextRobotStateInAutomaticMode() {
    unsigned char positionObstacle = PAS_D_OBSTACLE;

    //D�termination de la position des obstacles en fonction des t�l�m�tres
    if (robotState.distanceTelemetreDroit < 20 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 30 &&
          robotState.distanceTelemetreExtremeGauche > 30
            ) //Obstacle � droite     
            positionObstacle = OBSTACLE_A_DROITE;
    
    else if (
    robotState.distanceTelemetreExtremeDroit > 30 &&
            robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche < 20) //Obstacle � gauche
        
            positionObstacle = OBSTACLE_A_GAUCHE;
    
    else if (robotState.distanceTelemetreCentre < 30 ||
            (robotState.distanceTelemetreDroit < 15 &&
            robotState.distanceTelemetreGauche < 15) ||
            (robotState.distanceTelemetreExtremeDroit < 10 &&
            robotState.distanceTelemetreExtremeGauche < 10)||
            (robotState.distanceTelemetreDroit < 20 &&
            robotState.distanceTelemetreExtremeGauche < 20 )||
            (robotState.distanceTelemetreExtremeDroit < 20 &&
             robotState.distanceTelemetreGauche < 20))
            //Obstacle en face
            positionObstacle = OBSTACLE_EN_FACE;
    
    else if (robotState.distanceTelemetreExtremeGauche < 20)
            positionObstacle = OBSTACLE_A_GAUCHE;
    
    else if( robotState.distanceTelemetreExtremeDroit < 20 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 30 )
             positionObstacle = OBSTACLE_A_DROITE;
    
    
    else if (robotState.distanceTelemetreDroit > 30 &&
            robotState.distanceTelemetreCentre > 30 &&
            robotState.distanceTelemetreGauche > 30 && 
            robotState.distanceTelemetreExtremeGauche > 30 &&
            robotState.distanceTelemetreExtremeDroit > 30)
        
            positionObstacle = PAS_D_OBSTACLE;

    //D�termination de l?�tat � venir du robot
    if (positionObstacle == PAS_D_OBSTACLE)
        nextStateRobot = STATE_AVANCE;
    else if (positionObstacle == OBSTACLE_A_DROITE)
        nextStateRobot = STATE_TOURNE_GAUCHE;
    else if (positionObstacle == OBSTACLE_A_GAUCHE)
        nextStateRobot = STATE_TOURNE_DROITE;
    else if (positionObstacle == OBSTACLE_EN_FACE)
        nextStateRobot = STATE_TOURNE_SUR_PLACE_GAUCHE;

    //Si l?on n?est pas dans la transition de l?�tape en cours
    if (nextStateRobot != stateRobot - 1 )
        stateRobot = nextStateRobot;
}