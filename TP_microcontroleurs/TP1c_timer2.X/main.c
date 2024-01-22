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

void delay_timer2() {
    for (int i = 0; i <= 500; i++) {
        while(PIR1bits.TMR2IF == 0) {    
        }
        PIR1bits.TMR2IF = 0; 
    }
}


void main(void) {
    /* Code d'initialisation */
    init_leds();
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2OUTPS = 0;
    T2CONbits.T2CKPS = 2;
    PR2 = 249;
    while(1){
        /* Code a executer dans une boucle infinie */
        DIR_LED1 = 1;
        delay_timer2();
        DIR_LED1 = 0;
        DIR_LED2 = 1;
        delay_timer2();
        DIR_LED2 = 0;
        DIR_LED3 = 1;
        delay_timer2();
        DIR_LED3 = 0;
        DIR_LED4 = 1;
        delay_timer2();
        DIR_LED4 = 0;
        DIR_LED5 = 1;
        delay_timer2();
        DIR_LED5 = 0;
        DIR_LED6 = 1;
        delay_timer2();
        DIR_LED6 = 0;
        DIR_LED7 = 1;
        delay_timer2();
        DIR_LED7 = 0;
        DIR_LED8 = 1;
        delay_timer2();
        DIR_LED8 = 0;
    }
}
