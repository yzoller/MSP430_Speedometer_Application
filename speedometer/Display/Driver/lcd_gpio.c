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
  SET(CS_DIRPORT, CS_PIN);
  SET(CS_OUTPORT, CS_PIN);
}

void setupResetGPIO(){
  SET(RST_DIRPORT, RST_PIN);
  SET(RST_OUTPORT, RST_PIN);
}

void setupDataCmdSelectGPIO(){
  SET(DC_OUTPORT, DC_PIN);
  SET(DC_DIRPORT, DC_PIN);
  RESET(DC_OUTPORT, DC_PIN);
}

void setGPIOinIdleState(){
  delay_us(1);
  SET(CS_OUTPORT, CS_PIN);
  RESET(DC_OUTPORT, DC_PIN);
}

void resetLCD(){
  SET(RST_OUTPORT, RST_PIN);
  delay_us(1200);
  RESET(RST_OUTPORT, RST_PIN);
  delay_us(1200);
  SET(RST_OUTPORT, RST_PIN);
}

void setGPIOforCmd(){
  RESET(CS_OUTPORT, CS_PIN);
  RESET(DC_OUTPORT, DC_PIN);
  delay_us(1);
}

void setGPIOforData(){
  RESET(CS_OUTPORT, CS_PIN);
  SET(DC_OUTPORT, DC_PIN);
  delay_us(1);
}
/* END OF FILE */
