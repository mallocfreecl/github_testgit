#ifndef __UTILS_H__
#define __UTILS_H__

#include "base.h"
#include "types.h"

extern const uint16_t onehot16[16];

bool div_u16(uint16_t x, uint16_t y, uint16_t *div, uint16_t *mod);

char *strcpy(char *dst, const char *src);

void *memcpy(void *dst, const void *src, unsigned int len);

unsigned int strlen(const char *str);

#define UNSIGNED_SAT(val, bits) (((val) > ((1 << (bits)) - 1)) ? ((1 << (bits)) - 1) : (val))

#define NON_ZERO_TO_ONE(value) (((value) == 0) ? 0 : 1)

#endif
