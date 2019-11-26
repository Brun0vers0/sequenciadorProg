/*
 * File:   main.c
 * Author: curtaeletronica
 *
 * Created on 03 de Outubro de 2019, 08:27
 * 
 * IDE:         MPLAB X IDE v3.15
 * Compiler:    XC8 v1.45
 * OS:          Deepin 15.11 X86_64
 * Kernel:      4.15.0-30deepin-generic
 * 
 * Objetivo: 
 *      Testar as rotinas do teclado matricial 4x4 apresentando o valor 
 *      das teclas no display.
 * 
 * Pinos    |nº     |Conexão
 *  VDD     |11,32  | Alimentação (Vcc/+5V)
 *  VSS     |12,31  | Alimentação (GND/0V)
 *  RB0     |33     | L1 : 123A
 *  RB1     |34     | L2 : 456B
 *  RB2     |35     | L3 : 789C
 *  RB3     |36     | L4 : *0#D
 *  RB4     |37     | C1 : 147*
 *  RB5     |38     | C2 : 2580
 *  RB6     |39     | C3 : 369#
 *  RB7     |40     | C4 : ABCD
 *  RD0     |19     | LCD_D4 (LCD_Data 4)
 *  RD1     |20     | LCD_D5
 *  RD2     |21     | LCD_D6
 *  RD3     |22     | LCD_D7
 *  RD4     |27     | LCD_RS
 *  RD5     |28     | LCD_EN
 *  RD6     |29     | LCD_B0
 *  RD7     |30     | LCD_B1
 * 
*/

//***************** Bibliotecas
#include <xc.h>
#include "config.h"
#include "lcd.h"
#include "keyboard.h"
#include "fifo.h"
#include "serialIO.h"
#include "atuadores.h"
#include "timer0.h"
#include "executaSeq.h"
#include "exibeSeq.h"
#include "editaSeq.h"

//***************** Interrupções
void __interrupt() irq(void)
{
    INT_TIMER_0();
}



//***************** Programa Principal
void main(void)
{
    unsigned char tecla = 0;

    initLCD(); 
    screen_car();
    initKeyboard();
    initSerialIO(  &sensor, &atuador, 1 );
    //atuador.ABCD = 0x00; 
    initTimer0();
    
    while( 1 )                      // Laço de repetição infinita.
    {
//      checktecla ();
//        screen_menu ();
        keyboardScan();

        if( currentKey() && !previousKey() )
        {
            tecla = currentKey();
        }




        executaSeqScan();
        serialIOscan();
    }
}
    
//***************** Fim do Programa Principal
