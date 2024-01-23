/*
 * File:   main.c
 * Author: mathias & thibaut
 *
 * Created on 9 janvier 2024, 13:40
 */


#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

#define DIR_LED1 TRISDbits.TRISD0

#define DIR_POTO TRISAbits.TRISA0

#define LED1 PORTDbits.RD0

#define POTO PORTAbits.RA0

void init() {
    DIR_LED1 = 0;
    
    DIR_POTO = 1;
    
    ANSELAbits.ANSA0 = 1; 
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = 0;
    ADCON1bits.ADCS = 0;
    ADCON1bits.ADNREF = 0;
    ADCON1bits.ADPREF = 0;
    ADCON1bits.ADFM = 0;
    ADCON0bits.GO_nDONE = 1;
    
    ANSELBbits.ANSB0 = 0;
    
    //CCPTMRSbits.P4TSEL = 0;  // Met sur timer 2 PWM4 page 289
    PWM4CONbits.PWM4EN = 1;  // Active PWM module
    
    //Init timer2
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2OUTPS = 0;
    T2CONbits.T2CKPS = 0;
}

void ad_read() {
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO);
    PWM4DCH = ADRESH;
    PWM4DCL = ADRESL;
}

void main(void) {
    /* Code d'initialisation */
    init();
    while(1){
        /* Code a executer dans une boucle infinie */
        ad_read();
        PIR1bits.TMR2IF = 0;
        while (PIR1bits.TMR2IF != 1);
        RD0PPSbits.RD0PPS = 0x0F;
    }
}
