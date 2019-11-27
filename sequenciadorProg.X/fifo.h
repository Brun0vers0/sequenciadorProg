#ifndef FIFO_H
#define FIFO_H

void putFIFO( unsigned char c );
unsigned char getFIFO( void );
unsigned char statusFIFO( void );
void * displayFIFO( void );
unsigned char delFIFO( unsigned char n );
void resetFIFO (void);
void restartFIFO (void);
unsigned char getHead( void );
unsigned char getTail( void );
unsigned char readFIFO( unsigned char p );

#endif
