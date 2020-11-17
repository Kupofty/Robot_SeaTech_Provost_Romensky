#ifndef TIMER_H
#define TIMER_H
extern unsigned long timestamp;
void InitTimer23(void);
void InitTimer1(float freq);
void InitTimer4(float freq);
void SetFreqTimer4(float freq);
void SetFreqTimer1(float freq);
#endif 