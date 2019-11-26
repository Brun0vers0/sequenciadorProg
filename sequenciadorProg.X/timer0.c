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

int t0cont = 0;


void setT0( unsigned int c )
{
    t0cont = c;
    INTCONbits.T0IE = 1;
}

int statusT0( void )
{
    return( t0cont );
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

    INTCONbits.T0IE = 0;
    INTCONbits.GIE = 1;
}

