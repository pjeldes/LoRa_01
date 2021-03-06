#include <stdio.h>
#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "lora.h"
#include "Config_stm32.h"


void lora_init(void){
    //M1
    M1.Pin = GPIO_PIN_11;
    M1.Mode = GPIO_MODE_OUTPUT_PP;
    M1.Pull = GPIO_PULLUP;
    M1.Speed = GPIO_SPEED_FREQ_LOW;

    //M2
    M2.Pin = GPIO_PIN_12;
    M2.Mode = GPIO_MODE_OUTPUT_PP;
    M2.Pull = GPIO_PULLUP;
    M2.Speed = GPIO_SPEED_FREQ_LOW;

    __HAL_RCC_GPIOA_CLK_ENABLE();
    HAL_GPIO_Init(GPIOA,&M1);
    HAL_GPIO_Init(GPIOA,&M2);
}

//modos para lora

void lora_sleep_mode(void){
    //high state on pin
    HAL_GPIO_WritePin(GPIOA,M1.Pin,GPIO_PIN_SET);
    HAL_GPIO_WritePin(GPIOA,M2.Pin,GPIO_PIN_SET);
}

void lora_power_saving_mode(void){
    HAL_GPIO_WritePin(GPIOA,M1.Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,M2.Pin,GPIO_PIN_SET);
}


void lora_normal_mode(void){
    //low state on pin
    HAL_GPIO_WritePin(GPIOA,M1.Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,M2.Pin,GPIO_PIN_RESET);
}

void lora_set_param(UART_HandleTypeDef *UART, E32_LORA_HanldeTypedef E32){
    //parity, baudies, air data range
    //uint8_t pba = LORA_PARITY_8N1 | LORA_BAUDIOS_9600 | LORA_AIR_DATA_RATE_2_4_K;
    uint8_t pba = E32.patity | E32.baudios | E32.air_data_rate;

    //TRANSMISION, IO, wake up time, FEC swithc, Transmission power
    //uint8_t POWER = LORA_TRANSPARENT_TRANSMISSION | LORA_IO_DRIVE_MODE | LORA_WIRE_WAKE_UP_TIME | LORA_FEC_SWITCH | LORA_POWER_DBM_14;
    uint8_t POWER = E32.transmission_type | E32.IO_drive_mode | E32.wake_up_time | E32.fec_switch | E32.power_dbm;

    uint8_t cmd[] = {LORA_SET_PARAM, 0x00, LORA_ADDRES, pba, LORA_CHANEL, POWER};
    //uint8_t cmd[] = {0xC0, 0x00, 0x00, 0x3D, 0x17, 0xC4};
    uint8_t save_cmd[] = {0xc1,0xc1,0xc1};

    HAL_Delay(100);
    HAL_UART_Transmit(UART,cmd,sizeof(cmd),0x700);
    HAL_Delay(100);
    HAL_UART_Transmit(UART,save_cmd,sizeof(save_cmd),0x700);

}

void lora_get_param(UART_HandleTypeDef UART , UART_HandleTypeDef UART2,uint8_t *params){

    uint8_t cmd_get_param[] = {0xc1, 0xc1,0xc1};
    uint8_t save_params[6];

    HAL_Delay(10);
    HAL_UART_Transmit(&UART,cmd_get_param,sizeof(cmd_get_param),0x700);
    HAL_Delay(10);
    HAL_UART_Receive(&UART, save_params, sizeof(save_params),0x700);
    HAL_Delay(10);
    HAL_UART_Transmit(&UART2,save_params,sizeof(save_params),0x700);
    *params = save_params;

}