/*
 * File:   main.c
 * Author: mathias & thibaut
 *
 * Created on 9 janvier 2024, 11:44
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

const int delay_cycles = 20000; // NB of delay cycles

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

void delay_quasi_pile_poil() {
    for (int i = 0; i <= 100; i++) {
        TMR0 = 130;
        while(INTCON.TMR0IF == 0) {    
        }
        INTCON.TMR0IF = 0;    
    }
    
}

void main(void) {
    /* Code d'initialisation */
    init_leds();
    OPTION_REG.PS = 3;
    OPTION_REG.PSA = 0;
    OPTION_REG.TMR0CS = 1;
    
    while(1){
        PORTD |= 14;
        PORTB &= ~14;
        delay_quasi_pile_poil();
        PORTB |= 14;
        PORTD &= ~14;
        delay_quasi_pile_poil();
    }
}