/*
 * File:   main.c
 * Author: mathias & thibaut
 *
 * Created on 9 janvier 2024, 13:40
 */


#include "configbits.h" // Bits de configuration
#include <stdio.h>
#include <xc.h>         // Definition des registres specifiques au uC
#include "lcd.h"
#include "spi.h"

#define DIR_LED1 TRISDbits.TRISD0
#define LED1 PORTDbits.RD0

#define DIR_BUT1 TRISBbits.TRISB0

#define POTO PORTAbits.RA0

int isChiffrement;
int offset;

char texte[100];

void init(void) {
    // Init entrée
    DIR_BUT1 = 1;
    POTO = 1;
    DIR_LED1 = 0;
    ANSELBbits.ANSB0 = 0; // Passage en numérique du btn 1
    
    // Init POTO
    ANSELAbits.ANSA0 = 1; 
    ADCON0bits.ADON = 1;
    ADCON0bits.CHS = 0;
    ADCON1bits.ADCS = 0;
    ADCON1bits.ADNREF = 0;
    ADCON1bits.ADPREF = 0;
    ADCON1bits.ADFM = 0;
    ADCON0bits.GO_nDONE = 1;
    
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
    if (isChiffrement == 1) {
        sprintf(texte, "Chiffre : %d", offset);
        LCD_WriteString(texte);
    } else {
        sprintf(texte, "Dechiffre : %d", offset);
        LCD_WriteString(texte);
    }
}

int transformCesar(int value, int offsetBis) {
    int retour;
    if (isChiffrement == 1) {
        if (value < 58) {
            if (value + offsetBis >= 58) {
                offsetBis = offsetBis - (58 - value);
                retour = transformCesar(97, offsetBis);
            } else {
                retour = value + offsetBis;
            }
        } else {
            if (value + offsetBis >= 123) {
                offsetBis = offsetBis - (123 - value);
                retour = transformCesar(48, offsetBis);
            } else {
                retour = value + offsetBis;
            }
        }
    } else {
        if (value > 96) {
            if (value - offsetBis <= 96) {
                offsetBis = offsetBis - (value - 96);
                retour = transformCesar(57, offsetBis);
            } else {
                retour = value - offsetBis;
            }
        } else {
            if (value - offsetBis <= 47) {
                offsetBis = offsetBis - (value - 47);
                retour = transformCesar(122, offsetBis);
            } else {
                retour = value - offsetBis;
            }
        }
    }
            
    return retour; 
}


void __interrupt() isr(void) {
    // TODO verif correct 
    char tmp = RC1REG;
    
    //verif 0 à z
    if ((int)tmp > 64 && (int)tmp < 91) {
        tmp = (char)((int)tmp + 32);
    } 
    
    if (!((int)tmp < 48 || (int)tmp > 123 || ((int)tmp > 57 && (int)tmp < 97))) {
        
        TX1REG = (char)transformCesar((int)tmp, offset);
    }
}

int ad_read() {
    ADCON0bits.ADGO = 1;
    while(ADCON0bits.ADGO);
    return ADRESH;
}

void main(void) {
    /* Code d'initialisation */
    
    init();
    
    offset = 1;
    isChiffrement = 1;
    setTexteLed();
    while(1) {
        if (!PORTBbits.RB0) {
            //Changement chiffrement ou déchiffrement
            if (isChiffrement == 1) {
                isChiffrement = 0;
                setTexteLed();
            } else {
                isChiffrement = 1;
                setTexteLed();
            }
            while (!PORTBbits.RB0) {
            }
        }
        
        //offset = 35 max
        int value = ad_read();
        if ((int)(value / 7.5 +1) != (int)offset) {
            offset = (int)((double)value / 7.5)+1;
            setTexteLed();
        }
    }
}
