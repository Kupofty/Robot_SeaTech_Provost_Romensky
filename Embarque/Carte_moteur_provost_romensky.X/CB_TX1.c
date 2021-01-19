#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "CB_TX1.h"
#define CBTX1_BUFFER_SIZE 128

int cbTx1Head;
int cbTx1Tail;
int rSize;
unsigned char cbTx1Buffer[CBTX1_BUFFER_SIZE];
unsigned char isTransmitting = 0;


void CB_TX1_Add(unsigned char value) {
    cbTx1Buffer[cbTx1Head] = value;
    cbTx1Head += 1;
    if(cbTx1Head>=CBTX1_BUFFER_SIZE)
        cbTx1Head=0;
}

void SendMessage(unsigned char* message, int length) {
    unsigned char i = 0;

    if (CB_TX1_RemainingSize() > length) {
        //On peut écrire le message
        for (i = 0; i < length; i++)
            CB_TX1_Add(message[i]);
        if (CB_TX1_IsTransmitting()==0)
            SendOne();
    }
}


unsigned char CB_TX1_Get(void) {

    unsigned char result = cbTx1Buffer[cbTx1Tail];
    cbTx1Tail += 1;
    if(cbTx1Tail>=CBTX1_BUFFER_SIZE)
        cbTx1Tail=0;
    return result;
}

void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt(void) {
    IFS0bits.U1TXIF = 0; // clear TX interrupt flag
    if (cbTx1Tail != cbTx1Head) {
        SendOne();
    } else
        isTransmitting = 0;
}

void SendOne() {
    isTransmitting = 1;
    unsigned char value = CB_TX1_Get();
    U1TXREG = value; // Transmit one character
}

unsigned char CB_TX1_IsTransmitting(void) {
    return isTransmitting;
}

int CB_TX1_RemainingSize(void) {
    //Cas H>=T
    if (cbTx1Head>= cbTx1Tail)
       rSize = CBTX1_BUFFER_SIZE - cbTx1Head + cbTx1Tail;
    else
       rSize = cbTx1Tail - cbTx1Head;
    return rSize;
}
