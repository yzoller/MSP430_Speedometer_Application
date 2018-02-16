/**
 * @filename: lcd_gpio.h
 * @author: Yannick Zoller 
 **/
#ifndef LCD_GPIO_H_INCLUDED_
#define LCD_GPIO_H_INCLUDED_

#include<stdint.h>
#include<msp430fr5739.h>

#define DC_PORT         P1OUT
#define CS_PORT         P1OUT
#define RST_PORT        P1OUT
#define DIR_PORT        P1DIR

#define DC_PIN          BIT4
#define CS_PIN          BIT6
#define RST_PIN         BIT7

#define SET(port, pin)  {port |= pin;}
#define RESET(port, pin){port &= ~pin;}

void delay_us(uint16_t ticks);
void setupChipSelectGPIO();
void setupResetGPIO();
void setupDataCmdSelectGPIO();
void setGPIOinIdleState();
void resetLCD();
void setGPIOforCmd();
void setGPIOforData();

#endif // LCD_GPIO_H_INCLUDED_
/* END OF FILE */
