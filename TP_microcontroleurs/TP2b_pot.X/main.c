/*
 * File:   main.c
 * Author: mathias & thibaut
 *
 * Created on 9 janvier 2024, 13:40
 */


#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define DIR_LED1 TRISDbits.TRISD0
#define DIR_LED2 TRISDbits.TRISD1
#define DIR_LED3 TRISDbits.TRISD2
#define DIR_LED4 TRISDbits.TRISD3
#define DIR_LED5 TRISBbits.TRISB0
#define DIR_LED6 TRISBbits.TRISB1
#define DIR_LED7 TRISBbits.TRISB2
#define DIR_LED8 TRISBbits.TRISB3
#define DIR_POTO TRISAbits.TRISA0


#define LED1 PORTDbits.RD0
#define LED2 PORTDbits.RD1
#define LED3 PORTDbits.RD2
#define LED4 PORTDbits.RD3
#define LED5 PORTBbits.RB0
#define LED6 PORTBbits.RB1
#define LED7 PORTBbits.RB2
#define LED8 PORTBbits.RB3

#define POTO PORTAbits.RA0

void init() {
    DIR_LED1 = 0;
    DIR_LED2 = 0;
    DIR_LED3 = 0;
    DIR_LED4 = 0;
    DIR_LED5 = 0;
    DIR_LED6 = 0;
    DIR_LED7 = 0;
    DIR_LED8 = 0;
    
    DIR_POTO = 1;
    ANSELAbits.ANSA0 = 1; 
    
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = 0;
    ADCON1bits.ADCS = 0;
    ADCON1bits.ADNREF = 0;
    ADCON1bits.ADFM = 0;
}
void main(void) {
    /* Code d'initialisation */
    init();
    
    
    while(1){
        if (ADRESH < 150) {
            LED1 = 1;
            LED2 = 0;
            LED8 = 1;
        } else {
            LED1 = 0;
            LED2 = 1;
        }
    }
}
