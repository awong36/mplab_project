/******************************************************************************/
/* User Level #define Macros                                                  */
/******************************************************************************/
#define led1            LATGbits.LATG15
#define led1_pin        TRISGbits.TRISG15
#define led2            LATEbits.LATE6
#define led2_pin        TRISEbits.TRISE6
#define led3            LATCbits.LATC1
#define led3_pin        TRISCbits.TRISC1
#define led4            LATCbits.LATC4
#define led4_pin        TRISCbits.TRISC4

#define burner1         LATEbits.LATE2
#define burner1_pin     TRISEbits.TRISE2
#define burner2         LATEbits.LATE4
#define burner2_pin     TRISEbits.TRISE4

#define button0         PORTFbits.RF0
#define button0_pin     TRISFbits.TRISF0
#define button1         PORTFbits.RF1
#define button1_pin     TRISFbits.TRISF1

#define motor_rst       LATCbits.LATC3
#define motor_rst_pin   TRISCbits.TRISC3

#define uart_dir LATGbits.LATG8


#define Act_PWM         LATEbits.LATE7
#define Act_PWM_PIN     TRISEbits.TRISE7
#define Act_DIR         LATCbits.LATC2
#define Act_DIR_PIN     TRISCbits.TRISC2
#define Act_CUR         LATGbits.LATG13
#define Act_CUR_PIN     TRISGbits.TRISG13


#define pos_a           PORTAbits.RA5
#define pos_a_pin       TRISAbits.TRISA5
#define pos_b           PORTAbits.RA4
#define pos_b_pin       TRISAbits.TRISA4

#define an_add2         LATAbits.LATA1
#define an_add2_pin     TRISAbits.TRISA1
#define an_add1         LATFbits.LATF13
#define an_add1_pin     TRISFbits.TRISF13
#define an_add0         LATFbits.LATF12
#define an_add0_pin     TRISFbits.TRISF12

/* TODO Application specific user parameters used in user.c may go here */

/******************************************************************************/
/* User Function Prototypes                                                   */
/******************************************************************************/

/* TODO User level functions prototypes (i.e. InitApp) go here */

void InitApp(void);         /* I/O and Peripheral Initialization */
void InitUart(void);        /* UART Initialization */
void InitAct(void);         /*ACT driver ini*/