/*
 * File:   executaSeq.c
 * Author: 18175218
 *
 * Created on 26 de Novembro de 2019, 14:41
 */


#include <xc.h>
#include "atuadores.h"
#include "fifo.h"
#include "timer0.h"

unsigned char execSeq = 0;
unsigned int passo = 0;
unsigned int tSeq;
unsigned char pauseStop = 0;



void executarPauseStopSeq( void )
{
    ++pauseStop;
}

void executarSeqRestart( void )
{
    pauseStop = 0;
}

void executarSeq( void )
{
    execSeq = 10;
    restartFIFO();
    executarSeqRestart();
}

void resetSeq( void )
{
    atuador.ABCD = 0;
}

unsigned char fimSeq( void ) 
{
    return( !execSeq );
}

unsigned char printExec( void )
{
    if( execSeq == 10 )
        return( 1 );
    else
        return( 0 );
}

void executaSeqScan( void )
{
    switch( execSeq )
    {
        case 0:
                break;
        case 10:
            if( pauseStop == 0 )
                execSeq = 14;
            else if( pauseStop == 1 )
                execSeq = 11;
            else
                execSeq = 12;
            break;
        case 11:
            if( pauseStop == 0 )        // run
                execSeq = 14;
            else if( pauseStop > 1 )    // stop
                execSeq = 12;
            break;
        case 12:
            restartFIFO();
            resetSeq();
            execSeq = 0;
            break;
        case 14:
                passo = getFIFO();
                
                execSeq = 15;
                break;
                
        case 15:
                switch( passo )
                {
                    case 'A':   execSeq = 100;  break;
                    case 'B':   execSeq = 110;  break;
                    case 'C':   execSeq = 120;  break;
                    case 'D':   execSeq = 130;  break;
                    case 'a':   execSeq = 230;  break;
                    case 'b':   execSeq = 240;  break;
                    case 'c':   execSeq = 250;  break;
                    case 'd':   execSeq = 150;  break;

                    case '1':   
                    case '2':   
                    case '3':   
                    case '4':   
                    case '5':   
                    case '6':   
                    case '7':   
                    case '8':   
                    case '9':   
                                tSeq = (passo - '0') * 1000;
                                execSeq = 140;
                                break;
                    default:    execSeq = 0;    
                                restartFIFO();
                                break;
                }
                break;

        case 100: // A+
                atuador.A = 1;
                execSeq = 101;
                break;
        case 101:
                if( sensor.A1 == 1)
                    execSeq = 10;
                break;
        case 230: // A-
                atuador.A = 0;
                execSeq = 231;
                break;
        case 231:
                if( sensor.A0 == 1)
                    execSeq = 10;
                break;        

        case 110: // B+
                atuador.B = 1;
                execSeq = 111;
                break;
        case 111:
                if( sensor.B1 == 1)
                    execSeq = 10;
                break;
        case 240: // B-
                atuador.B = 0;
                execSeq = 241;
                break;
        case 241:
                if( sensor.B0 == 1)
                    execSeq = 10;
                break;        

        case 120: // C+
                atuador.C = 1;
                execSeq = 121;
                break;
        case 121:
                if( sensor.C1 == 1)
                    execSeq = 10;
                break;
        case 250: // C-
                atuador.C = 0;
                execSeq = 251;
                break;
        case 251:
                if( sensor.C0 == 1)
                    execSeq = 10;
                break;        

        case 130: // D+
                atuador.D = 1;
                execSeq = 131;
                break;
        case 131:
                execSeq = 10;
                break;
        case 150: // D-
                atuador.D = 0;
                execSeq = 151;
                break;
        case 151:
                execSeq = 10;
                break;
        case 140:// temporização 1 - 9 segundos 
                setT0( tSeq );
                execSeq = 141;
                break;
        case 141:
                if( !statusT0() )
                    execSeq = 10;
                break;

    }
}