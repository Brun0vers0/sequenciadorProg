/*
 * File:   editaSeq.c
 * Author: 18175218
 *
 * Created on 26 de Novembro de 2019, 14:42
 */


#include <xc.h>
#include "fifo.h"


unsigned char a = 0, b = 0, c = 0, d = 0;
//unsigned char seqTecla;


void editaSeqScan( unsigned char seqTecla )
{
    switch( seqTecla )
    {
        case 'A':
                ++a;
                if( a % 2 )
                    putFIFO( seqTecla );   
                else
                    putFIFO( seqTecla | 0x20 );
                break;
        case 'B':
                ++b;
                if( b % 2 )
                    putFIFO( seqTecla );
                else
                    putFIFO( seqTecla | 0x20 );
                break;
        case 'C':
                ++c;
                if( c % 2 )
                    putFIFO( seqTecla );
                else
                    putFIFO( seqTecla | 0x20 );
                break;
        case 'D':
                ++d;
                if( d % 2 )
                    putFIFO( seqTecla );
                else
                    putFIFO( seqTecla | 0x20 );
                break;  
        case '1':
        case '2':
        case '3':
        case '4':
        case '5':
        case '6':
        case '7':
        case '8':
        case '9':
                putFIFO(seqTecla);
                break;  
        case '0':
                //clearLCD();
                a = b = c = d = 0;
                //atuador.ABCD = 0;
                resetFIFO();
                break;  
        case '*':
                switch( delFIFO(1) )
                {
                    case 'A':   a = 0;  break;
                    case 'a':   a = 1;  break;
                    case 'B':   b = 0;  break;
                    case 'b':   b = 1;  break;
                    case 'C':   c = 0;  break;
                    case 'c':   c = 1;  break;
                    case 'D':   d = 0;  break;
                    case 'd':   d = 1;  break;
                }
                //clearLCD();
                break;
    }
        //writeLCD(0,1, displayFIFO() );
}
