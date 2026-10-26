#ifndef HAL_MOTOR_H
#define HAL_MOTOR_H

#include "main.h"

#define MOTOR_DIR_FORWARD 1
#define MOTOR_DIR_STOP    0

void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel);
void Motor_SetSpeedAndDir(uint16_t speed, uint8_t dir);

#endif