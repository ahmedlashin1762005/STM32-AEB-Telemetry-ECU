#include "HAL_Telemetry.h"
#include <stdio.h>
#include <string.h>

static UART_HandleTypeDef *telemetry_uart;
static char tx_buffer[128];

void Telemetry_Init(UART_HandleTypeDef *huart) {
    telemetry_uart = huart;
}

void Telemetry_SendSystemState(uint8_t state, uint32_t distance, uint16_t motor_pwm) {
    if (telemetry_uart->gState == HAL_UART_STATE_READY) {
        
        char* st_str;
        if (state == 0) st_str = "NORMAL";
        else if (state == 1) st_str = "WARNING";
        else st_str = "EMERGENCY_BRAKE";

        snprintf(tx_buffer, sizeof(tx_buffer), 
                 "{\"State\":\"%s\", \"Distance_cm\":%lu, \"PWM\":%u}\r\n", 
                 st_str, distance, motor_pwm);

        HAL_UART_Transmit_DMA(telemetry_uart, (uint8_t*)tx_buffer, strlen(tx_buffer));
    }
}