#include "stm32f1xx_hal.h"
#include "Config_stm32.h"
#include "lora.h"


int main(void){
    SysInitDefault();
    LedPinBluePill_Init();
    UartOneInit();
    HAL_Delay(10);
    //UartTwoInit();
    uint8_t buffer[] = "_Hola_mundo_\n";

    //lora
    lora_init();
    // lora_sleep_mode();
    // lora_get_param(UartONEConf_s);
    while(1){
      Blink_LedBluePill(100);
      //Uart_printf(UartTwoConf_s,"Hola mundo\n");
      lora_sleep_mode();
      lora_get_param(UartONEConf_s);
      //uint16_t Tam = sizeof(char)*14;
      //HAL_UART_Transmit(&UartTwoConf_s,buffer,Tam,HAL_MAX_DELAY);
    }

}

void SysTick_Handler(void){
  // codigo que se ejecuta luego de la interrupcion
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();


}