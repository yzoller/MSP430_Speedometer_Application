#include <msp430.h>
#include <spi_msp430.h>
#include <lcd_msp430.h>



void main(void)
{
	WDTCTL = WDTPW | WDTHOLD;		// stop watchdog timer
	PJDIR |= 0x01;					// configure P1.0 as output
	volatile int j;
	volatile unsigned int i;        // volatile to prevent optimization
	LCD_Init();

//	for(j = 0; j < LCD_WIDTH; j++){
//	    DrawPixel(j,5);
//	}
//	for(j = 0; j < LCD_HEIGHT; j++){
//        DrawPixel(5,j);
//	}
//	DrawPixel(0,0);
	char* string = "Hello";
	DrawString(1, string);
	DrawString(3, "World");

	while(1)
	{
		PJOUT ^= 0x01;				// toggle P1.0
		for(i=10000; i>0; i--);     // delay
	}
}
