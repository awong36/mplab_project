/* 
 * File:   main.c
 * Author: kr64077
 *
 * Created on May 27, 2016, 9:36 AM
 */
#include<p30fxxxx.h>
_FOSC(CSW_FSCM_OFF & XT_PLL4);//frequency of instruction tact is same as frequency of crystal
_FWDT(WDT_OFF);

#include <stdio.h>
#include <stdlib.h>

unsigned int broj1,broj2;
/*
 * 
 */
void main(void) {
           ADPCFGbits.PCFG4=1;//configures pin B4 as digital
           ADPCFGbits.PCFG5=1;//configures pin B5 as digital
           TRISBbits.TRISB4=0;// configures pin B4 as output
           TRISBbits.TRISB5=0;//configures pin B5 as output
           TRISDbits.TRISD0=1;//configures pin DO as output
            while(1)
                     {
                           for(broj1=0;broj1<700;broj1++) //pause
                           for(broj2=0;broj2<300;broj2++);
                           LATBbits.LATB4=~LATBbits.LATB4;//inverts pin B4
                           LATBbits.LATB5=~LATBbits.LATB5;//inverts pin B5
                           LATDbits.LATD0=~LATDbits.LATD0;//inverts pin B5
                           for(broj1=0;broj1<700;broj1++)//pause
                           for(broj2=0;broj2<300;broj2++);

                    }// while

}
