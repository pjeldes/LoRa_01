#include "stm32f1xx_hal.h"
#include "main.h"


int main(void){
    HAL_Init();
    SystemClock_Config();
    SysTick_Config(SystemCoreClock / 1000);
    Begin_Pin_13();
    //Iniciar UART_1
    Begin_Uart_1();
    unsigned char buffer1[] = "Hola Mundo_\n";

    while(1){
        HAL_GPIO_TogglePin(GPIOC, GPIO_PIN_13);
        HAL_Delay(100);

        HAL_UART_Transmit(&UART_ONE, buffer1 , sizeof(buffer1) , HAL_MAX_DELAY );
    }

}

void SysTick_Handler(void){
  // codigo que se ejecuta luego de la interrupcion
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();

}