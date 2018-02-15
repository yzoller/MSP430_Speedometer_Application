/****************************************************************
 * @filename: spi_usci_msp430.h
 * @author: Yannick Zoller
 * @brief: Serial Peripheral Interface (SPI) configuration
 *         for MSP430FR57xx
 * @functions:
 *  SPI_Init -- Configures and initializes the GPIOs and register
 *             for SPI communication
 *  SPI_SendData -- Sends data via SPI
 ***************************************************************/
#ifndef SPI_MSP430_H_INCLUDED_
#define SPI_MSP430_H_INCLUDED_

#include<stdint.h>
#include<msp430fr5739.h>

#define SIMO_PIN        BIT0
#define CLK_PIN         BIT5
/****************************************************************
 * @function: SPI_Init
 * @brief: Configures and initializes the GPIOs and register
 *         for SPI communication
 ***************************************************************/
void SPI_Init();
/****************************************************************
 * @function: SPI_SendData
 * @brief: Send data via SPI
 * @param: TXdata -- data to be send
 ***************************************************************/
void SPI_SendData(uint8_t TXdata);
#endif // SPI_MSP430_H_INCLUDED_
/* END OF FILE */
