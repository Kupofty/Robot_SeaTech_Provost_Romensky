
#ifndef PWM_H
#define	PWM_H


void InitPWM(void);
//void PWMSetSpeed(float,unsigned char);
void PWMUpdateSpeed();
void PWMSetSpeedConsigne(float vitesseEnPourcents, char moteur);
//void PWMSetSpeed(float vitesseEnPourcents, unsigned char num_moteur);
#endif	/* PWM_H */