/****************************************************************
 * @filename: spi_msp430.c
 * @author: Yannick Zoller
 * @brief: Serial Peripheral Interface (SPI) configuration
 *         for MSP430FR57xx
 ***************************************************************/
#include<spi_msp430.h>
#include<msp430fr5739.h>
#include<stdint.h>
/****************************************************************
 * @function: SPI_Init
 * @brief: Configures and initializes USCI register
 *         for SPI communication
 ***************************************************************/
void SPI_Init(){
  // halt USCI for configuration
  UCA0CTLW0 |= UCSWRST;

  // configure GPIO for SPI communication
  P1SEL1 |= CLK_PIN;
  P2SEL1 |= SIMO_PIN;

  // MSB first, synchronous 3-pin master mode, SMCLK clocksoure
  UCA0CTLW0 |= UCCKPH + UCMSB + UCMST + UCSYNC + UCSSEL_2;

  // set clock divider
  UCA0BRW = 0x0002;

  // release USCI for operation
  UCA0CTLW0 &= ~UCSWRST;
}
/****************************************************************
 * @brief: Send data via SPI
 * @param: TXdata -- data to be send
 ***************************************************************/
void SPI_SendData(uint8_t TXdata){
  // TX buffer ready?
  while(!(UCA0IFG & UCTXIFG));

  // write data to TX buffer
  UCA0TXBUF = TXdata;

  // transmission completed?
  while(UCA0STATW & UCBUSY);
}
/* END OF FILE */
