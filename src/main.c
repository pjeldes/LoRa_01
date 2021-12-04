#include "stm32f1xx_hal.h"
#include "Config_stm32.h"
#include "lora.h"


int main(void){
    SysInitDefault();
    LedPinBluePill_Init();
    UartOneInit();
    HAL_Delay(10);
    //UartTwoInit();
    //uint8_t buffer[] = "_Hola_mundo_\n";
    uint8_t cmd[] = {0xC0, 0x00, 0x00, 0x3D, 0x17, 0xC4};
    uint8_t cmd2[] = {0xC4, 0x17, 0x3d, 0x00, 0x00, 0xC0};
    //lora
    lora_init();
    // lora_sleep_mode();
    // lora_get_param(UartONEConf_s);
    while(1){
      Blink_LedBluePill(100);
      //Uart_printf(UartTwoConf_s,"Hola mundo\n");
      //lora_sleep_mode();
      //lora_set_param(&UartONEConf_s);
      HAL_Delay(100);
      HAL_UART_Transmit(&UartONEConf_s,cmd,sizeof(cmd),HAL_MAX_DELAY);
      //uint16_t Tam = sizeof(char)*14;
      //HAL_UART_Transmit(&UartTwoConf_s,buffer,Tam,HAL_MAX_DELAY);
      //otro
    }

}

void SysTick_Handler(void){
  // codigo que se ejecuta luego de la interrupcion
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();


}