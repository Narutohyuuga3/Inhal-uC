/* 
 * File:   pwm.h
 * Author: Creez
 *
 * Created on 7. Juli 2020, 17:50
 */

#ifndef PWM_H
#define	PWM_H

#include <pic18f24q10.h>

#define TRIS_CCP1 TRISB3
#define ANSEL_CCP1 ANSELB3
#define PWM_CYCLES 1024

volatile unsigned int pwmCount = 0; // Um PWM Dauer über Interrupt zu begrenzen

void pwm_Init(void);
void pwm_Sleep(void);
void pwm_Wake(void);
void pwm_Tastgrad(unsigned char tastgrad);
void pwm_IRQ(void);

#endif	/* PWM_H */

