/*
 * File:   timer0.c
 * Author: Dedê
 *
 * Created on 26 de Novembro de 2019, 14:12
 */

#include <xc.h>
#include <pic16f887.h>
#include "config.h"
#include "timer0.h"

int t0final = 0;
int t0cont = 0;

void intt0_1ms( void )
{
    TMR0 = 256 - 250;
    if( ++t0cont >= t0final )
    {
        t0cont = 0;
    }
}

void setT0( int c )
{
    t0cont = c;
}
int statusT0( void )
{
    return( t0cont );
}

void setT0limite( int c )
{
    t0final = c;
}
int statusT0limite( void )
{
    return( t0final );
}

void initTimer0( void )
{
    INTCONbits.GIE = 0;
    OPTION_REGbits.T0CS = 0;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 0;
    OPTION_REGbits.PS1 = 0;
    OPTION_REGbits.PS0 = 1;

    TMR0 = 256 - 250;

    setT0limite( 1000 );
    
    INTCONbits.T0IE = 1;
    INTCONbits.GIE = 1;
}

