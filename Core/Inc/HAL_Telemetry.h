#ifndef HAL_TELEMETRY_H
#define HAL_TELEMETRY_H

#include "main.h"

void Telemetry_Init(UART_HandleTypeDef *huart);
void Telemetry_SendSystemState(uint8_t state, uint32_t distance, uint16_t motor_pwm);

#endif