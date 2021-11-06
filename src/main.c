#include "stm32f1xx_hal.h"
#include "Config_stm32.h"


HAL_GPIO_TogglePin();

int main(void){
    SysInitDefault();
    LedPinBluePill_Init();
    UartOneInit();
    uint8_t buffer[] = "_Hola_mundo_\n";
    while(1){
      Blink_LedBluePill(100);
      Uart_printf(UartONEConf_s,"buffer Hello\n");
      //HAL_UART_Transmit(&UartONEConf_s,"_hola_mundo_\n",sizeof(char)*100,HAL_MAX_DELAY);
    }

}

void SysTick_Handler(void){
  // codigo que se ejecuta luego de la interrupcion
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();

}