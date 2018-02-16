/**
 * @filename: spi_usci_msp430.h
 * @author: Yannick Zoller
 **/
#ifndef SPI_MSP430_H_INCLUDED_
#define SPI_MSP430_H_INCLUDED_

#include<stdint.h>
#include<msp430fr5739.h>

#define SOFTWARERESET      UCSWRST
#define CLK_PIN            BIT5
#define SIMO_PIN           BIT0
#define PORT1_SELECT       P1SEL1
#define PORT2_SELECT       P2SEL1
#define SPI_CONTROL_WORD   UCA0CTLW0
#define CLK_PHASE          UCCKPH
#define MSB_FIRST          UCMSB
#define MASTER             UCMST
#define SYNCHRONOUS        UCSYNC
#define CLK_SOURCE         UCSSEL_2
#define CLK_DIVIDER        UCA0BRW

#define SPI_INTERRUPT_FLAG UCA0IFG
#define TX_INTERRUPT_FLAG  UCTXIFG
#define TX_BUFFER          UCA0TXBUF
#define SPI_STATUS_WORD    UCA0STATW
#define SPI_BUSY           UCBUSY

void SPI_Init(void);
void SPI_SendData(uint8_t TXdata);

#endif // SPI_MSP430_H_INCLUDED_
/* END OF FILE */
