#include "stm32f1xx_hal.h"

//options

//command
#define LORA_SET_PARAM                      0xc0

//byte 4
#define LORA_CHANEL                         0x0f

//byte 2
#define LORA_ADDRES                         0x00

//byte 3
#define LORA_PARITY_8N1                     0b00000000
#define LORA_PARITY_8O1                     0b01000000
#define LORA_PARITY_8E1                     0b10000000 


#define LORA_BAUDIOS_4800                   0b00010000
#define LORA_BAUDIOS_9600                   0b00011000
#define LORA_BAUDIOS_115200                 0b00111000

#define LORA_AIR_DATA_RATE_2_4_K            0b00000010
#define LORA_AIR_DATA_RATE_1_2_K            0b00000001


//byte 5
#define LORA_TRANSPARENT_TRANSMISSION       0b00000000
#define LORA_IO_DRIVE_MODE                  0b01000000
#define LORA_WIRE_WAKE_UP_TIME              0b00000000 
#define LORA_FEC_SWITCH                     0b00000100

#define LORA_POWER_DBM_20                   0b00000000
#define LORA_POWER_DBM_17                   0b00000001
#define LORA_POWER_DBM_14                   0b00000010
#define LORA_POWER_DBM_                     0b00000011

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
void lora_set_param(UART_HandleTypeDef *UART);