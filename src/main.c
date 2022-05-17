#include "stm32f1xx_hal.h"
#include "Config_stm32.h"
#include "stm32f1xx_it.h"
#include "lora.h"
#include <stdlib.h>


int main(void){
    //codigo para el receptor
    SysInitDefault();
    LedPinBluePill_Init();
    
    HAL_Delay(10);

    //lora message
    unsigned char *message = malloc(20);

    //uint8_t message[20]= {0};

    uint8_t *mensaje_prueba = malloc(58);
    HAL_StatusTypeDef Trasnmit_mes;


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
    E32.fec_switch = LORA_FEC_SWITCH_OFF;
    E32.IO_drive_mode = LORA_IO_DRIVE_MODE_ON;
    E32.transmission_type = LORA_TRANSPARENT_TRANSMISSION_OFF;
    E32.wake_up_time = LORA_WIRE_WAKE_UP_TIME_250ms;
    E32.power_dbm = LORA_POWER_DBM_20;

    //lora set param
    lora_sleep_mode();

    HAL_Delay(100);
    lora_set_param(&UartONEConf_s,E32);
    HAL_Delay(100);

    HAL_Delay(30);
    lora_set_param(&UartONEConf_s,E32);
    HAL_Delay(30);

    //lora_normal_mode();
    lora_power_saving_mode();
  //mensaje del emisor

    while(1){
      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, 0);
      HAL_Delay(1000);
      //Blink_LedBluePill(1000);
      //recive

      //mensaje del emisor\n\0
      HAL_Delay(10);
      //Uart_printf(UartTwoConf_s,message);

      HAL_UART_Receive(&UartONEConf_s,message,20,HAL_MAX_DELAY);
      //enviar mensaje al emisor
      HAL_Delay(10);
      // for(uint8_t k = 0; k < 5; k++){
      //   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,0);//encendido
      //   //HAL_Delay(1000);
      //   Trasnmit_mes = HAL_UART_Transmit(&UartONEConf_s,mensaje_prueba,58,HAL_MAX_D50ELAY);
      //   HAL_Delay(2000);
      //   HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13,1);
      // }
      //enviar mensaje
      HAL_UART_Transmit(&UartONEConf_s,(uint8_t*)"Cool\n",5,HAL_MAX_DELAY);
      // HAL_Delay(2000);
      // //Uart_printf(UartTwoConf_s,message);
      

      HAL_UART_Transmit(&UartTwoConf_s,message,20,HAL_MAX_DELAY);
      HAL_GPIO_WritePin(GPIOC,GPIO_PIN_13, 1);
      HAL_Delay(2000);


    }

}
