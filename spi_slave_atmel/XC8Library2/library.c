/*
 * library.c
 *
 * Created: 2/17/2021 10:42:51 PM
 *  Author: LENOVO
 */ 

#include <xc.h>
#define MISO PB4

//SPI initialize
void SPISlaveInit(void)
{
	//set MISO as output
	DDRB |= (1<<PB4);
	//enable SPI and enable SPI interrupt
	SPCR = (1<<SPE)|(1<<SPIE);
}
uint8_t SPI_masterReceive()
{
	// transmit dummy byte
	SPDR = 0xFF;

	// Wait for reception complete
	while(!(SPSR & (1 << SPIF)));

	// return Data Register
	return SPDR;
}


int main(void)
{
	//initialize slave SPI
	SPISlaveInit();
	

	
	while (1)
	{
		//loop
	}
}