/**
 * @filename: lcd_gpio.c
 * @author: Yannick Zoller 
 **/
#include<stdint.h>
#include<msp430fr5739.h>
#include<lcd_gpio.h>

void delay_us(uint16_t ticks){
  volatile uint16_t value = ticks;
  while(value > 0 ){
    value--;
  }
}

void setupChipSelectGPIO(){
  SET(DIR_PORT, CS_PIN);
  SET(CS_PORT, CS_PIN);
}

void setupResetGPIO(){
  SET(DIR_PORT, RST_PIN);
  SET(RST_PORT, RST_PIN);
}

void setupDataCmdSelectGPIO(){
  SET(DC_PORT, DC_PIN);
  SET(DIR_PORT, DC_PIN);
  RESET(DC_PORT, DC_PIN);
}

void setGPIOinIdleState(){
  delay_us(1);
  SET(CS_PORT, CS_PIN);
  RESET(DC_PORT, DC_PIN);
}

void resetLCD(){
  SET(RST_PORT, RST_PIN);
  delay_us(1200);
  RESET(RST_PORT, RST_PIN);
  delay_us(1200);
  SET(RST_PORT, RST_PIN);
}

void setGPIOforCmd(){
  RESET(CS_PORT, CS_PIN);
  RESET(DC_PORT, DC_PIN);
  delay_us(1);
}

void setGPIOforData(){
  RESET(CS_PORT, CS_PIN);
  SET(DC_PORT, DC_PIN);
  delay_us(1);
}
/* END OF FILE */
