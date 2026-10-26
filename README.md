# Autonomous Emergency Braking (AEB) & Telemetry ECU

## 🏎️ Project Overview
This project implements a Bare-Metal embedded software engine for an Autonomous Emergency Braking (AEB) system, developed on the **STM32F401RE** ARM Cortex-M4 microcontroller. Designed with automotive standards in mind, the ECU continuously monitors forward distance, dynamically adjusts motor speed via PWM, triggers zero-latency emergency braking upon detecting critical obstacles, and broadcasts real-time telemetry data for Pit-Wall/Dashboard monitoring.

## ⚙️ Software Architecture
The core philosophy of this firmware is a **Strict Non-Blocking Architecture**. In safety-critical automotive systems, the CPU cannot afford to be halted by delay functions. 
* **State Machine Logic:** The system operates asynchronously across three distinct states:
  * **NORMAL:** Path is clear. PWM is at 100% (`1000`), system monitors distance regularly.
  * **WARNING:** Proximity alert. PWM drops to 50% (`500`) for gradual deceleration.
  * **EMERGENCY (AEB Active):** Critical proximity or IR trigger. PWM drops to 0% (`0`), immediately halting the vehicle.
* **Hardware Timers over Delays:** Ultrasonic sensor triggering and PWM generation are entirely hardware-driven using `TIM1` and `TIM2`, freeing the CPU for telemetry execution.
* **Interrupt-Driven Safety:** The IR obstacle sensor is tied directly to the EXTI (External Interrupt) line. If an unexpected object appears, the interrupt preempts the main execution context to apply the brakes with true zero-latency.

## 🛠️ Hardware & Pin Mapping
| Component | STM32 Pin | Function / Alternate Function |
| :--- | :--- | :--- |
| **Ultrasonic Trig** | `PA9` | TIM1 Output (Trigger Pulse) |
| **Ultrasonic Echo** | `PA10` | Input Capture |
| **Motor IN1** | `PB5` | Direction Control (GPIO) |
| **Motor IN2** | `PB4` | Direction Control (GPIO) |
| **Motor ENA (PWM)**| `PB3` | TIM2_CH2 (Mapped via Alternate Function) |
| **IR Sensor** | `PA8` | EXTI_8 (Falling Edge Interrupt) |
| **Telemetry (TX)** | `PA2` | USART2 (115200 Baud Rate) |

## 💡 Engineering Challenges & Solutions

### 1. High-Current Transients & MCU Protection
**Challenge:** H-Bridge motor drivers (like the L298N) can generate severe reverse voltage spikes during sudden braking (Back-EMF), which can permanently damage the MCU's logic pins or cause erratic resets.
**Solution:** Implemented galvanic isolation using a **6N137 High-Speed Optocoupler**. The PWM signal from `PB3` is optically transmitted to the driver, physically decoupling the STM32's 3.3V logic circuit from the 9V/12V high-current motor circuit, ensuring 100% MCU safety even during dead short circuits.

### 2. Blocking Functions in Sensor Reading
**Challenge:** Standard Ultrasonic (HC-SR04) implementations rely on `while()` loops to wait for the Echo pulse, blocking the CPU and delaying the transmission of telemetry data.
**Solution:** Developed a timeout-protected, non-blocking distance calculation algorithm. If the Echo signal is lost or out of range, the system auto-assigns a safe default value (`999 cm`) without freezing the main loop, maintaining a deterministic execution time.

### 3. Pin Conflicts & Alternate Functions
**Challenge:** The initial PWM channel (`PA1`) conflicted with the 4-bit parallel data bus required for the 16x2 LCD display.
**Solution:** Utilized the STM32's Alternate Function (AF) capabilities to remap `TIM2_CH2` hardware output from `PA1` to `PB3`, resolving the hardware conflict purely through software configuration without sacrificing timer resolution.

## 📡 Live Telemetry Output
The ECU transmits continuous JSON-formatted telemetry strings via USART for data logging and dashboard visualization:
```json
{"State":"NORMAL", "Distance_cm":156, "PWM":1000}
{"State":"WARNING", "Distance_cm":10, "PWM":500}
{"State":"EMERGENCY_BRAKE", "Distance_cm":3, "PWM":0}
```




Author:

Ahmed Lashin

Embedded Systems & Telemetry Engineer
