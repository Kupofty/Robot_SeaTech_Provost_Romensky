#ifndef CB_TX1_H
#define CB_TX1_H

void CB_TX1_Add(unsigned char value);
void SendMessage(unsigned char* message, int length);
unsigned char CB_TX1_Get(void);
void SendOne();
unsigned char CB_TX1_IsTransmitting(void);
int CB_TX1_RemainingSize(void);

#endif