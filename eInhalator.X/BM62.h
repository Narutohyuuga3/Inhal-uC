/* 
 * File:   BM62.h
 * Author: Creez
 *
 * Created on 3. Dezember 2020, 20:48
 */

#ifndef BM62_H
#define	BM62_H

#include "pwm.h"

#define RST_BT LATA1
#define TRIS_RST_BT TRISA1
#define ANSEL_RST_BT ANSELA1

#define WAKE_BT LATB4
#define TRIS_WAKE_BT TRISB4
#define ANSEL_WAKE_BT ANSELB4

#define INT_BT RB1
#define TRIS_INT_BT TRISB1
#define ANSEL_INT_BT ANSELB1

#define SPK_IN RB2
#define TRIS_SPK_IN TRISB2
#define ANSEL_SPK_IN ANSELB2

#define MIC_OUT LATB3
#define TRIS_MIC_OUT TRISB3
#define ANSEL_MIC_OUT ANSELB3

volatile unsigned int lsCount;

extern unsigned int shaken;
extern unsigned char status;

void bm62_Init(void);
void bm62_IRQ(void);
void bm62_RST(void);
void bm62_Enable(void);
void bm62_Disable(void);
void bm62_Pairing(void);

#endif	/* BM62_H */

