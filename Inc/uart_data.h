#ifndef UART_DATA_H
#define UART_DATA_H

#include "stm32f1xx_hal_msp.h"

#define DATA_RECEIVE_LEN_MAX 1024
#define DATA_SIZE 2
#define USED_BY_USR 1
#define USED_BY_DMA 0

typedef struct{
  uint8_t receive_data[DATA_RECEIVE_LEN_MAX];
  uint32_t valid_len;
  uint8_t used;
}usart_data;

usart_data *get_valid_databuffer(void);
void data_input(uint8_t *buffer, uint32_t len);
void init_databuffer(void);
void set_databuffer_owner(usart_data *data, uint8_t owner);

#endif
