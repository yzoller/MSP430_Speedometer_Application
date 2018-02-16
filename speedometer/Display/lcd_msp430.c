/****************************************************************
 * @filename: lcd_msp430.c
 * @author: Yannick Zoller
 ***************************************************************/
#include<stdint.h>
#include<string.h>
#include<msp430fr5739.h>
#include<font.h>
#include<spi_msp430.h>
#include<lcd_msp430.h>

static void inRegSetPinHigh(uint8_t port, uint8_t pin){
  port |= pin;
}

static void inRegSetPinLow(uint8_t port, uint8_t pin){
  port &= ~pin;
}

static uint8_t getHighByte(uint16_t data){
  return (uint8_t)(data >> 8);
}
static uint8_t getLowByte(uint16_t data){
  return (uint8_t)(data & 0xFF);
}
static void delay_us(uint16_t ticks){
  volatile uint16_t value = ticks;
  while(value > 0 ){
    value--;
  }
}

static void setupChipSelect(){
  inRegSetPinHigh(P1DIR, CS_PIN);
  inRegSetPinHigh(CS_PORT, CS_PIN);
}

static void setupReset(){
  inRegSetPinHigh(P1DIR, RST_PIN);
  inRegSetPinHigh(RST_PORT, RST_PIN);
}

static void setupDataCmdSelect(){
  inRegSetPinHigh(DC_PORT, DC_PIN);
  inRegSetPinHigh(P1DIR, DC_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
}

static void setGPIOinIdleState(){
  delay_us(1);
  inRegSetPinHigh(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
}

static void resetLCD(){
  inRegSetPinHigh(RST_PORT, RST_PIN);
  delay_us(1200);
  inRegSetPinLow(RST_PORT, RST_PIN);
  delay_us(1200);
  inRegSetPinHigh(RST_PORT, RST_PIN);
}

void configureGPIOforLCD(){
  setupChipSelect();
  setupReset();
  setupDataCmdSelect();
  setGPIOinIdleState();
  resetLCD();
}


void configureLCD(){
  inRegSetPinHigh(RST_PORT, RST_PIN);
  delay_us(1200);
  inRegSetPinLow(RST_PORT, RST_PIN);
  delay_us(1200);
  inRegSetPinHigh(RST_PORT, RST_PIN);
  delay_us(1200);

  WriteCmd(WAKEUP);
  delay_us(1000);

  Write24(FRAME_CTL1, 0x01, 0x2C, 0x2D);
  Write24(FRAME_CTL2, 0x01, 0x2C, 0x2D);
  Write24(FRAME_CTL3, 0x01, 0x2C, 0x2D);

  Write8(FRAME_INVERT, 0x07);

  Write24(POWER_CTL1, 0xA2, 0x02, 0x84);
  Write8(POWER_CTL2, 0xC5);
  Write16(POWER_CTL3, 0x0A, 0x00);
  Write16(POWER_CTL4, 0x8A, 0x2A);
  Write16(POWER_CTL5, 0x8A, 0xEE);

  Write8(VCOM_CTL1, 0x0E);
  Write8(MEMACC_CTL, 0xC8);

	WriteCmd(GAMMA_POLP);
	WriteData(0x0F);
	WriteData(0x1A);
	WriteData(0x0F);
	WriteData(0x18);
	WriteData(0x2F);
	WriteData(0x28);
	WriteData(0x20);
	WriteData(0x22);
	WriteData(0x1F);
	WriteData(0x1B);
	WriteData(0x23);
	WriteData(0x37);
	WriteData(0x00);
	WriteData(0x07);
	WriteData(0x02);
	WriteData(0x10);

	WriteCmd(GAMMA_POLN);
	WriteData(0x0F);
	WriteData(0x1B);
	WriteData(0x0F);
	WriteData(0x17);
	WriteData(0x33);
	WriteData(0x2C);
	WriteData(0x29);
	WriteData(0x2E);
	WriteData(0x30);
	WriteData(0x30);
	WriteData(0x39);
	WriteData(0x3F);
	WriteData(0x00);
	WriteData(0x07);
	WriteData(0x03);
	WriteData(0x10);

  Write8(COLOR_MODE, 0x05);

  WriteCmd(DISPLAY_ON);

  ClearDisplay();
}
void ClearDisplay(){ 
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
  SPI_Init();
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
    __no_operation();
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
    __no_operation();
    DrawChar8x8(row, i, temp[i]);
    i++;
  }
}
void WriteCmd(uint8_t cmd){
  inRegSetPinLow(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
  delay_us(1);

  SPI_SendData(cmd);

  delay_us(1);
  inRegSetPinHigh(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
}

void WriteData(uint8_t data){
  inRegSetPinLow(CS_PORT, CS_PIN);
  inRegSetPinHigh(DC_PORT, DC_PIN);
  delay_us(1);

  SPI_SendData(data);

  delay_us(1);
  inRegSetPinHigh(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
}
void Write8(uint8_t cmd, uint8_t data1){
  inRegSetPinLow(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
  delay_us(1);

  SPI_SendData(cmd);


  inRegSetPinHigh(DC_PORT, DC_PIN);


  SPI_SendData(data1);

  delay_us(1);
  inRegSetPinHigh(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
}

void Write16(uint8_t cmd, uint8_t data1, uint8_t data2){
  inRegSetPinLow(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
  delay_us(1);

  SPI_SendData(cmd);


  inRegSetPinHigh(DC_PORT, DC_PIN);


  SPI_SendData(data1);
  SPI_SendData(data2);

  delay_us(1);
  inRegSetPinHigh(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
}

void Write24(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3){
  inRegSetPinLow(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
  delay_us(1);

  SPI_SendData(cmd);


  inRegSetPinHigh(DC_PORT, DC_PIN);

  SPI_SendData(data1);
  SPI_SendData(data2);
  SPI_SendData(data3);

  delay_us(1);
  inRegSetPinHigh(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
}

void Write32(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  inRegSetPinLow(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
  delay_us(1);

  SPI_SendData(cmd);


  inRegSetPinHigh(DC_PORT, DC_PIN);
  SPI_SendData(data1);
  SPI_SendData(data2);
  SPI_SendData(data3);
  SPI_SendData(data4);

  delay_us(1);
  inRegSetPinHigh(CS_PORT, CS_PIN);
  inRegSetPinLow(DC_PORT, DC_PIN);
}
/* END OF FILE */
