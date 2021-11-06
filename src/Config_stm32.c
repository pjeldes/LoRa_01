#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "Config_stm32.h"



//config osc.

void SysOscConfig(void){
    OscConf_s.OscillatorType = RCC_OSCILLATORTYPE_HSI;//oscilador interno
    OscConf_s.HSEState = RCC_HSE_ON;
    OscConf_s.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    HAL_RCC_OscConfig(&OscConf_s);
}

//cofig clk

void SysClkConfig(void){
    ClkConf_s.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2|RCC_CLOCKTYPE_HCLK;
    ClkConf_s.AHBCLKDivider = RCC_SYSCLK_DIV1;
    ClkConf_s.APB1CLKDivider = RCC_HCLK_DIV1;
    ClkConf_s.APB2CLKDivider = RCC_HCLK_DIV1;

    HAL_RCC_ClockConfig(&ClkConf_s,FLASH_LATENCY_0);
}

//-------------Led(pin 13)----------------//

void LedPinBluePill_Init(void){
    GpioConf_s.Pin = LEDPIN_BLUEPILL;
    GpioConf_s.Mode = GPIO_MODE_OUTPUT_PP;
    GpioConf_s.Pull = GPIO_PULLUP;
    GpioConf_s.Speed = GPIO_SPEED_FREQ_LOW;

    __HAL_RCC_GPIOC_CLK_ENABLE();
    HAL_GPIO_Init(GPIOC,&GpioConf_s);
}

//this function shoud be used in infynite loop(while (1))

void Blink_LedBluePill(int msDelay){
    HAL_GPIO_TogglePin(GPIOC,LEDPIN_BLUEPILL);
    HAL_Delay(msDelay);
}

//UART configs

void UartOneInit(void){

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART1_CLK_ENABLE();

    //GPIO to UART1
    GpioConf_s.Pin = GPIO_PIN_9;
    GpioConf_s.Mode = GPIO_MODE_AF_PP;
    GpioConf_s.Pull = GPIO_NOPULL;
    GpioConf_s.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA,&GpioConf_s);

    GpioConf_s.Pin = GPIO_PIN_10;
    GpioConf_s.Mode = GPIO_MODE_AF_PP;
    GpioConf_s.Pull = GPIO_NOPULL;
    GpioConf_s.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA,&GpioConf_s);

    UartONEConf_s.Instance = USART1;
    UartONEConf_s.Init.BaudRate = 9600;//baudios
    UartONEConf_s.Init.WordLength = UART_WORDLENGTH_8B;
    UartONEConf_s.Init.StopBits = UART_STOPBITS_1;
    UartONEConf_s.Init.Parity = UART_PARITY_NONE;
    UartONEConf_s.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartONEConf_s.Init.Mode = USART_MODE_TX_RX;

    HAL_UART_Init(&UartONEConf_s);
}

void Uart_printf(UART_HandleTypeDef UART,uint8_t *string){

    const uint16_t TAM = sizeof(uint8_t)*14;
    HAL_Delay(10);
    HAL_UART_Transmit(&UART,string,TAM,HAL_MAX_DELAY);
}

void SysInitDefault(void){
    HAL_Init();
    HAL_Delay(1);
    SysOscConfig();
    HAL_Delay(1);
    SysClkConfig();
    HAL_Delay(1);
    SysTick_Config(SystemCoreClock / 1000);
    HAL_Delay(1);
}