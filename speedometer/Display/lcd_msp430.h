/**
 * @filename: lcd_msp430.h
 * @author: Yannick Zoller
 **/
#ifndef LCD_MSP430_H_INCLUDED_
#define LCD_MSP430_H_INCLUDED_

#include<stdint.h>
#include<msp430fr5739.h>

#define LCD_WIDTH       128
#define LCD_HEIGHT      160

#define BACK_COLOR      0xFFFF
#define FONT_COLOR      0x0000

#define WAKEUP          0x11
#define DISPLAY_ON      0x29
#define SET_COL_ADR     0x2A
#define SET_ROW_ADR     0x2B
#define WRITE_RAM       0x2C
#define COLOR_MODE      0x3A
#define VCOM_CTL1       0xC5
#define MEMACC_CTL      0x36

void LCD_Init();
void clearDisplay();
void DrawPixel(uint8_t x, uint8_t y);
void DrawChar8x8(uint8_t row, uint8_t col, uint8_t letter);
void DrawString(uint8_t row, char* temp);

#endif // LCD_MSP430_H_INCLUDED_
/* END OF FILE */
