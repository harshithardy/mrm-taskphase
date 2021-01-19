/* 
 * File:   newmain.c
 * Author: LENOVO
 *
 * Created on January 20, 2021, 2:18 AM
 */

#include <stdio.h>
#include <stdlib.h>
#include<xc.h>
#define _XTAL_FREQ 20000000
#include "config.h"


void Timer0Delay(void);       //Delay Function

int main(int argc, char** argv) {

    TRISB=0x00;               //Port-B as Output
      
    while(1){
        PORTB= ~PORTB;       //Toggle Output
        Timer0Delay();       //Delay
    }
    return (EXIT_SUCCESS);
}

void Timer0Delay(void){     //1sec delay
    T0CON=0x07;             //Timer-1 16-bit mode Prescaler 1:256
    TMR0H=0xB3;             //Count Hight Byte
    TMR0L=0xB4;             //Count Low Byte
    
    T0CON.TMR0ON=1;              //Run timer
    while(INTCON.TMR0IF==0);     //Wait for flag to over flow
    T1CON.TMR0ON=0;              //Switch off timer
    INTCON.TMR0IF=0;             //Clear Interrupt
    

}
void interrupt MY_ISR(void)
{
    TMR0IF=0;
    PORTB=1;
    _delay_us(3);
    PORTB =0;
}

