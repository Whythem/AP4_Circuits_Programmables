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

#define LED1 PORTDbits.RD0
#define LED2 PORTDbits.RD1
#define LED3 PORTDbits.RD2
#define LED4 PORTDbits.RD3
#define LED5 PORTBbits.RB0
#define LED6 PORTBbits.RB1
#define LED7 PORTBbits.RB2
#define LED8 PORTBbits.RB3

int tick_count = 0;

void init_leds() {
    DIR_LED1 = 0;
    DIR_LED2 = 0;
    DIR_LED3 = 0;
    DIR_LED4 = 0;
    DIR_LED5 = 0;
    DIR_LED6 = 0;
    DIR_LED7 = 0;
    DIR_LED8 = 0;
}

void modif_led() {
    switch(tick_count) {
        //case 125: 
        //    LED1 = 0;
        //    LED2 = 1;
        //    break;
        case 250:
            LED1 = 0;
            LED2 = 1;
            break;
        //case 375:
        //    LED3 = 0;
        //    LED4 = 1;
        //    break;
        case 500:
            LED2 = 0;
            LED3 = 1;
            break;
        //case 625:
        //    LED5 = 0;
        //    LED6 = 1;
        //    break;
        case 750:
            LED3 = 0;
            LED4 = 1;
            break;
        //case 875:
        //    LED7 = 0;
        //    LED8 = 1;
        //    break;
        case 1000:
            LED4 = 0;
            LED1 = 1;
            tick_count = 0;
            break;
    }
}

void __interrupt() isr(void) {
    if (PIR1bits.TMR2IF == 1) {
        tick_count++;
        if (!(tick_count % 125)) {
            modif_led();
        }
        PIR1bits.TMR2IF = 0; // Réinitialiser le drapeau d'interruption
    }
}

void main(void) {
    /* Code d'initialisation */
    init_leds();
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2OUTPS = 7;
    T2CONbits.T2CKPS = 0;
    
    INTCONbits.GIE = 1;
    INTCONbits.PEIE = 1;
    PIE1bits.TMR2IE = 1;
    PIR1bits.TMR2IF = 1;
    
    OPTION_REGbits.PS = 3;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.TMR0CS = 0;
    
    
    PR2 = 249;
    while(1){
        LED8 = 1;
        for (int i = 0; i <= 1000; i++) {
            TMR0 = 130;
            while(INTCONbits.TMR0IF == 0){
            }
            INTCONbits.TMR0IF = 0;    
        }
        LED7 = 1;
        for (int i = 0; i <= 1000; i++) {
            TMR0 = 130;
            while(INTCONbits.TMR0IF == 0){
            }
            INTCONbits.TMR0IF = 0;    
        }
        LED6 = 1;
        for (int i = 0; i <= 1000; i++) {
            TMR0 = 130;
            while(INTCONbits.TMR0IF == 0){
            }
            INTCONbits.TMR0IF = 0;    
        }
        LED5 = 1;
        for (int i = 0; i <= 1000; i++) {
            TMR0 = 130;
            while(INTCONbits.TMR0IF == 0){
            }
            INTCONbits.TMR0IF = 0;    
        }
        
    }
}
