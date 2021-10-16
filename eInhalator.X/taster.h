/* 
 * File:   taster.h
 * Author: Creez
 *
 * Created on 3. Dezember 2020, 18:51
 */

#ifndef TASTER_H
#define	TASTER_H

#define TASTER_ANZAHL 1
#define TASTER_KURZ 20 // in Millisekunden
#define TASTER_LANG 1000 // in Millisekunden

unsigned int TASTER_COUNTER[TASTER_ANZAHL];
unsigned char TASTER_GEDRUECKT[1 + (TASTER_ANZAHL / 8)]; // Flag für kurzzeitig gedrückten Taster
unsigned char TASTER_GEHALTEN[1 + (TASTER_ANZAHL / 8)]; // Flag für langzeitig gehaltenen Taster
unsigned char TASTER_GESPERRT[1 + (TASTER_ANZAHL / 8)]; // Flag ob Tastendruck verarbeitet

#define TASTER0 RB5
#define TRIS_TASTER0 TRISB5
#define ANSEL_TASTER0 ANSELB5


void taster_Auswertung(void);
void taster_Init(void);
void taster_IRQ(void);

#endif	/* TASTER_H */

