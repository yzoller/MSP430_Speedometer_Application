/**
 * @filename: lcd_com.c
 * @author: Yannick Zoller 
 **/
#include<stdint.h>
#include<msp430fr5739.h>
#include<spi_msp430.h>
#include<lcd_gpio.h>
#include<lcd_com.h>

void initCommunication(){
  SPI_Init();
}

void WriteCmd(uint8_t cmd){
  setGPIOforCmd();
  SPI_SendByte(cmd);
  setGPIOinIdleState();
}

void WriteData(uint8_t data){
  setGPIOforData();
  SPI_SendByte(data);
  setGPIOinIdleState();
}
void Write8(uint8_t cmd, uint8_t data1){
  setGPIOforCmd();
  SPI_SendByte(cmd);
  SET(DC_OUTPORT, DC_PIN);
  SPI_SendByte(data1);
  setGPIOinIdleState();
}

void Write16(uint8_t cmd, uint8_t data1, uint8_t data2){
  setGPIOforCmd();
  SPI_SendByte(cmd);
  SET(DC_OUTPORT, DC_PIN);
  SPI_SendByte(data1);
  SPI_SendByte(data2);
  setGPIOinIdleState();
}

void Write24(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3){
  setGPIOforCmd();
  SPI_SendByte(cmd);
  SET(DC_OUTPORT, DC_PIN);
  SPI_SendByte(data1);
  SPI_SendByte(data2);
  SPI_SendByte(data3);
  setGPIOinIdleState();
}

void Write32(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  setGPIOforCmd();
  SPI_SendByte(cmd);
  SET(DC_OUTPORT, DC_PIN);
  SPI_SendByte(data1);
  SPI_SendByte(data2);
  SPI_SendByte(data3);
  SPI_SendByte(data4);
  setGPIOinIdleState();
}

/* END OF FILE */
