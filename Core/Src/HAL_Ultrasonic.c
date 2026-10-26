#include "HAL_Ultrasonic.h"

static TIM_HandleTypeDef *us_htim;

void Ultrasonic_Init(TIM_HandleTypeDef *htim) {
    us_htim = htim;
    __HAL_RCC_TIM1_CLK_ENABLE();
    HAL_TIM_Base_Start(us_htim);
}

static void delay_us(uint16_t us) {
    __HAL_TIM_SET_COUNTER(us_htim, 0);
    while (__HAL_TIM_GET_COUNTER(us_htim) < us);
}

uint32_t Ultrasonic_Read_Distance(void) {
    uint32_t pMillis;
    uint32_t Value1 = 0;
    uint32_t Value2 = 0;

    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);
    delay_us(3);
    
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_SET);
    delay_us(10);
    HAL_GPIO_WritePin(GPIOA, GPIO_PIN_9, GPIO_PIN_RESET);

    pMillis = HAL_GetTick();
    while (!(HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10))) {
        if ((HAL_GetTick() - pMillis) > 10) {
            return 999; 
        }
    }
    Value1 = __HAL_TIM_GET_COUNTER(us_htim);

    pMillis = HAL_GetTick();
    while (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_10)) {
        if ((HAL_GetTick() - pMillis) > 50) {
            return 999; 
        }
    }
    Value2 = __HAL_TIM_GET_COUNTER(us_htim);

    uint32_t time_taken;
    if (Value2 >= Value1) {
        time_taken = Value2 - Value1;
    } else {
        time_taken = (65535 - Value1) + Value2;
    }

    uint32_t distance = (time_taken * 34) / 2000;

    if (distance == 0 || distance > 400) {
        return 999; 
    }

    return distance;
}