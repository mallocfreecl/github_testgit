#include "debug.h"
#include "ADCSample.h"
#include "AppMain.h"
#include "DTC.h"
#include "IsrHandler.h"
#include "MotorAPI.h"
#include "PwmIn.h"
#include "SDKTypes.h"
#include "bemf_control.h"
#include "freemaster.h"
#include "testmode.h"

/* 修改版本号, 24.03.27 by lxs */
const Version_t Version = {
  0x9840,
  {.bits =
     {
       0x0,
       0x2,
       0x10,
     }},
  0x03, 
  0x03,
};

/* SCI enable, freemaster disable , 21.07.30 by yhd */
Debug_t DebugVar = {
  true,  // PwmInSpeedCtrlEn
  0,     // PhaseDiffOffset
  true,  // SCIEn
  false, // DirectSpeedCtrlEn
  0,     // DirectSpeed
  false, // FreeMasterEn
};

/*  test mode variable, 21.07.30 by yhd */
__root const u32 FlashCheckSum @0xFBF0 = 0x2263751d;
__root const u8 FlashECUInfo[12] @0xFBF4 = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x01, 0x01};

#if DEBUG_USE_FREE_MASTER

FMSTR_TSA_TABLE_BEGIN(VersionTbl)
FMSTR_TSA_RO_VAR(Version.ProductVersion, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(Version.InnerVersion, FMSTR_TSA_UINT16)
FMSTR_TSA_TABLE_END()

FMSTR_TSA_TABLE_BEGIN(ADCTbl)
FMSTR_TSA_RO_VAR(ADCResults.Voltage.Bat, FMSTR_TSA_UINT16)
// FMSTR_TSA_RO_VAR(ADCResults.Temperature.Chip, FMSTR_TSA_SINT16)

FMSTR_TSA_RO_VAR(ADCResults.Voltage.BatFast, FMSTR_TSA_UINT16)

#if 0
FMSTR_TSA_RO_VAR(ADCResults.Current.U, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(ADCResults.Current.V, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(ADCResults.Current.W, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(ADCResults.Current.DC, FMSTR_TSA_SINT16)
#endif

#if 0
FMSTR_TSA_RO_VAR(ADCResults.RawAD.Current.Sector0, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(ADCResults.RawAD.Current.Sector1, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(ADCResults.RawAD.Current.Sector2, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(ADCResults.RawAD.Current.Sector3, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(ADCResults.RawAD.Current.Sector4, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(ADCResults.RawAD.Current.Sector5, FMSTR_TSA_UINT16)

FMSTR_TSA_RO_VAR(ADCResults.Current.U0, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(ADCResults.Current.V0, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(ADCResults.Current.W0, FMSTR_TSA_SINT16)

FMSTR_TSA_RO_VAR(ADCResults.Current.U1, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(ADCResults.Current.V1, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(ADCResults.Current.W1, FMSTR_TSA_SINT16)

FMSTR_TSA_RO_VAR(ADCResults.Current.DC, FMSTR_TSA_SINT16)
#endif

FMSTR_TSA_TABLE_END()

FMSTR_TSA_TABLE_BEGIN(PwmInTbl)
FMSTR_TSA_RO_VAR(PwmInAPI.Freq, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(PwmInAPI.LowDuty, FMSTR_TSA_UINT16)
#if 0
FMSTR_TSA_RO_VAR(PwmInAPI.BusIdleTime, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(PwmInAPI.BusState, FMSTR_TSA_UINT8)
#endif

FMSTR_TSA_RO_VAR(B.Valid, FMSTR_TSA_UINT8)
FMSTR_TSA_TABLE_END()

FMSTR_TSA_TABLE_BEGIN(MotorInfoTbl)
FMSTR_TSA_RO_VAR(MotorVar.TargetSpeed, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(MotorVar.CurrentSpeed, FMSTR_TSA_SINT16)
FMSTR_TSA_RO_VAR(MotorVar.WindMillingSpeed, FMSTR_TSA_SINT16)

#if 0
// FMSTR_TSA_RO_VAR(MotorVar.PwmMult, FMSTR_TSA_SINT16)
// FMSTR_TSA_RO_VAR(MotorVar.PwmMultComp, FMSTR_TSA_SINT16)
// FMSTR_TSA_RO_VAR(MotorVar.NewInc, FMSTR_TSA_SINT16)
// FMSTR_TSA_RO_VAR(MotorVar.PhaseDiff, FMSTR_TSA_SINT16)
#endif

FMSTR_TSA_RO_VAR(MotorVar.SpeedTooLowTime, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(MotorVar.SpeedTooHighTime, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(MotorVar.SpeedLoseStepTime, FMSTR_TSA_UINT16)
// FMSTR_TSA_RO_VAR(MotorVar.CurrentTooLowTime, FMSTR_TSA_UINT16)
// FMSTR_TSA_RO_VAR(MotorVar.CurrentTooHighTime, FMSTR_TSA_UINT16)
// FMSTR_TSA_RO_VAR(MotorVar.CurrentTooHighTimeMax, FMSTR_TSA_UINT16)
// FMSTR_TSA_RO_VAR(MotorVar.PhaseDiffZeroCnt, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(MotorVar.StartToClose, FMSTR_TSA_UINT8)
FMSTR_TSA_RW_VAR(MotorVar.FaultRecord, FMSTR_TSA_UINT16)

FMSTR_TSA_RO_VAR(DW.MotorRestartAndFaultCnt_bnwn.ShortCntLast_PreviousInput, FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DW.MotorRestartAndFaultCnt_bnwn.OpenCntLast_PreviousInput, FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DW.MotorRestartAndFaultCnt_bnwn.LockCntLast_PreviousInput, FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DW.MotorRestartAndFaultCnt_bnwn.TimeCnt, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(DW.MotorRestartAndFaultCnt_bnwn.RestartIntervalLast_PreviousInp, FMSTR_TSA_UINT16)
FMSTR_TSA_TABLE_END()

FMSTR_TSA_TABLE_BEGIN(MotorTuneTbl)
#if DEBUG_SCI_SPEED_EN
FMSTR_TSA_RW_VAR(DebugVar.PwmInSpeedCtrlEn, FMSTR_TSA_UINT8)
FMSTR_TSA_RW_VAR(U.PwmInHighDuty, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(DebugVar.DirectSpeedCtrlEn, FMSTR_TSA_UINT8)
FMSTR_TSA_RW_VAR(DebugVar.DirectSpeed, FMSTR_TSA_UINT16)
#endif

FMSTR_TSA_RW_VAR(DebugVar.PhaseDiffOffset, FMSTR_TSA_SINT16)
FMSTR_TSA_RW_VAR(SCIDebug.Motor.OverModulateK, FMSTR_TSA_UINT16)

FMSTR_TSA_RW_VAR(mult_controller.param.Kp, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(mult_controller.param.Ki, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(inc_controller.param.Kp, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(inc_controller.param.Ki, FMSTR_TSA_UINT16)

FMSTR_TSA_RW_VAR(m.accel_open, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(m.uf_offset, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(m.uf_slope, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(m.uf_boost, FMSTR_TSA_UINT16)
FMSTR_TSA_RW_VAR(m.uf_min, FMSTR_TSA_UINT16)

FMSTR_TSA_RW_VAR(MotorVar.VolatgeCompEn, FMSTR_TSA_UINT8)
FMSTR_TSA_RW_VAR(MotorVar.ParamTuneEn, FMSTR_TSA_UINT8)
FMSTR_TSA_RW_VAR(MotorVar.CloseLoopEn, FMSTR_TSA_UINT8)
FMSTR_TSA_TABLE_END()

FMSTR_TSA_TABLE_BEGIN(DTCTbl)
FMSTR_TSA_RO_VAR(DTCVar.PowerUpCnt, FMSTR_TSA_UINT16)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxBatHigh], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxBatLow], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxChipTHigh], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxChipTLow], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorShort], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorOpen], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorLock], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorSpeedOutRange], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorCurrentOutRange], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorDrvErr], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorDrvOverCurrent], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorDrvOverTemp], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorDrvVCCLow], FMSTR_TSA_UINT8)
FMSTR_TSA_RO_VAR(DTCVar.Records[eDTCIdxMotorDrvVGLow], FMSTR_TSA_UINT8)
FMSTR_TSA_TABLE_END()

FMSTR_TSA_TABLE_LIST_BEGIN()
FMSTR_TSA_TABLE(VersionTbl)
FMSTR_TSA_TABLE(ADCTbl)
FMSTR_TSA_TABLE(MotorInfoTbl)
FMSTR_TSA_TABLE(MotorTuneTbl)
FMSTR_TSA_TABLE(DTCTbl)
FMSTR_TSA_TABLE(PwmInTbl)
FMSTR_TSA_TABLE_LIST_END()

#endif
