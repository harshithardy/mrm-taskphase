/*
 * File:   spiinterface.c
 * Author: LENOVO
 *
 * Created on February 14, 2021, 3:02 PM
 */


#include <xc.h>
#include"newxc8_header.h"
#include <stdio.h>
#include <stdlib.h>
#define led_out PORTD
#define SDI TRISBbits.RB0
#define SDO TRISCbits.RC7
#define SCK TRISBbits.RB1

#define slave_rdy PORTDbits.RD4
#define slave_rdy_dir TRISDbits.RD4

void enable_Int(){

    PIE1bits.SSPIE =1;
    INTCONbits.PEIE = 1;
    PIR1bits.SSPIF = 0;
}
void setup_SPI(void){

    //Configure SPI pins for Master mode
    SDI =1; //SDI
    SDO =0; //SDO
    SCK =0; //SCK

    // Set the idle state for the clock to be low.
    SSPSTAT = 0x00;
    
    //Disable SPI Master mode, clock = fosc/4
    SSPCON1 = 0x00;
    
}

void enable_SPI(){

    SSPCON1bits.SSPEN = 1;
}
void disable_SPI(){

    SSPCON1bits.SSPEN = 0;
}

void setup_IO(void){

    //Use 4 pins to display the data. 1 pin is used to activate the slave.
    TRISDbits= 0;
    slave_rdy_dir = 0;
}
unsigned char wait_SPI(void){
    
    while(!SSPSTATbits.BF);
    
    return SSPBUF;
    
}

void sendSPI(unsigned char data){
    SSPSTATbits.BF=0;
    SSPBUF = data; //load the SSPBUF with the transmition data.
    wait_SPI(); //this method returns dummy data from slave; no need to save them.

}

unsigned char receiveSPI(){
    unsigned char data;
    SSPBUF= 0; //the data loaded on the SSPBUF are not important.
    data = wait_SPI(); //save the received data from the slave.
    return data;
}

void main(void) {

    unsigned char tx_data = 0x02;
    unsigned char rx_data = 0x00;

    slave_rdy = 1;

    enable_Int();
    
    setup_SPI();
    
    setup_IO();

    enable_SPI(); 

    led_out = tx_data; //only the low nibble is displayed on the leds.

    slave_rdy = 0;

    sendSPI(tx_data);

    led_out = 0x01;
    while(1);
    
}