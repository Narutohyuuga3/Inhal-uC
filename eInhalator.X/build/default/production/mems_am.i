# 1 "mems_am.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files (x86)\\Microchip\\xc8\\v2.10\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "mems_am.c" 2
# 1 "./mems_am.h" 1
# 22 "./mems_am.h"
unsigned int shaken = 0;

unsigned int mems_am_Shake(bool reset);
void mems_am_Init(void);
void mems_am_Sleep(void);
void mems_am_IRQ(void);
unsigned char mems_am_Read(unsigned char address);
void mems_am_Write(unsigned char address, unsigned char data);
# 1 "mems_am.c" 2


unsigned int mems_am_Shake(bool reset){

    if(reset == 1){
        shaken = 0;

        return 0;
    }

    else{

        xHigh2 = mems_am_Read(0b10111011);
        xLow2 = mems_am_Read(0b10111100);
        xHigh=xHigh2;
        xLow=xLow2;
        resultX= (xHigh*256)+xLow;

        if(resultX > Threshhold_shaken || resultX < (Threshhold_shaken*(-1))){

            shaken++;
        }

        return shaken;
    }
}

void mems_am_Init(void){

    INT1PPS = 0x08;
    INT1IP = 1;
    INT1IF = 0;
}

void mems_am_Wake(void){

    INT1IE = 0;

    mems_am_Write (0x38,0b00000000);
    mems_am_Write (0x6B,0b00000100);
    mems_am_Write(0x6c,0b00000111);
}

void mems_am_Sleep(void){

    INT1IE = 1;

    unsigned char threshHold=8;

    mems_am_Write (0x70,0b01000000);
    mems_am_Write (0x6B,0b00001100);
    mems_am_Write (0x6C,0b00000111);
    mems_am_Write (0x1D,0b00001001);

    mems_am_Write (0x38,0b11100000);

    mems_am_Write (0x20,threshHold);

    mems_am_Write (0x21,threshHold);

    mems_am_Write (0x22,threshHold);

    mems_am_Write (0x69,0b11000001);

    mems_am_Write (0x19,99);

    mems_am_Write (0x6B,0b00101100);


}

void mems_am_IRQ(void){


}

unsigned char mems_am_Read(unsigned char address){

}
void mems_am_Write(unsigned char address, unsigned char data){

}
