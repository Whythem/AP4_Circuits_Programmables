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
    RXPPSbits.RXPPS = 31; //Connexion RC7 à RXPPS p.153
    
    TRISCbits.TRISC6 = 0; //sortie
    TRISCbits.TRISC7 = 1; // entrée
    ANSELCbits.ANSC7 = 0; // numérique
    
    TX1STAbits.SYNC = 0;
    TX1STAbits.BRGH = 0; // low speed p.363
    BAUD1CONbits.BRG16 = 1;
    SP1BRGHbits.SP1BRGH = 0; // Octet haut
    SP1BRGLbits.SP1BRGL = 51; // Octet bas
    
    RC1STAbits.SPEN = 1; //Activation pins
    TX1STAbits.TXEN = 1; // Activation transmitter
    RC1STAbits.CREN = 1; //Activation receiver
}

void delay() {
    while(PIR1bits.TMR2IF == 0) {    
    }
    PIR1bits.TMR2IF = 0; 
}

void main(void) {
    /* Code d'initialisation */
    init();
    
    T2CONbits.TMR2ON = 1;
    T2CONbits.T2OUTPS = 7;
    T2CONbits.T2CKPS = 0;
    

}
