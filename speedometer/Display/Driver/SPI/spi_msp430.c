/**
 * @filename: spi_msp430.c
 * @author: Yannick Zoller
 **/
#include<spi_msp430.h>
#include<msp430fr5739.h>
#include<stdint.h>

void SPI_Init(){
  SPI_CONTROL_WORD |= SOFTWARERESET;

  PORT1_SELECT |= CLK_PIN;
  PORT2_SELECT |= SIMO_PIN; 

  SPI_CONTROL_WORD |= (CLK_PHASE + MSB_FIRST + MASTER
                       + SYNCHRONOUS + CLK_SOURCE);

  CLK_DIVIDER = 0x0002;
  SPI_CONTROL_WORD &= ~SOFTWARERESET;
}

void SPI_SendData(uint8_t TXdata){
  while(!(SPI_INTERRUPT_FLAG_REG & TX_INTERRUPT_FLAG));

  TX_BUFFER = TXdata;

  while(SPI_STATUS_WORD & SPI_BUSY);
}
/* END OF FILE */
