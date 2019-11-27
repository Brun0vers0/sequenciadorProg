/*
 * File:   exibeSeq.c
 * Author: 18175218
 *
 * Created on 26 de Novembro de 2019, 14:42
 */


#include <xc.h>
#include "lcd.h"
#include "fifo.h"

const char indPassosSize = 5;
const char indiceEdit[] = {0,3,6,9,13};
const char indiceExec[] = {1,5,8,11,14};
char linhaEdit[17] = "            [  ]";
char linhaExec[17] = "[  ]            ";


void telaEdicao( void )
{
    clearLCD();
    writeLCD(0,0, "     <<< Edicao]" );
    writeLCD(0,1, linhaEdit );
}
void telaExecut( void )
{
    clearLCD();
    writeLCD(0,0, "[Execucao >>>   " );
    writeLCD(0,1, linhaExec );
}

void exibeEdicao( void )
{
    char i = getHead();
    char j = 5;
    char passo = 0;

    writeLCD(0,1, linhaEdit );

    while( i && j )
    {
        --i;
        --j;
        passo = readFIFO( i );
        gotoxy(indiceEdit[j], 1);


        if( passo >= '0' && passo <= '9' )
        {
            putLCD( passo );
            putLCD('s');
        }
        else
        {
            if( passo & 0x20 ) // minuscula
            {
                putLCD( passo & ~0x20 );
                putLCD('-');
            }
            else
            {
                putLCD( passo );
                putLCD('+');
            }
        }
    }
}

void exibeExec( void )
{
    char i = getTail();
    char j = 0;
    char passo = 0;

    writeLCD(0,1, linhaExec );

    while( i<getHead() && j<5 )
    {
        passo = readFIFO( i );
        gotoxy(indiceExec[j], 1);


        if( passo >= '0' && passo <= '9' )
        {
            putLCD( passo );
            putLCD('s');
        }
        else
        {
            if( passo & 0x20 ) // minuscula
            {
                putLCD( passo & ~0x20 );
                putLCD('-');
            }
            else
            {
                putLCD( passo );
                putLCD('+');
            }
        }
        ++i;
        ++j;
    }
    
}
