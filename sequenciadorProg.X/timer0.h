/* 
 * File:   timer0.h
 * Author: Dedê
 *
 * Created on 26 de Novembro de 2019, 14:11
 */

#ifndef TIMER0_H
#define	TIMER0_H

void initTimer0();
void intt0_1ms( void );
void setT0( int c );
int statusT0( void );
void setT0limite( int c );
int statusT0limite( void );

#endif	/* TIMER0_H */

