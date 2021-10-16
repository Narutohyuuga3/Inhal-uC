#include "spi.h"

void spi_Init(void){
    
    RC5PPS = 0x10; // Serial Data Out C5
    RC3PPS = 0x0f; // Serial Clock C3
    SSP1DATPPS = 0x14; // Serial Data In C4
    SSP1CLKPPS = 0x13; // Serial Data In C3
    
    TRIS_SCLK = 0; // Port Dir Setup
    TRIS_MISO = 1;
    TRIS_MOSI = 0;
    
    SCLK = 0; // Port Latch Setup
    MISO = 1;
    MOSI = 0;
    
    //WPUCbits.WPUC4 = 1;
    
    SSP1STATbits.SMP = 1;
    SSP1STATbits.CKE = 1;
    SSP1CON1bits.CKP = 0; // Clk Idle = high
    SSP1CON1bits.SSPM = 0b00010; // SysClk / 16
    SSP1CON3bits.BOEN = 0; // Buffer override = 1
    
    SSP1CON1bits.SSPEN = 1; // Enable
}

void spi_Wake(void){
    
    
    
    TRIS_SCLK = 0; // Port Dir Setup
    TRIS_MISO = 1;
    TRIS_MOSI = 0;
    
    SCLK = 0; // Port Latch Setup
    MISO = 0;
    MOSI = 0;
    
    SSP1CON1bits.SSPEN = 1; // Enable
}

void spi_Tris(void){
    
    TRIS_SCLK = 1; // tristate
    TRIS_MISO = 1;
    TRIS_MOSI = 1;
}

void spi_Sleep(void){
    
    SSP1CON1bits.SSPEN = 0; // Enable
    
    SCLK = 0; // Port Latch Setup
    MISO = 0;
    MOSI = 0;
    
    TRIS_SCLK = 0; // Port Dir Setup
    TRIS_MISO = 0;
    TRIS_MOSI = 0;
}

unsigned char spi_RW(unsigned char daten){
    
    SSP1BUF = daten;
    SSP1CON1bits.WCOL = 0;
    while(SSP1IF == 0);
    
    SSP1IF = 0;
    SSP1STATbits.BF = 0;
    
    unsigned char reDaten = SSP1BUF;
	
	return reDaten;
}

