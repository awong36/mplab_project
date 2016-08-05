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

#include <stdint.h>          /* For uint16_t definition                       */
#include <stdbool.h>         /* For true/false definition                     */
#include "user.h"            /* variables/params used by user.c               */
#include "uart.h"
#include "system.h"


#include <PPS.h>
/******************************************************************************/
/* User Functions                                                             */
/******************************************************************************/

/* <Initialize variables in user.h and insert code for user algorithms.> */

void InitApp(void)
{
    /* TODO Initialize User Ports/Peripherals/Project here */

    /* Setup analog functionality and port direction */
    // output
           led1_pin=0;
           led2_pin=0;
           led3_pin=0;
           led4_pin=0;
           burner1_pin=0;
           burner2_pin=0;
           motor_rst_pin=0;

           an_add0_pin=0;
           an_add1_pin =0;
           an_add2_pin =0;


     // input
           button0_pin=1;
           button1_pin=1;

           pos_a_pin = 1;
           pos_b_pin = 1;




    /* AN10 configured analog input ANA_TEMP */
    ANSELBbits.ANSB10 = 1;
    TRISBbits.TRISB10 = 1;
    /* AN11 configured analog input VMON_24V */
    ANSELBbits.ANSB11 = 1;
    TRISBbits.TRISB11 = 1;
    /*AN12 configured analog input VMON_3.3V */
    ANSELBbits.ANSB12 = 1;
    TRISBbits.TRISB12 = 1;
    /*AN13 configured analog input VMON_5V */
    ANSELBbits.ANSB13 = 1;
    TRISBbits.TRISB13 = 1;
    /*AN14 configured analog input VMON_12V */
    ANSELBbits.ANSB14 = 1;
    TRISBbits.TRISB14 = 1;

    /* Initialize peripherals */
}

void InitUart(void){

#define BAUDRATE  115200L



TRISDbits.TRISD15=0;
TRISGbits.TRISG8=0;
TRISDbits.TRISD14=1;
//Initialze UART1
RPINR18bits.U1RXR  = 78;       /*RPI78 configured as UART1 RX for MODBUS_UI_RX*/
RPOR4bits.RP79R   = 0b000001; /*RP79 configured as UART1 TX for MODBUS_UI_TX */
RPOR14bits.RP120R = 0b000010; /*RP120 configured as UART1_RTS for MODBUS_UI_TXEN */


const double Baudrate = ( double )FCY / ( 16 * BAUDRATE ) - 1;
unsigned int baudrate = ( unsigned int )( Baudrate + 0.5 );
U1MODEbits.STSEL = 0; // 1-Stop bit
U1MODEbits.PDSEL = 0; // No Parity, 8-Data bits
U1MODEbits.ABAUD = 0; // Auto-Baud disabled
U1MODEbits.BRGH = 0; // Standard-Speed mode
U1STAbits.OERR    = 0;           //Clear the Receive //Overflow Flag.
IFS0bits.U1RXIF   = 0;           //Clear the UART1 Receive //Interrupt flag.
U1BRG = baudrate; // Baud Rate setting fogr 115200
U1STAbits.UTXISEL0 = 0; // Interrupt after one TX character is transmitted
U1STAbits.UTXISEL1 = 0;
IEC0bits.U1TXIE = 1; // Enable UART TX interrupt

U1MODEbits.RTSMD = 1; // U1RTS in simplex mode
U1MODEbits.UEN = 0b01; // RTS used and RTS pin is enabled, CTS is not used


 U1STAbits.URXISEL = 0; // Interrupt after one RX character is received;
 IEC0bits.U1RXIE = 1; // Enable UART RX interrupt

U1MODEbits.UARTEN = 1; // Enable UART
U1STAbits.UTXEN = 1; // Enable UART TX


}

void InitAct(void){
Act_PWM_PIN=0;
Act_DIR_PIN=0;
Act_CUR_PIN=0;

}

