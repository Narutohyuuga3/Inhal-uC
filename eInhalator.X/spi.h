
#ifndef SPI_H_
#define SPI_H_

#include <pic18f24q10.h>

#define MISO RC3
#define TRIS_MISO TRISC3
#define ANSEL_MISO ANSELC3

#define MOSI LATC4
#define TRIS_MOSI TRISC4
#define ANSEL_MOSI ANSELC4

#define SCLK LATC5
#define TRIS_SCLK TRISC5
#define ANSEL_SCLK ANSELC5

void spi_Init(void);
void spi_Wake(void);
void spi_Tris(void);
void spi_Sleep(void);
unsigned char spi_RW(unsigned char daten);

#endif /* SPI_H_ */

