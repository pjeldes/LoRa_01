#include "stm32f1xx_hal.h"

//macro


GPIO_InitTypeDef M1;
GPIO_InitTypeDef M2;


//function

/** Function: lora_init(void)
 * La funcion lora_init() inicia los gpio 11 y 12(A1, A2, ver pinout BluePill), para usar los modos de configuracion del modulo E32915T20.
 * */
void lora_init(void);

/** Function: void lora_sleep_mode(void)
 * La funcion lora_sleep_mode(), usa el modulo sleep m1 -> 1, m2 -> 1, este mdo permite la configuracion de parametros, tales como: frecuencia, direccion, canal, tasa de datos por aire, baudios, potencia de transmision.
 * */
void lora_sleep_mode(void);
void lora_normal_mode(void);
void lora_get_param(UART_HandleTypeDef UART);