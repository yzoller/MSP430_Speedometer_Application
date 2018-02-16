/**
 * @filename: lcd_setup.c
 * @author: Yannick Zoller 
 **/
#include<lcd_com.h>
#include<lcd_setup.h>

void setupFrame(){
  Write24(FRAME_CTL1, 0x01, 0x2C, 0x2D);
  Write24(FRAME_CTL2, 0x01, 0x2C, 0x2D);
  Write24(FRAME_CTL3, 0x01, 0x2C, 0x2D);
  Write8(FRAME_INVERT, 0x07);
}

void setupPower(){
  Write24(POWER_CTL1, 0xA2, 0x02, 0x84);
  Write8(POWER_CTL2, 0xC5);
  Write16(POWER_CTL3, 0x0A, 0x00);
  Write16(POWER_CTL4, 0x8A, 0x2A);
  Write16(POWER_CTL5, 0x8A, 0xEE);
}

void setupGamma(){
  WriteCmd(GAMMA_POLP);
  WriteData(0x0F);
  WriteData(0x1A);
  WriteData(0x0F);
  WriteData(0x18);
  WriteData(0x2F);
  WriteData(0x28);
  WriteData(0x20);
  WriteData(0x22);
  WriteData(0x1F);
  WriteData(0x1B);
  WriteData(0x23);
  WriteData(0x37);
  WriteData(0x00);
  WriteData(0x07);
  WriteData(0x02);
  WriteData(0x10);
  WriteCmd(GAMMA_POLN);
  WriteData(0x0F);
  WriteData(0x1B);
  WriteData(0x0F);
  WriteData(0x17);
  WriteData(0x33);
  WriteData(0x2C);
  WriteData(0x29);
  WriteData(0x2E);
  WriteData(0x30);
  WriteData(0x30);
  WriteData(0x39);
  WriteData(0x3F);
  WriteData(0x00);
  WriteData(0x07);
  WriteData(0x03);
  WriteData(0x10);
}

/* END OF FILE */
