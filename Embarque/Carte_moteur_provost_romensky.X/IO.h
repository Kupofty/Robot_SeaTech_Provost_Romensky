#ifndef IO_H
#define IO_H

//Affectation des pins des LEDS
#define LED_ORANGE _LATC10 
#define LED_BLEUE _LATG7
#define LED_BLANCHE _LATG6

// Prototypes fonctions
void InitIO();

// Definitions des pins pour les hacheurs moteurs
#define MOTEUR1_IN1 _LATB14
#define MOTEUR1_IN2 _LATB15

#define MOTEUR6_IN1 _LATC6
#define MOTEUR6_IN2 _LATC7 

// Configuration  specifique du moteur gauche
#define MOTEUR_GAUCHE_OUTPUT_IO_H MOTEUR1_IN1
#define MOTEUR_GAUCHE_OUTPUT_IO_L MOTEUR1_IN2
#define MOTEUR_GAUCHE_ENABLE_PWM_L IOCON1bits.PENL
#define MOTEUR_GAUCHE_ENABLE_PWM_H IOCON1bits.PENH
#define MOTEUR_GAUCHE_DUTY_CYCLE PDC1

// Configuration  specifique du moteur droit
#define MOTEUR_DROIT_OUTPUT_IO_H MOTEUR6_IN1
#define MOTEUR_DROIT_OUTPUT_IO_L MOTEUR6_IN2
#define MOTEUR_DROIT_ENABLE_PWM_L IOCON6bits.PENL
#define MOTEUR_DROIT_ENABLE_PWM_H IOCON6bits.PENH
#define MOTEUR_DROIT_DUTY_CYCLE PDC6

// Motor alias
#define MOTEUR_DROIT 0
#define MOTEUR_GAUCHE 1

#endif /* IO_H */