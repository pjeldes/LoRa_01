#include "stm32f1xx_hal.h"
#include "Config_stm32.h"
#include "lora.h"
#include "stm32f1xx_it.h"

#include <stdlib.h>
#include <stdbool.h>
#include "stm32f1xx_hal_pwr.h"
#include "system_stm32f1xx.h"

// uint8_t message;

// void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart){
//   //Uart_printf(UartTwoConf_s,(uint8_t*)"Interrupt call back\n");
//   HAL_UART_Transmit_IT(&UartTwoConf_s,(uint8_t*)"message\n",1);
// }

// void HAL_UART_RxHalfCpltCallback(UART_HandleTypeDef *huart){
//   HAL_UART_Receive_IT(&UartONEConf_s,&message,1);
// }



int main(void){
    //codigo para el receptor
    //sleep mode low power
    SysInitDefault();
    LedPinBluePill_Init();
    
    HAL_Delay(10);

    //lora message
    uint8_t *message = malloc(20);

    //uart 2
    UartOneInit();
    UartTwoInit();

    //lora
    lora_init();
    E32_LORA_HanldeTypedef E32;
    E32.addres = LORA_ADDRES;
    E32.channel = LORA_CHANEL;
    E32.baudios = LORA_BAUDIOS_9600;
    E32.patity = LORA_PARITY_8N1;
    E32.air_data_rate = LORA_AIR_DATA_RATE_1_2_K;
    E32.fec_switch = LORA_FEC_SWITCH;
    E32.IO_drive_mode = LORA_IO_DRIVE_MODE;
    E32.transmission_type = LORA_TRANSPARENT_TRANSMISSION;
    E32.wake_up_time = LORA_WIRE_WAKE_UP_TIME;
    E32.power_dbm = LORA_POWER_DBM_14;

    //lora set param
    lora_sleep_mode();
    HAL_Delay(10);
    lora_set_param(&UartONEConf_s,E32);
    HAL_Delay(10);
    lora_power_saving_mode();
   
    //HAL_PWR_EnableWakeUpPin(PWR_WAKEUP_PIN1);
  //mensaje del emisor
    //bool STM_SLEEP_ON = false;

    uint32_t TICKNIT = 0x05;
    //HAL_UART_Receive_IT(&UartONEConf_s,&message,20);
    while(1){
      //Blink_LedBluePill(1000);
      //HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
      Uart_printf(UartTwoConf_s,(uint8_t*)"\n Enter sleep mode\n");
      
      HAL_Delay(1000);
      //desbilito interrupciones
      //SysTick->CTRL =TICKNIT;
      //HAL_SYSTICK_IRQHandler()
      HAL_SuspendTick();

      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_RESET);
      //HAL_Delay(500);

      //indica si se suspendio el systick y funciono el writepin
      // for(uint8_t i = 0; i<10; i++){
      //   HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
      //   HAL_Delay(500);
      // }
      asm("nop");
      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,GPIO_PIN_SET);
      //HAL_Delay(3000);

      //------------------LOW POWER MODES-------------------------//

      HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON,PWR_SLEEPENTRY_WFI);
      //HAL_PWR_EnterSTOPMode(PWR_LOWPOWERREGULATOR_ON,PWR_STOPENTRY_WFI);
      //HAL_PWR_EnterSTANDBYMode();
      
      //HAL_UART_Receive_IT(&UartONEConf_s,&message,20);
      

      //indica si se suspendio el systick y funciono el writepin

      //if stop mode
      //SysOscConfig();
      //SysClkConfig();
      //SysInitDefault();
      HAL_ResumeTick();
      //HAL_NVIC_DisableIRQ(GPIO_PIN_5);

      HAL_Delay(1000);
      for(uint8_t i = 0; i<10; i++){
        HAL_GPIO_TogglePin(GPIOC,GPIO_PIN_13);
        HAL_Delay(500);
      }
      
      //Uart_printf(UartTwoConf_s,(uint8_t*)"wake up from sleep mode\n");
      HAL_UART_Receive(&UartONEConf_s,message,20,HAL_MAX_DELAY);
      Uart_printf(UartTwoConf_s,message);

      

    }

}



// void SysTick_Handler(void){
//   // codigo que se ejecuta luego de la interrupcion
//   HAL_IncTick();
//   HAL_SYSTICK_IRQHandler();

// }

// void USART1_IRQHandler(void){

//   HAL_UART_IRQHandler(&UartONEConf_s);

// }