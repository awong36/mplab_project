/******************************************************************************/
/* Files to Include                                                           */
/******************************************************************************/
/* Device header file */
#if defined(__XC16__)
    #include <xc.h>
#elif defined(__C30__)
    #if defined(__dsPIC33E__)
    	#include <p33Exxxx.h>
    #elif defined(__dsPIC33F__)
    	#include <p33Fxxxx.h>
    #endif
#endif


#include <stdint.h>        /* Includes uint16_t definition                    */
#include <stdbool.h>       /* Includes true/false definition                  */
#include <stdio.h>
#include <stdlib.h>
#include "system.h"        /* System funct/params, like osc/peripheral config */
#include "user.h"          /* User funct/params, such as InitApp              */
#include "uart.h"




/******************************************************************************/
/* Global Variable Declaration                                                */
/******************************************************************************/


void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt( void );
void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt( void );
void Ini_val(void);
void ACT_test(void);
void Blinking(void);
void ADC_test(void);
void Blower_test(void);

//void PWM_Init(void);




char ReceivedChar= ' ';
char str[50]="\n\r";
unsigned int   *str_ptr;

unsigned int dly;
char        loop_cnt;
char         cnt;
/* i.e. uint16_t <variable_name>; */

/******************************************************************************/
/* Main Program                                                               */
/******************************************************************************/

int16_t main(void)
{

    /* Configure the oscillator for the device */
    ConfigureOscillator();

    /* Initialize IO ports and peripherals */
    InitApp();

    InitUart();
    InitAct();


    char i;
    Ini_val();
    char str[50]="\n\r";
    str_ptr=str;
    for( i=0;i<10;i++){
        putsUART1(str_ptr);
    }
    
    sprintf(str, "\n\r------Start Testing------");
    putsUART1(str_ptr);

 //           PWM_Init();
    ADC_test();

    while( 1 ){
        while( ReceivedChar == ' ' )
        {
            sprintf(str, "\n\r Blinking Test");
            putsUART1(str_ptr);
            Blinking();
        }
        while( ReceivedChar == '0' ){
            Ini_val();
        }
        while( ReceivedChar == '1' ){
            Ini_val();
            sprintf(str, "\n\r ACT TEST");
            putsUART1(str_ptr);
            ACT_test();

        }
        while( ReceivedChar == '2' ){
            Ini_val();
            sprintf(str, "\n\r ADC Test");
            putsUART1(str_ptr);
            ADC_test();

        }

        while( ReceivedChar == '3' ){
            Ini_val();
            sprintf(str, "\n\r Blower Test");
            putsUART1(str_ptr);
            Blower_test();

        }



    }
}


void Ini_val(void){
    led1=0;
    led2=0;
    led3=0;
    led4=0;
    motor_rst=0;
    burner1=0;
    burner2=0;
    Act_PWM=0;
    Act_DIR=0;
    Act_CUR=0;
}



void Blinking(void){
    sprintf(str, "\n\r 3.3V,5V,12V and 24V LEDs must be lit");
    putsUART1(str_ptr);
    sprintf(str, "\n\r DEBUG LED 1~4 must be blinking");
    putsUART1(str_ptr);
    sprintf(str, "\n\r HRTBEAT LED must be blinking");
    putsUART1(str_ptr);
        while( ReceivedChar == ' ' )
        {
            loop_cnt++;
            if(++cnt>4){cnt=0;}
            for(dly=0;dly<60000;dly++);
            switch (cnt)
            {
              case 0x0001:
                  led1=1;led2=0;led3=0;led4=0;
                  motor_rst=1;
                  //burner1=1;
                 break;
              case 0x0002:
                 led1=0;led2=1;led3=0;led4=0;
                 //burner2=1;
                 break;
              case 0x0003:
                 led1=0;led2=0;led3=1;led4=0;
                 burner1=0;
                 break;
              case 0x0004:
                 led1=0;led2=0;led3=0;led4=1;
                 burner2=0;
                  motor_rst=0;
                 break;
              default:
                  led1=0;led2=0;led3=0;led4=0;
                 break;
            }
        }
}

 void ACT_test(void)
 {
    str_ptr=str;
    int pos,dly1;
    // Pwm Ini
    PTPER = 500;
    PHASE4 = 500;
    SPHASE4 = 500;
    MDC = 150;
    DTR4 = 0;
    ALTDTR4 = 0;
    IOCON4 = 0x8C00;
    PWMCON4 = 0x0100;
    FCLCON4 = 0x0003;
    PTCON2 = 0x0000;
    /* Enable PWM Module */
    PTCON = 0x8000;
    //quadrature Ini
    RPINR14bits.QEA1R = 20; //Set RP69 (D5) as QEI1 A
    RPINR14bits.QEB1R = 21; //Set RP68 (D4) as QEI1 B
    POS1CNTH = 0;
    POS1CNTL = 0;
    QEI1CONbits.QEIEN = 1; //Turn on QEI 1

        while(ReceivedChar == '1')
        {
            pos = POS1CNTL;
            if(++dly1> 10000){
                dly1=0;
                sprintf(str, "\n\r Position: %d",pos);
                putsUART1(str_ptr);
            }
            if(pos>5000){ Act_DIR=1;}
            else if (pos< 10){Act_DIR=0;}
        }
    MDC = 0;
    PTCON = 0x0000;
 }

void ADC_test(void){


IFS0bits.AD1IF = 0;
IEC0bits.AD1IE = 0;
AD1CON1bits.ADON = 0;

AD1CON1bits.ADSIDL = 0;
AD1CON1bits.ADDMABM = 0;
AD1CON1bits.AD12B = 1;
AD1CON1bits.FORM = 0b00; //Data output format
AD1CON1bits.SSRC = 0b111; //Sample trigger source select
AD1CON1bits.SSRCG = 0;
//AD1CON1bits.SIMSAM = 1; //Simultaneous sample select
AD1CON1bits.ASAM = 1; //Sample auto-start
AD1CON1bits.SAMP = 0;
AD1CON1bits.DONE = 0;


AD1CON2bits.VCFG = 0b011; //Reference voitage select
AD1CON2bits.CSCNA = 0; //Input scan select
AD1CON2bits.CHPS = 0b00; //Channel select
AD1CON2bits.BUFS = 1; //Buffer fill status
AD1CON2bits.SMPI = 0b0000; //Sample and conversion operation
AD1CON2bits.BUFM = 0;
AD1CON2bits.ALTS = 0;

//TCY = 133 ns, TAD = 2*TCY = 266 ns, Tconv = 12*TAD, TADmin = 76 ns
AD1CON3bits.ADRC = 0; //Conversion clock source
AD1CON3bits.SAMC = 0b00000; //0 TAD
AD1CON3bits.ADCS = 0b00000001; //2*TCY = TAD

AD1CON4bits.ADDMAEN = 0;
//AD1CON4bits.DMABL = 0b000;

AD1CHS123bits.CH123SB = 0b000;
AD1CHS123bits.CH123NB = 0b000;
AD1CHS123bits.CH123NA = 0;
AD1CHS123bits.CH123SA = 0; //CH1 positive input is AN3

AD1CHS0bits.CH0NB =0 ;
AD1CHS0bits.CH0SB = 0 ;
AD1CHS0bits.CH0NA = 0;
AD1CHS0bits.CH0SA = 0xA; //CH0 positive input is AN0

//AD1CSSHbits. = ;
AD1CSSL = 0b0000000000000001;

AD1CON1bits.ADON = 1; // turn on ADC

AD1CON1bits.SAMP = 1; // Start sampling
AD1CON1bits.SAMP = 0; // Start the conversion


while(ReceivedChar == '2')
{
    str_ptr=str;
    char i;
    unsigned int adc_val[8],dly1,dly2,dly3;
         if(++dly2> 10){
            dly2=0;
            for(i=0;i<8;i++){
            switch (i)
                {
                  case 0:
                     an_add2=0;an_add1=0;an_add0=0;
                     break;
                  case 1:
                     an_add2=0;an_add1=0;an_add0=1;
                     break;
                  case 2:
                     an_add2=0;an_add1=1;an_add0=0;
                     break;
                  case 3:
                     an_add2=0;an_add1=1;an_add0=1;
                     break;
                  case 4:
                     an_add2=1;an_add1=0;an_add0=0;
                     break;
                  case 5:
                     an_add2=1;an_add1=0;an_add0=1;
                     break;
                  case 6:
                     an_add2=1;an_add1=1;an_add0=0;
                     break;
                  case 7:
                     an_add2=1;an_add1=1;an_add0=1;
                     break;
                  default:
                      an_add2=0;an_add1=0;an_add0=0;
                     break;
                }
            AD1CON1bits.SAMP = 1; // Start sampling
            AD1CON1bits.SAMP = 0; // Start the conversion
            for(dly3=0;dly3<10000;dly3++);
            while(IFS0bits.AD1IF == 0);
            adc_val[i]=ADC1BUF0;
//            if(adc_val[i]>ADC1BUF0){adc_val[i]--;}
//            else if(adc_val[i]<ADC1BUF0){adc_val[i]++;}
            }
        }
    sprintf(str, "\n\r ---------------TC Reading----------");
    putsUART1(str_ptr);
    sprintf(str, "\n\r");
    putsUART1(str_ptr);
    sprintf(str, "\n\r%d,%d,%d,%d,%d,%d,%d,%d",adc_val[0],
            adc_val[1],adc_val[2],adc_val[3],adc_val[4],adc_val[5],
            adc_val[6],adc_val[7]);
    putsUART1(str_ptr);

}

}


void Blower_test(void){
    str_ptr=str;
    int pos,dly1;
    // Pwm Ini

    RPOR4bits.RP80R   = 0b101001; /*RP80 configured as OC13 for BURNER_FAN_A_SPEED_PWM */
    RPOR15bits.RP126R = 0b101010; /*RP126 configured as OC14 for BURNER_FAN_B_SPEED_PWM*/

    PTPER = 500;
    PHASE4 = 500;
    SPHASE4 = 500;
    MDC = 150;
    DTR4 = 0;
    ALTDTR4 = 0;
    IOCON4 = 0x8C00;
    PWMCON4 = 0x0100;
    FCLCON4 = 0x0003;
    PTCON2 = 0x0000;
    /* Enable PWM Module */
    PTCON = 0x8000;
    //quadrature Ini
    RPINR14bits.QEA1R = 20; //Set RP69 (D5) as QEI1 A
    RPINR14bits.QEB1R = 21; //Set RP68 (D4) as QEI1 B
    POS1CNTH = 0;
    POS1CNTL = 0;
    QEI1CONbits.QEIEN = 1; //Turn on QEI 1

        while(ReceivedChar == '1')
        {
            pos = POS1CNTL;
            if(++dly1> 10000){
                dly1=0;
                sprintf(str, "\n\r Position: %d",pos);
                putsUART1(str_ptr);
            }
            if(pos>5000){ Act_DIR=1;}
            else if (pos< 10){Act_DIR=0;}
        }
    MDC = 0;
    PTCON = 0x0000;


}




void __attribute__((interrupt, no_auto_psv)) _U1TXInterrupt( void )
{
IFS0bits.U1TXIF = 0; // Clear TX Interrupt flag
//U1TXREG = 'a'; // Transmit one character
}

 void __attribute__((interrupt, no_auto_psv)) _U1RXInterrupt( void )
 {
 IFS0bits.U1RXIF = 0; // Clear RX Interrupt flag
/* Check for receive errors */
 ReceivedChar = U1RXREG;
        if(U1STAbits.FERR == 1)
            {
                U1STAbits.FERR=0;
            }
                    /* Must clear the overrun error to keep UART receiving */
        if(U1STAbits.OERR == 1)
            {
                U1STAbits.OERR = 0;
             }
 }
