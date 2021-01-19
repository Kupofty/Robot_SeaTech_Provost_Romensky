#include <xc.h>
#include <stdio.h>
#include <stdlib.h>
#include "CB_RX1.h"
#define CBRX1_BUFFER_SIZE 128
int cbRx1Head ;
int cbRx1Tail ;
unsigned char cbRx1Buffer[CBRX1_BUFFER_SIZE] ;

void CB_RX1_Add(unsigned char value)
{
    if (CB_RX1_GetRemainingSize () >0)
    {
        cbRx1Buffer[cbRx1Head] = value;
        cbRx1Head += 1;
        if(cbRx1Head>=CBRX1_BUFFER_SIZE)
            cbRx1Head=0;
    }
}
unsigned char CB_RX1_Get(void)
{
    unsigned char value=cbRx1Buffer[cbRx1Tail] ;
    cbRx1Tail += 1;
    if(cbRx1Tail>=CBRX1_BUFFER_SIZE)
        cbRx1Tail=0;
    return value ;
}

unsigned char CB_RX1_IsDataAvailable(void)
    {
    if( cbRx1Head!= cbRx1Tail )
        return 1 ;
    else
        return 0 ;
    }

void __attribute__ (( interrupt,no_auto_psv )) _U1RXInterrupt(void) {
    IFS0bits.U1RXIF = 0 ; // clearRXinterruptflag
    // check for receive errors ?/
    if ( U1STAbits.FERR ==1 ) {
        U1STAbits.FERR = 0 ;
        }
    //must cleartheoverrunerrortokeepuartreceiving//
    if ( U1STAbits.OERR == 1 ) {
        U1STAbits.OERR = 0 ;
        }
    // get the data ?/
    while (U1STAbits.URXDA == 1 ) {
        CB_RX1_Add(U1RXREG) ;
        }
}

int CB_RX1_GetRemainingSize(void)
    {
    int rSizeAvailble;
    if (cbRx1Head>= cbRx1Tail)
       rSizeAvailble = CBRX1_BUFFER_SIZE - cbRx1Head + cbRx1Tail;
    else
       rSizeAvailble = cbRx1Tail - cbRx1Head;
    return rSizeAvailble;
    }
int CB_RX1_GetDataSize(void)
    {
    int rSizeRecep ;
    rSizeRecep = CBRX1_BUFFER_SIZE - CB_RX1_GetRemainingSize();
    return rSizeRecep;
    }
