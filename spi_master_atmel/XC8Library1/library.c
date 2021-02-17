/*
 * library.c
 *
 *  Author: LENOVO
 */ 

#include <xc.h>
#define SPI_DDR DDRB
#define CS PINB2
#define MOSI PINB3
#define MISO PINB4
#define SCK PINB5
#define SPI_trans

char data;
void SPI_mastinit()
{
	SPI_DDR =(1<<CS)|(1<<MOSI)|(1<<SCK); //set CS, MOSI and SCK to output
	SPCR = (1<<SPE)|(1<<MSTR)|(1<<SPR0) ;// enable SPI, set as master and clock  fosc/16
}

void SPImastsend(uint8_t data)
{   PORTB  &= ~(1<<CS); // 
	//send data
	SPDR = data; //load data into the buffer
	//wait until transmission
	while(!(SPSR&(1<<SPIF)));
	
	PORTB = (1<<CS); //making cs high
}

 
int myfunc(void)
{   
        //initialize master SPI 
        SPI_mastinit();
 while(1);
 
}