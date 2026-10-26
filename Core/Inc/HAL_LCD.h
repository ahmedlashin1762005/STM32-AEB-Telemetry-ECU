#ifndef HAL_LCD_H
#define HAL_LCD_H

#include "main.h"

void LCD_Init(void);
void LCD_Clear(void);
void LCD_SetCursor(uint8_t row, uint8_t col);
void LCD_SendString(char *str);
void LCD_PrintNumber(uint32_t num);

#endif