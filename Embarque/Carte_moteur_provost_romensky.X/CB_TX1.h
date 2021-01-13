#ifndef CB_TX1_H
#define CB_TX1_H
void SendMessage(unsigned char* , int);
void CB_TX1_Add(unsigned char);
void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void);
unsigned char CB_TX1_Get(void);
void SendOne();
unsigned char CB_TX1_IsTranmitting (void);
int CB_TX1_RemainingSize (void);

