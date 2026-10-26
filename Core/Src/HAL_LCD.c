#include "HAL_LCD.h"
#include <stdio.h>

extern TIM_HandleTypeDef htim1;

static void LCD_Delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(&htim1, 0);
    while (__HAL_TIM_GET_COUNTER(&htim1) < us);
}

static void LCD_SendNibble(uint8_t nibble) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_4, (nibble >> 0) & 0x01);
    HAL_GPIO_WritePin(GPIOB, GPIO_PIN_0, (nibble >> 1) & 0x01);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_1, (nibble >> 2) & 0x01);
    HAL_GPIO_WritePin(GPIOC, GPIO_PIN_0, (nibble >> 3) & 0x01);

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_SET);
    LCD_Delay_us(5);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_1, GPIO_PIN_RESET);
    LCD_Delay_us(100);
}

static void LCD_SendCommand(uint8_t cmd) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    LCD_SendNibble(cmd >> 4);
    LCD_SendNibble(cmd & 0x0F);
    HAL_Delay(2);
}

static void LCD_SendData(uint8_t data) {
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_SET);
    LCD_SendNibble(data >> 4);
    LCD_SendNibble(data & 0x0F);
    LCD_Delay_us(100);
}

void LCD_Init(void) {
    HAL_Delay(50); 
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_0, GPIO_PIN_RESET);
    
    LCD_SendNibble(0x03); HAL_Delay(5);
    LCD_SendNibble(0x03); HAL_Delay(1);
    LCD_SendNibble(0x03);
    LCD_SendNibble(0x02); 

    LCD_SendCommand(0x28);
    LCD_SendCommand(0x0C);
    LCD_SendCommand(0x06);
    LCD_Clear();
}

void LCD_Clear(void) {
    LCD_SendCommand(0x01);
    HAL_Delay(2);
}

void LCD_SetCursor(uint8_t row, uint8_t col) {
    uint8_t addr = (row == 0) ? (0x80 + col) : (0xC0 + col);
    LCD_SendCommand(addr);
}

void LCD_SendString(char *str) {
    while (*str) {
        LCD_SendData(*str++);
    }
}

void LCD_PrintNumber(uint32_t num) {
    char buf[10];
    snprintf(buf, sizeof(buf), "%lu", num);
    LCD_SendString(buf);
}