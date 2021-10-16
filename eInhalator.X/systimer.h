/* 
 * File:   systimer.h
 * Author: Creez
 *
 * Created on 5. Juli 2020, 19:34
 */

#ifndef SYSTIMER_H
#define	SYSTIMER_H

#include <pic18f24q10.h>
#include "taster.h"

#define TIMERANZAHL 2

volatile unsigned int timerMatch = 0; // Gibt an ob Timer ausgelöst hat (1)
volatile unsigned int timerActivate = 0; // Gibt an ob Timer aktiviert ist (1)
unsigned int timerSleepReset = 0; // Gibt an ob Timer beim Schalfengehen genullt werden (1), oder beim Wakeup fortsetzen soll (0) 

volatile unsigned int timAkt; // Systemzeitpunkt
volatile unsigned int startTime[TIMERANZAHL]; // Startzeitpunkt 
volatile unsigned int durationTime[TIMERANZAHL]; // Verzögerungszeit

void systimer_Init (void);
void systimer_Sleep (void);
void systimer_Wake (void);
void systimer_IRQ(void);

#endif	/* SYSTIMER_H */

