#include"taster.h"

void taster_Init(void){
    
    TRIS_TASTER0 = 1;
    ANSEL_TASTER0 = 0;
    
    INT0PPS = 0x0D; // INT0 auf RB5
            
    INT0IP = 1;
    PIR0bits.INT0IF = 0;
    
    taster_Wake();
}

void taster_Sleep(void){
    
    PIE0bits.INT0IE = 1;
}

void taster_Wake(void){
    
    PIE0bits.INT0IE = 0;
}

void taster_Auswertung(void){
    
    if(TASTER0 == 1){ // Wenn Taster losgelassen
        
        if(!((TASTER_GEDRUECKT[0] & (1 << 0)) | (TASTER_GEHALTEN[0] & (1 << 0)))){ // Wenn weder Gedr�ckt noch gehalten gesetzt
            
            if(TASTER_COUNTER[0] >= TASTER_KURZ){ // Wenn Schwellwert f�r Entprellung �berschritten wurde
            
                TASTER_GEDRUECKT[0] |= (1 << 0); // Gedr�ckt setzen
            }
        
            else{
            
                TASTER_COUNTER[0] = 0; // Counter zur�cksetzen
                TASTER_GESPERRT[0] &= ~(1 << 0); // Taster entsperren
            } 
        }
    }
    
    else if(TASTER0 == 0){ // Wenn Taster gedr�ckt
        
        if(TASTER_COUNTER[0] >= TASTER_LANG){ // Wenn Schwellwert f�r langes Dr�cken �berschritten wurde
            
            if(!(TASTER_GESPERRT[0] & (1 << 0))){ // Wenn Taster nicht bereits gesperrt
                
                TASTER_GEHALTEN[0] |= (1 << 0); // Gehalten setzen
                TASTER_GESPERRT[0] |= (1 << 0); // Taster sperren
            }
        }
        
        else{
            
            TASTER_COUNTER[0]++;
        }   
    }
}

void taster_IRQ(void){
    
    taster_Wake();
}
