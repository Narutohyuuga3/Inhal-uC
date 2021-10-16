/* 
 * File:   warten.h
 * Author: Creez
 *
 * Created on 5. Juli 2020, 18:49
 */

#ifndef WARTEN_H
#define	WARTEN_H

#include <xc.h>

#define _XTAL_FREQ 64000000
	// Für delay.h

void warten(unsigned int dauer);
void wartenuS(unsigned int dauer);

#endif	/* WARTEN_H */

