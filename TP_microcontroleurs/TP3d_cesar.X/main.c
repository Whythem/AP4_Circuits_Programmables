/*
 * File:   main.c
 * Author: mathias & thibaut
 *
 * Created on 9 janvier 2024, 13:40
 */


#include "configbits.h" // Bits de configuration
#include <xc.h>         // Definition des registres specifiques au uC
#include "lcd.h"
#include "spi.h"

#define DIR_LED1 TRISDbits.TRISD0
#define LED1 PORTDbits.RD0

#define DIR_BUT1 TRISBbits.TRISB0

#define POTO PORTAbits.RA0

int isChiffrement = 1;
int offset = 1;

void init(void) {
    // Init entrée
    DIR_BUT1 = 1;
    POTO = 1;
    DIR_LED1 = 0;
    ANSELBbits.ANSB0 = 0; // Passage en numérique du btn 1
    
    // Init ecran led
    SPI_InitializePins();
    LCD_InitializePins();
    SPI_Initialize();
    LCD_Initialize();
    
    // Init UART
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

void setTexteLed() {
    LCD_Clear();
    LCD_GoTo(0,0);
    if (isChiffrement) {
        LCD_WriteString("Chiffre : ");
    } else {
        LCD_WriteString("Dechiffre : ");
    }
}

void __interrupt() isr(void) {
    // TODO chiffré ou déchiffré
    if (isChiffrement) {
        TX1REG = (char)((int)RC1REG + offset);
    } else {
        TX1REG = (char)((int)RC1REG - offset);
    }
}



void main(void) {
    /* Code d'initialisation */
    
    init();
    
    setTexteLed();
    while(1) {
        if (!PORTBbits.RB0) {
            //Changement chiffrement ou déchiffrement
            if (isChiffrement) {
                isChiffrement = 0;
                setTexteLed();
            } else {
                isChiffrement = 1;
                setTexteLed();
            }
            while (!PORTBbits.RB0) {
            }
        }
        
        
    }
}
