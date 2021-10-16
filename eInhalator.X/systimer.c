#include  "systimer.h"

void systimer_Init (void){
    
    IPR0bits.TMR0IP = 1; // Hohe Prio
    PIR0bits.TMR0IF = 0;
    PIE0bits.TMR0IE = 1;
    
    T0CON0bits.T016BIT = 0;
    T0CON0bits.T0OUTPS = 0;
   
    T0CON1bits.T0CS = 0b010; // CLK / 4
    T0CON1bits.T0CKPS = 0b0011; // Presc 1/8
    
    systimer_Wake();
}

void systimer_Sleep (void){
    
    T0CON0bits.T0EN = 0;
    
    for (unsigned char i = 0; i < TIMERANZAHL; i++){ // Über alle Timer iterieren
    
        if(timerSleepReset & (1 << i)){ // Schauen ob Timer genullt werden soll
            
            startTime[i] = timAkt; // Startzeit auf aktuellen Systemzeitpunkt stellen
        }
    }
}

void systimer_Wake (void){
    
    T0CON0bits.T0EN = 1;
}

void systimer_IRQ(void){
    
        timAkt ++; // globale Zählervariable erhöhen
        
        for (unsigned char i = 0; i < TIMERANZAHL; i++){ // Über alle Timer iterieren
            
            if ((startTime[i] + durationTime[i] == timAkt) && (timerActivate & (1 << i))){ 
                
                timerMatch |= (1 << i); // Timer auslösen
                timerActivate &= ~(1 << i); // Timer deaktivieren
            }
        }
    
        return;
}
