/* 
 * File:   mems_am.h
 * Author: Creez
 *
 * Created on 3. Dezember 2020, 18:47
 */

#ifndef MEMS_AM_H
#define	MEMS_AM_H

#define CS_SENSOR LATC2
#define TRIS_CS_SENSOR TRISC2
#define ANSEL_CS_SENSOR ANSELC2

#define INT_SENSOR RB0
#define TRIS_INT_SENSOR TRISB0
#define ANSEL_INT_SENSOR ANSELB0

#define RST 1
#define POLL 0

unsigned int shaken = 0;

unsigned int mems_am_Shake(unsigned char reset);
void mems_am_Init(void);
void mems_am_Sleep(void);
void mems_am_IRQ(void);
unsigned char  mems_am_Read(unsigned char address);
void mems_am_Write(unsigned char address, unsigned char data);

#endif	/* MEMS_AM_H */

