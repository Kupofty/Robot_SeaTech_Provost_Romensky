#include <xc.h>
#include "UART.h"
#include "ChipConfig.h"
#define BAUDRATE 115200
#define BRGVAL ( (FCY/BAUDRATE)/4)-1

void InitUART ( void) {
U1MODEbits.STSEL=0;// 1?s t o p b i t
U1MODEbits.PDSEL=0  ; // No P a ri ty , 8?data b i t s
U1MODEbits.ABAUD=0 ; // Auto?Baud Di s a bl e d
U1MODEbits.BRGH=1 ; // Low Speed mode
U1BRG = BRGVAL; // BAUD Rate S e t ti n g
U1STAbits.UTXISEL0 = 0 ; // I n t e r r u p t a f t e r one Tx c h a r a c t e r i s t r a n smi t t e d
U1STAbits.UTXISEL1 = 0 ;
IFS0bits.U1TXIF = 0 ; // c l e a r TX i n t e r r u p t f l a g
IEC0bits.U1TXIE = 1 ; // Di s a bl e UART Tx i n t e r r u p t
U1STAbits.URXISEL = 0 ; // I n t e r r u p t a f t e r one RX c h a r a c t e r i s r e c e i v e d ;
IFS0bits.U1RXIF = 0 ; // c l e a r RX i n t e r r u p t f l a g
IEC0bits.U1RXIE = 1 ; // Di s a bl e UART Rx i n t e r r u p t
U1MODEbits.UARTEN = 1 ; // Enable UART
U1STAbits.UTXEN = 1 ; // Enable UART Tx
}

void SendMessageDirect(unsigned char * message, int length)
{
    unsigned char i = 0 ;
    for (i= 0; i<length ; i++)
    {
        while(U1STAbits.UTXBF); //wait while Tx buffer full
        U1TXREG = *(message)++; // Transmit one character
    }
}

//Interruption en mode loopback
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt(void)
{
    IFS0bits.U1RXIF = 0 ; // c l e a r RX i n t e r r u p t f l a g
    //? check f o r r e c e i v e e r r o r s ?/
    if( U1STAbits .FERR == 1 ) {
        U1STAbits .FERR = 0 ;
    }
    //? must c l e a r the ove r run e r r o r t o keep u a r t r e c e i v i n g ?/
    if( U1STAbits .OERR == 1 ) {
        U1STAbits.OERR = 0 ;
        }
    //?get the data ?/
    while ( U1STAbits .URXDA == 1 ) {
    U1TXREG = U1RXREG;
    }
}
