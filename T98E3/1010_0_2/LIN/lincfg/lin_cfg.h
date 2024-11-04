/****************************************************************************** 
* 
* Freescale Semiconductor Inc. 
* (c) Copyright 2022-2023 Freescale Semiconductor, Inc. 
* ALL RIGHTS RESERVED. 
* 
****************************************************************************//*!  
* 
* @file      lin_cfg.h 
* 
* @author    FPT Software
*  
* @version   1.0 
*  
* @date      Sat Sep 23 14:12:40 CST 2023
*  
* @brief     Hardware configuration file
* 
******************************************************************************/
#ifndef    _LIN_CFG_H_  
#define    _LIN_CFG_H_  
#include "lin_hw_cfg.h" 
/* Define operating mode */
#define _MASTER_MODE_     0 
#define _SLAVE_MODE_      1 
#define LIN_MODE   _SLAVE_MODE_
/* Define protocol version */
#define PROTOCOL_21       0  
#define PROTOCOL_J2602    1  
#define PROTOCOL_20       2 
#define LIN_PROTOCOL    PROTOCOL_21

#define SCI_ADDR        SCI0_ADDR    /* For slave */ 
#define LIN_BAUD_RATE    19200    	 /*For slave*/ 
/**********************************************************************/
/***************          Diagnostic class selection  *****************/
/**********************************************************************/
#define _DIAG_CLASS_I_          0
#define _DIAG_CLASS_II_         1
#define _DIAG_CLASS_III_        2

#define _DIAG_CLASS_SUPPORT_    _DIAG_CLASS_I_
/**************** FRAME SUPPORT DEFINITION ******************/
#define _TL_SINGLE_FRAME_       0
#define _TL_MULTI_FRAME_        1

#define _TL_FRAME_SUPPORT_      _TL_SINGLE_FRAME_

/**********************************************************************/
/***************               Flags             **********************/
/**********************************************************************/
typedef unsigned int l_flag_handle;
/* Signal flag */

#define LI0_D_EWP_Setspeed_flag 0xFF00

#define LI0_D_EWP_Post_running_mode_flag 0xFF01

#define LI0_Setspeed_flag 0xFF02

#define LI0_Actual_speed_flag 0xFF03

#define LI0_Voltage_flag 0xFF04

#define LI0_Temperature_flag 0xFF05

#define LI0_Current_flag 0xFF06

#define LI0_Wakeup_status_flag 0xFF07

#define LI0_RPM_Monitoring_flag 0xFF08

#define LI0_Status_Emergency_mode_flag 0xFF09

#define LI0_Over_temperature_flag 0xFF0A

#define LI0_Overcurren_flag 0xFF0B

#define LI0_Dry_run_flag 0xFF0C

#define LI0_Voltage_Error_flag 0xFF0D

#define LI0_Deblocking_flag 0xFF0E

#define LI0_Electrical_error_flag 0xFF0F

#define LI0_Status_Post_running_mode_flag 0xFF10

#define LI0_Communication_error_flag 0xFF11
 

/**********Frame flag definition **********/
/* Frame flag */

#define  LI0_EcpmEcm_Lin3Fr01_ECM_LIN3_flag  0x00FF

#define  LI0_EcmEcm_Lin3Fr02_ECM_LIN3_flag  0x01FF

#define  LI0_MasterReq_flag  0x02FF

#define  LI0_SlaveResp_flag  0x03FF

/* Signal and Frame association */
/**********************************************************************/
/***************               Interfaces           *******************/
/**********************************************************************/
typedef enum { 
   LI0
}l_ifc_handle; 

/**********************************************************************/
/***************               Signals              *******************/
/**********************************************************************/
/* Number of signals */
#define LIN_NUM_OF_SIGS  18
/* List of signals */   
typedef enum {

   /* Interface_name = LI0 */

   LI0_D_EWP_Setspeed

   , LI0_D_EWP_Post_running_mode
  
   , LI0_Setspeed
  
   , LI0_Actual_speed
  
   , LI0_Voltage
  
   , LI0_Temperature
  
   , LI0_Current
  
   , LI0_Wakeup_status
  
   , LI0_RPM_Monitoring
  
   , LI0_Status_Emergency_mode
  
   , LI0_Over_temperature
  
   , LI0_Overcurren
  
   , LI0_Dry_run
  
   , LI0_Voltage_Error
  
   , LI0_Deblocking
  
   , LI0_Electrical_error
  
   , LI0_Status_Post_running_mode
  
   , LI0_Communication_error
  
  
} l_signal_handle; 
/**********************************************************************/
/*****************               Frame             ********************/
/**********************************************************************/
/* Number of frames */
#define LIN_NUM_OF_FRMS  4 
/* List of frames */
typedef enum {
/* All frames for master node */

   /* Interface_name = LI0 */

   LI0_EcpmEcm_Lin3Fr01_ECM_LIN3

   , LI0_EcmEcm_Lin3Fr02_ECM_LIN3
  
   , LI0_MasterReq
  
   , LI0_SlaveResp
  
  
} l_frame_handle; 
 
/**********************************************************************/
/***************             Configuration          *******************/
/**********************************************************************/
/* Size of configuration in ROM and RAM used for interface: LI1 */
#define LIN_SIZE_OF_CFG  6 
#define LIN_CFG_FRAME_NUM  2 /**********************************************************************/
/***************        Static API Functions        *******************/
/**********************************************************************/ 

/* SIGNAL INTERACTION */


/* Scalar signal read */
#define l_bool_rd_LI0_D_EWP_Setspeed() l_bool_rd(LI0_D_EWP_Setspeed)

#define l_bool_rd_LI0_D_EWP_Post_running_mode() l_bool_rd(LI0_D_EWP_Post_running_mode)

#define l_bool_rd_LI0_Setspeed() l_bool_rd(LI0_Setspeed)

#define l_bool_rd_LI0_Actual_speed() l_bool_rd(LI0_Actual_speed)

#define l_bool_rd_LI0_Voltage() l_bool_rd(LI0_Voltage)

#define l_bool_rd_LI0_Temperature() l_bool_rd(LI0_Temperature)

#define l_bool_rd_LI0_Current() l_bool_rd(LI0_Current)

#define l_bool_rd_LI0_Wakeup_status() l_bool_rd(LI0_Wakeup_status)

#define l_bool_rd_LI0_RPM_Monitoring() l_bool_rd(LI0_RPM_Monitoring)

#define l_bool_rd_LI0_Status_Emergency_mode() l_bool_rd(LI0_Status_Emergency_mode)

#define l_bool_rd_LI0_Over_temperature() l_bool_rd(LI0_Over_temperature)

#define l_bool_rd_LI0_Overcurren() l_bool_rd(LI0_Overcurren)

#define l_bool_rd_LI0_Dry_run() l_bool_rd(LI0_Dry_run)

#define l_bool_rd_LI0_Voltage_Error() l_bool_rd(LI0_Voltage_Error)

#define l_bool_rd_LI0_Deblocking() l_bool_rd(LI0_Deblocking)

#define l_bool_rd_LI0_Electrical_error() l_bool_rd(LI0_Electrical_error)

#define l_bool_rd_LI0_Status_Post_running_mode() l_bool_rd(LI0_Status_Post_running_mode)

#define l_bool_rd_LI0_Communication_error() l_bool_rd(LI0_Communication_error)



#define l_u8_rd_LI0_D_EWP_Setspeed() l_u8_rd(LI0_D_EWP_Setspeed)

#define l_u8_rd_LI0_D_EWP_Post_running_mode() l_u8_rd(LI0_D_EWP_Post_running_mode)

#define l_u8_rd_LI0_Setspeed() l_u8_rd(LI0_Setspeed)

#define l_u8_rd_LI0_Actual_speed() l_u8_rd(LI0_Actual_speed)

#define l_u8_rd_LI0_Voltage() l_u8_rd(LI0_Voltage)

#define l_u8_rd_LI0_Temperature() l_u8_rd(LI0_Temperature)

#define l_u8_rd_LI0_Current() l_u8_rd(LI0_Current)

#define l_u8_rd_LI0_Wakeup_status() l_u8_rd(LI0_Wakeup_status)

#define l_u8_rd_LI0_RPM_Monitoring() l_u8_rd(LI0_RPM_Monitoring)

#define l_u8_rd_LI0_Status_Emergency_mode() l_u8_rd(LI0_Status_Emergency_mode)

#define l_u8_rd_LI0_Over_temperature() l_u8_rd(LI0_Over_temperature)

#define l_u8_rd_LI0_Overcurren() l_u8_rd(LI0_Overcurren)

#define l_u8_rd_LI0_Dry_run() l_u8_rd(LI0_Dry_run)

#define l_u8_rd_LI0_Voltage_Error() l_u8_rd(LI0_Voltage_Error)

#define l_u8_rd_LI0_Deblocking() l_u8_rd(LI0_Deblocking)

#define l_u8_rd_LI0_Electrical_error() l_u8_rd(LI0_Electrical_error)

#define l_u8_rd_LI0_Status_Post_running_mode() l_u8_rd(LI0_Status_Post_running_mode)

#define l_u8_rd_LI0_Communication_error() l_u8_rd(LI0_Communication_error)




#define l_u16_rd_LI0_D_EWP_Setspeed() l_u16_rd(LI0_D_EWP_Setspeed)

#define l_u16_rd_LI0_D_EWP_Post_running_mode() l_u16_rd(LI0_D_EWP_Post_running_mode)

#define l_u16_rd_LI0_Setspeed() l_u16_rd(LI0_Setspeed)

#define l_u16_rd_LI0_Actual_speed() l_u16_rd(LI0_Actual_speed)

#define l_u16_rd_LI0_Voltage() l_u16_rd(LI0_Voltage)

#define l_u16_rd_LI0_Temperature() l_u16_rd(LI0_Temperature)

#define l_u16_rd_LI0_Current() l_u16_rd(LI0_Current)

#define l_u16_rd_LI0_Wakeup_status() l_u16_rd(LI0_Wakeup_status)

#define l_u16_rd_LI0_RPM_Monitoring() l_u16_rd(LI0_RPM_Monitoring)

#define l_u16_rd_LI0_Status_Emergency_mode() l_u16_rd(LI0_Status_Emergency_mode)

#define l_u16_rd_LI0_Over_temperature() l_u16_rd(LI0_Over_temperature)

#define l_u16_rd_LI0_Overcurren() l_u16_rd(LI0_Overcurren)

#define l_u16_rd_LI0_Dry_run() l_u16_rd(LI0_Dry_run)

#define l_u16_rd_LI0_Voltage_Error() l_u16_rd(LI0_Voltage_Error)

#define l_u16_rd_LI0_Deblocking() l_u16_rd(LI0_Deblocking)

#define l_u16_rd_LI0_Electrical_error() l_u16_rd(LI0_Electrical_error)

#define l_u16_rd_LI0_Status_Post_running_mode() l_u16_rd(LI0_Status_Post_running_mode)

#define l_u16_rd_LI0_Communication_error() l_u16_rd(LI0_Communication_error)




/* Scalar signal write */
#define l_bool_wr_LI0_D_EWP_Setspeed(value) l_bool_wr(LI0_D_EWP_Setspeed, value)

#define l_bool_wr_LI0_D_EWP_Post_running_mode(value) l_bool_wr(LI0_D_EWP_Post_running_mode, value)

#define l_bool_wr_LI0_Setspeed(value) l_bool_wr(LI0_Setspeed, value)

#define l_bool_wr_LI0_Actual_speed(value) l_bool_wr(LI0_Actual_speed, value)

#define l_bool_wr_LI0_Voltage(value) l_bool_wr(LI0_Voltage, value)

#define l_bool_wr_LI0_Temperature(value) l_bool_wr(LI0_Temperature, value)

#define l_bool_wr_LI0_Current(value) l_bool_wr(LI0_Current, value)

#define l_bool_wr_LI0_Wakeup_status(value) l_bool_wr(LI0_Wakeup_status, value)

#define l_bool_wr_LI0_RPM_Monitoring(value) l_bool_wr(LI0_RPM_Monitoring, value)

#define l_bool_wr_LI0_Status_Emergency_mode(value) l_bool_wr(LI0_Status_Emergency_mode, value)

#define l_bool_wr_LI0_Over_temperature(value) l_bool_wr(LI0_Over_temperature, value)

#define l_bool_wr_LI0_Overcurren(value) l_bool_wr(LI0_Overcurren, value)

#define l_bool_wr_LI0_Dry_run(value) l_bool_wr(LI0_Dry_run, value)

#define l_bool_wr_LI0_Voltage_Error(value) l_bool_wr(LI0_Voltage_Error, value)

#define l_bool_wr_LI0_Deblocking(value) l_bool_wr(LI0_Deblocking, value)

#define l_bool_wr_LI0_Electrical_error(value) l_bool_wr(LI0_Electrical_error, value)

#define l_bool_wr_LI0_Status_Post_running_mode(value) l_bool_wr(LI0_Status_Post_running_mode, value)

#define l_bool_wr_LI0_Communication_error(value) l_bool_wr(LI0_Communication_error, value)




#define l_u8_wr_LI0_D_EWP_Setspeed(value) l_u8_wr(LI0_D_EWP_Setspeed, value)

#define l_u8_wr_LI0_D_EWP_Post_running_mode(value) l_u8_wr(LI0_D_EWP_Post_running_mode, value)

#define l_u8_wr_LI0_Setspeed(value) l_u8_wr(LI0_Setspeed, value)

#define l_u8_wr_LI0_Actual_speed(value) l_u8_wr(LI0_Actual_speed, value)

#define l_u8_wr_LI0_Voltage(value) l_u8_wr(LI0_Voltage, value)

#define l_u8_wr_LI0_Temperature(value) l_u8_wr(LI0_Temperature, value)

#define l_u8_wr_LI0_Current(value) l_u8_wr(LI0_Current, value)

#define l_u8_wr_LI0_Wakeup_status(value) l_u8_wr(LI0_Wakeup_status, value)

#define l_u8_wr_LI0_RPM_Monitoring(value) l_u8_wr(LI0_RPM_Monitoring, value)

#define l_u8_wr_LI0_Status_Emergency_mode(value) l_u8_wr(LI0_Status_Emergency_mode, value)

#define l_u8_wr_LI0_Over_temperature(value) l_u8_wr(LI0_Over_temperature, value)

#define l_u8_wr_LI0_Overcurren(value) l_u8_wr(LI0_Overcurren, value)

#define l_u8_wr_LI0_Dry_run(value) l_u8_wr(LI0_Dry_run, value)

#define l_u8_wr_LI0_Voltage_Error(value) l_u8_wr(LI0_Voltage_Error, value)

#define l_u8_wr_LI0_Deblocking(value) l_u8_wr(LI0_Deblocking, value)

#define l_u8_wr_LI0_Electrical_error(value) l_u8_wr(LI0_Electrical_error, value)

#define l_u8_wr_LI0_Status_Post_running_mode(value) l_u8_wr(LI0_Status_Post_running_mode, value)

#define l_u8_wr_LI0_Communication_error(value) l_u8_wr(LI0_Communication_error, value)




#define l_u16_wr_LI0_D_EWP_Setspeed(value) l_u16_wr(LI0_D_EWP_Setspeed, value)

#define l_u16_wr_LI0_D_EWP_Post_running_mode(value) l_u16_wr(LI0_D_EWP_Post_running_mode, value)

#define l_u16_wr_LI0_Setspeed(value) l_u16_wr(LI0_Setspeed, value)

#define l_u16_wr_LI0_Actual_speed(value) l_u16_wr(LI0_Actual_speed, value)

#define l_u16_wr_LI0_Voltage(value) l_u16_wr(LI0_Voltage, value)

#define l_u16_wr_LI0_Temperature(value) l_u16_wr(LI0_Temperature, value)

#define l_u16_wr_LI0_Current(value) l_u16_wr(LI0_Current, value)

#define l_u16_wr_LI0_Wakeup_status(value) l_u16_wr(LI0_Wakeup_status, value)

#define l_u16_wr_LI0_RPM_Monitoring(value) l_u16_wr(LI0_RPM_Monitoring, value)

#define l_u16_wr_LI0_Status_Emergency_mode(value) l_u16_wr(LI0_Status_Emergency_mode, value)

#define l_u16_wr_LI0_Over_temperature(value) l_u16_wr(LI0_Over_temperature, value)

#define l_u16_wr_LI0_Overcurren(value) l_u16_wr(LI0_Overcurren, value)

#define l_u16_wr_LI0_Dry_run(value) l_u16_wr(LI0_Dry_run, value)

#define l_u16_wr_LI0_Voltage_Error(value) l_u16_wr(LI0_Voltage_Error, value)

#define l_u16_wr_LI0_Deblocking(value) l_u16_wr(LI0_Deblocking, value)

#define l_u16_wr_LI0_Electrical_error(value) l_u16_wr(LI0_Electrical_error, value)

#define l_u16_wr_LI0_Status_Post_running_mode(value) l_u16_wr(LI0_Status_Post_running_mode, value)

#define l_u16_wr_LI0_Communication_error(value) l_u16_wr(LI0_Communication_error, value)




/* Byte array read */
#define l_bytes_rd_LI0_D_EWP_Setspeed(start, count, data) l_bytes_rd(LI0_D_EWP_Setspeed, start, count, data)

#define l_bytes_rd_LI0_D_EWP_Post_running_mode(start, count, data) l_bytes_rd(LI0_D_EWP_Post_running_mode, start, count, data)

#define l_bytes_rd_LI0_Setspeed(start, count, data) l_bytes_rd(LI0_Setspeed, start, count, data)

#define l_bytes_rd_LI0_Actual_speed(start, count, data) l_bytes_rd(LI0_Actual_speed, start, count, data)

#define l_bytes_rd_LI0_Voltage(start, count, data) l_bytes_rd(LI0_Voltage, start, count, data)

#define l_bytes_rd_LI0_Temperature(start, count, data) l_bytes_rd(LI0_Temperature, start, count, data)

#define l_bytes_rd_LI0_Current(start, count, data) l_bytes_rd(LI0_Current, start, count, data)

#define l_bytes_rd_LI0_Wakeup_status(start, count, data) l_bytes_rd(LI0_Wakeup_status, start, count, data)

#define l_bytes_rd_LI0_RPM_Monitoring(start, count, data) l_bytes_rd(LI0_RPM_Monitoring, start, count, data)

#define l_bytes_rd_LI0_Status_Emergency_mode(start, count, data) l_bytes_rd(LI0_Status_Emergency_mode, start, count, data)

#define l_bytes_rd_LI0_Over_temperature(start, count, data) l_bytes_rd(LI0_Over_temperature, start, count, data)

#define l_bytes_rd_LI0_Overcurren(start, count, data) l_bytes_rd(LI0_Overcurren, start, count, data)

#define l_bytes_rd_LI0_Dry_run(start, count, data) l_bytes_rd(LI0_Dry_run, start, count, data)

#define l_bytes_rd_LI0_Voltage_Error(start, count, data) l_bytes_rd(LI0_Voltage_Error, start, count, data)

#define l_bytes_rd_LI0_Deblocking(start, count, data) l_bytes_rd(LI0_Deblocking, start, count, data)

#define l_bytes_rd_LI0_Electrical_error(start, count, data) l_bytes_rd(LI0_Electrical_error, start, count, data)

#define l_bytes_rd_LI0_Status_Post_running_mode(start, count, data) l_bytes_rd(LI0_Status_Post_running_mode, start, count, data)

#define l_bytes_rd_LI0_Communication_error(start, count, data) l_bytes_rd(LI0_Communication_error, start, count, data)




/* Byte array write */
#define l_bytes_wr_LI0_D_EWP_Setspeed(start, count, data) l_bytes_wr(LI0_D_EWP_Setspeed, start, count, data)

#define l_bytes_wr_LI0_D_EWP_Post_running_mode(start, count, data) l_bytes_wr(LI0_D_EWP_Post_running_mode, start, count, data)

#define l_bytes_wr_LI0_Setspeed(start, count, data) l_bytes_wr(LI0_Setspeed, start, count, data)

#define l_bytes_wr_LI0_Actual_speed(start, count, data) l_bytes_wr(LI0_Actual_speed, start, count, data)

#define l_bytes_wr_LI0_Voltage(start, count, data) l_bytes_wr(LI0_Voltage, start, count, data)

#define l_bytes_wr_LI0_Temperature(start, count, data) l_bytes_wr(LI0_Temperature, start, count, data)

#define l_bytes_wr_LI0_Current(start, count, data) l_bytes_wr(LI0_Current, start, count, data)

#define l_bytes_wr_LI0_Wakeup_status(start, count, data) l_bytes_wr(LI0_Wakeup_status, start, count, data)

#define l_bytes_wr_LI0_RPM_Monitoring(start, count, data) l_bytes_wr(LI0_RPM_Monitoring, start, count, data)

#define l_bytes_wr_LI0_Status_Emergency_mode(start, count, data) l_bytes_wr(LI0_Status_Emergency_mode, start, count, data)

#define l_bytes_wr_LI0_Over_temperature(start, count, data) l_bytes_wr(LI0_Over_temperature, start, count, data)

#define l_bytes_wr_LI0_Overcurren(start, count, data) l_bytes_wr(LI0_Overcurren, start, count, data)

#define l_bytes_wr_LI0_Dry_run(start, count, data) l_bytes_wr(LI0_Dry_run, start, count, data)

#define l_bytes_wr_LI0_Voltage_Error(start, count, data) l_bytes_wr(LI0_Voltage_Error, start, count, data)

#define l_bytes_wr_LI0_Deblocking(start, count, data) l_bytes_wr(LI0_Deblocking, start, count, data)

#define l_bytes_wr_LI0_Electrical_error(start, count, data) l_bytes_wr(LI0_Electrical_error, start, count, data)

#define l_bytes_wr_LI0_Status_Post_running_mode(start, count, data) l_bytes_wr(LI0_Status_Post_running_mode, start, count, data)

#define l_bytes_wr_LI0_Communication_error(start, count, data) l_bytes_wr(LI0_Communication_error, start, count, data)



/* NOTIFICATION */

#define l_flg_tst_LI0_D_EWP_Setspeed_flag() l_flg_tst(LI0_D_EWP_Setspeed_flag)

#define l_flg_tst_LI0_D_EWP_Post_running_mode_flag() l_flg_tst(LI0_D_EWP_Post_running_mode_flag)

#define l_flg_tst_LI0_Setspeed_flag() l_flg_tst(LI0_Setspeed_flag)

#define l_flg_tst_LI0_Actual_speed_flag() l_flg_tst(LI0_Actual_speed_flag)

#define l_flg_tst_LI0_Voltage_flag() l_flg_tst(LI0_Voltage_flag)

#define l_flg_tst_LI0_Temperature_flag() l_flg_tst(LI0_Temperature_flag)

#define l_flg_tst_LI0_Current_flag() l_flg_tst(LI0_Current_flag)

#define l_flg_tst_LI0_Wakeup_status_flag() l_flg_tst(LI0_Wakeup_status_flag)

#define l_flg_tst_LI0_RPM_Monitoring_flag() l_flg_tst(LI0_RPM_Monitoring_flag)

#define l_flg_tst_LI0_Status_Emergency_mode_flag() l_flg_tst(LI0_Status_Emergency_mode_flag)

#define l_flg_tst_LI0_Over_temperature_flag() l_flg_tst(LI0_Over_temperature_flag)

#define l_flg_tst_LI0_Overcurren_flag() l_flg_tst(LI0_Overcurren_flag)

#define l_flg_tst_LI0_Dry_run_flag() l_flg_tst(LI0_Dry_run_flag)

#define l_flg_tst_LI0_Voltage_Error_flag() l_flg_tst(LI0_Voltage_Error_flag)

#define l_flg_tst_LI0_Deblocking_flag() l_flg_tst(LI0_Deblocking_flag)

#define l_flg_tst_LI0_Electrical_error_flag() l_flg_tst(LI0_Electrical_error_flag)

#define l_flg_tst_LI0_Status_Post_running_mode_flag() l_flg_tst(LI0_Status_Post_running_mode_flag)

#define l_flg_tst_LI0_Communication_error_flag() l_flg_tst(LI0_Communication_error_flag)



#define l_flg_clr_LI0_D_EWP_Setspeed_flag() l_flg_clr(LI0_D_EWP_Setspeed_flag)

#define l_flg_clr_LI0_D_EWP_Post_running_mode_flag() l_flg_clr(LI0_D_EWP_Post_running_mode_flag)

#define l_flg_clr_LI0_Setspeed_flag() l_flg_clr(LI0_Setspeed_flag)

#define l_flg_clr_LI0_Actual_speed_flag() l_flg_clr(LI0_Actual_speed_flag)

#define l_flg_clr_LI0_Voltage_flag() l_flg_clr(LI0_Voltage_flag)

#define l_flg_clr_LI0_Temperature_flag() l_flg_clr(LI0_Temperature_flag)

#define l_flg_clr_LI0_Current_flag() l_flg_clr(LI0_Current_flag)

#define l_flg_clr_LI0_Wakeup_status_flag() l_flg_clr(LI0_Wakeup_status_flag)

#define l_flg_clr_LI0_RPM_Monitoring_flag() l_flg_clr(LI0_RPM_Monitoring_flag)

#define l_flg_clr_LI0_Status_Emergency_mode_flag() l_flg_clr(LI0_Status_Emergency_mode_flag)

#define l_flg_clr_LI0_Over_temperature_flag() l_flg_clr(LI0_Over_temperature_flag)

#define l_flg_clr_LI0_Overcurren_flag() l_flg_clr(LI0_Overcurren_flag)

#define l_flg_clr_LI0_Dry_run_flag() l_flg_clr(LI0_Dry_run_flag)

#define l_flg_clr_LI0_Voltage_Error_flag() l_flg_clr(LI0_Voltage_Error_flag)

#define l_flg_clr_LI0_Deblocking_flag() l_flg_clr(LI0_Deblocking_flag)

#define l_flg_clr_LI0_Electrical_error_flag() l_flg_clr(LI0_Electrical_error_flag)

#define l_flg_clr_LI0_Status_Post_running_mode_flag() l_flg_clr(LI0_Status_Post_running_mode_flag)

#define l_flg_clr_LI0_Communication_error_flag() l_flg_clr(LI0_Communication_error_flag)


/* INTERFACE MANAGEMENT */

#define l_ifc_init_LI0() l_ifc_init(LI0)



#define l_ifc_wake_up_LI0() l_ifc_wake_up(LI0)



#define l_ifc_rx_LI0() l_ifc_rx(LI0)



#define l_ifc_tx_LI0() l_ifc_tx(LI0)



#define l_ifc_aux_LI0() l_ifc_aux(LI0)



#define l_ifc_read_status_LI0() l_ifc_read_status(LI0)


#endif    /* _LIN_CFG_H_ */
