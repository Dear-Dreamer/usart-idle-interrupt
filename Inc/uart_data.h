#ifndef __USART_DATA_H
#define __USART_DATA_H

#include "stm32f1xx_hal.h"

#define MAX_DATA_LEN    2048
#define USED_BY_DMA 1
#define USED_BY_USER 0
typedef struct{
  uint8_t receive_data[MAX_DATA_LEN];
  uint8_t used;
  uint16_t valid_len;
}usart_data;

void init_usartdata(void);
void set_databuffer_owner(usart_data *buffer, uint8_t owner);
usart_data *get_valid_databuffer(void);
void usartdata_start_receive(void);
void usartdata_stop_receive(void);
void usartdata_process(void);

#endif
