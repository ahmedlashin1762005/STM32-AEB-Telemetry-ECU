#ifndef HAL_ULTRASONIC_H
#define HAL_ULTRASONIC_H

#include "main.h"

void Ultrasonic_Init(TIM_HandleTypeDef *htim);
uint32_t Ultrasonic_Read_Distance(void);

#endif