
// CONFIG1L
#pragma config WDTEN = OFF      // Watchdog Timer (Disabled - Controlled by SWDTEN bit)
#pragma config PLLDIV = 1       // PLL Prescaler Selection (No prescale (4 MHz oscillator input drives PLL directly))
#pragma config CFGPLLEN = OFF   // PLL Enable Configuration Bit (PLL Disabled)
#pragma config STVREN = ON      // Stack Overflow/Underflow Reset (Enabled)
#pragma config XINST = ON       // Extended Instruction Set (Enabled)

// CONFIG1H
#pragma config CPUDIV = OSC1    // CPU System Clock Postscaler (No CPU system clock divide)
#pragma config CP0 = OFF        // Code Protect (Program memory is not code-protected)

// CONFIG2L
#pragma config OSC = ECPLL      // Oscillator (EC+PLL (CLKO-RA6), USB-EC+PLL)
#pragma config SOSCSEL = HIGH   // T1OSC/SOSC Power Selection Bits (High Power T1OSC/SOSC circuit selected)
#pragma config CLKOEC = ON      // EC Clock Out Enable Bit  (CLKO output enabled on the RA6 pin)
#pragma config FCMEN = ON       // Fail-Safe Clock Monitor (Enabled)
#pragma config IESO = ON        // Internal External Oscillator Switch Over Mode (Enabled)

// CONFIG2H
#pragma config WDTPS = 32768    // Watchdog Postscaler (1:32768)

// CONFIG3L
#pragma config DSWDTOSC = INTOSCREF// DSWDT Clock Select (DSWDT uses INTRC)
#pragma config RTCOSC = T1OSCREF// RTCC Clock Select (RTCC uses T1OSC/T1CKI)
#pragma config DSBOREN = ON     // Deep Sleep BOR (Enabled)
#pragma config DSWDTEN = ON     // Deep Sleep Watchdog Timer (Enabled)
#pragma config DSWDTPS = G2     // Deep Sleep Watchdog Postscaler (1:2,147,483,648 (25.7 days))

// CONFIG3H
#pragma config IOL1WAY = ON     // IOLOCK One-Way Set Enable bit (The IOLOCK bit (PPSCON<0>) can be set once)
#pragma config ADCSEL = BIT10   // ADC 10 or 12 Bit Select (10 - Bit ADC Enabled)
#pragma config MSSP7B_EN = MSK7 // MSSP address masking (7 Bit address masking mode)

// CONFIG4L
#pragma config WPFP = PAGE_127  // Write/Erase Protect Page Start/End Location (Write Protect Program Flash Page 127)
#pragma config WPCFG = OFF      // Write/Erase Protect Configuration Region  (Configuration Words page not erase/write-protected)

// CONFIG4H
#pragma config WPDIS = OFF      // Write Protect Disable bit (WPFP<6:0>/WPEND region ignored)
#pragma config WPEND = PAGE_WPFP// Write/Erase Protect Region Select bit (valid when WPDIS = 0) (Pages WPFP<6:0> through Configuration Words erase/write protected)
#pragma config LS48MHZ = SYS48X8// Low Speed USB mode with 48 MHz system clock bit (System clock at 48 MHz USB CLKEN divide-by is set to 8)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
#include <xc.h>
#include<stdio.h>
#include<stdlib.h>
#define _XTAL_FREQ 80000000
#define TMR2PRESCALE 4


long PWM_freq=5000;
   
    PWM_Initialize()
{
  PR2 = (_XTAL_FREQ/(PWM_freq*4*TMR2PRESCALE)) - 1;
    OSCCON=0x72;         /* set internal clock to 8MHz */
    TRISC.TRISC2=0;  /* Set CCP1 pin as output for PWM out */
    T2CON=0;             /* no pre-scalar,timer2 is off */
    TMR2=0;
    T2CON.TMR2ON=1;  /* Turn ON Timer2 */ 
  
    
}

PWM_Duty(unsigned int duty)
{
      if(duty<1023)
  {

    duty = ((float)duty/1023)*(_XTAL_FREQ/(PWM_freq*TMR2PRESCALE)); // On reducing //duty = (((float)duty/1023)*(1/PWM_freq)) / ((1/_XTAL_FREQ) * TMR2PRESCALE);
    CCPR1L=1;  /* load duty cycle */
    CCP1CON=0x0C;        /* set PWM mode and no decimal value for PWM */
  }
}

void ADC_Initialize()
{
  
    ADCON0=0b11000111;
    ADCON1=0b10110101;
}
unsigned int ADC_Read(unsigned char channel)
{
  ADCON0 &= 0b11000101; //Clearing the Channel Selection Bits
  ADCON0 |= channel<<3; //Setting the required Bits
  __delay_ms(50); //Acquisition time to charge hold capacitor
  ADCON0.GO_nDONE=1; // initialize a/d conversion//
   while(ADCON0.GO_nDONE==1); //Wait for A/D Conversion to complete
      return( ADRESL + ADRESH*256);
  
}

void main()
{
    int adc_value;
   TRISB = 0x00;//setting port b as output port
    PORTB = 0xff//setting port b as high
    
    TRISA = 0; // setting port a input port
    
     
    ADCON0=0b11000011;
    ADCON1=0b10110101;
  ADC_Initialize(); //Initializes ADC Module
  PWM_Initialize();  //This sets the PWM frequency of PWM1

  do
  {
    adc_value = ADC_Read(4); //Reading Analog Channel 0 
    PWM_Duty(adc_value);
    
      __delay_ms(50); 
      
  }while(1); //Infinite Loop
  
}
  
