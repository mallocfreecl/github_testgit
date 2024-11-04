/*BEGIN_FILE_HDR
**************************************************************************
* NOTICE
* This software is the property of XiangBin Electric. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* XiangBin Electric.
**************************************************************************
* File Name:UserInfo.c
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
#include "UserInfo.h"

/* Variables */
/******************************************************************/
const u32 FlashCheckSum = 0x602E0C38uL;/*  Modify CheckSum - 2024-09-05-by CL  */
const u8 FlashECUInfo[12u] = {0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0xFFu,0x01u,0x01u};
