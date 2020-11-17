//Partie PWM
#include <xc.h> // library xc.h inclut tous les uC
#include "IO.h"
#include "PWM.h"
#include "Robot.h"
#include "ToolBox.h"

#define PWMPER 40.0
float acceleration = 5;

void InitPWM(void) {
    PTCON2bits.PCLKDIV = 0b000; //Divide by 1
    PTPER = 100 * PWMPER; //Période en pourcentage

    //Réglage PWM moteur 1 sur hacheur 1
    IOCON1bits.POLH = 1; //High = 1 and active on low =0
    IOCON1bits.POLL = 1; //High = 1
    IOCON1bits.PMOD = 0b01; //Set PWM Mode to Redundant
    FCLCON1 = 0x0003; //Désactive la gestion des faults

    //Reglage PWM moteur 2 sur hacheur 6
    IOCON6bits.POLH = 1; //High = 1
    IOCON6bits.POLL = 1; //High = 1
    IOCON6bits.PMOD = 0b01; //Set PWM Mode to Redundant
    FCLCON6 = 0x0003; //Désactive la gestion des faults

    /* Enable PWM Module */
    PTCONbits.PTEN = 1;
}

//void PWMSetSpeed(float vitesseEnPourcents, unsigned char num_moteur) {
//    if (num_moteur == MOTEUR_GAUCHE) {
//        if (vitesseEnPourcents > 0) {
//            robotState.vitesseGaucheCommandeCourante = vitesseEnPourcents;
//            MOTEUR_GAUCHE_ENABLE_PWM_L = 0; //Pilotage de la pin en mode IO
//            MOTEUR_GAUCHE_OUTPUT_IO_L = 1; //Mise à 1 de la pin
//            MOTEUR_GAUCHE_ENABLE_PWM_H = 1; //Pilotage de la pin en mode PWM
//        } else {
//            robotState.vitesseGaucheCommandeCourante = vitesseEnPourcents;
//            MOTEUR_GAUCHE_ENABLE_PWM_H = 0; //Pilotage de la pin en mode IO
//            MOTEUR_GAUCHE_OUTPUT_IO_H = 1; //Mise à 1 de la pin
//            MOTEUR_GAUCHE_ENABLE_PWM_L = 1; //Pilotage de la pin en mode PWM
//        }
//        MOTEUR_GAUCHE_DUTY_CYCLE = Abs(robotState.vitesseGaucheCommandeCourante * PWMPER);
//    } else if (num_moteur == MOTEUR_DROIT) {
//        if (vitesseEnPourcents > 0) {
//            robotState.vitesseDroiteCommandeCourante = vitesseEnPourcents;
//            MOTEUR_DROIT_ENABLE_PWM_L = 0; //Pilotage de la pin en mode IO
//            MOTEUR_DROIT_OUTPUT_IO_L = 1; //Mise à 1 de la pin
//            MOTEUR_DROIT_ENABLE_PWM_H = 1; //Pilotage de la pin en mode PWM
//        } else {
//            robotState.vitesseDroiteCommandeCourante = vitesseEnPourcents;
//            MOTEUR_DROIT_ENABLE_PWM_H = 0; //Pilotage de la pin en mode IO
//            MOTEUR_DROIT_OUTPUT_IO_H = 1; //Mise à 1 de la pin
//            MOTEUR_DROIT_ENABLE_PWM_L = 1; //Pilotage de la pin en mode PWM
//        }
//        MOTEUR_DROIT_DUTY_CYCLE = Abs(robotState.vitesseDroiteCommandeCourante * PWMPER);
//    }
//}




void PWMUpdateSpeed() {
    // Ce t te f o n c t i o n e s t éa p p el e s u r time r e t permet de s u i v r e de s rampes d ?éé a c c l r a t i o n
    if (robotState.vitesseDroiteCommandeCourante < robotState.vitesseDroiteConsigne)
        robotState. vitesseDroiteCommandeCourante = Min(
            robotState . vitesseDroiteCommandeCourante + acceleration,
            robotState. vitesseDroiteConsigne);
    if (robotState . vitesseDroiteCommandeCourante > robotState.vitesseDroiteConsigne)
        robotState.vitesseDroiteCommandeCourante = Max(
            robotState . vitesseDroiteCommandeCourante - acceleration,
            robotState . vitesseDroiteConsigne);
    if (robotState . vitesseDroiteCommandeCourante > 0) {
        MOTEUR_DROIT_ENABLE_PWM_L = 0; // p i l o t a g e de l a pin en mode IO
        MOTEUR_DROIT_OUTPUT_IO_L = 1; //Mise à 1 de l a pin
        MOTEUR_DROIT_ENABLE_PWM_H = 1; // Pil o t a g e de l a pin en mode PWM
    } else {
        MOTEUR_DROIT_ENABLE_PWM_H = 0; // p i l o t a g e de l a pin en mode IO
        MOTEUR_DROIT_OUTPUT_IO_H = 1; //Mise à 1 de l a pin
        MOTEUR_DROIT_ENABLE_PWM_L = 1; // Pil o t a g e de l a pin en mode PWM
    }
    MOTEUR_DROIT_DUTY_CYCLE = Abs(robotState . vitesseDroiteCommandeCourante) * PWMPER;
    if (robotState . vitesseGaucheCommandeCourante < robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Min(
            robotState.vitesseGaucheCommandeCourante + acceleration,
            robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > robotState.vitesseGaucheConsigne)
        robotState.vitesseGaucheCommandeCourante = Max(
            robotState.vitesseGaucheCommandeCourante - acceleration,
            robotState.vitesseGaucheConsigne);
    if (robotState.vitesseGaucheCommandeCourante > 0) {
        MOTEUR_GAUCHE_ENABLE_PWM_L = 0; // p i l o t a g e de l a pin en mode IO
        MOTEUR_GAUCHE_OUTPUT_IO_L = 1; //Mise à 1 de l a pin
        MOTEUR_GAUCHE_ENABLE_PWM_H = 1; // Pil o t a g e de l a pin en mode PWM
    } else {
        MOTEUR_GAUCHE_ENABLE_PWM_H = 0; // p i l o t a g e de l a pin en mode IO
        MOTEUR_GAUCHE_OUTPUT_IO_H = 1; //Mise à 1 de l a pin
        MOTEUR_GAUCHE_ENABLE_PWM_L = 1; // Pil o t a g e de l a pin en mode PWM
    }
    MOTEUR_GAUCHE_DUTY_CYCLE = Abs(robotState . vitesseGaucheCommandeCourante) * PWMPER;}

void PWMSetSpeedConsigne(float vitesseEnPourcents, char moteur) {
    if (moteur == MOTEUR_GAUCHE)
        robotState.vitesseGaucheConsigne = vitesseEnPourcents;
    else
        robotState.vitesseDroiteConsigne = vitesseEnPourcents;}