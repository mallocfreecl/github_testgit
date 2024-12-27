#ifndef ISRHANDLER_H
#define ISRHANDLER_H

#include "SDKTypes.h"

extern Time_t Time;

extern void MotorDrv_IO_Err_Handler(int sno);

extern void SCIRxHandler(int sno);
extern void SCITxHandler(int sno);

extern void CCTimer0_A_RestartHandler(int sno);
extern void CCTimer0_B_RestartHandler(int sno);
extern void CCTimer2_A_RestartHandler(int sno);
extern void CCTimer2_A_CaptureHandler(int sno);
extern void CCTimer2_A_OverflowHandler(int sno);
extern void CCTimer2_B_RestartHandler(int sno);
extern void CCTimer2_B_CaptureHandler(int sno);
extern void CCTimer2_B_OverflowHandler(int sno);

extern void ADCListDoneHandler(int sno);
extern void ADCDMAErrorHandler(int sno);

#endif
