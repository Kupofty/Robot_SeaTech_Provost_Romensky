#ifndef ROBOT_H
#define ROBOT_H
typedef struct robotStateBITS {

    union {

        struct {
            unsigned char taskEnCours;
            float vitesseGaucheConsigne;
            float vitesseGaucheCommandeCourante;
            float vitesseDroiteConsigne;
            float vitesseDroiteCommandeCourante;
            float acceleration;
            float distanceTelemetreCentre;
            float distanceTelemetreGauche;
            float distanceTelemetreDroit;
            float distanceTelemetreExtremeDroit;
            float distanceTelemetreExtremeGauche;
        };
    };
} ROBOT_STATE_BITS;
extern volatile ROBOT_STATE_BITS robotState;
#endif 