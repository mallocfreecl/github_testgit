/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2022-2023 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
***************************************************************************//*! 
* 
* @file      lin_cfg.c 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Sat Sep 23 14:12:41 CST 2023 
*  
* @brief     Common LIN configuration, data structure
* 
******************************************************************************/
#include "lin_cfg.h"
#include "lin_sw.h"
/* Mapping interface with hardware */
const lin_hardware_name lin_virtual_ifc = SCI0; 
l_u8 lin_lld_response_buffer[10];
 
l_u8 lin_successful_transfer; 
l_u8 lin_error_in_response; 
l_u8 lin_goto_sleep_flg; 
/* Save configuration flag */
l_u8 lin_save_configuration_flg = 0;
lin_word_status_str lin_word_status; 
l_u8 lin_current_pid; 

/******************************* Signal Data **********************************/

l_u8 LI0_D_EWP_Setspeed_data[2] = {0x00, 0x00};

l_u8 LI0_D_EWP_Post_running_mode_data[1] = {0x00};

l_u8 LI0_Setspeed_data[1] = {0x00};

l_u8 LI0_Actual_speed_data[1] = {0x00};

l_u8 LI0_Voltage_data[1] = {0x00};

l_u8 LI0_Temperature_data[1] = {0x00};

l_u8 LI0_Current_data[1] = {0x00};

l_u8 LI0_Wakeup_status_data[1] = {0x00};

l_u8 LI0_RPM_Monitoring_data[1] = {0x00};

l_u8 LI0_Status_Emergency_mode_data[1] = {0x00};

l_u8 LI0_Over_temperature_data[1] = {0x00};

l_u8 LI0_Overcurren_data[1] = {0x00};

l_u8 LI0_Dry_run_data[1] = {0x00};

l_u8 LI0_Voltage_Error_data[1] = {0x00};

l_u8 LI0_Deblocking_data[1] = {0x00};

l_u8 LI0_Electrical_error_data[1] = {0x00};

l_u8 LI0_Status_Post_running_mode_data[1] = {0x00};

l_u8 LI0_Communication_error_data[1] = {0x00};

/******************************* Signal Table **********************************/
const lin_signal_struct  lin_signal_tbl[LIN_NUM_OF_SIGS] ={
 /*sig_type        sig_size_bit      sig_data*/

   {LIN_SIG_SCALAR, 13, &LI0_D_EWP_Setspeed_data[0]}
  

   ,{LIN_SIG_SCALAR, 3, &LI0_D_EWP_Post_running_mode_data[0]}
  
   ,{LIN_SIG_SCALAR, 8, &LI0_Setspeed_data[0]}
  
   ,{LIN_SIG_SCALAR, 8, &LI0_Actual_speed_data[0]}
  
   ,{LIN_SIG_SCALAR, 8, &LI0_Voltage_data[0]}
  
   ,{LIN_SIG_SCALAR, 8, &LI0_Temperature_data[0]}
  
   ,{LIN_SIG_SCALAR, 8, &LI0_Current_data[0]}
  
   ,{LIN_SIG_SCALAR, 2, &LI0_Wakeup_status_data[0]}
  
   ,{LIN_SIG_SCALAR, 2, &LI0_RPM_Monitoring_data[0]}
  
   ,{LIN_SIG_SCALAR, 2, &LI0_Status_Emergency_mode_data[0]}
  
   ,{LIN_SIG_SCALAR, 2, &LI0_Over_temperature_data[0]}
  
   ,{LIN_SIG_SCALAR, 2, &LI0_Overcurren_data[0]}
  
   ,{LIN_SIG_SCALAR, 2, &LI0_Dry_run_data[0]}
  
   ,{LIN_SIG_SCALAR, 2, &LI0_Voltage_Error_data[0]}
  
   ,{LIN_SIG_SCALAR, 2, &LI0_Deblocking_data[0]}
  
   ,{LIN_SIG_SCALAR, 1, &LI0_Electrical_error_data[0]}
  
   ,{LIN_SIG_SCALAR, 3, &LI0_Status_Post_running_mode_data[0]}
  
   ,{LIN_SIG_SCALAR, 1, &LI0_Communication_error_data[0]}
  
};
/*************************** Flag set when signal is updated ******************/
l_bool lin_signal_flag_tbl[LIN_NUM_OF_SIGS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
/* Flag is to notify to application whether signal is transmited or received successfully */
l_bool lin_flag_signal_handle_tbl[LIN_NUM_OF_SIGS] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
/* Diagnostic signal */
l_u8 lin_diag_signal_tbl[16];
/***************************** Frame Definition ******************************/
/*unconditional frame */

const lin_frm2sig LI0_EcpmEcm_Lin3Fr01_ECM_LIN3_signal[16] = {

   {LI0_Setspeed, 0}

   ,{LI0_Actual_speed, 8} 

   ,{LI0_Voltage, 16} 

   ,{LI0_Temperature, 24} 

   ,{LI0_Current, 32} 

   ,{LI0_Wakeup_status, 40} 

   ,{LI0_RPM_Monitoring, 42} 

   ,{LI0_Status_Emergency_mode, 44} 

   ,{LI0_Over_temperature, 46} 

   ,{LI0_Overcurren, 48} 

   ,{LI0_Dry_run, 50} 

   ,{LI0_Voltage_Error, 52} 

   ,{LI0_Deblocking, 54} 

   ,{LI0_Electrical_error, 56} 

   ,{LI0_Status_Post_running_mode, 60} 

   ,{LI0_Communication_error, 63} 

};

const lin_frm2sig LI0_EcmEcm_Lin3Fr02_ECM_LIN3_signal[2] = {

   {LI0_D_EWP_Setspeed, 0}

   ,{LI0_D_EWP_Post_running_mode, 13} 

};



/*****************************event trigger frame*****************************/

/**********************************  Frame table **********************************/
const lin_frame_struct lin_frame_tbl[LIN_NUM_OF_FRMS] ={

   { LIN_FRM_UNCD, 8, LIN_RES_PUB, 16  , (l_u8*)&LI0_EcpmEcm_Lin3Fr01_ECM_LIN3_signal[0]  }

   ,{ LIN_FRM_UNCD, 8, LIN_RES_SUB, 2 , (l_u8*)&LI0_EcmEcm_Lin3Fr02_ECM_LIN3_signal[0] }
  
   ,{ LIN_FRM_DIAG, 8, LIN_RES_SUB, 8 , (l_u8*)0 }
  
   ,{ LIN_FRM_DIAG, 8, LIN_RES_PUB, 8 , (l_u8*)0 }
  
};
/*********************************** Frame flag Initialization **********************/
l_bool lin_frame_flag_tbl[LIN_NUM_OF_FRMS] = {0, 0, 0, 0};
l_bool lin_flag_frame_handle_tbl[LIN_NUM_OF_FRMS] = {0, 0, 0, 0};


/**************************** Lin configuration Initialization ***********************/
/* max_response_frame_timeout = round((1.4x(10+Nx10)xTbit)/Tbase_period) + 3 */

const l_u16 lin_max_frame_res_timeout_val[8]={

6, 7, 9, 10, 12, 13, 15, 16

};


  

l_u8 lin_configuration_RAM[LIN_SIZE_OF_CFG]= {0x00, 0x18, 0x33, 0x3C, 0x3D ,0xFF};
const l_u16  lin_configuration_ROM[LIN_SIZE_OF_CFG]= {0x00, 0x18, 0x33, 0x3C, 0x3D ,0xFFFF};


/***************************************** Node Attribute*****************************************/
   
l_u8 lin_configured_NAD = 0x03;     /*<configured_NAD>*/ 
const l_u8 lin_initial_NAD    =0x03;     /*<initial_NAD>*/ 
const lin_product_id product_id = {0x0062, 0x0017, 0x0001 };  /* {<supplier_id>,<function_id>,<variant>} */ 
const l_signal_handle response_error =  LI0_Communication_error;               




/************************** TL Layer and Diagnostic: SINGLE interface **************************/
lin_tl_pdu_data tx_single_pdu_data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};
lin_tl_pdu_data rx_single_pdu_data = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};





 

lin_tl_pdu_data *tl_current_tx_pdu_ptr;
lin_tl_pdu_data *tl_current_rx_pdu_ptr;
l_u8 tl_slaveresp_cnt = 0;
 
/* This function is an example of response; real implementation is application-dependent */
/* You can use one of the following define to set PCI of response frame for */
/* this service to the correct value */
l_u8 ld_read_by_id_callout(l_u8 id, l_u8 *data){
    l_u8 retval = LD_ID_NO_RESPONSE;
    /* Following code is an example - Real implementation is application-dependent */
    /*
     * the handling does essentially depend on the id of the
     * requested item
     */
    /* This example implement with ID = 32 - LIN_READ_USR_DEF_MIN */
    if (id == LIN_READ_USR_DEF_MIN)
    {
      /*
       * id received is user defined 32
       */
      /* A positive response is ready to be sent to the user defined request */
     
      data[0] = (l_u8) (id + 1);    /* Data user define */
      data[1] = (l_u8) (id + 2);    /* Data user define */
      data[2] = (l_u8) (id + 3);    /* Data user define */
      data[3] = (l_u8) (id + 4);    /* Data user define */
      data[4] = (l_u8) (id + 5);    /* Data user define */
      retval = LD_POSITIVE_RESPONSE;
    }
    else 
    {
      /*
       * id received is user defined 63 - no response
       */
    }
    return retval;    
}
