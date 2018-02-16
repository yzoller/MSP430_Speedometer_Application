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

#define DC_PORT         P1OUT
#define CS_PORT         P1OUT
#define RST_PORT        P1OUT

#define DC_PIN          BIT4
#define CS_PIN          BIT6
#define RST_PIN         BIT7

#define SET(port, pin)  {port |= pin;}
#define RESET(port, pin){port &= ~pin;}

//Commands
#define WAKEUP          0x11
#define DISPLAY_ON      0x29
#define SET_COL_ADR     0x2A
#define SET_ROW_ADR     0x2B
#define WRITE_RAM       0x2C
#define MEMACC_CTL      0x36
#define COLOR_MODE      0x3A
#define FRAME_CTL1      0xB1
#define FRAME_CTL2      0xB2
#define FRAME_CTL3      0xB3
#define FRAME_INVERT    0xB4
#define POWER_CTL1      0xC0
#define POWER_CTL2      0xC1
#define POWER_CTL3      0xC2
#define POWER_CTL4      0xC3
#define POWER_CTL5      0xC4
#define VCOM_CTL1       0xC5
#define GAMMA_POLP      0xE0
#define GAMMA_POLN      0xE1

void LCD_Init(void);
void configureGPIOforLCD(void);
void configureLCD(void);
void clearDisplay(void);
void DrawPixel(uint8_t x, uint8_t y);
void DrawPixel(uint8_t x, uint8_t y);
void DrawChar8x8(uint8_t row, uint8_t col, uint8_t letter);
void DrawString(uint8_t row, char* temp);
void WriteCmd(uint8_t cmd);
void WriteData(uint8_t data);
void Write8(uint8_t cmd, uint8_t data1);
void Write16(uint8_t cmd, uint8_t data1, uint8_t data2);
void Write24(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3);
void Write32(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);

#endif // LCD_MSP430_H_INCLUDED_
/* END OF FILE */
