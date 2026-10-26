#include "HAL_Motor.h"

static TIM_HandleTypeDef *motor_htim;
static uint32_t motor_channel;

void Motor_Init(TIM_HandleTypeDef *htim, uint32_t channel) {
    motor_htim = htim;
    motor_channel = channel;
    HAL_TIM_PWM_Start(motor_htim, motor_channel);
}

void Motor_SetSpeedAndDir(uint16_t speed, uint8_t dir) {
    __HAL_TIM_SET_COMPARE(motor_htim, motor_channel, speed);
    
    if (dir == MOTOR_DIR_FORWARD) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_SET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    } else if (dir == MOTOR_DIR_STOP) {
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_5, GPIO_PIN_RESET);
        HAL_GPIO_WritePin(GPIOB, GPIO_PIN_4, GPIO_PIN_RESET);
    }
}