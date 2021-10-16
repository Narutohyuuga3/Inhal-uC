#include "config.h"
#include <stdio.h>
#include <stdlib.h>
#include <pic18f24q10.h>
#include <xc.h>
#include "spi.h"
#include "warten.h"
#include "systimer.h"
#include "pwm.h"
#include "taster.h"
#include "mems_am.h"
#include "BM62.h"


#define LED_BLAU LATC1
#define TRIS_LED_BLAU TRISC1
#define ANSEL_LED_BLAU ANSELC1

#define LED_ROT LATC0
#define TRIS_LED_ROT TRISC0
#define ANSEL_LED_ROT ANSELC0


unsigned char status = 0; // (...|Standby|status|status)

void __init(void);

void __sleep(void);

void wechsleStatus(unsigned char neuStatus);

void wechsleStandby(unsigned char neuStandby);


void __interrupt(high_priority) high_isr(void) {
    
    if (TMR0IF && TMR0IE) {

        systimer_IRQ();
    
        taster_Auswertung(); // Tastendrücke auswerten
        
        TMR0IF = 0;
    }
    
    if(INT0IF && INT0IE){
        
        taster_IRQ(); 
       
        INT0IF = 0;
    }
    
    if(INT1IF && INT1IE){
        
        mems_am_IRQ();
    
        INT1IF = 0;
    }
    
    if(INT2IF && INT2IE){
        
        bm62_IRQ();
    
        INT2IF = 0;
    }
}

void __interrupt(low_priority) low_isr(void) {
    
    if (TMR2IF && TMR2IE) {
        
        pwm_IRQ();
        
        TMR2IF = 0;
    }
    
    return;
}



int main(void){
    
    __init();
    
    while(1){
        
        switch(status & 0x03){
            
            case 0: // Sleep
                
                bm62_Disable();
                //warten
                bm62_RST(); // BM62 resetten
               
                if(status & (1 << 2)){ // Wenn Standby, Wakeup durch Beschleunigung
                    
                    
                } 
                
                else{ // Wenn Aus, Wakeup nur über Taster
                    
                    
                }
                
                __sleep();
                
                wechsleStandby(1); // Standby aktivieren
                wechsleStatus(1);
                
            break;
            
            case 1: // Wake
                
                if(TASTER_GEDRUECKT[0] & (1 << 0)){
                    
                    bm62_Enable();
                    TASTER_GEDRUECKT[0] &= ~(1 << 0);
                    
                    wechsleStatus(2);
                }
                
                else if(TASTER_GEHALTEN[0] & (1 << 0)){
                    
                    bm62_Pairing();
                    TASTER_GEHALTEN[0] &= ~(1 << 0);
                    
                    wechsleStatus(2);
                }

            break;
            
            case 2: // Run
                
                if(TASTER_GEDRUECKT[0] & (1 << 0) || timerMatch & (1 << 0)){ // Ausschalten bei kurzem Tastendruck, oder Timer
                    
                    TASTER_GEDRUECKT[0] &= ~(1 << 0);
                    
                    wechsleStatus(0);
                }
                
                if(TASTER_GEHALTEN[0] & (1 << 0)){ // Bei langem Tastendruck, Standby deaktivieren und Ausschalten
                    
                    wechsleStandby(0);
                    TASTER_GEHALTEN[0] &= ~(1 << 0);
                    
                    wechsleStatus(0);
                }
                
                
                
            break;
        } 
    } 
}

void __init(void) {
    /*
    PMD0 = 0x7B; //  clock nvm an
    PMD1 = 0x7A; //  Timer  0 + 2 an
    PMD2 = 0x47; // ADC an
    PMD3 = 0xF7; // PWM4 an
    PMD4 = 0xE1; // SPI1 an
    PMD5 = 0xF1; // PWM4 an
    */
    
    TRISA = 0x03; // A 1+2 In
    ANSELA = 0x03; // A 1+2 Analog In
    ANSELB = 0x00;
    ANSELC = 0x00;
    ANSELD = 0x00;
    
    //SLRCONAbits.SLRA2 = 1;
    
    INT1PPS = 0x0c; // INT1 B1
    
    INT1IP = 0; // Int 1 low prio
    INT1EDG = 0; // Fallende Flanke
    INT1IE = 0; // Int 1 enable
    
    TRISA4 = 0;
    TRISA5 = 0;
    TRISB5 = 0;
    TRISC2 = 0;
    TRISE2 = 0;
    TRISE1 = 0;
    
    warten(100);
  
    systimer_Init();
    pwm_Init();
    spi_Init();

    
    INTCONbits.IPEN = 1; // prio enable
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;

}

void __sleep(void) {

    spi_Tris();

    systimer_Sleep();
    pwm_Sleep();
    spi_Sleep();

    INTCONbits.GIEH = 0;
    INTCONbits.GIEL = 0;
    

    INT1IE = 1; // Int 1 enable
    
    PIR0 = 0;
    PIR1 = 0;
    PIR2 = 0;
    PIR3 = 0;
    PIR4 = 0;
    PIR5 = 0;
    PIR6 = 0;
    PIR7 = 0;
    
    warten(1000);
    
    SLEEP();
  
    INT1IE = 0; // Int 1 enable
    
    __init();
 
    INTCONbits.GIEH = 1;
    INTCONbits.GIEL = 1;
}

void wechsleStatus(unsigned char neuStatus){
    
    status &= ~0x03;
    status |= neuStatus & 0x03;
}

void wechsleStandby(unsigned char neuStandby){
    
    if(neuStandby == 1){
        
        status |= (1 << 2);
    }
    
    else{
        
        status &= ~(1 << 2);
    }
}