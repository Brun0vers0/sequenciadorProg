/* 
 * File:   timer0.h
 * Author: Dedê
 *
 * Created on 26 de Novembro de 2019, 14:11
 */

#ifndef TIMER0_H
#define	TIMER0_H


extern int t0cont;


#define INT_TIMER_0()                                   \
    if( INTCONbits.T0IE && INTCONbits.T0IF )            \
    {                                                   \
        INTCONbits.T0IF = 0;                            \
        TMR0 = 256 - 250;                               \
        if( t0cont  )                                   \
        {                                               \
            --t0cont;                                   \
        }                                               \
    }                                                   \



void initTimer0();
void setT0( unsigned int c );
int statusT0( void );

#endif	/* TIMER0_H */

