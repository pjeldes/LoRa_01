#include "stm32f1xx_hal.h"

#ifndef _CONFIG_STM32_H
#define _CONFIG_STM32_H


#define LEDPIN_BLUEPILL                 GPIO_PIN_13
#define BAUD_RATE_SET                   9600

//init structs
RCC_OscInitTypeDef OscConf_s;
RCC_ClkInitTypeDef ClkConf_s;
GPIO_InitTypeDef GpioConf_s;
GPIO_InitTypeDef GpioConfTwo_s;
UART_HandleTypeDef UartONEConf_s;
UART_HandleTypeDef UartTwoConf_s;

TIM_HandleTypeDef htim3;


//functions

void SysOscConfig(void);
void SysClkConfig(void);
void LedPinBluePill_Init(void);

/** Function: Blink_led_BluePill(void)
 * Esta funcion logra que el GPIO_PIN_13 parpadee, esta funcion solo debe ser ejecutada en el loop (while(1)).
 **/
void Blink_LedBluePill(int msDelay);

/** Fucntion: UartOneInit(void)
 * inicia el UART 1. con una serie de parametros por defecto: baudrate 9600, parity: None, largoPalabra: 8bits,
 * bit de parada: 1.
 * */
void UartOneInit(void);

void UartTwoInit(void);

/** Function: Uart_printf(UART_HandleTypeDef UART,uint8_t *string)
 * Esta funcion imprime usando uart indicado.
 *  
 * */
void Uart_printf(UART_HandleTypeDef UART,uint8_t *string);

/** Function: SysInitDefault(void)
 * Esta funcion inicia el STM32 con una serie de parametros configurados previamente. Solo se usa 1 vez
 **/
void SysInitDefault(void);
void tim3(void);

#endif