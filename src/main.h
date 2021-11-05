#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal.h"
static UART_HandleTypeDef UART_ONE;
RCC_OscInitTypeDef OSC_INIT_CONF;
RCC_ClkInitTypeDef CLK_INIT_CONF;
GPIO_InitTypeDef GPIO_InitStruct;

void SystemClock_Config(void)
{
  /* configuracion del oscilador */

OSC_INIT_CONF.OscillatorType = RCC_OSCILLATORTYPE_HSI; //oscilador interno
OSC_INIT_CONF.HSIState = RCC_HSI_ON;
OSC_INIT_CONF.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
OSC_INIT_CONF.PLL.PLLState = RCC_PLL_NONE;
HAL_RCC_OscConfig(&OSC_INIT_CONF);

 /* configuracion del clock */

  CLK_INIT_CONF.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1|RCC_CLOCKTYPE_PCLK2;
  CLK_INIT_CONF.SYSCLKSource = RCC_SYSCLKSOURCE_HSI;
  CLK_INIT_CONF.AHBCLKDivider = RCC_SYSCLK_DIV1;
  CLK_INIT_CONF.APB1CLKDivider = RCC_HCLK_DIV1;
  CLK_INIT_CONF.APB2CLKDivider = RCC_HCLK_DIV1;

  HAL_RCC_ClockConfig(&CLK_INIT_CONF, FLASH_LATENCY_0);

}

void Begin_Uart_1(void){
      /*Configurar los pines PB9 y PB10, ver PIOUT bluePILL, para usar el UART*/
  __HAL_RCC_GPIOA_CLK_ENABLE();
  __HAL_RCC_USART1_CLK_ENABLE();
  
  GPIO_InitStruct.Pin = GPIO_PIN_9;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  GPIO_InitStruct.Pin = GPIO_PIN_10;
  GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
  GPIO_InitStruct.Pull = GPIO_NOPULL;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;

  HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);

  /*---UART----*/
  
  UART_ONE.Instance = USART1;
  UART_ONE.Init.BaudRate = 9600;//baudios
  UART_ONE.Init.WordLength = UART_WORDLENGTH_8B;
  UART_ONE.Init.StopBits = UART_STOPBITS_1;
  UART_ONE.Init.Parity = UART_PARITY_NONE;
  UART_ONE.Init.HwFlowCtl = UART_HWCONTROL_NONE;
  UART_ONE.Init.Mode = USART_MODE_TX_RX;

  HAL_UART_Init(&UART_ONE);
}

void Begin_Pin_13(void){
  
  GPIO_InitStruct.Pin = GPIO_PIN_13;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
  __HAL_RCC_GPIOC_CLK_ENABLE();
  HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
}