

#include <xc.h>
#include"conbit.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define Baud_rate 9600
#define _XTAL_FREQ 20000000

void __interrupt() routISR()
{
if(PIR1bits.RCIF==1) 
{
if(RCSTAbits.OERR)
{ 
RCSTAbits.CREN = 0;
NOP();
RCSTAbits.CREN=1;
} 


PIR1bits.RCIF=0;
TXREG=(RCREG +1);
while(TXSTAbits.TRMT==0);
}

}
void MSdelay(unsigned int val)
{
unsigned int i,j;
for(i=0;i<=val;i++)
for(j=0;j<81;j++); 
}
void UART_Initialize()
{

TRISC.RC6=0;
TRISC.RC7=1;
// sets baud rate9600
SPBRG= 31; // store value for 9600 baud rate
TXSTAbits.CSRC = 0; // Don't care for asynchronous mode
TXSTAbits.TX9 = 0; // Selects 8-bit data transmission
TXSTAbits.TXEN = 1; // Enable Data tranmission on RC6 pin
TXSTAbits.SYNC = 0; // Selects Asynchronous Serial Communication Mode
TXSTAbits.BRGH = 0; // Default Baud rate speed 
BAUDCONbits.BRG16 = 0; // selects only 8 bit register for baud rate 
RCSTA = 0x90; // Enables UART Communication PORT

}
void main(void) {
OSCCON=0x72; // Select internal oscillator with frequency = 8MHz
INTCONbits.GIE=1;//global interrupt
INTCONbits.PEIE=1;
PIR1bits.RCIF=0;
PIE1bits.RCIE=1;//enable received interrupt 
IPR1bits.RCIP=1;
UART_Initialize();
while(1)
    ;
{
    //empty
}
 return;
}
