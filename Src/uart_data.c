#include "uart_data.h"

#define NUMBER_DATA 3
usart_data data[NUMBER_DATA];
static usart_data *current_usartdata;
extern UART_HandleTypeDef UartHandle;

void set_databuffer_owner(usart_data *buffer, uint8_t owner)
{
  buffer->used = owner;
}

void init_usartdata(void)
{
  uint32_t i = 0;
  for(i = 0; i < NUMBER_DATA; i++)
  {
    data[i].used = USED_BY_DMA;
  }
  current_usartdata = &data[0];
}

usart_data *get_valid_databuffer(void)
{
  usart_data *udata = 0;
  uint8_t used;
  uint32_t i = 0;
  for(i = 0; i < NUMBER_DATA; i++)
  {
    __HAL_UART_DISABLE_IT(&UartHandle, UART_IT_IDLE);
    used = data[i].used;
    __HAL_UART_ENABLE_IT(&UartHandle, UART_IT_IDLE);
    if(used == USED_BY_USER)
    {
      udata = &data[i];
      break;
    }
  }
  return udata;
}

void usartdata_start_receive(void)
{
  HAL_UART_Receive_DMA(&UartHandle, current_usartdata->receive_data, MAX_DATA_LEN + 1);
}

void usartdata_stop_receive(void)
{
  HAL_UART_DMAStop(&UartHandle);
}

void usartdata_process(void)
{
  usart_data *udata = 0;
  uint32_t i = 0;

  HAL_UART_DMAStop(&UartHandle);
  current_usartdata->valid_len = MAX_DATA_LEN + 1 - __HAL_DMA_GET_COUNTER(UartHandle.hdmarx);
  current_usartdata->used = USED_BY_USER;
  for(i = 0; i < NUMBER_DATA; i++)
  {
    if(data[i].used == USED_BY_DMA)
    {
      udata = &data[i];
      break;
    }
  }
  if(udata)
  {
    current_usartdata = udata;
    HAL_UART_Receive_DMA(&UartHandle, current_usartdata->receive_data, MAX_DATA_LEN + 1);
  }
}
