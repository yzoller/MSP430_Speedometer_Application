/**
 * @filename: lcd_setup.h
 * @author: Yannick Zoller 
 **/
#ifndef LCD_SETUP_H_INCLUDED_
#define LCD_SETUP_H_INCLUDED_

#define FRAME_CTL1      0xB1
#define FRAME_CTL2      0xB2
#define FRAME_CTL3      0xB3
#define FRAME_INVERT    0xB4
#define POWER_CTL1      0xC0
#define POWER_CTL2      0xC1
#define POWER_CTL3      0xC2
#define POWER_CTL4      0xC3
#define POWER_CTL5      0xC4
#define GAMMA_POLP      0xE0
#define GAMMA_POLN      0xE1

void setupFrame();
void setupPower();
void setupGamma();

#endif // LCD_SETUP_H_INCLUDED_
/* END OF FILE */
