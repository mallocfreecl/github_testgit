#ifndef UARTDEBUG_H
#define UARTDEBUG_H

#include "SDKTypes.h"
#if 0
typedef unsigned char uint8;           /**< \brief 8 bit unsigned value  */
typedef unsigned short uint16;         /**< \brief 16 bit unsigned value */
typedef unsigned long uint32;           /**< \brief 32 bit unsigned value */
typedef unsigned long long uint64;     /**< \brief 64 bit unsigned value */

typedef signed char sint8;             /**< \brief 8 bit signed value  */
typedef signed short sint16;           /**< \brief 16 bit signed value */
typedef signed long sint32;             /**< \brief 32 bit signed value */
typedef signed long long int64;        /**< \brief 64 bit signed value */
#endif

#define RX_ID0 0x10 // debug
#define RX_ID1 0x20 // debug
#define RX_ID2 0x01 // testmode
#define RX_ID3 0x03 // testmode
#define RX_ID4 0x05 // testmode
#define RX_ID5 0x07 // testmode

extern void Wr_Sig_U8(u8 signum, u8 value);
extern u8 Rd_Sig_U8(u8 signum);
extern void Rst_Sig_U8(u8 signum);
extern u8 Rd_Sig_Id(void);
extern void UartSendFrameStart(u8 id);

extern void UART2_Tx_Handle(void);
extern void UART2_Rx_Handle(void);

#endif
