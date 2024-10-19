
#include "crc16.h"
#include "utils.h"

uint16_t crc16(uint16_t *data, int len)
{

  uint16_t sum = 0xFFFF;
  uint16_t data_byte;
  int j;
  uint8_t i, sum_bit, data_bit;

  for (j = 0; j < len; j++)
  {
    data_byte = data[j];
    for (i = 0; i < 16; i++)
    {
      sum_bit = (sum & 0x01) ? 1 : 0;
      data_bit = (data_byte & onehot16[i]) ? 1 : 0;
      if (sum_bit != data_bit)
      {
        sum = (sum >> 1) ^ 0x8408;
      }
      else
      {
        sum = (sum >> 1);
      }
    }
  }
  return sum;
}
