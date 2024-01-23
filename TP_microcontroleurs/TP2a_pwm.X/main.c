/*
 * File:   main.c
 * Author: mathias & thibaut
 *
 * Created on 9 janvier 2024, 11:44
 */


#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define DIR_LED1 TRISDbits.TRISD0
#define DIR_BUT1 TRISBbits.TRISB0

#define LED1 PORTDbits.RD0


void init() {
    DIR_LED1 = 0;
    DIR_BUT1 = 1;
    LED1 = 1;
    ANSELBbits.ANSB0 = 0;
    
    //CCPTMRSbits.P4TSEL = 0;  // Met sur timer 2 PWM4 page 289
    PWM4CONbits.PWM4EN = 1;  // Active PWM module
    
    //Init timer2
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2OUTPS = 0;
    T2CONbits.T2CKPS = 0;
}


void main(void) {
    /* Code d'initialisation */
    init();
    
    while(1){
        
        if (!PORTBbits.RB0) {
            PWM4DCH = 256;
            PWM4DCLbits.PWM4DCL = 3; 
            PIR1bits.TMR2IF = 0;
            while (PIR1bits.TMR2IF != 1);
            RD0PPSbits.RD0PPS = 0x0F;
            
        } else {
            PWM4DCH = 25;
            PWM4DCLbits.PWM4DCL = 2;
            PIR1bits.TMR2IF = 0;
            while (PIR1bits.TMR2IF != 1);
            RD0PPSbits.RD0PPS = 0x0F;
            
        }
    }
}