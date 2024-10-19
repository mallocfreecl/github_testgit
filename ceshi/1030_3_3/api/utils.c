#include "utils.h"
#define DEBUG 0

const uint16_t onehot16[16] = {0x0001, 0x0002, 0x0004, 0x0008, 0x0010, 0x0020, 0x0040, 0x0080,
                               0x0100, 0x0200, 0x0400, 0x0800, 0x1000, 0x2000, 0x4000, 0x8000};

bool div_u16(uint16_t x, uint16_t y, uint16_t *div, uint16_t *mod)
{
  uint32_t q, z, foo;
  switch (y)
  {
  case 0:
    return false;
  case 16:
    *div = x >> 4;
    *mod = x & 15;
    return true;
  default:
    q = 0;
    while (1 == 1)
    {
      z = 1;
      foo = y;
      while (foo <= x)
      {
        foo <<= 1;
        z <<= 1;
      };
      if (z == 1)
      {
        *mod = x;
        *div = q;
        return true;
      };
      x -= foo >> 1;
      q += z >> 1;
    };
  }
}

char *strcpy(char *dst, const char *src)
{
  while (*src != 0)
  {
    *dst++ = *src++;
  }
  *dst = 0;
  return dst;
}

void *memcpy(void *dst, const void *src, unsigned int len)
{
  uint8_t *dst8;
  uint8_t *src8;
  dst8 = (uint8_t *)dst;
  src8 = (uint8_t *)src;
  while (len > 0)
  {
    *dst8++ = *src8++;
    len--;
  }
  return dst;
}

unsigned int strlen(const char *str)
{
  unsigned int len = 0;
  while (*str != '\0')
  {
    len++;
    str++;
  }
  return len;
}
