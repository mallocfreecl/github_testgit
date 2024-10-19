#ifndef __TYPES_H__
#define __TYPES_H__

/* ===================================== */
/* linux-like types                      */
/* ===================================== */
#include "stdbool.h"
#include "stdint.h"

#ifdef __GNUC__ /* GNU */
#include <signal.h>
#define _INLINE_ inline
#define _PACKED_ __attribute__((packed))
#if __MSP430__
#define _INTERRUPT_ static interrupt(NOVECTOR)
#else
#define _INTERRUPT_ static void
#endif
#endif

#ifdef __ICC430__ /* IAR */
#ifndef __IARC__
#define __IARC__
#endif

#include <in430.h>
#define _INLINE_
#define _PACKED_
#define _INTERRUPT_ __interrupt void

#ifdef MAZ_STDINT
typedef unsigned long long uint64_t;
typedef unsigned long uint32_t;
typedef unsigned short uint16_t;
typedef unsigned char uint8_t;

typedef signed long long int64_t;
typedef signed long int32_t;
typedef signed short int16_t;
typedef signed char int8_t;

typedef int intptr_t;
typedef unsigned int uintptr_t;
#endif
#endif

#ifdef DPI /* DPI simulation */
#include <stdint.h>
#endif

/* ===================================== */
/* depricated types                      */
/* ===================================== */

#ifdef MAZ_STDINT
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned long u32;
typedef unsigned long long u64;

typedef signed char s8;
typedef signed short s16;
typedef signed long s32;
typedef signed long long s64;
#endif

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef volatile u64 reg64;
typedef volatile u32 reg32;
typedef volatile u16 reg16;
typedef volatile u8 reg8;

/* ===================================== */
/* additional types                      */
/* ===================================== */

#if 0
#if defined(DPI) && defined(__cplusplus)
#else
typedef enum {
	false = 0,
	true  = 1
} bool;
#endif
#endif

#ifndef DPI
typedef int ssize_t;
#endif

#ifndef NULL
#define NULL ((void *)0)
#endif

#endif /* __TYPES_H__ */
