#ifndef LCD_I2C_H
#define LCD_I2C_H

#include "stm32f3xx_hal.h"

void LCD_Init(I2C_HandleTypeDef *hi2c);
void LCD_Send_Cmd(uint8_t cmd);
void LCD_Send_Data(uint8_t data);
void LCD_Print(char *str);
void LCD_Set_Cursor(uint8_t row, uint8_t col);
void LCD_Backlight_On(void);

#endif
