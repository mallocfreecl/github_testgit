/*BEGIN_FILE_HDR
**************************************************************************
* NOTICE
* This software is the property of XiangBin Electric. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* XiangBin Electric.
**************************************************************************
* File Name:GlobalVars.c
********************************************************************
* Project/Product:LXT9818_PMP
* Title:
* Author:yhd
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
*     1.0       2021-07-23      yhd            Original
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
.ProductType = 0x9861u,/*新项目，修改版本号 24.11.13 by zlh*/
	
.InnerVersion.bits.MinorHardVersion = 0u,
.InnerVersion.bits.InnerVersion = 1u,
	.InnerVersion.bits.SoftVersion = 0x10u,/*新项目修改版本号 2023-11-13-by zlh*/

.DebugVersion = 0u,/*  Modify DebugVersion - 2024-06-13-by CL  */
.FctVersion = 0x1u,/*修改FCT版本号，24-11-13 by CL*/
	/* 电机库版本，对于有电机库的代码，代表所使用电机库的版本 */
.McLib =0,
};
/*polyspace-begin  MISRA2012:9.2*/
u32 PowerUpTimeMs = 0u; /* Power up time in microseconds */
