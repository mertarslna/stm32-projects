#include "lcd_i2c.h"

#define LCD_ADDR 0x3F << 1  // Senin LCD adresine göre değişebilir
#define LCD_BACKLIGHT 0x08

I2C_HandleTypeDef *LCD_hi2c;

void LCD_Write(uint8_t data)
{
    uint8_t buf[1];
    buf[0] = data | LCD_BACKLIGHT;
    HAL_I2C_Master_Transmit(LCD_hi2c, LCD_ADDR, buf, 1, HAL_MAX_DELAY);
}

void LCD_Send_Cmd(uint8_t cmd)
{
    LCD_Write(cmd & 0xF0);   // Upper nibble
    HAL_Delay(1);
    LCD_Write((cmd << 4) & 0xF0); // Lower nibble
    HAL_Delay(1);
}

void LCD_Send_Data(uint8_t data)
{
    LCD_Write((data & 0xF0) | 0x01);
    HAL_Delay(1);
    LCD_Write(((data << 4) & 0xF0) | 0x01);
    HAL_Delay(1);
}

void LCD_Init(I2C_HandleTypeDef *hi2c)
{
    LCD_hi2c = hi2c;
    HAL_Delay(50);  // Power on delay
    LCD_Send_Cmd(0x33);
    LCD_Send_Cmd(0x32);
    LCD_Send_Cmd(0x28);
    LCD_Send_Cmd(0x0C);
    LCD_Send_Cmd(0x06);
    LCD_Send_Cmd(0x01);
}

void LCD_Print(char *str)
{
    while(*str) LCD_Send_Data(*str++);
}

void LCD_Set_Cursor(uint8_t row, uint8_t col)
{
    uint8_t addr = (row==0 ? 0x80 : 0xC0) + col;
    LCD_Send_Cmd(addr);
}

void LCD_Backlight_On(void)
{
    LCD_Write(LCD_BACKLIGHT);
}
