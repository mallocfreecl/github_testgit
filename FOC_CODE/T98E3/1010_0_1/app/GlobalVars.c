
/*BEGIN_FILE_HDR
**************************************************************************
* NOTICE
* This software is the property of XiangBin Electric. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* XiangBin Electric.
**************************************************************************
* File Name:GlobalVars.c
********************************************************************
* Project/Product:LXT9816_PMP
* Title:
* Author:zyg
*********************************************************************
* Description:
*
* (Requirements, pseudo code and etc.)
*********************************************************************
* Limitations:
*
* (limitations)
*********************************************************************
*********************************************************************
* Revision History：
*
* Version       Date         	  Author         Descriptions
* ----------    --------------  ------------   ----------------------------------------
* 1.0           2021-08-20      zyg            Original
*
*
********************************************************************
*END_FILE_HDR*/

/* Includes*/
/******************************************************************/
#include "GlobalVars.h"

/* Variables */
/******************************************************************/
/*消除polyspace警告,2021-09-22-by zyg*/
/*polyspace-begin  MISRA2012:9.2*/
const Version_t ProductVersion = 
{
.ProductType = 0x98E3u,  /* ProductType由32位改为16位 24-8-26 by CL*/
	
.InnerVersion.bits.MinorHardVersion = 0u,
.InnerVersion.bits.InnerVersion = 1u, /*硬件版本号HV1.0 24-8-26 by CL*/
.InnerVersion.bits.SoftVersion = 0x10u,

.FctVersion = 1u,/*添加FCT测试版本 24-8-26 by CL*/
.DebugVersion = 0u,/*  Modify DebugVersion - 2023-09-26-by lpy  */
};
/*polyspace-begin  MISRA2012:9.2*/
u32 PowerUpTimeMs = 0u; /* Power up time in microseconds */
