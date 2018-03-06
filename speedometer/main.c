#include <msp430fr5739.h>
#include <lcd_msp430.h>

void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	PJDIR |= 0x01;					// configure P1.0 as output
	volatile unsigned int i;        // volatile to prevent optimization
	LCD_Init();

	DrawString(3, " Studienarbeit");
	DrawString(6, " \"Fahrradtacho");
	DrawChar8x8(8, 6, 'm');
	DrawChar8x8(8, 7, 'i');
	DrawChar8x8(8, 8, 't');
	DrawString(10, "    Display\"");
	DrawString(13, " Yannick Zoller");
	DrawString(15, "   06.03.2018");

	while(1)
	{
		PJOUT ^= 0x01;				// toggle PJ.0
		for(i=10000; i>0; i--);     // delay
	}
}
