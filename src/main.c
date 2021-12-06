#include "stm32f1xx_hal.h"
#include "Config_stm32.h"
#include "lora.h"


int main(void){
    SysInitDefault();
    LedPinBluePill_Init();
    
    HAL_Delay(10);

    //lora message
    char message[12];

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

    while(1){
      Blink_LedBluePill(100);
      //recive
      HAL_USART_Receive(&UartONEConf_s,message,sizeof(message),HAL_MAX_DELAY);
      HAL_Delay(10);
      Uart_printf(UartTwoConf_s,message);




    }

}

void SysTick_Handler(void){
  // codigo que se ejecuta luego de la interrupcion
  HAL_IncTick();
  HAL_SYSTICK_IRQHandler();


}