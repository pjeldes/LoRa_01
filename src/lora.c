#include <stdio.h>
#include <stdlib.h>
#include "stm32f1xx_hal.h"
#include "stm32f1xx_hal_gpio.h"
#include "lora.h"


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

void lora_normal_mode(void){
    //low state on pin
    HAL_GPIO_WritePin(GPIOA,M1.Pin,GPIO_PIN_RESET);
    HAL_GPIO_WritePin(GPIOA,M2.Pin,GPIO_PIN_RESET);
}

void lora_get_param(UART_HandleTypeDef UART){
    //uint8_t *params = malloc(sizeof(char)*6);

    //uint8_t cmd[] = {0xc1, 0xc1,0xc1};
    uint8_t cmd[] = {0xC0, 0x00, 0x00, 0x3D, 0x17, 0xC4};
    uint8_t recive[] = {0x00,0x00,0x00,0x00,0x00,0x00};
    

    for(uint8_t i = 0; i < 6;i++){
        HAL_UART_Transmit(&UART,cmd[i],1,0x700);
        HAL_Delay(100);
    }
    //HAL_UART_Transmit(&UART,cmd,6,0x700);
    HAL_UART_Receive(&UART,recive,6,0x700);
    HAL_Delay(1);


}