#include "pwm.h"

void pwm_Sleep(void){
    
    pwmCount = 0;
    CCPR1 = 0;
    T2CONbits.ON = 0; // Timer 2 disable
}

void pwm_Init(void){

    RB3PPS = 0x05; // CCP1 B3 
    TRIS_CCP1 = 0;
    
    T2CLKCONbits.CS = 0b00001; // Fosc Clocksource
    T2CONbits.CKPS = 0b111; // /128 Prescaler
    T2PR = 0xff; // Compareregister
    T2HLT = 0x00; // Normalmode
    CCPR1 = 0;
    
    IPR4bits.TMR2IP = 0; // Niedrige Prio
    PIE4bits.TMR2IE = 1;
    PIR4bits.TMR2IF = 0;
   
    CCP1CONbits.MODE = 0xC; // CCP1 PWM
    CCP1CONbits.FMT = 0; // Right aligned
    CCP1CONbits.EN = 1; // Enable
}

void pwm_Wake(void){
    
    T2CONbits.ON = 1; // Timer 2 enable
    
    while (TMR2IF == 0);
    TMR2IF = 0;
}

void pwm_Tastgrad(unsigned char tastgrad){
    
    CCPR1 = tastgrad;
}

void pwm_IRQ(void){
    
    if(pwmCount < PWM_CYCLES){
        
        pwmCount ++;
    }
    
    else {
        
        pwm_Sleep();
    }
    
}