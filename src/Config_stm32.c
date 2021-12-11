#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "Config_stm32.h"



//config osc.

void SysOscConfig(void){
    OscConf_s.OscillatorType = RCC_OSCILLATORTYPE_HSI;//oscilador interno
    OscConf_s.HSIState = RCC_HSI_ON;
    OscConf_s.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
    OscConf_s.PLL.PLLState = RCC_PLL_ON;
    OscConf_s.PLL.PLLSource = RCC_PLLSOURCE_HSI_DIV2;
    OscConf_s.PLL.PLLMUL = RCC_PLL_MUL2;

    HAL_RCC_OscConfig(&OscConf_s);
}

//cofig clk

void SysClkConfig(void){
    ClkConf_s.ClockType = RCC_CLOCKTYPE_SYSCLK|RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2|RCC_CLOCKTYPE_HCLK;
    ClkConf_s.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;//RCC_SYSCLKSOURCE_HSI
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
    //GpioConf_s.Pull = GPIO_NOPULL;
    GpioConf_s.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA,&GpioConf_s);

    GpioConf_s.Pin = GPIO_PIN_10;
    GpioConf_s.Mode = GPIO_MODE_INPUT;
    GpioConf_s.Pull = GPIO_NOPULL;
    GpioConf_s.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA,&GpioConf_s);

    UartONEConf_s.Instance = USART1;
    UartONEConf_s.Init.BaudRate = 9600;//baudios
    UartONEConf_s.Init.WordLength = UART_WORDLENGTH_8B;
    UartONEConf_s.Init.StopBits = UART_STOPBITS_1;
    UartONEConf_s.Init.Parity = USART_PARITY_NONE;//1 se usa para configurar, segun manual del e32
    UartONEConf_s.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartONEConf_s.Init.Mode = USART_MODE_TX_RX;

    HAL_UART_Init(&UartONEConf_s);
    HAL_NVIC_SetPriority(USART1_IRQn, 0, 0);
    HAL_NVIC_EnableIRQ(USART1_IRQn);
    //HAL_UART_Init(&UartONEConf_s);
}

void UartTwoInit(void){

    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_USART2_CLK_ENABLE();
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
    __HAL_AFIO_REMAP_SWJ_NOJTAG();

    //GPIO to UART2
    GpioConfTwo_s.Pin = GPIO_PIN_2;
    GpioConfTwo_s.Mode = GPIO_MODE_AF_PP;
    GpioConfTwo_s.Pull = GPIO_NOPULL;
    GpioConfTwo_s.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA,&GpioConfTwo_s);

    GpioConfTwo_s.Pin = GPIO_PIN_3;
    GpioConfTwo_s.Mode = GPIO_MODE_AF_PP;
    GpioConfTwo_s.Pull = GPIO_NOPULL;
    GpioConfTwo_s.Speed = GPIO_SPEED_FREQ_LOW;

    HAL_GPIO_Init(GPIOA,&GpioConfTwo_s);

    UartTwoConf_s.Instance = USART2;
    UartTwoConf_s.Init.BaudRate = 9600;//baudios
    UartTwoConf_s.Init.WordLength = UART_WORDLENGTH_8B;
    UartTwoConf_s.Init.StopBits = UART_STOPBITS_1;
    UartTwoConf_s.Init.Parity = USART_PARITY_NONE;//1 se usa para configurar, segun manual del e32
    UartTwoConf_s.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    UartTwoConf_s.Init.Mode = USART_MODE_TX_RX;
    UartTwoConf_s.Init.OverSampling = UART_OVERSAMPLING_16;

    HAL_UART_Init(&UartTwoConf_s);
    //HAL_NVIC_SetPriority(USART2_IRQn, 0, 0);
    //HAL_NVIC_EnableIRQ(USART2_IRQn);
}

void Uart_printf(UART_HandleTypeDef UART,uint8_t *string){

    uint16_t TAM = 0;
    while(string[TAM] != '\0'){
        TAM++;
    }
    HAL_Delay(10);
    HAL_UART_Transmit(&UART,(uint8_t*)string,TAM,0x700);
}

void MspInit(void){
    __HAL_RCC_AFIO_CLK_ENABLE();
    __HAL_RCC_PWR_CLK_ENABLE();
     __HAL_AFIO_REMAP_SWJ_NOJTAG();
}

void SysInitDefault(void){
    HAL_Init();
    HAL_Delay(1);
    SysOscConfig();
    HAL_Delay(1);
    SysClkConfig();
    HAL_Delay(1);
    SysTick_Config(SystemCoreClock / 10000);
    HAL_Delay(1);
    MspInit();
}