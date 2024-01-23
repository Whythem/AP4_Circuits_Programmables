/*
 * File:   main.c
 * Author: mathias & thibaut
 *
 * Created on 9 janvier 2024, 13:40
 */


#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define DIR_LED1 TRISDbits.TRISD0

#define LED1 PORTDbits.RD0

void init() {
    DIR_LED1 = 0;

    ANSELBbits.ANSB0 = 0;
    
    //CCPTMRSbits.P4TSEL = 0;  // Met sur timer 2 PWM4 page 289
    PWM4CONbits.PWM4EN = 1;  // Active PWM module
    RD0PPSbits.RD0PPS = 0x0F;
    
    //Init timer2
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2OUTPS = 7;
    T2CONbits.T2CKPS = 0;
    PR2 = 244;
}

void main(void) {
    /* Code d'initialisation */
    init();
    
    
    while(1){
        for (int i = 0; i < 1024; i++) {
            PWM4DCH = i >> 2;
            PWM4DCLbits.PWM4DCL = i &3;
            while(PIR1bits.TMR2IF == 0);
            PIR1bits.TMR2IF = 0;
        }
        for (int i = 1024; i > 0; i--) {
            PWM4DCH = i >> 2;
            PWM4DCLbits.PWM4DCL = i &3;
            while(PIR1bits.TMR2IF == 0);
            PIR1bits.TMR2IF = 0; 
        }
    }
}
