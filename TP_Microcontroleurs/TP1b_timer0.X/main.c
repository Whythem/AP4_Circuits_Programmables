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

void delay_quasi_pile_poil() {
    for (int i = 0; i <= 1000; i++) {
        TMR0 = 130;
        while(INTCONbits.TMR0IF == 0){
        }
        INTCONbits.TMR0IF = 0;    
    }
}

void main(void) {
    /* Code d'initialisation */
    init_leds();
    OPTION_REGbits.PS = 3;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.TMR0CS = 0;
    
    while(1){
        PORTD |= 15;
        PORTB &= ~15;
        delay_quasi_pile_poil();
        PORTB |= 15;
        PORTD &= ~15;
        delay_quasi_pile_poil();
    }
}