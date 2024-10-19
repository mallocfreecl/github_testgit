#ifndef UARTDEBUG_C
#define UARTDEBUG_C

#include "uartdebug.h"
#include "driver_generic.h"
#include "sci.h"

typedef enum
{
  UART_1,
  UART_2
} _uart_num;

typedef enum
{
  IDErr,
  IDCheckErr,
  ChecksumErr,
  TimeoutErr
} _uart_errtype;

typedef struct
{
  u8 id;
  u8 state;
  u8 length;
  u8 cnt;
  u8 buffer[8];
  u8 chksumbuffer[2];
  u16 checksum;
  u8 timeoutcnt;
  u8 timeouten;
} _uart_state_machine;

_uart_state_machine Uart_RxState_Machine;
_uart_state_machine Uart_TxState_Machine;

#define TX_LEN 0x08
#define RX_LEN 0x08
#define UART_NUM UART_2

#define RECEIVE_ID_STATE 0
#define CHECK_ID_STATE 1
#define SEND_DATA_STATE 2
#define RECEIVE_DATA_STATE 3
#define SEND_COMPLETE_STATE 4
#define CHECK_CHKSUM_STATE 5
#define SEND_LASTCHK_STATE 6
#define SEND_ID_STATE 7
#define SEND_ANTIID_STATE 8
#define SEND_IDLE_STATE 9

#define TIMEOUT_CNT_EN 1
#define TIMEOUT_CNT_DIS 0
#define TIMEOUT5MS_1MSBASE 5

u8 uart_sig_ttbl[8];
u8 uart_sig_rtbl[8];
u8 uart_sig_id;

static u8 GetUartReciveData(_uart_num uart_num);
static void UartErrHandle(_uart_errtype errtype);
static void UartSendByte(_uart_num uart_num, u8 data);
u8 Rd_Sig_U8(u8 signum);
u8 Rd_Sig_Id(void);
void Wr_Sig_U8(u8 signum, u8 value);
void UART2_Rx_Handle(void);
void UART2_Tx_Handle(void);
void UartSendFrameStart(u8 id);

void copymemory(u8 des[], u8 src[], u8 length)
{
  u8 i;
  for (i = 0; i < length; i++)
  {
    des[i] = src[i];
  }
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
static u8 GetUartReciveData(_uart_num uart_num)
{
  u8 ch;

  _sci_receive_byte(SCI, &ch, false);

  return ch;
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
static void UartSendByte(_uart_num uart_num, u8 data)
{
  _sci_transmit_byte(SCI, data, false);
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void Wr_Sig_U8(u8 signum, u8 value)
{
  uart_sig_ttbl[signum] = value;
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
u8 Rd_Sig_U8(u8 signum)
{
  return uart_sig_rtbl[signum];
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void Rst_Sig_U8(u8 signum)
{
  uart_sig_rtbl[signum] = 0x00;
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
u8 Rd_Sig_Id(void)
{
  return uart_sig_id;
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
static void UartErrHandle(_uart_errtype errtype)
{
  Uart_RxState_Machine.timeouten = TIMEOUT_CNT_DIS;
  Uart_RxState_Machine.timeoutcnt = 0;
  Uart_RxState_Machine.state = RECEIVE_ID_STATE;
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void UART2_Rx_Handle(void)
{
  u8 temp;
  temp = GetUartReciveData(UART_NUM);

  Uart_RxState_Machine.timeouten = TIMEOUT_CNT_EN;
  Uart_RxState_Machine.timeoutcnt = 0;

  if (Uart_RxState_Machine.state == RECEIVE_ID_STATE)
  {
    if ((temp == RX_ID0) || (temp == RX_ID1) || (temp == RX_ID2) || (temp == RX_ID3) || (temp == RX_ID4) ||
        (temp == RX_ID5))
    {
      Uart_RxState_Machine.id = temp;
      Uart_RxState_Machine.state = CHECK_ID_STATE;
    }
    else
    {
      UartErrHandle(IDErr);
    }
  }
  else if (Uart_RxState_Machine.state == CHECK_ID_STATE)
  {
    u8 antitemp;
    antitemp = (~temp);
    if (Uart_RxState_Machine.id == antitemp)
    {
      Uart_RxState_Machine.state = RECEIVE_DATA_STATE;
      Uart_RxState_Machine.length = RX_LEN;
      Uart_RxState_Machine.cnt = 0;
      Uart_RxState_Machine.checksum = 0;
    }
    else
    {
      UartErrHandle(IDCheckErr);
    }
  }
  else if (Uart_RxState_Machine.state == RECEIVE_DATA_STATE)
  {
    Uart_RxState_Machine.buffer[Uart_RxState_Machine.cnt] = temp;
    Uart_RxState_Machine.checksum += temp;
    Uart_RxState_Machine.cnt++;
    if (Uart_RxState_Machine.cnt >= Uart_RxState_Machine.length)
    {
      Uart_RxState_Machine.state = CHECK_CHKSUM_STATE;
      Uart_RxState_Machine.cnt = 0;
    }
  }
  else if (Uart_RxState_Machine.state == CHECK_CHKSUM_STATE)
  {
    Uart_RxState_Machine.chksumbuffer[Uart_RxState_Machine.cnt] = temp;
    Uart_RxState_Machine.cnt++;
    if (Uart_RxState_Machine.cnt >= 2)
    {
      u16 chksum = 0;
      chksum = ((u16)Uart_RxState_Machine.chksumbuffer[0] << 8) | Uart_RxState_Machine.chksumbuffer[1];
      if (chksum == Uart_RxState_Machine.checksum)
      {
        uart_sig_id = Uart_RxState_Machine.id;
        copymemory(uart_sig_rtbl, Uart_RxState_Machine.buffer, Uart_RxState_Machine.length);
        Uart_RxState_Machine.state = RECEIVE_ID_STATE;
        Uart_RxState_Machine.timeouten = TIMEOUT_CNT_DIS;
        Uart_RxState_Machine.timeoutcnt = 0;
      }
      else
      {
        UartErrHandle(ChecksumErr);
      }
    }
  }
  else
  {
  }
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void UART2_Tx_Handle(void)
{
  if (Uart_TxState_Machine.state == SEND_ID_STATE)
  {
    u8 temp;
    temp = Uart_TxState_Machine.id;
    UartSendByte(UART_NUM, ~temp);
    Uart_TxState_Machine.state = SEND_DATA_STATE;
  }
  else if (Uart_TxState_Machine.state == SEND_DATA_STATE)
  {
    if (Uart_TxState_Machine.cnt < Uart_TxState_Machine.length)
    {
      Uart_TxState_Machine.checksum += Uart_TxState_Machine.buffer[Uart_TxState_Machine.cnt];
      UartSendByte(UART_NUM, Uart_TxState_Machine.buffer[Uart_TxState_Machine.cnt]);
      Uart_TxState_Machine.cnt++;
    }
    else
    {
      UartSendByte(UART_NUM, Uart_TxState_Machine.checksum >> 8);
      Uart_TxState_Machine.state = SEND_LASTCHK_STATE;
    }
  }
  else if (Uart_TxState_Machine.state == SEND_LASTCHK_STATE)
  {
    UartSendByte(UART_NUM, Uart_TxState_Machine.checksum);
    SDK_SCITxIntEn(false);

    Uart_TxState_Machine.state = SEND_COMPLETE_STATE;
    Uart_TxState_Machine.state = SEND_IDLE_STATE;
  }
  else if (Uart_TxState_Machine.state == SEND_COMPLETE_STATE)
  {
  }
  else
  {
  }
}
/****************************************************************
 * FUNCTION    :
 * DESCRIPTION :
 * INPUTS      :
 * OUTPUTS     :
 *****************************************************************/
void UartSendFrameStart(u8 id)
{
  Uart_TxState_Machine.state = SEND_ID_STATE;
  Uart_TxState_Machine.id = id;
  Uart_TxState_Machine.cnt = 0;
  Uart_TxState_Machine.checksum = 0;
  Uart_TxState_Machine.length = TX_LEN;
  copymemory(Uart_TxState_Machine.buffer, uart_sig_ttbl, Uart_TxState_Machine.length);
  UartSendByte(UART_NUM, Uart_TxState_Machine.id);
  SDK_SCITxIntEn(true);
}
#endif
