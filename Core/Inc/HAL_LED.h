#ifndef HAL_LED_H
#define HAL_LED_H

#include "main.h"

#define LED_WARNING   0
#define LED_EMERGENCY 1

void LED_On(uint8_t led_type);
void LED_Off(uint8_t led_type);

#endif