/**
 * @filename: lcd_msp430.c
 * @author: Yannick Zoller
 **/
#include<stdint.h>
#include<string.h>
#include<msp430fr5739.h>
#include<font.h>
#include<lcd_msp430.h>
#include<lcd_gpio.h>
#include<lcd_com.h>
#include<lcd_setup.h>

static uint8_t getHighByte(uint16_t data){
  return (uint8_t)(data >> 8);
}

static uint8_t getLowByte(uint16_t data){
  return (uint8_t)(data & 0xFF);
}

static void configureGPIOforLCD(){
  setupChipSelect();
  setupReset();
  setupDataCmdSelect();
  setGPIOinIdleState();
  resetLCD();
}

static void configureLCD(){
  resetLCD(); 
  delay_us(1200);

  WriteCmd(WAKEUP);
  delay_us(1000);

  setupFrame();
  setupPower();
  Write8(VCOM_CTL1, 0x0E);
  Write8(MEMACC_CTL, 0xC8);
  setupGamma();
  Write8(COLOR_MODE, 0x05);
  WriteCmd(DISPLAY_ON);

  clearDisplay();
}
void clearDisplay(){ 
  volatile uint8_t i, j;

  Write32(SET_COL_ADR, 0x00, 0x00, 0x00, (LCD_WIDTH)-1);
  Write32(SET_ROW_ADR, 0x00, 0x00, 0x00, (LCD_HEIGHT)-1);

  WriteCmd(WRITE_RAM);

  for(i = 0; i <  LCD_HEIGHT; i++){
    for(j = 0; j < LCD_WIDTH; j++){
      WriteData(getHighByte(BACK_COLOR));
      WriteData(getLowByte(BACK_COLOR));
    }
  }
}

void LCD_Init(){
  initCommunication();
  configureGPIOforLCD();
  configureLCD();
}

void DrawPixel(uint8_t x, uint8_t y){
  if(( x < LCD_WIDTH-1 ) || ( y < LCD_HEIGHT-1 )){
    return;
  }

	Write32(SET_COL_ADR, 0x00, x, 0x00, x);
	Write32(SET_ROW_ADR, 0x00, y, 0x00, y);

	Write16(WRITE_RAM, getHighByte(FONT_COLOR), getLowByte(FONT_COLOR));
}
void DrawChar8x8(uint8_t row, uint8_t col, uint8_t letter){
//  if (( row < LCD_HEIGHT/8 ) || (col < LCD_WIDTH/8)){
//    return;
//  }
  uint8_t x1 = col * 8;
  uint8_t x2 = x1 + 7;
  uint8_t y1 = row * 8;
  uint8_t y2 = y1 + 7;

  Write32(SET_COL_ADR, 0x00, x1, 0x00, x2);
  Write32(SET_ROW_ADR, 0x00, y1, 0x00, y2);

  uint8_t line = letter - (uint8_t)32;
  uint8_t p = 8, bit = 0;
  volatile uint8_t i = 0;
  WriteCmd(WRITE_RAM);
  for (i = 0; i < 8; i++){
    uint8_t temp = font_table[(line*8)+i];
    p = 8;
    bit = 0;
    while(p > 0){

      // shift bit to test place, AND and shift result back
      bit = ((1u << (p-1)) & temp) >> (p-1);

      if (bit == 1){
        WriteData(getHighByte(FONT_COLOR));
        WriteData(getLowByte(FONT_COLOR));
      }
      else{
        WriteData(getHighByte(BACK_COLOR));
        WriteData(getLowByte(BACK_COLOR));
      }
      p--;
    }
  }
}
void DrawString(uint8_t row, char* temp){
  uint8_t i = 0;

  while((temp[i] != '\0') && (i < LCD_WIDTH)){
    DrawChar8x8(row, i, temp[i]);
    i++;
  }
}
/* END OF FILE */
