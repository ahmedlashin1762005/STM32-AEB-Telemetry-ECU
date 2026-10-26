#include "HAL_LED.h"

void LED_On(uint8_t led_type) {
    if (led_type == LED_WARNING) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_SET);
    } else if (led_type == LED_EMERGENCY) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_SET);
    }
}

void LED_Off(uint8_t led_type) {
    if (led_type == LED_WARNING) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_10, GPIO_PIN_RESET);
    } else if (led_type == LED_EMERGENCY) {
        HAL_GPIO_WritePin(GPIOC, GPIO_PIN_7, GPIO_PIN_RESET);
    }
}