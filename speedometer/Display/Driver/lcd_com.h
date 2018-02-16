/**
 * @filename: lcd_com.h
 * @author: Yannick Zoller 
 **/
#ifndef LCD_COM_H_INCLUDED_
#define LCD_COM_H_INCLUDED_

#include<stdint.h>

void initCommunication();
void WriteCmd(uint8_t cmd);
void WriteData(uint8_t data);
void Write8(uint8_t cmd, uint8_t data1);
void Write16(uint8_t cmd, uint8_t data1, uint8_t data2);
void Write24(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3);
void Write32(uint8_t cmd, uint8_t data1, uint8_t data2, uint8_t data3, uint8_t data4);

#endif // LCD_COM_H_INCLUDED_
/* END OF FILE */
