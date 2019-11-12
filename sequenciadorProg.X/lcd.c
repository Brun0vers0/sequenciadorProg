/* 
 * File:   lcd.c
 * Author: 18175242
 *
 * Created on 22 de Agosto de 2019, 16:03
 */

#include <xc.h>
#include "config.h"
#include "lcd.h"
#include "fifo.h"


volatile  LCDbits_t LCD __at(0x008);  

const char indPassosSize = 5;
const char indicePassos[] = {0,3,7,11,14};


void initLCD( void )
    {
        LCD.B0  = 0;
        LCD.B1  = 0;
        LCD.RS  = 0;
        LCD.BUS = 0x3;
        LCD.EN  = 1;
        TRISD = 0xC0;
        
        __delay_ms(100);
        
        cmdLCD(LCD_DATA_BITS_4);
        cmdLCD(LCD_LINE2);
        cmdLCD(LCD_ON);
        cmdLCD(LCD_CLEAR);
        cmdLCD(LCD_HOME);
        
        __delay_ms(100);
    }

void cmdLCD( unsigned char cmd )
{
        volatile REGnibble_t nibble;
   
        nibble.HILO = cmd;
        LCD.RS = 0;
        LCD.BUS = nibble.HI ;
         LCD.EN = 0;
        if( cmd == LCD_CLEAR || cmd == LCD_HOME )   
        __delay_ms(2);
        else 
        __delay_us(40);    
        LCD.EN = 1;
   
        if( cmd != (LCD_DATA_BITS_4) )
    {
       LCD.RS = 0;
       LCD.BUS = nibble.LO;
       LCD.EN = 0;
       if( cmd == LCD_CLEAR || cmd == LCD_HOME )
            __delay_ms(2);
       else
            __delay_us(40);    
       LCD.EN = 1;
    }
}
void putLCD( unsigned char c )
 {
        volatile REGnibble_t nibble;
   
        nibble.HILO = c;
        LCD.RS = 1;
        LCD.BUS= nibble.HI;
        LCD.EN = 0;
        __delay_ms(2);
        LCD.EN = 1;

        LCD.RS = 1;
        LCD.BUS = nibble.LO;
        LCD.EN = 0;
        __delay_ms(2);
        LCD.EN = 1;
}
void gotoxy( unsigned char x, unsigned char y )
{
        cmdLCD((LCD_GOTOL0 | LCD_GOTOL1 * y) + (x & 0X3F));    
}
void writeLCD( unsigned char x, unsigned char y, const char * ptr )
{
        gotoxy(x,y);
        while( *ptr )
        putLCD( *ptr++ );    
}

char lcdb0(void)
{
    return(LCD.B0);
}
char lcdb1(void)
{
    return(LCD.B1);
}

void clearLCD( void )
{
    cmdLCD(0x01);
}


int checktecla (void)
{
    char linha2[17] = "      [  ]      ";
    char aux;
            for( char i=0; i<indPassosSize; i++ )
    {
        aux = getFIFO();
        if(aux>= '0' && aux<= '9')
        {
            linha2[i] = aux;
            linha2[i+1] = 's';
        }    
        else if( aux & 0x20 ) // Minusculo
        {
            linha2[i] = aux & ~0x20;
            linha2[i+1] = '-';
        }
        else if ( aux )
        {
            linha2[i] = aux;
            linha2[i+1] = '+';
        }
            writeLCD(0,1,linha2);
    }
}

void screen_car (void)
{
    writeLCD(2,0,"SEQUENCIADOR");
    __delay_ms(200);
    writeLCD(2,1,"PROGRAMAVEL");
    __delay_ms(2000);
    clearLCD();
}

void screen_menu (void)
{
    writeLCD(0,0,"INSIRA A SEQUEN.");
}
