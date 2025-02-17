/******************************************************************************
*
* Freescale Semiconductor Inc.
* (c) Copyright 2008-2009 Freescale Semiconductor, Inc.
* ALL RIGHTS RESERVED.
*
******************************************************************************/
/**************************************************************************//**
* @addtogroup common_core_api_group
* @{
******************************************************************************/
/**************************************************************************//**
*
* @file      lin_common_proto.c
*
* @author    FPT Software
*
* @brief     Common LIN protocol functions
*
******************************************************************************/
/******************************************************************************
 *
 * History:
 *
 * 20090408		v1.0	First version
 *
 *****************************************************************************/
 
#include "lin_sw.h"
#include "lin_common_proto.h"
#include "lin_lin21_proto.h"
#include "lin_j2602_proto.h"
#include "lin_common_api.h"
/* Unuse for GPIO */
#if ( _LIN_GPIO_ == 0 ) && !defined(_MC9S08SC4_H)
#include "lin_commontl_proto.h"
#include "lin_lin21tl_api.h"
#include "lin_j2602tl_api.h"
#endif /* End ( _LIN_GPIO_ == 0 ) && !defined(_MC9S08SC4_H) */

/**
* @var l_u8 frame_signal_error
* frame or signal error
*/
l_u8 frame_signal_error;

/* ---------------------------- For 1 interface -----------------------------------*/
#if LIN_MODE == _SLAVE_MODE_
/* Global variables */
/**
* @var l_u8 frame_index
* index of frame in frames table
*/
l_u8 frame_index;
l_u8 frm_index_b;

void lin_pid_response_callback_handler
  (
    /* [IN] event id */
    lin_lld_event_id event_id,
    /* [IN] PID to process */
    l_u8 pid
  )
{
  if (LIN_LLD_PID_OK == event_id){
    lin_process_pid(pid);
  } else if (LIN_LLD_TX_COMPLETED == event_id){
    lin_update_tx(pid);
  } else if (LIN_LLD_RX_COMPLETED == event_id){
    lin_update_rx(pid);
  } else if (LIN_LLD_BUS_ACTIVITY_TIMEOUT == event_id){
    lin_bus_activity_timeout(pid);
  } else {
    lin_handle_error(event_id, pid);
  }

} /* end of lin_pid_response_callback_handler() */


void lin_process_pid
  (
    /* [IN] PID to process */
    l_u8 pid
  )
{
  l_u8 action;
  const lin_frame_struct *lin_frame_ptr;
  
  /* Clear goto sleep flag */
  lin_goto_sleep_flg = 0;
  
  /* get frame index */
  frame_index = lin_get_frame_index(pid);
  if (0xFF == frame_index){
    action = 0;
  } else {
    action = 1;
    lin_frame_ptr = &(lin_frame_tbl[frame_index]);
    /* PID belongs to this node, then check type of frame */
#if (LIN_PROTOCOL == PROTOCOL_21)
    if (LIN_FRM_EVNT == lin_frame_ptr->frm_type){
      if (0 != lin_frame_flag_tbl[*(lin_frame_ptr->frame_data)]){
         /* Frame is updated */
         lin_make_res_evnt_frame(lin_configuration_RAM[1 + *(lin_frame_ptr->frame_data)]);
         /* Set response */
          action = 2;     
       } else {
          action = 0;
       }
    } else {
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
      if (LIN_RES_PUB == lin_frame_ptr->frm_response){
        if (LIN_FRM_UNCD == lin_frame_ptr->frm_type){
          lin_process_uncd_frame(pid, MAKE_UNCONDITIONAL_FRAME);
          action = 2;
        } 
/* Unuse for GPIO */
#if (_LIN_GPIO_ == 0) && !defined(_MC9S08SC4_H)
        else {
          if(0 == tl_slaveresp_cnt){
            action = 0;
          }else{
#if _TL_FRAME_SUPPORT_  ==  _TL_MULTI_FRAME_
            /* Check error in multi frames */
            if(tl_service_status != LD_SERVICE_ERROR){
#endif
            lin_make_res_diag_frame();
            tl_slaveresp_cnt--; 
            action = 2;
#if _TL_FRAME_SUPPORT_  ==  _TL_MULTI_FRAME_
            }else{
              /* Check is CF */
              /* ignore response when error */
              action = 0;
            }
#endif
          }
        }
#endif /* End (_LIN_GPIO_ == 0) && !defined(_MC9S08SC4_H) */        
      }
#if (LIN_PROTOCOL == PROTOCOL_21)
    }
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
  }
/* Ignore diagnostic frame when interface is GPIO */
#if (_LIN_GPIO_ == 1)
  if (pid == 0x3C || pid == 0x3D){
    action = 0;
  }
#endif /* End (_LIN_GPIO_ == 1) */
  switch (action)
  {
    case 1:
      /* Receive response */
      lin_lld_rx_response(lin_frame_ptr->frm_len);
    break;
    case 2:
      /* Set response */
      lin_lld_set_response(lin_frame_ptr->frm_len);
    break;
    default:
      /* ignore response */
      lin_lld_ignore_response();
    break;
  }
}

void lin_update_rx 
(
    /* [IN] PID to process */
    l_u8 pid
  )
{
  //l_bool pid_found = 0;

  /* Set successful transfer */
  lin_successful_transfer = 1;
  /* PID belongs to this node, then check type of frame */
  if (LIN_FRM_UNCD == lin_frame_tbl[frame_index].frm_type){
    lin_process_uncd_frame(pid, UPDATE_UNCONDITIONAL_FRAME);
  } 
  /* Unuse for GPIO */
#if (_LIN_GPIO_ == 0) && !defined(_MC9S08SC4_H)  
  else if (LIN_FRM_DIAG == lin_frame_tbl[frame_index].frm_type){
    lin_update_rx_diag_frame();
  }
#endif /* End (_LIN_GPIO_ == 0) && !defined(_MC9S08SC4_H) */
 /* Update rx frame flags */  
  lin_flag_frame_handle_tbl[frame_index] = 1;

    /* update word status */
  #if (LIN_PROTOCOL == PROTOCOL_21)
    lin_update_word_status_lin21 (pid);
  #else
    lin_update_word_status_j2602 (LIN_LLD_RX_COMPLETED, pid);
  #endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
}

void lin_update_tx 
(
    /* [IN] PID to process */
    l_u8 pid
  )
{
  /* Set successful transfer */
  lin_successful_transfer = 1;
  /* Clear frame flag */
  lin_frame_flag_tbl[frame_index] = 0;
  if (1 == frame_signal_error){
    /* Set no error in response */
    lin_error_in_response = 0;
    frame_signal_error = 0;
  }
  /* Update transmit flags */
  lin_update_tx_flags(frame_index);        
  /* Set flag in tx frame handle */
  lin_flag_frame_handle_tbl[frame_index] = 1;
  
  /* check event trigger frame and clear flag */
  if (LIN_FRM_EVNT == lin_frame_tbl[frame_index].frm_type){
    lin_frame_flag_tbl[*(lin_frame_tbl[frame_index].frame_data)] = 0;
  }
  /* Update word status */
  #if (LIN_PROTOCOL == PROTOCOL_21)
  lin_update_err_signal();
  lin_update_word_status_lin21 (pid);
  #else
  if (0x3D != pid){
    *lin_signal_tbl[response_error].sig_data = 0;
  }
  lin_update_word_status_j2602 (LIN_LLD_TX_COMPLETED, pid);
  #endif /* End  (LIN_PROTOCOL == PROTOCOL_21) */
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
  if (0x3D == pid){  
    /* process message */
    tl_tx_msg_size--;
    if(0 == tl_tx_msg_size){
      tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
      tl_tx_msg_status = LD_COMPLETED;
      tl_service_status = LD_SERVICE_IDLE;
      tl_diag_state = LD_DIAG_IDLE;
    } else {
      tl_check_timeout = N_MAX_TIMEOUT_CNT;
      tl_check_timeout_type = LD_CHECK_N_AS_TIMEOUT; 
      tl_diag_state = LD_DIAG_TX_PHY;
    }    
  }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */  
}

void lin_handle_error
  (
    /* [IN] event id */
    lin_lld_event_id event_id,
    /* [IN] PID to process */
    l_u8 pid
  )
{
  frame_index = lin_get_frame_index(pid);
  switch (event_id) 
  {
    /* PID error */
    case LIN_LLD_PID_ERR:
      /* do nothing here */
      break;
    /* Frame error */
    case LIN_LLD_FRAME_ERR:
    case LIN_LLD_CHECKSUM_ERR:
    case LIN_LLD_READBACK_ERR:
    case LIN_LLD_NODATA_TIMEOUT:
      if (LIN_FRM_EVNT != lin_frame_tbl[frame_index].frm_type){
      /* Set response error */
          lin_error_in_response = 1;
      }
      /* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
      if (0x3C == pid){
        tl_receive_msg_status = LD_FAILED;
        tl_rx_msg_status = LD_FAILED;
        lin_tl_rx_queue.queue_status = LD_RECEIVE_ERROR;
        tl_slaveresp_cnt = 0;
        tl_diag_state = LD_DIAG_IDLE;
      }else if(0x3D == pid){
        tl_tx_msg_status = LD_FAILED;
        lin_tl_tx_queue.queue_status = LD_TRANSMIT_ERROR;
        tl_diag_state = LD_DIAG_IDLE;
      }
      tl_service_status = LD_SERVICE_ERROR;
#else /* Single frame support */
#if (_LIN_GPIO_ == 0) && !defined(_MC9S08SC4_H)
      if (0x3C == pid){
         tl_slaveresp_cnt = 0;
      }
#endif /* (_LIN_GPIO_ == 0) && !defined(_MC9S08SC4_H) */
#endif /*End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)*/
      break;
    default:
      break;
  }
  /* Update word status */
#if (LIN_PROTOCOL == PROTOCOL_21)
    lin_update_err_signal();
    lin_update_word_status_lin21 (pid);
#else 
    lin_update_status_byte(event_id);
    lin_update_word_status_j2602 (event_id, pid);
#endif  /* End (LIN_PROTOCOL == PROTOCOL_21)*/

}

void lin_bus_activity_timeout
  (
    /* [IN] PID to process */
    l_u8 pid
  )
{
  #if (LIN_PROTOCOL == PROTOCOL_21)
    lin_update_word_status_lin21 (pid);
  #else 
    lin_update_word_status_j2602 (LIN_LLD_BUS_ACTIVITY_TIMEOUT, pid);
  #endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
  /* Change to low power mode */
  lin_lld_set_low_power_mode();
}

void lin_update_tx_flags
  (
    /* [IN] index of frame */
    l_u8 frm_id
  )
{
  const lin_frame_struct *frame_struct_ptr;
  lin_frm2sig *ptr;
  l_u8 i,signal_id;
  
  /* Set flags on tx signal handle */
  frame_struct_ptr = &(lin_frame_tbl[frm_id]);
  ptr = (lin_frm2sig*)(frame_struct_ptr->frame_data);
  /* Find the signal id associated with frame */
  if(LIN_FRM_DIAG != lin_frame_tbl[frm_id].frm_type){
    for (i=0; i < frame_struct_ptr->num_of_sig; i++){
      signal_id = (l_u8)ptr[i].sig_id;
      /* Update signal flags */
      lin_flag_signal_handle_tbl[signal_id] = 1;
    } 
  } 
}
/* Unuse for GPIO */
#if (_LIN_GPIO_ == 0) && !defined(_MC9S08SC4_H)
void lin_update_rx_diag_frame
  (
  )
{
  /* Check goto sleep */
  if(0x00 == lin_lld_response_buffer[1]) {
    lin_goto_sleep_flg = 1;
    lin_lld_set_low_power_mode();
    return;
  }
  /* TL support */
/* Single frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_)
  /* Copy response to diagnostic PDU in TL  */  
  lin_tl_put_pdu();
#endif /*End (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_)*/
  /* Process PDU income*/
  lin_tl_handler();     
}

void lin_make_res_diag_frame 
  (

  )
{
  /* get data from tx queue to response buffer */
  lin_tl_get_pdu();
}
#endif /* End (_LIN_GPIO_ == 0) && !defined(_MC9S08SC4_H) */
l_u8 lin_get_frame_index
  (
    /* [IN] PID of frame */
    l_u8 pid
  )
{
  l_u8 i;
  for (i = LIN_NUM_OF_FRMS; 0 < i; i--){
    if (lin_configuration_RAM[i] == pid){
      return (i - 1);
    }
  }
  return 0xFF;
}

void lin_process_uncd_frame
(
    /* [IN] PID to process */ 
    l_u8 pid,
    /* [IN] make or update */
    l_u8 type
)
{
  l_u8 i, tmp_offset, index, signal_id;
  l_s8 length, to_fill,byte_offset, tmp_byte_data;
  l_u16 tmp16,tmp_sig_size;
  lin_frm2sig *ptr;

  frame_index = lin_get_frame_index(pid);
  ptr = (lin_frm2sig*)(lin_frame_tbl[frame_index].frame_data);
  if (MAKE_UNCONDITIONAL_FRAME == type){
    /* Set frame length */
    lin_lld_response_buffer[0] = lin_frame_tbl[frame_index].frm_len;
    /* Set buffer to 0 */  
    for (i=lin_lld_response_buffer[0]; 0 < i; i--){
      lin_lld_response_buffer[i] = 0xFF;
    }
  }
  for (i=0; i < lin_frame_tbl[frame_index].num_of_sig; i++){
    signal_id = (l_u8)ptr[i].sig_id;
    if (signal_id == response_error){
      frame_signal_error = 1;
    } 
     /* get length of signal */
    length = (lin_signal_tbl[signal_id].sig_size_bit);
    tmp_sig_size = length;             
    tmp_offset = ptr[i].offset;
    /* get index in buffer */
    index = (tmp_offset >> 3) + 1;
    /* Get signal value */
    if (LIN_SIG_SCALAR == lin_signal_tbl[signal_id].sig_type){      /* Get number of bit to fill in the first byte */
      byte_offset = tmp_offset & 0x07;
      to_fill = 8 - (l_s8)(byte_offset);
      if (MAKE_UNCONDITIONAL_FRAME == type){ /* make unconditional frame */
        /* Get data of signal */
        if (length <=8 ){
            tmp16 = (l_u16)l_u8_rd((l_signal_handle)signal_id);
          } else {
            tmp16 = l_u16_rd((l_signal_handle)signal_id);
          }
          /* Packing to frame data */
          tmp_sig_size = (1 << byte_offset)-1;
          tmp_byte_data = (l_u8)(tmp16 << (byte_offset)) | (tmp_sig_size) | (((1 << (8 - length - byte_offset)) - 1) << (byte_offset+length));
          lin_lld_response_buffer[index++] &= tmp_byte_data;
          if (length > to_fill){
            length -= to_fill;
            if (length > 8) {
              lin_lld_response_buffer[index++] = (l_u8)((tmp16 << (byte_offset)) >> 8);
              tmp_byte_data = (l_u8)(tmp16 >> (l_u8)(8+to_fill)) | ((tmp_sig_size) << byte_offset);
              lin_lld_response_buffer[index] &= tmp_byte_data;
            }else if (length == 8){
              lin_lld_response_buffer[index++] = (l_u8)((tmp16 << (byte_offset)) >> 8);
            }
            
             else {
              tmp_byte_data = (l_u8)(tmp16 >> (to_fill)) | ((0xFF) << length);
              lin_lld_response_buffer[index] &= tmp_byte_data;
            }
          }
      } else {
        /* unpacking frame */
        tmp16 = (l_u16)(lin_lld_response_buffer[index++] >> (byte_offset));
        if (length > to_fill){
          length -= to_fill;
          if (length >= 8){
            tmp16 |= (l_u16)(lin_lld_response_buffer[index++] << to_fill);
            tmp16 |= (l_u16)(lin_lld_response_buffer[index] << (l_u8)(8+to_fill));
          } else {
            tmp16 |= (l_u16)(lin_lld_response_buffer[index] << (to_fill));
          }
        }
        tmp16 &= ((1 << tmp_sig_size) - 1);
        /* Check for update */
        if (tmp_sig_size > 8) {
          l_u16_wr_b((l_signal_handle)signal_id, tmp16,frame_index);
        } else if (tmp_sig_size > 1){
          l_u8_wr_b((l_signal_handle)signal_id,(l_u8)tmp16,frame_index);
        } else {
          l_bool_wr_b((l_signal_handle)signal_id, (l_bool)tmp16,frame_index);     
        }        
        /* Update signal flags */
        lin_flag_signal_handle_tbl[signal_id] = 1;
      }
    } else {
      if (MAKE_UNCONDITIONAL_FRAME == type){
        l_bytes_rd((l_signal_handle)signal_id, 0, length>>3, &(lin_lld_response_buffer[index]));
      } else {
        l_bytes_wr_b((l_signal_handle)signal_id, 0, length>>3, &(lin_lld_response_buffer[index]),frame_index);
        /* update RX signal array */   
        lin_flag_signal_handle_tbl[signal_id] = 1;
      }
    }
    if (MAKE_UNCONDITIONAL_FRAME == type){
      lin_signal_flag_tbl[signal_id] = 0;
    }
  } /* end of for */
}
#endif /* End of (LIN_MODE == _SLAVE_MODE_) */

/*-----------------------------------------------------------------------*/
#if LIN_MODE == _MASTER_MODE_

#ifdef MULTI_TIMER_MODE
extern const l_u16 max_tl_timeout_counter[LIN_NUM_OF_IFCS];
#endif /* End MULTI_TIMER_MODE */

void lin_pid_response_callback_handler
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] event id */ 
    lin_lld_event_id event_id, 
    /* [IN] PID to process */ 
    l_u8 pid
  )
{
  if (LIN_LLD_PID_OK == event_id){
    lin_process_pid(iii, pid);
  } else if (LIN_LLD_TX_COMPLETED == event_id){
    lin_update_tx(iii, pid);
  } else if (LIN_LLD_RX_COMPLETED == event_id){
    lin_update_rx(iii, pid);
  } else if (LIN_LLD_BUS_ACTIVITY_TIMEOUT == event_id){
    lin_bus_activity_timeout(iii, pid);
  } else {
    lin_handle_error(iii, event_id, pid);
  }
}

l_u8 lin_tick_callback_handler 
(
    /* [IN] interface name */
    l_ifc_handle iii
  )
{
  lin_schedule_struct *sch;
  l_u8 *current_entry;
  l_u8 frame_index; 
  const lin_configuration *conf;
  lin_tl_descriptor *tl_conf;
  l_u8 *cur_pid;
  l_u8 *_active_schedule_id;     
  
  /* TL support */
  lin_tl_queue *current_pdu;
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
  l_u8 i;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
     
  /* Get current configuration */  
  conf = &lin_ifc_configuration[iii];
  tl_conf = conf->tl_desc;
  /* Get active_schedule_id*/
  _active_schedule_id = conf->active_schedule_id;
  cur_pid = conf->current_pid;

/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
  /* process diagnostic interleaved mode */
  if(*cur_pid == 0x3D && *conf->diagnostic_mode==DIAG_INTER_LEAVE_MODE && *conf->tl_diag_interleave_state == DIAG_NO_RESPONSE){
    /* go back normal schedule table */
    *_active_schedule_id = *conf->previous_schedule_id;
    conf->schedule_start_entry[*_active_schedule_id] = 0;
  }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
  
  sch = (lin_schedule_struct*)&conf->schedule_tbl[*_active_schedule_id];
  
  if (LIN_SCH_TBL_NULL != sch->sch_tbl_type) 
  {
    /* Check if next_transmit is 0 */
    if (0 == *(conf->next_transmit_tick)) 
    {
      /* update word status */
#if (LIN_PROTOCOL == PROTOCOL_21)
      lin_update_word_status_lin21(iii, (lin_lld_event_id)0, *cur_pid);
#else
      lin_update_word_status_j2602(iii, (lin_lld_event_id)0, *cur_pid);
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
      
      /* Check protocol */
#if (LIN_PROTOCOL == PROTOCOL_21)
      if (conf->word_status->bit.etf_collision){
        /* Call collison resolver */
        lin_collision_resolve(iii, *cur_pid) ;
        conf->word_status->bit.etf_collision = 0;
        *(conf->error_in_response)=0;
        /* Update active schedule table */
        sch = (lin_schedule_struct*)&conf->schedule_tbl[*_active_schedule_id];       
      }
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
      
      current_entry = (l_u8 *)&conf->schedule_start_entry[*_active_schedule_id];
        
      /* Set new transmit tick */
      /* Decrease next_transmit_tick by 1 because it will execute this section next period after next_transmit_tick==0. */
      *(conf->next_transmit_tick) = sch->ptr_sch_data[*current_entry].delay_integer-1;
      
      /* Get frame index to send */
      frame_index = (l_u8)sch->ptr_sch_data[*current_entry].frm_id;
      
      if ((frame_index - conf->frame_start) < conf->num_of_frames) {
        *cur_pid = conf->configuration_RAM[frame_index - conf->frame_start + 1];
      }
      
      /* TL support */    
      /* get PDU poiter for MasterRequest frame */ 
      current_pdu = (lin_tl_queue *)&(sch->ptr_sch_data[*current_entry].tl_queue_data);   

/* Single frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_)
    /* Get TL configuration */
      if((LIN_SCH_TBL_NORM == sch->sch_tbl_type)&&(0x3C == *cur_pid))
         tl_conf->tl_tx_single_pdu = current_pdu;
      
      
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */      

      /* increase start entry */
      *current_entry = (* current_entry + 1);
      
      /* Check if it is the last entry */
      if (*current_entry >= sch->num_slots) 
      {
        /* switch schedule table */  
         lin_switch_sch_table(iii); 
         
      } 
      
      if (LIN_FRM_SPRDC == conf->frame_tbl[frame_index].frm_type) 
      {
        /* Sporadic frame */
        *cur_pid = lin_check_sporadic_update(iii, (l_frame_handle)frame_index);
      }
      
      if (0xFF != *cur_pid) 
      {
      
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
        if ((0x3C == *cur_pid) && (LIN_SCH_TBL_DIAG != sch->sch_tbl_type)){
           for(i=0;i<8;i++){
             conf->response_buffer[i+1] = (*current_pdu)[i];
           }
        }
#else /* Single frame support */
        /* Transmit PID */
        if ((0x3C == *cur_pid) || (0x3D == *cur_pid)) 
        {
          if (DIAG_INTER_LEAVE_MODE == conf->diagnostic_mode) 
          {
            *(conf->diagnostic_frame_to_send) = (*(conf->diagnostic_frame_to_send) - 1);
          }
          
        }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
     
        lin_lld_tx_header(iii, *cur_pid);
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) 
        /* process diagnostic interleaved mode */
        if(*cur_pid == 0x3D && *conf->diagnostic_mode==DIAG_INTER_LEAVE_MODE){
          *conf->tl_diag_interleave_state = DIAG_NO_RESPONSE;
          if(INTERLEAVE_MAX_TIMEOUT == (tl_conf->tl_interleave_timeout_counter++)){
            /* switch to normal table */
            *conf->active_schedule_id = *conf->previous_schedule_id;
            conf->schedule_start_entry[*conf->active_schedule_id] = 0;
            /* inform service error */
            *conf->tl_service_status = LD_SERVICE_ERROR;
            *conf->diagnostic_mode= DIAG_NONE;
          }
        }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
        /* Next tick will not start a transmission */
        return 0; 
      }          
    }   /* End (LIN_SCH_TBL_NULL != sch->sch_tbl_type)  */

    /* Decrease next_transmit_tick */
    *(conf->next_transmit_tick) = (*(conf->next_transmit_tick) - 1);
    
    if (0 == *(conf->next_transmit_tick)) 
    {
      /* Next tick will start a transmissioin */  
      return *_active_schedule_id;
    }
  }
  
  return 0;
}

void lin_process_pid
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] PID to process */
    l_u8 pid
  )
{
  l_u8 action;
  l_u8 volatile associate_frame;
  const lin_frame_struct *lin_frame_ptr;
  l_u8 frame_index;
  const lin_configuration *conf;
  lin_tl_descriptor *tl_conf;
        
  /* Get current configuration */  
  conf = &lin_ifc_configuration[iii];
  /* Get TL configuration */
  tl_conf = conf->tl_desc;
  
  /* Clear goto sleeep flag */
  *(conf->goto_sleep_flg) = 0;
  frame_index = lin_get_frame_index(iii, pid);
  if (0xFF == frame_index){
    action = 0;
  } else {
    action = 1;
    lin_frame_ptr = &(conf->frame_tbl[frame_index]);
    /* PID belongs to this node, then check type of frame */
    switch(lin_frame_ptr->frm_type){
      /* Unconditional frame */
      case LIN_FRM_UNCD:
        if (LIN_RES_PUB == lin_frame_ptr->frm_response){
          lin_process_uncd_frame(iii, pid, MAKE_UNCONDITIONAL_FRAME);
          /* Set response */
          action = 2;
        }
        break;
#if (LIN_PROTOCOL == PROTOCOL_21)
      /* Event trigger frame */
      case LIN_FRM_EVNT:
        if (_MASTER_ == conf->function){
          /* Rx response */
          action = 1;
        } else {
          associate_frame = (l_u8)(*(((lin_associate_frame_struct*)(lin_frame_ptr->frame_data))->act_uncn_frm)); 
          if (0 != conf->frame_flg[associate_frame]){
             /* Frame is updated */
             lin_make_res_evnt_frame(iii, conf->configuration_RAM[1 + (associate_frame)-conf->frame_start]);
             /* Set response */
              action = 2;     
           }
        }
        break;
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
      /* Diagnostic frame */
      case LIN_FRM_DIAG:
        if ( LIN_RES_PUB == lin_frame_ptr->frm_response){
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
          action = 2;
          /* Master node */
          if(0x3C == pid){
            if(DIAG_INTER_LEAVE_MODE == *conf->diagnostic_mode){ 
              lin_tl_make_mreq_pdu(iii);
            }
          } else {
            /* Slave mode */
            if((tl_conf->tl_slaveresp_cnt == 0) && (0x3D == pid)) {
              action = 0;
            } else {
#if _TL_FRAME_SUPPORT_  ==  _TL_MULTI_FRAME_
              /* Check error in multi frames */
              if(*conf->tl_service_status != LD_SERVICE_ERROR){
#endif
              lin_make_res_diag_frame(iii, pid);
              tl_conf->tl_slaveresp_cnt--;        
#if _TL_FRAME_SUPPORT_  ==  _TL_MULTI_FRAME_
              }else{
                /* Check is CF */
                /* ignore response when error */
                action = 0;
                break;
              }
#endif
            }
          }
#else /* Single frame support */
          /* TL support */  
          /* Master mode */
          action = 2;
          if(0x3C == pid){
            lin_tl_make_mreq_pdu(iii, 0);
          }else{ 
          /* Slave mode */
            if((tl_conf->tl_slaveresp_cnt == 0) && (0x3D == pid)) {
              action = 0;
            } else {
              lin_make_res_diag_frame(iii, pid);
              tl_conf->tl_slaveresp_cnt--;        
            }
          }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */          
        } else {
            /* Rx response */
            action = 1;
        }
        break;
      default:
        break;
    }
  }
  switch (action)
  {
    case 1:
      /* Receive response */
      lin_lld_rx_response(iii, lin_frame_ptr->frm_len);
    break;
    case 2:
      /* Set response */
      lin_lld_set_response(iii, lin_frame_ptr->frm_len);
    break;
    default:
      /* ignore response */
      lin_lld_ignore_response(iii);
    break;
  }
}

void lin_update_rx
(
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] PID to process */
    l_u8 pid
  )
{

  l_bool pid_found = 0;
  l_u8 frame_index;
  const lin_configuration *conf;   
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
  lin_tl_descriptor *tl_conf;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
  /* Get current configuration */  
  conf = &lin_ifc_configuration[iii]; 
   
   /* Set successful transfer */ 
  *(conf->successful_transfer) = 1;
  frame_index = lin_get_frame_index(iii, pid);
  if (0xFF != frame_index){
    /* This PID doesn't belong to this node */
    /* PID belongs to this node, then check type of frame */
    switch(conf->frame_tbl[frame_index].frm_type){
      /* Unconditional frame */
      case LIN_FRM_UNCD:
        lin_process_uncd_frame(iii,pid,UPDATE_UNCONDITIONAL_FRAME);
        break;
      /* Event trigger frame */
      case LIN_FRM_EVNT:
        *(conf->error_in_response) = 0;
        lin_update_rx_evnt_frame(iii, pid);
        break;
      /* Diagnostic frame */
      case LIN_FRM_DIAG:
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) 
          /* process diagnostic interleaved mode */
          if(pid == 0x3D && *conf->diagnostic_mode==DIAG_INTER_LEAVE_MODE){
            tl_conf = conf->tl_desc;
            *conf->tl_diag_interleave_state = DIAG_RESPONSE;
            /* do not check interleave time out counter when response receive */
            tl_conf->tl_interleave_timeout_counter = 0;
          }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
          
          lin_update_rx_diag_frame(iii, pid);
        break;
      default:
        break;
    }
    /* Update rx frame flags */  
    lin_flag_frame_handle_tbl[frame_index] = 1;
      /* update word status */
    if (_SLAVE_ == conf->function){
#if (LIN_PROTOCOL == PROTOCOL_21)
        lin_update_word_status_lin21 (iii, LIN_LLD_RX_COMPLETED, pid);
#else
        lin_update_word_status_j2602 (iii, LIN_LLD_RX_COMPLETED, pid);
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
    }
  }
}

void lin_update_tx 
(
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] PID to process */
    l_u8 pid
  )
{
  l_u8 frame_index; 
  const lin_configuration *conf; 
  const lin_frame_struct *lin_frame_ptr; 
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
  lin_tl_descriptor *tl_conf;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)*/
  
  /* Get current configuration */  
  conf = &lin_ifc_configuration[iii];
  /* Set successful transfer */
  *(conf->successful_transfer) = 1;
  if (1 == frame_signal_error){
      /* Set no error in response */
      *(conf->error_in_response) = 0;
      frame_signal_error = 0;
  }
  /* Find frame index by pid */  
  frame_index = lin_get_frame_index(iii, pid);
  /* Clear frame flag */
  conf->frame_flg[frame_index] = 0;
  /* Update transmit flags */
  lin_update_tx_flags(iii, frame_index);
  /* Set flag in tx frame handle */
  lin_flag_frame_handle_tbl[frame_index] = 1;
    /* check event trigger frame and clear flag */
  if (LIN_FRM_EVNT == conf->frame_tbl[frame_index].frm_type){
    lin_frame_ptr = &(conf->frame_tbl[frame_index]);
    lin_frame_flag_tbl[(l_u8)(*(((lin_associate_frame_struct*)(lin_frame_ptr->frame_data))->act_uncn_frm))] = 0;
  }
  
/* Multi frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
  if ((0x3C == pid) && _MASTER_ == conf->function && (DIAG_INTER_LEAVE_MODE == *conf->diagnostic_mode)){
    /* Callback to trtansport layer */
    tl_process_mreq(iii);
  }else if(_SLAVE_ == conf->function && 0x3D == pid){
    /* Get TL configuration */
    tl_conf = conf->tl_desc; 
  
    /* process messgae */
    tl_conf->tl_tx_msg_size--;
    if(0 == tl_conf->tl_tx_msg_size){
      tl_conf->tl_check_timeout_type = LD_NO_CHECK_TIMEOUT;
      tl_conf->tl_tx_msg_status = LD_COMPLETED;
      *conf->tl_service_status = LD_SERVICE_IDLE;
    } else {
    
#ifdef MULTI_TIMER_MODE
   tl_conf->tl_check_timeout = max_tl_timeout_counter[iii];
#else
      tl_conf->tl_check_timeout = N_MAX_TIMEOUT_CNT;
#endif /* End MULTI_TIMER_MODE */
      tl_conf->tl_check_timeout_type = LD_CHECK_N_AS_TIMEOUT; 
    }
  }
#else /* Single frame support */    
  if(0x3C == pid && _MASTER_ == conf->function)
  if(LIN_SCH_TBL_DIAG == conf->schedule_tbl[*conf->active_schedule_id].sch_tbl_type){
    l_u8 NAD = conf->response_buffer[1];         
    
    /* switch to slave response - next schedule table */
    *conf->active_schedule_id += 1;
    
    conf->schedule_start_entry[*conf->active_schedule_id] = 0;
    conf->tl_desc->tl_cnt_to_send = 0;
  }else if(0x3D == pid && _SLAVE_ == conf->function){
    /* slave response completed */
    conf->tl_desc->tl_service_status = LD_SERVICE_IDLE;    
  }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
  
  /* Update word status */
  if (_SLAVE_ == conf->function){
#if (LIN_PROTOCOL == PROTOCOL_21)
      lin_update_err_signal(iii);
      lin_update_word_status_lin21 (iii, LIN_LLD_TX_COMPLETED, pid);
#else
    if (0x3D != pid){
      *conf->signal_tbl[conf->node_attribute->response_error].sig_data = 0;
    }
    lin_update_word_status_j2602 (iii, LIN_LLD_TX_COMPLETED, pid);
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
  }
}

void lin_handle_error
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] event id */
    lin_lld_event_id event_id,
    /* [IN] PID to process */
    l_u8 pid
  )
{
  l_bool not_found;
  l_u8 i;
  const lin_configuration *conf;

  conf = &(lin_ifc_configuration[iii]);
  switch (event_id) 
  {
    /* PID error */
    case LIN_LLD_PID_ERR:
      /* do nothing here */
      break;
    /* Frame error */
    case LIN_LLD_FRAME_ERR:
    case LIN_LLD_CHECKSUM_ERR:
    case LIN_LLD_READBACK_ERR:
    case LIN_LLD_NODATA_TIMEOUT:
#if (LIN_PROTOCOL == PROTOCOL_21)
      /* Check if frame type is event trigger */
      /* Find the corresponding frame */
      not_found = 1;
      for (i = conf->num_of_frames; (0 < i) && (1 == not_found); i--){
        if (conf->configuration_RAM[i] == pid){
          if (LIN_FRM_EVNT != conf->frame_tbl[i-1+conf->frame_start].frm_type) {
            /* Set response error */
            *(conf->error_in_response) = 1;
          } else {
            *(conf->error_in_response) = 0;
          }
          not_found = 0;
        }
      }
#else
      *(conf->error_in_response) = 1;
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
      /* TL support */     
      if ((0x3C == pid)||(0x3D == pid)){
/* multi frame support */      
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
        lin_tl_handler_error(iii, pid);
#else /* single frame support */       
        lin_tl_no_response(iii); 
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */
        
      }
      break;
    default:
      break;
  }

  /* Update word status */
  if (_SLAVE_ == conf->function){
#if (LIN_PROTOCOL == PROTOCOL_21)
      lin_update_err_signal(iii);
      lin_update_word_status_lin21 (iii, event_id, pid);
#else
      lin_update_status_byte(iii, event_id);
      lin_update_word_status_j2602 (iii, event_id, pid);
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
  }
}

void lin_bus_activity_timeout 
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] PID to process */ 
    l_u8 pid
  )
{
  const lin_configuration *conf;   
  /* Get current configuration */  
  conf = &lin_ifc_configuration[iii];
  /* Set goto sleep mode */
	*(conf->goto_sleep_flg) = 1;
  if (_SLAVE_ == conf->function){
#if (LIN_PROTOCOL == PROTOCOL_21)
      lin_update_word_status_lin21 (iii, LIN_LLD_BUS_ACTIVITY_TIMEOUT, pid);
#else
      lin_update_word_status_j2602 (iii, LIN_LLD_BUS_ACTIVITY_TIMEOUT, pid);
#endif /* End (LIN_PROTOCOL == PROTOCOL_21) */
  }
  /* Change to low power mode */
  lin_lld_set_low_power_mode(iii);
}

void lin_switch_sch_table
  (
    /* [IN] interface name */
    l_ifc_handle iii
  )
{
/* single frame support */      
#if (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_)
  l_u8 tmp_sch_id;
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_) */
  const lin_configuration *conf;
  l_u8 *_active_schedule_id;
  l_u8 *_previous_schedule_id;
  
  /* Get current configuration */
  conf = &lin_ifc_configuration[iii];
  _active_schedule_id   = conf->active_schedule_id;
  _previous_schedule_id = conf->previous_schedule_id;
  switch(conf->schedule_tbl[*(conf->active_schedule_id)].sch_tbl_type)
  {
    /* Collision */
    case LIN_SCH_TBL_COLL:
      /* Set active table equal to previous table */
      *_active_schedule_id = *_previous_schedule_id;
      break;
    /* Diagnostic schedule table */
    case LIN_SCH_TBL_DIAG:
/* single frame support */      
#if (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_)
      if (DIAG_INTER_LEAVE_MODE == conf->diagnostic_mode){
        /* Swap schedule table */
        /* SWAP_PTR(conf->active_schedule_id, conf->previous_schedule_id, tmp_sch_id); */
        tmp_sch_id = *_active_schedule_id;
        *_active_schedule_id = *_previous_schedule_id;
        *_previous_schedule_id = tmp_sch_id;
      }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_) */
      /* Set start entry of active schedule table to 0 */
      conf->schedule_start_entry[*_active_schedule_id] = 0;
      break;
    /* Normal schedule table*/
    case LIN_SCH_TBL_NORM:
/* multi frame support */      
#if (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_)
      if (DIAG_INTER_LEAVE_MODE == *conf->diagnostic_mode){
        *_previous_schedule_id = *_active_schedule_id;
        *_active_schedule_id = conf->schedule_start+3;
      }
#else /* single frame support */
      if (*(conf->diagnostic_frame_to_send) > 0 ){
        /* Swap schedule table */
        /* SWAP_PTR(conf->active_schedule_id, conf->previous_schedule_id, tmp_sch_id); */
        tmp_sch_id = *_active_schedule_id;
        *_active_schedule_id = *_previous_schedule_id;
        *_previous_schedule_id = tmp_sch_id;
      }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */    
      
      /* Set start entry of active schedule table to 0 */
      conf->schedule_start_entry[*_active_schedule_id] = 0;
      break;
    /* Goto sleep schedule table */
    case LIN_SCH_TBL_GOTO:
      /* Switch to NULL_SCHEDULE_TABLE */
      /* In the lin_sch_table, the NULL_SCHEDULE_TABLE for interface  iii */
      /* is located at shedule_start */
      *_active_schedule_id = conf->schedule_start;
      conf->schedule_start_entry[*_active_schedule_id] = 0;
    break;
    default: break;
  }
}

l_u8 lin_check_sporadic_update
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] index of frame */
    l_frame_handle frm_id
  )
{
  l_u8 j;
  lin_associate_frame_struct *ptr;
  const lin_configuration *conf;
  
  /* Get current configuration */
  conf = &lin_ifc_configuration[iii];
  ptr = (lin_associate_frame_struct*)(conf->frame_tbl[frm_id].frame_data);
  /* Check associate frame */
  for (j=0; j < ptr->num_asct_uncn_pid; j++) {
    if (conf->frame_flg[ptr->act_uncn_frm[j]] != 0){
      /* Frame is updated, return the PID of associate updated frame */
      return conf->configuration_RAM[ptr->act_uncn_frm[j] - conf->frame_start+1];
    }
  }
  /* There's no updated frame */
  return 0xFF;
}

void lin_update_tx_flags
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] index of frame */
    l_u8 frm_id
  )
{  
  const lin_configuration *conf;   
  const lin_frame_struct *frame_struct_ptr;
  lin_frm2sig *ptr;
  l_u8 i,signal_id;
  /* Get current configuration */  
  conf = &lin_ifc_configuration[iii];
  
  /* Set flags on tx signal handle */
  frame_struct_ptr = &(conf->frame_tbl[frm_id]);
  /* Get the frame data */
  ptr = (lin_frm2sig*)(frame_struct_ptr->frame_data);
  /* Find the signal id associated with frame */
  if (LIN_FRM_DIAG != conf->frame_tbl[frm_id].frm_type){
  for (i=0; i < frame_struct_ptr->num_of_sig; i++){
    signal_id = (l_u8)ptr[i].sig_id;
    /* Update associated signal */
    lin_flag_signal_handle_tbl[signal_id] = 1;    
    }
  }
/* single frame support */
#if (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_)
  /* TL support */
  /* Check if Diagnostic Frame */
  else {
     lin_tl_update_tx_flag(iii);
  }
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_MULTI_FRAME_) */ 
}

void lin_update_rx_diag_frame
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] PID to process */
    l_u8 pid
  )
{
  l_u8 i, j;  
  const lin_configuration *conf;

  conf = &(lin_ifc_configuration[iii]);
  
  /* Update diagnostic signals */  
  j = (pid - 0x3C) << 3; 
  
  /* Check goto sleep */
  if(0x00 == conf->response_buffer[1]) {
    (*conf->goto_sleep_flg) = 1;
    lin_lld_set_low_power_mode(iii);
    return;
  }
  for (i=1; i<9; i++, j++) {
    /* Update corresponding signals */
    conf->diag_signal_tbl[j] = conf->response_buffer[i];		
  }
/* single frame support */      
#if (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_)
  /* TL support */
  /* Copy response to diagnostic PDU in TL  */  
  lin_tl_put_pdu(iii);
#endif /* End (_TL_FRAME_SUPPORT_ == _TL_SINGLE_FRAME_) */  
  /* Process PDU income*/
  lin_tl_handler(iii);   
    
 }

void lin_make_res_diag_frame
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] PID of frame */
    l_u8 pid
  )
{
  const lin_configuration *conf;
  /* Get current configuration */  
  conf = &lin_ifc_configuration[iii];
  /* Get TL configuration */
  
  lin_tl_get_pdu(iii);
}

l_u8 lin_get_frame_index
  (
    /* [IN] interface name */
    l_ifc_handle iii,
    /* [IN] PID of frame */
    l_u8 pid
  )
{
  l_u8 i;
  const lin_configuration *conf;   
  /* Get current configuration */  
  conf = &lin_ifc_configuration[iii];

  for (i = conf->num_of_frames; 0 < i; i--){
    if (conf->configuration_RAM[i] == pid){
      return (i + conf->frame_start - 1); 
    }
  }  
  return 0xFF;
}

void lin_update_signal_scalar
  (
    /* [IN] current configuration */
    const lin_configuration *conf_ptr,
    /* [IN] value to compare */
    l_u16 value,
    /* [IN] signal name */
    l_signal_handle signal_name
  )
{
  l_u8 signal_size;

  signal_size = conf_ptr->signal_tbl[signal_name].sig_size_bit;
  /* Check for update */
  if (signal_size > 8) {
    l_u16_wr(signal_name, value);
  } else if (signal_size > 1){
    l_u8_wr(signal_name, (l_u8)value);
  } else {
    l_bool_wr(signal_name, (l_bool)value);
  }
}

void lin_process_uncd_frame
(
    /* [IN] interface name */
    l_ifc_handle iii,
     /* [IN] PID to process */ 
    l_u8 pid,
    /* [IN] make or update */
    l_u8 type
)
{
  l_u8 i, tmp_offset, index, frame_index, signal_id, *response_buffer_ptr, tmp_sig_size;
  static l_u8 tmp_byte_data;
  l_s8 length, to_fill, byte_offset;
  const lin_frame_struct *frame_struct_ptr;
  const lin_signal_struct *lin_signal_str_ptr;
  l_u16 tmp16;
  lin_frm2sig *ptr;
  const lin_configuration *conf;

  conf = &(lin_ifc_configuration[iii]);
  frame_index = lin_get_frame_index(iii,pid);
  if (0xFF != frame_index){
    response_buffer_ptr = conf->response_buffer;
    frame_struct_ptr = &(conf->frame_tbl[frame_index]);
    ptr = (lin_frm2sig*)(frame_struct_ptr->frame_data);
    if (MAKE_UNCONDITIONAL_FRAME == type){
      /* Set frame length */
      response_buffer_ptr[0] = frame_struct_ptr->frm_len;
      /* Set buffer to 0 */
      for (i=response_buffer_ptr[0]; 0 < i; i--){
        response_buffer_ptr[i] = 0xFF;
      }
    }
    for (i=0; i < frame_struct_ptr->num_of_sig; i++){
      signal_id = (l_u8)ptr[i].sig_id;
      if (signal_id == conf->node_attribute->response_error){
        frame_signal_error = 1;
      }
       /* get length of signal */
      lin_signal_str_ptr = &(conf->signal_tbl[signal_id]);
      length = lin_signal_str_ptr->sig_size_bit;
      tmp_sig_size = length;
      tmp_offset = ptr[i].offset;
      /* get index in buffer */
      index = (tmp_offset >> 3) + 1;
      /* Get signal value */
      if (LIN_SIG_SCALAR == lin_signal_str_ptr->sig_type){
        byte_offset = tmp_offset & 0x07;
        to_fill = 8 - (l_s8)(byte_offset);
        if (MAKE_UNCONDITIONAL_FRAME == type){ /* make unconditional frame */
          /* Get data of signal */
          if (length <=8 ){
            tmp16 = (l_u16)l_u8_rd((l_signal_handle)signal_id);
          } else {
            tmp16 = l_u16_rd((l_signal_handle)signal_id);
          }
          /* Packing to frame data */
          tmp_byte_data = (l_u8)(tmp16 << (byte_offset)) | ((1 << byte_offset)-1) | (((1 << (8 - length - byte_offset)) - 1) << (byte_offset+length));
          response_buffer_ptr[index++] &= tmp_byte_data;
          if (length > to_fill){
            length -= to_fill;
            if (length > 8) {
              response_buffer_ptr[index++] = (l_u8)((tmp16 << (byte_offset)) >> 8);
              tmp_byte_data = (l_u8)(tmp16 >> (l_u8)(8+to_fill)) | (((1 << (8-to_fill)) - 1) << to_fill);
              response_buffer_ptr[index] &= tmp_byte_data;
            }else if (length == 8){
              response_buffer_ptr[index++] = (l_u8)((tmp16 << (byte_offset)) >> 8);
            } else {
              tmp_byte_data = (l_u8)(tmp16 >> (to_fill)) | (((1 << (8 - length)) - 1) << length); 
              response_buffer_ptr[index] &= tmp_byte_data;
            }
          }
        } else {
          /* unpacking frame */
          tmp16 = (l_u16)(response_buffer_ptr[index++] >> (byte_offset));
          if (length > to_fill){
            length -= to_fill;
            if (length >= 8){
              tmp16 |= (l_u16)(response_buffer_ptr[index++] << to_fill);
              tmp16 |= (l_u16)(response_buffer_ptr[index] << (l_u8)(8+to_fill));
            } else {
              tmp16 |= (l_u16)(response_buffer_ptr[index] << (to_fill));
            }
          }
          tmp16 &= ((1 << tmp_sig_size) - 1);
          lin_update_signal_scalar(conf, tmp16, (l_signal_handle)signal_id);
          /* Update signal flags */
          lin_flag_signal_handle_tbl[signal_id] = 1;
        }
      } else {
        if (MAKE_UNCONDITIONAL_FRAME == type){
          l_bytes_rd((l_signal_handle)signal_id, 0, (length >> 3), &(response_buffer_ptr[index]));
        } else {
          l_bytes_wr((l_signal_handle)signal_id, 0, (length>>3), &(response_buffer_ptr[index])); 
            /* Update signal flags */
          lin_flag_signal_handle_tbl[signal_id] = 1;
        }
      }
      if (MAKE_UNCONDITIONAL_FRAME == type){
        conf->signal_flg[signal_id] = 0;
      }
    }
  }
}
#endif /* End of (LIN_MODE == _MASTER_MODE_) */
/**
* @}
*/
