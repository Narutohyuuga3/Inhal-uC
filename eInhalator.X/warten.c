#include "warten.h"

void warten(unsigned int dauer)
{
	for (unsigned int i = 0x00; i < dauer; i++)
	{
		__delay_ms(0x01);
	}
	
	return;
}

void wartenuS(unsigned int dauer)
{
	for (unsigned int i = 0x00; i < dauer; i++)
	{
		__delay_us(0x01);	}
	
	return;
}