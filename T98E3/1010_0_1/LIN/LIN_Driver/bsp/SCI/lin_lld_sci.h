/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************/
/**************************************************************************//**
* @addtogroup SCI_group
* @{
******************************************************************************/
/**************************************************************************//**
*
* @file      bsp/SCI/lin_lld_sci.h
*
* @author    FPT Software
*
* @brief     SCI for LIN network
*
******************************************************************************/

/******************************************************************************
 *
 * History:
 *
 * 20101027   v1.0  First version
 * 20111005   v1.1  Updated hardware support, multi timers
 *
 *****************************************************************************/

#ifndef __LIN_LLD_SCI
#define __LIN_LLD_SCI

/* MODULE LIN_LLD_SCI. */

#include "lin_reg.h"
#include "lin_cfg.h"
#include "lin_sw.h"

#ifndef SCI_VERSION
  #error "SCI_VERSION is not defined in lin_hw_cfg.h"
#endif

/*** MARCOS ***/
#if (SCI_VERSION == SCI_V5)
  #define LIN_LLD_SCI_MCU_RESET          /**< MCU reset */
#endif /* End (SCI_VERSION == SCI_V5) */

/* Lin status bit mask */
#define LIN_STA_SUCC_TRANSFER           1         /**< LIN status bit mask: success transfer */
#define LIN_STA_ERROR_RESP              2         /**< LIN status bit mask: error in response */
#define LIN_STA_BUS_ACTIVITY            4         /**< LIN status bit mask: bus activity */
#define LIN_STA_FRAME_ERR               8         /**< LIN status bit mask: frame error */
#define LIN_STA_CHECKSUM_ERR            16        /**< LIN status bit mask: checksum error */
#define LIN_STA_READBACK_ERR            32        /**< LIN status bit mask: readback error */
#define LIN_STA_PARITY_ERR              64        /**< LIN status bit mask: parity error */
#define LIN_STA_RESET                   128       /**< LIN status bit mask: reset */

/*增加超时标志*/
extern l_u8 IDEA_TimeOut;
/*增加信号错误标志位*/
extern l_u8 Lin_Error_Flag;
#if (LIN_MODE == _SLAVE_MODE_)
/* Low-level API prototype */

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_init(l_ifc_handle iii)
* @brief SCI v5 init
*
* @param iii <B>[IN]</B> lin interface handle
*
* @SDD_ID LIN_SDD_168
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#l_u16</B> <I>temp</I>
*
*
* @details Init SCI for LIN network
*
*
* @see #lin_goto_idle_state
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_init(l_ifc_handle iii);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_deinit()
* @brief SCI deinit
*
* @SDD_ID LIN_SDD_169
* @endif
*
* @return #void
*
* @details
*   Deinit SCI for LIN network
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_deinit(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_tx_wake_up()
* @brief This function requests to send wake up signal via SCI channel
*
*
* @SDD_ID LIN_SDD_170
* @endif
*
* @return #void
*
*
* @details
*   This function requests to send wake up signal via SCI channel
*   Send 4Tbit to 64 Tbit
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_tx_wake_up(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_int_enable()
* @brief This function enables SCI Interrupt
*
* @SDD_ID LIN_SDD_171
* @endif
*
* @return #void
*
* @details
*   This function enables SCI Interrupt
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_int_enable(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_int_disable()
* @brief This function disables SCI Interrupt
*
* @SDD_ID LIN_SDD_172
* @endif
*
* @return #void
*
* @details
*   This function disables SCI Interrupt
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_int_disable(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_ignore_response()
* @brief Set low level ignore flag lin_lld_ignore_flag
*
* @SDD_ID LIN_SDD_173
* @endif
*
* @return #void
*
* @details
*   Set low level ignore flag lin_lld_ignore_flag
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_ignore_response(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_set_low_power_mode()
* @brief Request to enter low power mode in SCI Driver
*
* @SDD_ID LIN_SDD_174
* @endif
*
* @return #void
*
* @details
*   Request to enter low power mode in SCI Driver
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_set_low_power_mode(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_rx_response(l_u8  msg_length)
*
* @param msg_length <B>IN</B> length of response data expect to wait
*
* @brief This function requests to receive response data of LIN frame via SCI channel
*
* @SDD_ID LIN_SDD_175
* @endif
*
* @return #void
*
* @details
*   This function requests to receive response data of LIN frame via SCI channel
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_rx_response(l_u8  msg_length);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_rx()
*
* @brief SCI RX
*
* @SDD_ID LIN_SDD_176
* @endif
*
* @return #void
*
* @details
*   SCI RX
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_rx(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_tx()
*
* @brief SCI TX
*
* @SDD_ID LIN_SDD_177
* @endif
*
* @return #void
*
* @details
*   SCI TX
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_tx(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_aux()
*
* @brief SCI AUX
*
* @SDD_ID LIN_SDD_178
* @endif
*
* @return #void
*
* @details
*   SCI AUX
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_aux(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_tx_response()
*
* @brief This function requests to send first data and set lin_lld_state to SEND_DATA
*
* @SDD_ID LIN_SDD_179
* @endif
*
* @return #void
*
*
* @details
*   This function requests to send first data and set lin_lld_state to SEND_DATA
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_tx_response(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn l_u8 lin_lld_sci_get_status()
*
* @brief Get LIN status ( return lin_status )
*
* @SDD_ID LIN_SDD_180
* @endif
*
* @return #l_u8
*
* @details
*   Get LIN status ( return lin_status )
*//*END*----------------------------------------------------------------------*/
l_u8 lin_lld_sci_get_status(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn l_u8 lin_lld_sci_get_state()
*
* @brief This function is to get state of Low level layer
*
* @SDD_ID LIN_SDD_181
* @endif
*
* @return #l_u8
*
* @details
*   This function is to get state of Low level layer
*//*END*----------------------------------------------------------------------*/
extern l_u8 lin_lld_sci_get_state(void);

extern l_u16 lin_lld_sci_get_idle_time(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_timeout()
*
* @brief This function is called in period Tbit in order to check timeout for IDLE and MAXFRAME
*
* @SDD_ID LIN_SDD_
* @endif
*
* @return #void
*
* @details
*   This function is called in period Tbit in order to check timeout for IDLE and MAXFRAME
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_timeout(void);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_isr()
*
* @brief SCI Interrupt service routine that handles LIN Communication
*
* @SDD_ID LIN_SDD_189
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#l_u8</B> <I>sci_flag_sr1</I>
*   -# <B>#l_u8</B> <I>tmp_byte</I>
*
* @details
*   SCI Interrupt service routine that handles LIN Communication
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_isr(void);

/*** INTERNAL FUNCTIONS ***/

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_goto_idle_state()
*
* @brief Enter IDLE state
*
* @SDD_ID LIN_SDD_182
* @endif
*
* @return #void
*
* @details
*   Enter IDLE state
*//*END*----------------------------------------------------------------------*/
void lin_goto_idle_state(void);
void lin_lld_sci_lastbyte_tx_set(l_u8 byte);
l_u8 lin_lld_sci_lastbyte_tx_get(void);

#endif /* End (LIN_MODE == _SLAVE_MODE_) */

#if LIN_MODE == _MASTER_MODE_

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_init(sci_channel_name  channel, l_ifc_handle iii)
*
* @param channel <B>IN</B> sci channel name
* @param iii <B>IN</B> LIN interface name
*
* @brief SCI Init
*
* @SDD_ID LIN_SDD_97
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#l_u16</B> <I>*tmp</I>
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*   -# <B>#lin_configuration</B> <I>*lconf_p</I>
*
* @static_global_var
*   -# <B>#lin_ifc_configuration</B>
*
* @see lin_goto_idle_state
*
* @details
*   This function is inited SCI for LIN network
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_init(sci_channel_name  channel, l_ifc_handle iii);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_deinit(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief SCI deinit
*
* @SDD_ID LIN_SDD_98
* @endif
*
* @return #void
*
*
* @static_global_var
*   -# <B>#lin_node</B>
*   -# <B>#lnode_p</B>
*
* @see lin_lld_sci_int_disable
* @see lin_node_descrs
*
* @details
*   This function is deinited SCI
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_deinit(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_tx_header(sci_channel_name  channel, l_u8  pid_id)
*
* @param channel <B>IN</B> sci channel name
* @param pid_id <B>IN</B> PID to be send
*
* @brief This function requests to send header of LIN frame via SCI channel
*
* @SDD_ID LIN_SDD_99
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
*
* @see lin_process_parity
* @see lin_node_descrs
*
* @details
*   This function requests to send header of LIN frame via SCI channel
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_tx_header(sci_channel_name  channel, l_u8  pid_id);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_tx_wake_up(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief This function requests to send wake up signal via SCI channel.
*
* @SDD_ID LIN_SDD_100
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @see lin_goto_idle_state
*
* @details
*   This function requests to send wake up signal via SCI channel.
*   Send 4Tbit to 64 Tbit
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_tx_wake_up(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_int_enable(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief This function enables SCI Interrupt
*
* @SDD_ID LIN_SDD_101
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
*
* @details
*   This function enables SCI Interrupt
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_int_enable(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_int_disable(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief This function disables SCI Interrupt
*
* @SDD_ID LIN_SDD_102
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
*
* @details
*   This function disables SCI Interrupt
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_int_disable(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_ignore_response(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief Set low level ignore flag lin_lld_ignore_flag
*
* @SDD_ID LIN_SDD_103
* @endif
*
* @return #void
*
* @see lin_goto_idle_state
*
* @details
*   Set low level ignore flag lin_lld_ignore_flag
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_ignore_response(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_set_low_power_mode(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief SRequest to enter low power mode in SCI Driver
*
* @SDD_ID LIN_SDD_104
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @details
*   Request to enter low power mode in SCI Driver
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_set_low_power_mode(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_rx_response(sci_channel_name  channel, l_u8  msg_length)
*
* @param channel <B>IN</B> sci channel name
* @param msg_length <B>IN</B> length of response data expect to wait
*
* @brief This function requests to receive response data of LIN frame via SCI channel
*
* @SDD_ID LIN_SDD_105
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @details
*   This function requests to receive response data of LIN frame via SCI channel
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_rx_response(sci_channel_name  channel,l_u8  msg_length);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_rx(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief SCI RX
*
* @SDD_ID LIN_SDD_106
* @endif
*
* @return #void
*
* @details
*   SCI RX
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_rx(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_tx(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief SCI TX
*
* @SDD_ID LIN_SDD_107
* @endif
*
* @return #void
*
* @details
*   SCI TX
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_tx(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_aux(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief SCI AUX
*
* @SDD_ID LIN_SDD_108
* @endif
*
* @return #void
*
* @details
*   SCI AUX
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_aux(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_tx_response(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief This function requests to send first data and set lin_lld_state to SEND_DATA
*
* @SDD_ID LIN_SDD_109
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @details
*   This function requests to send first data and set lin_lld_state to SEND_DATA
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_tx_response(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn l_u8 lin_lld_sci_get_status(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief Get LIN status ( return lin_status )
*
* @SDD_ID LIN_SDD_110
* @endif
*
* @return #l_u8
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @details
*   Get LIN status ( return lin_status )
*//*END*----------------------------------------------------------------------*/
l_u8 lin_lld_sci_get_status(sci_channel_name  channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn l_u8 lin_lld_sci_get_state(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief Get LIN state ( return state )
*
* @SDD_ID LIN_SDD_
* @endif
*
* @return #l_u8
*
* @local_var
*   -# <B>#lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @details
*   Get LIN state ( return state )
*//*END*----------------------------------------------------------------------*/
l_u8 lin_lld_sci_get_state(sci_channel_name channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_timeout(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief This function is called in period Tbit in order to check timeout for IDLE and MAXFRAME
*
* @SDD_ID LIN_SDD_111
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#register lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @details
*   This function is called in period Tbit in order to check timeout for IDLE and MAXFRAME
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_timeout(sci_channel_name channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_lld_sci_isr(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief SCI Interrupt service routine that handles LIN Communication
*
* @SDD_ID LIN_SDD_117
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#l_u8 </B> <I>sci_flag_sr1</I>
*   -# <B>#l_u8 </B> <I>tmp_byte</I>
*   -# <B>#register lin_node </B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @see #lin_goto_idle_state
* @see #lin_checksum
* @see #lin_process_parity
*
* @details
*   SCI Interrupt service routine that handles LIN Communication
*//*END*----------------------------------------------------------------------*/
void lin_lld_sci_isr(sci_channel_name channel);

/*FUNCTION*--------------------------------------------------------------*//**
* @fn void lin_goto_idle_state(sci_channel_name  channel)
*
* @param channel <B>IN</B> sci channel name
*
* @brief Enter IDLE state
*
* @SDD_ID LIN_SDD_112
* @endif
*
* @return #void
*
* @local_var
*   -# <B>#register lin_node</B> <I>*lnode_p</I>
*
* @static_global_var
*   -# <B>#lin_node_descrs</B>
*
* @details
*   Enter IDLE state
*//*END*----------------------------------------------------------------------*/
void lin_goto_idle_state(sci_channel_name channel);
#endif /* End (LIN_MODE == _MASTER_MODE_) */

#endif /* ifndef _LIN_LLD_SCI */

/**
* @}
*/
