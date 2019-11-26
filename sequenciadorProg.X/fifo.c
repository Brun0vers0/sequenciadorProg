/*
 * File:   fifo.c
 * Author: curtaeletronica
 *
 * Created on 8 de Outubro de 2019, 12:18
 */


#include <xc.h>

#include "fifo.h"

#define FIFO_SIZE 16

unsigned char fifo[FIFO_SIZE];
unsigned char fifoHead = 0;
unsigned char fifoTail = 0;

void putFIFO( unsigned char c )
{
    fifo[ fifoHead ] = c;
    ++fifoHead;
}

unsigned char getFIFO( void )
{
    unsigned char aux = 0;
    
    if( fifoTail != fifoHead )
    {
        aux = fifo[ fifoTail ];
        ++fifoTail;        
    }
    return( aux );
}

unsigned char statusFIFO( void )
{
    return( (fifoHead - fifoTail) % FIFO_SIZE );
}

void * displayFIFO( void )
{
    return( fifo );
}   

unsigned char delFIFO( unsigned char n )
{
    unsigned char ret;
    while( n && fifoHead )
    {
        --fifoHead;
        ret = fifo[fifoHead];
        fifo[ fifoHead ] = 0;
        --n;
    }
    return( ret );
}

void resetFIFO (void)
{
    delFIFO(16);
    fifoHead = 0;
    fifoTail = 0;
}

void restartFIFO (void)
{
    fifoTail = 0;         
}