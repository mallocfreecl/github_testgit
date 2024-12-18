/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************/
/**************************************************************************//**
* @addtogroup J2602_core_api_group
* @{
******************************************************************************/
/**************************************************************************//**
*
* @file      lin_j2602_proto.c 
*
* @author    FPT Software
*
* @brief     J2602 LIN protocol functions
*
******************************************************************************/
/******************************************************************************
 *
 * History:
 *
 * 20090408		v1.0	First version
 *
 *****************************************************************************/
 
#include "lin_j2602_proto.h"

/* ---------------------------- For 1 interface -----------------------------------*/
#if LIN_MODE == _SLAVE_MODE_
#if LIN_PROTOCOL != PROTOCOL_21

void lin_update_word_status_j2602 
  (
    /* [IN] event of Low-level driver */
    lin_lld_event_id event_id, 
    /* [IN] PID of frame */
    l_u8 pid
  ) 
{
  lin_word_status.word = ((lin_error_in_response) | (lin_successful_transfer << 1) |
                         ((lin_error_in_response | lin_successful_transfer) << 2) |
                         (pid << 8)) & 0xFF0F;
}

void lin_update_status_byte 
  (
    /* [IN] interface name */
    lin_lld_event_id event_id
  ) 
{

  l_u8 *signal_data_ptr;  
  signal_data_ptr = lin_signal_tbl[response_error].sig_data; 
  switch (event_id){
    /* Parity error */
    case LIN_LLD_PID_ERR:
      /* Set ID Parity Error 0x07 */
      *(signal_data_ptr) = 0x07;
      break;
    /* Byte Field Framing Error*/
    case LIN_LLD_FRAME_ERR:
      /* Set Byte Field Framing Error 0x06 */      
      *(signal_data_ptr) = 0x06;      
      break;
    /* Checksum error */
    case LIN_LLD_CHECKSUM_ERR:
      /* Set Checksum error 0x05 */
      *(signal_data_ptr) = 0x05;    
      break;
    /* Data error */
    case LIN_LLD_READBACK_ERR:
      /* Set Data error 0x04 */
      *(signal_data_ptr) = 0x04;
      break;
     default:
      break; 
  }
  *(signal_data_ptr)|=0x01;
}
#endif /* End (LIN_PROTOCOL != PROTOCOL_21) */
#endif /* End of (LIN_MODE == _SLAVE_MODE_)*/

/*-----------------------------------------------------------------------*/
#if LIN_MODE == _MASTER_MODE_

void lin_update_word_status_j2602 
  (
    /* [IN] interface name */
    l_ifc_handle iii, 
    /* [IN] event of Low-level driver */
    lin_lld_event_id event_id, 
    /* [IN] PID of frame */
    l_u8 pid
  ) 
{
  l_u8 err_in_res, suc_in_tras;
  lin_word_status_str *word_status;
  lin_configuration const *conf;

  conf = &(lin_ifc_configuration[iii]);
  err_in_res = *(conf->error_in_response);
  suc_in_tras = *(conf->successful_transfer); 
  
  word_status = conf->word_status;
  word_status->bit.error_in_res = err_in_res;
  word_status->bit.successful_transfer = suc_in_tras;
  word_status->bit.overrun = (err_in_res | suc_in_tras);
  word_status->bit.last_pid = pid;
}

void lin_update_status_byte 
  (
    /* [IN] interface name */
    l_ifc_handle iii, 
    /* [IN] interface name */
    lin_lld_event_id event_id
  ) 
{
  l_u8 *signal_data_ptr;
  lin_configuration const *conf;

  conf = &(lin_ifc_configuration[iii]);  
  signal_data_ptr = conf->signal_tbl[conf->node_attribute->response_error].sig_data; 
  switch (event_id){
    /* Parity error */
    case LIN_LLD_PID_ERR:
      /* Set ID Parity Error 0x07 */
      *(signal_data_ptr) = 0x07;
      break;
    /* Byte Field Framing Error*/
    case LIN_LLD_FRAME_ERR:
      /* Set Byte Field Framing Error 0x06 */      
      *(signal_data_ptr) = 0x06;      
      break;
    /* Checksum error */
    case LIN_LLD_CHECKSUM_ERR:
      /* Set Checksum error 0x05 */
      *(signal_data_ptr) = 0x05;    
      break;
    /* Data error */
    case LIN_LLD_READBACK_ERR:
      /* Set Data error 0x04 */
      *(signal_data_ptr) = 0x04;
      break;
    default:
      break; 
  }
}
#endif /* End of (LIN_MODE == _SLAVE_MODE_)*/
/**
* @}
*/
