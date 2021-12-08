#include "stm32f1xx_hal.h"
#include "Config_stm32.h"
#include "lora.h"
#include <stdlib.h>
#include <stdbool.h>


int main(void){
    //codigo para el receptor
    //sleep mode low power
    SysInitDefault();
    LedPinBluePill_Init();
    
    HAL_Delay(10);

    //lora message
    unsigned char *message = malloc(20);

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
    lora_normal_mode();
  //mensaje del emisor
    //bool STM_SLEEP_ON = false;
    while(1){
      Blink_LedBluePill(1000);
      HAL_Delay(1000);
      //HAL_UART_Receive_IT(&UartONEConf_s,message,20);
      HAL_SuspendTick();
      HAL_PWR_EnterSLEEPMode(PWR_LOWPOWERREGULATOR_ON,PWR_SLEEPENTRY_WFI);
      HAL_UART_Receive(&UartONEConf_s,message,20,HAL_MAX_DELAY);
      HAL_ResumeTick();



    }

}

void SysTick_Handler(void){
  // codigo que se ejecuta luego de la interrupcion
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();


}