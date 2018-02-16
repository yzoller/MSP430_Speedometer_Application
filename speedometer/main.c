#include <msp430fr5739.h>
#include <spi_msp430.h>
#include <lcd_msp430.h>



void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	PJDIR |= 0x01;					// configure P1.0 as output
	volatile unsigned int i;        // volatile to prevent optimization
	LCD_Init();

	char* string = "Hello";
	DrawString(1, string);
	DrawString(3, "World");

	while(1)
	{
		PJOUT ^= 0x01;				// toggle PJ.0
		for(i=10000; i>0; i--);     // delay
	}
}
