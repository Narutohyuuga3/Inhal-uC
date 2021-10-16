#include"mems_am.h"

unsigned int mems_am_Shake(unsigned char reset){
    
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
   
    INT1PPS = 0x08; // INT1 auf RB0
    INT1IP = 1;
    INT1IF = 0;
}

void mems_am_Wake(void){
    
    INT1IE = 0;
    
    mems_am_Write (0x38,0b00000000);//adress INT_DISABLE
    mems_am_Write (0x6B,0b00000100);//normal mode
    mems_am_Write(0x6c,0b00000111);//accel enable
}

void mems_am_Sleep(void){
    
    INT1IE = 1;
    
    unsigned char threshHold=8;
    
    mems_am_Write (0x70,0b01000000);
    mems_am_Write (0x6B,0b00001100);//adress PWR_MGMT_1//Sleep off Cycle off GyroStandby off Temp off
    mems_am_Write (0x6C,0b00000111);//adress PWR_MGMT_2//enable Accelxyz disable Gyroxyz
    mems_am_Write (0x1D,0b00001001); //Adress ACCEL_CONFIG2
    //Fchoice_B=1 A_DLPF_CFG=0b001 die bits davor??????
    mems_am_Write (0x38,0b11100000); //adress INT_ENABLE
    //ENABLE X,Y,Z motion Interrupt
    mems_am_Write (0x20,threshHold); //Adress ACCEL_WOM_X_THR 
    //Threshhold x
    mems_am_Write (0x21,threshHold); //Adress ACCEL_WOM_Y_THR 
    //Threshhold y
    mems_am_Write (0x22,threshHold); //Adress ACCEL_WOM_Z_THR 
    //Threshhold z
    mems_am_Write (0x69,0b11000001); //ACCEL_INTEL_CTRL
    //enable Wake on motion logic,compare to prev 
    mems_am_Write (0x19,99); //adress SMPLRT_DIV
    //set Check Rate to 1000/value+1
    mems_am_Write (0x6B,0b00101100); //adress PWR_MGMT_1
    //CYCLE=1 :When set to 1, and SLEEP and STANDBY are not set to 1,
    //the chip will cycle between sleep and taking a single accelerometer sample at a rate determined by SMPLRT_DIV
}

void mems_am_IRQ(void){
    
    
}

unsigned char mems_am_Read(unsigned char address){
    
}
void mems_am_Write(unsigned char address, unsigned char data){
    
}
