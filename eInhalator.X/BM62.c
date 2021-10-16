#include "BM62.h"
#include "warten.h"

void bm62_Init(void){
    
    INT2PPS = 0x0A; // INT2 auf Port B2
    

    TRIS_WAKE_BT = 0;
    ANSEL_WAKE_BT = 0;
    WAKE_BT = 0;


    TRIS_INT_BT = 1;
    ANSEL_INT_BT = 0;
    INT_BT = 0;

    TRIS_SPK_IN = 1;
    ANSEL_SPK_IN = 0;
    SPK_IN = 0;


    TRIS_MIC_OUT = 0;
    ANSEL_MIC_OUT = 0;
    MIC_OUT = 0;

}

void bm62_IRQ(void){
    
    if(lsCount > 100){
        
        if((status & 0x03) == 2 && shaken > 0){ //PWM Signal im AN-Zustand bei geschütteltem Inhalator übertragen

            pwm_Wake();
            lsCount = 0;;
            
            INT2IE = 0; // Interrupt ausschalten
        }   
    }
    
    else{
        
        lsCount++;
    }
}

void bm62_RST(void){
    
    RST_BT = 0;
    TRIS_RST_BT = 0; 

    warten(15);

    RST_BT = 1;
    TRIS_RST_BT = 1;
    ANSEL_RST_BT = 1;
}

void bm62_Enable(void){
    
    INT2IE = 1;
    
    WAKE_BT = 1;
    
    warten(1200);
    
    WAKE_BT = 0;
}

void bm62_Pairing(void){
    
    INT2IE = 1;
    
    WAKE_BT = 1;
    
    warten(3200);
    
    WAKE_BT = 0;
}

void bm62_Disable(void){
    
    INT2IE = 0;
    
    WAKE_BT = 1;
    
    warten(2200);
    
    WAKE_BT = 0;
}