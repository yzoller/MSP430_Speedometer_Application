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
  SPI_SendData(cmd);
  setGPIOinIdleState();
}

void WriteData(uint8_t data){
  setGPIOforData();
  SPI_SendData(data);
  setGPIOinIdleState();
}
void Write8(uint8_t cmd, uint8_t data1){
  setGPIOforCmd();
  SPI_SendData(cmd);
  SET(DC_PORT, DC_PIN);
  SPI_SendData(data1);
  setGPIOinIdleState();
}

void Write16(uint8_t cmd, uint8_t data1, uint8_t data2){
  setGPIOforCmd();
  SPI_SendData(cmd);
  SET(DC_PORT, DC_PIN);
  SPI_SendData(data1);
  SPI_SendData(data2);
  setGPIOinIdleState();
}

void Write24(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3){
  setGPIOforCmd();
  SPI_SendData(cmd);
  SET(DC_PORT, DC_PIN);
  SPI_SendData(data1);
  SPI_SendData(data2);
  SPI_SendData(data3);
  setGPIOinIdleState();
}

void Write32(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4){
  setGPIOforCmd();
  SPI_SendData(cmd);
  SET(DC_PORT, DC_PIN);
  SPI_SendData(data1);
  SPI_SendData(data2);
  SPI_SendData(data3);
  SPI_SendData(data4);
  setGPIOinIdleState();
}

/* END OF FILE */
