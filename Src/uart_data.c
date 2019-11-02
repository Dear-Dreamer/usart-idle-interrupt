#include "uart_data.h"
#include "stm32f1xx_hal_msp.h"

usart_data data[DATA_SIZE];

usart_data *get_valid_databuffer(void)
{
  usart_data *buffer = 0;
  uint8_t i;
  for(i = 0; i < DATA_SIZE; i++)
  {
    if(data[i].used == USED_BY_DMA)
    {
      buffer = &data[i];
      break;
    }
  }
  return buffer;
}

void init_databuffer(void)
{
  uint8_t i;
  for(i = 0; i < DATA_SIZE; i++)
  {
    data[i].used = USED_BY_DMA;
  }
}

void data_input(uint8_t *buffer, uint32_t len)
{
  uint32_t i;
  printf("\r\nreceived len %d", len);
  printf("\r\nreceived data:");
  for(i = 0; i < len; i++)
  {
    printf("%c", buffer[i]);
  }
}

void set_databuffer_owner(usart_data *data, uint8_t owner)
{
  data->used = owner;
}
