# 1 "taster.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "taster.c" 2
# 1 "./taster.h" 1
# 15 "./taster.h"
unsigned int TASTER_COUNTER[1];
unsigned char TASTER_GEDRUECKT[1 + (1 / 8)];
unsigned char TASTER_GEHALTEN[1 + (1 / 8)];
unsigned char TASTER_GESPERRT[1 + (1 / 8)];






void taster_Auswertung(void);
void taster_Init(void);
void taster_IRQ(void);
# 1 "taster.c" 2


void taster_Init(void){

    TRISB5 = 1;
    ANSELB5 = 0;

    INT0PPS = 0x0D;

    INT0IP = 1;
    INT0IF = 0;

    taster_Wake();
}

void taster_Sleep(void){

    INT0IE = 1;
}

void taster_Wake(void){

    INT0IE = 0;
}

void taster_Auswertung(void){

    if(RB5 == 1){

        if(!((TASTER_GEDRUECKT[0] & (1 << 0)) | (TASTER_GEHALTEN[0] & (1 << 0)))){

            if(TASTER_COUNTER[0] >= 20){

                TASTER_GEDRUECKT[0] |= (1 << 0);
            }

            else{

                TASTER_COUNTER[0] = 0;
                TASTER_GESPERRT[0] &= ~(1 << 0);
            }
        }
    }

    else if(RB5 == 0){

        if(TASTER_COUNTER[0] >= 1000){

            if(!(TASTER_GESPERRT[0] & (1 << 0))){

                TASTER_GEHALTEN[0] |= (1 << 0);
                TASTER_GESPERRT[0] |= (1 << 0);
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
