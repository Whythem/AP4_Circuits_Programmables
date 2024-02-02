/*
 * File:   main.c
 * Author: mathias & thibaut
 *
 * Created on 9 janvier 2024, 13:40
 */


#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC

void init() {
    RC6PPSbits.RC6PPS = 20; // Connexion RC6 à TX/CK  p 154.
    RXPPSbits.RXPPS = 23; //Connexion RC7 à RXPPS p.153
    
    TRISCbits.TRISC6 = 0; //sortie
    TRISCbits.TRISC7 = 1; // entrée
    ANSELCbits.ANSC7 = 0; // numérique
    
    TX1STAbits.SYNC = 0;
    TX1STAbits.BRGH = 0; // low speed p.363
    BAUD1CONbits.BRG16 = 1;
    SP1BRGHbits.SP1BRGH = 0; // Octet haut
    SP1BRGLbits.SP1BRGL = 51; // Octet bas
    
    TX1STAbits.TXEN = 1; // Activation transmitter
    RC1STAbits.CREN = 1; //Activation receiver
    RC1STAbits.SPEN = 1; //Activation pins
    
    INTCONbits.GIE = 1; // Enable all interrupts
    INTCONbits.PEIE = 1; // enable peripherals interupts
    PIE1bits.RCIE = 1;  // enable the USART receive interrupt
}

void __interrupt() isr(void) {
    TX1REG = RC1REG;
}

void main(void) {
    /* Code d'initialisation */
    init();
    while(1) {
    
    }
}
