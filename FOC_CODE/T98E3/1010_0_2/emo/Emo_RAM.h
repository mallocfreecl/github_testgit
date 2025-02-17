/*BEGIN_FILE_HDR
**************************************************************************
* NOTICE
* This software is the property of XiangBin Electric. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* XiangBin Electric.
**************************************************************************
* File Name:Emo_RAM.h
********************************************************************
* Project/Product:LXT9816
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
#ifndef EMO_H
#define EMO_H

/* Includes*/
/******************************************************************/
#include "tle_device.h"
#include "Emo.h"
#include "Mat.h"
#include "Table.h"
#include "foc_defines.h"
#include "GlobalVars.h"

/* Defines*/
/******************************************************************/
/* Motor states */
#define EMO_MOTOR_STATE_UNINIT (0u)
#define EMO_MOTOR_STATE_STOP   (1u)
#define EMO_MOTOR_STATE_START  (2u)
#define EMO_MOTOR_STATE_RUN    (3u)
#define EMO_MOTOR_STATE_FAULT  (4u)

#define EMO_ERROR_NONE              (0u)
#define EMO_ERROR_MOTOR_INIT        (1u)
#define EMO_ERROR_MOTOR_NOT_STOPPED (2u)
#define EMO_ERROR_MOTOR_NOT_STARTED (3u)

/* Motor Start error */
#define EMO_ERROR_VALUE_CU_KI           (0x0001)
#define EMO_ERROR_VALUE_CU_KP           (0x0002)
#define EMO_ERROR_VALUE_CU_ADCC         (0x0004)
#define EMO_ERROR_LIMITS_REFCURRENT     (0x0008)
#define EMO_ERROR_REFCURRENT            (0x0010)
#define EMO_ERROR_SPEED_POINTS          (0x0020)
#define EMO_ERROR_T_SPEED_LP            (0x0040)
#define EMO_ERROR_STARTCURRENT          (0x0080)
#define EMO_ERROR_STARTTIME             (0x0100)
#define EMO_ERROR_SPEEDSLEWRATE         (0x0200)
#define EMO_ERROR_MINTIME               (0x0400)
#define EMO_ERROR_POLPAIR               (0x0800)
#define EMO_ERROR_CSAOFFSET             (0x1000)

/* Svm Parameter */
/* EMO_SVM_MINTIME defines the minimum time slot required to place **
** the ADC measurement inside the 3phase PWM pattern               **
** 80 * CCU6_CLK = 80 * 25ns = 2us                                 */
#define EMO_SVM_MINTIME           (5*CCU6_T12_CLK)
#define EMO_SVM_DEADTIME          (CCU6_T12DTC&0xFF)
#define EMO_DECOUPLING            (0u)

/* FluxEstimator filter time */
#define FOC_ESTFLUX_FILT_TIME FOC_FLUX_ADJUST

/*0 = stays in open-loop operation, 1 = switch into closed-loop operation */
#define EMO_RUN                                   (1)
/*******************************************************************************
**                      Global Type Definitions                              **
*******************************************************************************/
typedef struct{
	sint32 I1;
	sint32 I2;
	uint16 T1;
	uint16 T2;
}IShunt_t;

typedef struct{
  uint8 En;
  sint16 CurrKp;
  sint16 CurrKi;
  sint16 AngleShift;
} DebugVar_t;

/** \brief PI configuration */
typedef struct
{
    sint16 Kp;                      /**< \brief Proportional parameter */
    sint16 Ki;                      /**< \brief Integral parameter */
    sint16 IMin;                    /**< \brief Minimum of I output */
    sint16 IMax;                    /**< \brief Maximum of I output */
    sint16 PiMin;                   /**< \brief Minimum of PI output */
    sint16 PiMax;                   /**< \brief Maximum of PI output */
} TEmo_Pi_Cfg;

/** \brief Low pass configuration */
typedef struct
{
    sint16 CoefA;                   /**< \brief Coefficient A */
    sint16 CoefB;                   /**< \brief Coefficient B */
    sint16 Min;                     /**< \brief Minimum */
    sint16 Max;                     /**< \brief Maximum */
} TEmo_Lp_Cfg;

/** \brief FOC status */
typedef struct
{
    TComplex StatCurr;              /**< \brief Stationary current 0*/
    TComplex RotCurr;               /**< \brief Rotating current 2*/
    TComplex StatVolt;              /**< \brief Stationary voltage 4*/
    TComplex RotVolt;               /**< \brief Rotating voltage 6*/
    uint16 Angle;                   /**< \brief Angle 8*/
		uint16 Angle1;
		uint16 Angle2;
    uint16 FluxAngle;               /**< \brief Angle calculated by flux estimator 9*/
    uint16 StoredAngle;             /**< \brief Stored Angle 10*/
    uint16 PhaseRes;                /**< \brief Phase resistance 11*/
    uint16 PhaseInd;                /**< \brief Phase inductance 12*/
    sint16 StartEndSpeed;           /**< \brief End speed for start 13*/
    uint16 StartVoltAmp;            /**< \brief Voltage offset for start with mode 1 14*/
    uint16 dummy;                   /**< \brief Voltage slew rate for start 15*/
    TMat_Lp_Simple RealFluxLp;      /**< \brief Real flux low pass 16*/
    TMat_Lp_Simple ImagFluxLp;      /**< \brief Imaginary flux low pass 20*/
    uint16 CountStart;              /**< \brief Counter for Start with angle=0 24*/
    uint16 PolePair;                /**< \brief                                     */
    sint16 StartCurrent;            /**< \brief Start Current 26*/
    uint16 TimeSpeedzero;           /**< \brief Time for Speed zero 27*/
    sint16 SpeedtoFrequency;        /**< \brief Time for Speed zero 28*/
    sint32 StartSpeedSlewRate;      /**< \brief Voltage slew rate for start 30*/
    uint16 CsaGain;                 /**< \brief CsaGain Faktor 32*/
    uint16 DcLinkVoltage;           /**< \brief Dc Link Voltage 33*/
    uint16 Dcfactor1;               /**< \brief 327670/Dc Link Voltage 34*/
    sint16 StartSpeedSlope;         /**< \brief Start Speed Slope 35*/
    sint16 StartFrequencySlope;     /**< \brief Start Frequency Slope 36*/
    sint32 StartSpeedSlopeMem;      /**< \brief Start Speed Slope Memory*/
    TComplex StartVoltage;          /**< \brief Startvoltage for Startmode 1*/
    uint16 StartAngle;              /**< \brief Start angle for Mode 0 and 1 */
    TComplex RotVoltCurrentcontrol;
    uint16 StartVoltAmpDivUz;       /**< \brief Voltage offset for start with mode 1 14*/
    uint16 Dcfactor2;               /**< \brief Kfactor2*Dc Link Voltage 34*/
    uint32 Kdcdivident1;            /**< \brief Divident for K/Uz 34*/
	/*消除polyspace警告 24-11-1 by CL*/
    uint32 Kdcfactor2;              /**< \brief Factor for K*Uz 34*/
    uint16 Kdcfactoriqc;            /**< \brief Factor for iqcmax=K*Uz  */
    uint16 StatVoltAmpM;            /**< \brief Amplitude for Stat. Voltage FM 34*/
    uint16 LpCoefb0;                /**< \brief Timeconst for Pt1 Fluxestimator at open loop   34*/
    uint16 LpCoefb1;                /**< \brief Timeconst for Pt1 Fluxestimator with amp<0.9ampmax   34*/
    uint16 LpCoefb2;                /**< \brief Timeconst for Pt1 Fluxestimator with amp>0.9ampmax 34*/
} TEmo_Foc;


/** \brief FOC configuration */
typedef struct
{
    float Rshunt;
    float NominalCurrent;           /**< \brief Nominal Current */
    float PWM_Frequency;
    float PhaseRes;                 /**< \brief Phase resistance */
    float PhaseInd;                 /**< \brief Phase inductance */
    uint16 SpeedPi_Kp;              /**< \brief Speedcontroller Kp *64 */
    uint16 SpeedPi_Ki;              /**< \brief Speedcontroller Ki */
    float MaxRefCurr;               /**< \brief MaxRefCurrent for SpeedController */
    float MinRefCurr;               /**< \brief MinRefCurrent for SpeedController */
    float MaxRefStartCurr;          /**< \brief MaxRefCurrent for SpeedController by Start*/
    float MinRefStartCurr;          /**< \brief MinRefCurrent for SpeedController by Start*/
    float SpeedLevelPos;            /**< \brief SpeedLevel for MaxRefCurrent for SpeedController by Start*/
    float SpeedLevelNeg;            /**< \brief SpeedLevel for MinRefCurrent for SpeedController by Start*/
    float TimeConstantSpeedFilter;  /**< \brief Time constant for Speedfilter*/
    float TimeConstantEstFluxFilter;/**< \brief Time constant for estimator flux */
    uint16 CsaOffset;               /**< \brief Offset of current sense amplifier */
    uint16 PolePair;                /**< \brief Pol Pair counter */
    float StartCurrent;             /**< \brief Start Current */
    float TimeSpeedzero;            /**< \brief Time for Speed zero */
    float StartSpeedEnd;            /**< \brief Max Speed for Start */
    float StartSpeedSlewRate;       /**< \brief Start Speed SlewRate */
    uint16 EnableFrZero;            /**< \brief Enable Start width Frequenz=0*/
    float SpeedLevelSwitchOn;       /**< \brief Speedlevel for switch on */
    float AdjustmCurrentControl;    /**< \brief Adjustment for CurrentControl */
    float MaxSpeed;                 /**< \brief Maximum Speed */
} TEmo_Focpar_Cfg;



/** \brief Control status */
typedef struct
{
    sint16 RefSpeed;                /**< \brief Reference speed 0*/
    sint16 ActSpeed;                /**< \brief Actual speed 1*/
    sint16 RefCurr;                 /**< \brief Reference current (imaginary) 2*/
    sint16 DemagCurr;
    uint16 SpeedPiInit;             /**< \brief Initialization value for speed PI 4*/
    TMat_Pi SpeedPi;                /**< \brief Speed PI control */
    TMat_Pi RealCurrPi;             /**< \brief Real current PI control */
    TMat_Pi ImagCurrPi;             /**< \brief Imaginary current PI control */
    TMat_Lp_Simple SpeedLp;         /**< \brief Speed low pass */
    uint16 AngleBuffer[32];         /**< \brief buffer for angle */
    uint16 PtrAngle;                /**< \brief pointer for anglebuffer */
    sint16 MaxRefCurrent;           /*  69  */
    sint16 MinRefCurrent;           /*  70  */
    sint16 MaxRefStartCurrent;      /*  71  */
    sint16 MinRefStartCurrent;      /*  72  */
    sint16 Speedlevelmaxstart;      /*  73  */
    sint16 Speedlevelminstart;      /*  74  */
    sint16 SpeedLevelSwitchOn;      /*  75  */
    TMat_Lp_Simple SpeedLpdisplay;  /**< \brief Speed low pass 76*/
    TMat_Lp_Simple FluxbtrLp;       /* 82 */
    sint16 Speedest;                /* 88 */
    sint16 Speedpll;                /* 89 */
    uint16 FluxAnglePll;            /* 90 */
    uint16 Pllkp;                   /* 91 */
    uint16 Anglersptr;              /* 95 92*/
    uint16 Factorspeed;             /* 96 93*/
    uint16 Expspeedhigh;            /* 97 94*/
    uint16 Exppllhigh;              /* 98 95*/
    uint16 EnableStartVoltage;      /* 99 96*/
    TMat_Lp_Simple RotCurrImagLpdisplay;

		uint16 CloseLoopSwitchAngleDiff;
	
    sint32 IShunt;  /* Unit:0.1A */
		uint8 IShuntBufIdx;
		IShunt_t IShuntBuf[2];
		sint32 ActIShunt;/*记录实际的电流值,2021-08-11-by zyg*/
		/* 限流阈值定义 2024/10/24 by CL*/
		sint16 IShuntLimitMax;
		sint16 IShuntLimitMin;
} TEmo_Ctrl;

typedef struct
{
    uint16 comp60up;
    uint16 comp61up;
    uint16 comp62up;
    uint16 comp60down;
    uint16 comp61down;
    uint16 comp62down;
    uint16 CompT13ValueUp;
    uint16 CompT13ValueDown;
		uint16 T1;
		uint16 T2;
}CCU6Compares_t;

typedef struct
{
    CCU6Compares_t EdgeSelect[2];
}CompareVal_t;

/** \brief Space vector modulation status */
typedef struct
{
    uint16 Angle;                   /**< \brief Angle 0*/
    uint16 Amp;                     /**< \brief Amplitude 1*/
    uint16 Sector;                  /**< \brief Sector number 2*/
    uint16 T1;                      /**< \brief Time T1 4*/
    uint16 T2;                      /**< \brief Time T2 6*/
    TPhaseCurr PhaseCurr;           /**< \brief Phase current 8*/
    uint16 CsaOffset;               /**< \brief Offset of current sense amplifier 11*/
    uint16 MaxAmp;                  /**< \brief Maximum amplitude 12*/
    uint16 MaxAmp9091pr;            /**< \brief Maximum amplitude 90 prozent13*/
    uint16 MaxAmp4164pr;            /**< \brief Maximum amplitude 41 prozent14*/
	/*消除polyspace警告 24-11-1 by CL*/
    uint32 Kfact256;                /**< \brief Faktor Maximum Amp auf 256 Inc 15*/
    uint32 MaxAmpQuadrat;           /**< \brief Maximum amplitude Quadrat 16*/
    uint16 CompT13ValueUp;
    uint16 CompT13ValueDown;
    uint16 T13Trigger;
    uint16 StoredSector1;            /**< \brief Stored Sector nr 24*/
    uint16 CounterOffsetAdw;         /**< \brief Counter for Adw Offsetestimation*/
    uint32 CsaOffsetAdwSumme;        /**< \brief OffsetValue Adw*/	
    uint16 CsaOffsetAdw;             /**< \brief OffsetValue Adw*/
} TEmo_Svm;

/* Variables */
/******************************************************************/
extern  TEmo_Ctrl Emo_Ctrl;
extern TEmo_Foc Emo_Foc;
extern TEmo_Svm Emo_Svm;
extern const TEmo_Focpar_Cfg Emo_Focpar_Cfg;
extern CompareVal_t CompareVal;

/* Function declaration */
/******************************************************************/
extern void Emo_RAM_MHighTask(void);
extern void Emo_MLowTask(void);
extern void Emo_InitFoc(void);

extern void Emo_CaculateIShunt(void);

extern void Emo_ExeSvmTest(TEmo_Svm *pSvm);
extern void Emo_EstFluxTest(void);
extern uint16 Emo_CalcAngleAmpTest(TComplex Stat, uint16 *pAmp);
extern void Emo_CalcAngleAmpSvmTest(void);
extern void Emo_setspeedreferenz(sint16 speedreferenz);

__STATIC_INLINE TComplex Limitsvektor(TComplex *inp, TEmo_Svm *par);
__STATIC_INLINE TComplex Limitsvektorphase(TComplex *inp, TEmo_Svm *par);

/* INLINE functions ***********************************************************/

extern sint16 abs(sint16 inp);

/*******************************************************************************
**                      Global Inline Function Definitions                    **
*******************************************************************************/


/** \brief Performs Limits Raumvektor algorithm.
 *
 * \param[inout]
 * \param[in] Input TComplex in fixed-point format
 *
 * \return  output TComplex in fixed-point format
 * \ingroup math_api
 */
__STATIC_INLINE TComplex Limitsvektor(TComplex *inp, TEmo_Svm *par)
{
    uint32 btrqu;
    TComplex outp = {0, 0};
    uint16 inpa;
    btrqu = inp->Real * inp->Real + inp->Imag * inp->Imag;

    if (btrqu > par->MaxAmpQuadrat)
    {
        if ((abs(inp->Real)) > par->MaxAmp9091pr)
        {
            if (inp->Real < 0)
            {
                outp.Real = -par->MaxAmp9091pr;
            }
            else
            {
                outp.Real = par->MaxAmp9091pr;
            }

            if (inp->Imag < 0)
            {
                outp.Imag = -par->MaxAmp4164pr;
            }
            else
            {
                outp.Imag = par->MaxAmp4164pr;
            }
        }
        else
        {
            inpa = abs(inp->Real);
            inpa = (inpa * par->Kfact256) >> MAT_FIX_SHIFT;

            if (inpa > 256)
            {
                inpa = 256;
            }
						else/* add else - 2021-07-28-by zyg*/
						{
							
						}
            inpa = Table_sqrtmqu[inpa];
            inpa = (inpa * par->MaxAmp) >> 8;
            outp.Real = inp->Real;

            if (inp->Imag < 0)
            {
                outp.Imag = -inpa;
            }
            else
            {
                outp.Imag = inpa;
            }
        }
    }
    else
    {
        outp.Real = inp->Real;
        outp.Imag = inp->Imag;
    }

    return outp;
} /* End of Limitsvektor */


/** \brief Performs Limits Raumvektor algorithm.
 *
 * \param[inout]
 * \param[in] Input TComplex in fixed-point format
 *
 * \return  output TComplex in fixed-point format
 * \ingroup math_api
 */
__STATIC_INLINE TComplex Limitsvektorphase(TComplex *inp, TEmo_Svm *par)
{
    uint32 btrqu;
    uint32 btrfactor;
    TComplex outp = {0, 0};
    btrqu = inp->Real * inp->Real + inp->Imag * inp->Imag;

    if (btrqu > par->MaxAmpQuadrat)
    {
        btrfactor = par->MaxAmpQuadrat / (btrqu >> 15);
        btrfactor = 32500 - ((32767 - btrfactor) >> 1);
        outp.Real = (sint16)(__ssat(Mat_FixMulScale(inp->Real , btrfactor, 0), MAT_FIX_SAT));
        outp.Imag = (sint16)(__ssat(Mat_FixMulScale(inp->Imag , btrfactor, 0), MAT_FIX_SAT));
    }
    else
    {
        outp.Real = inp->Real;
        outp.Imag = inp->Imag;
    }

    return outp;
} /* End of Limitsvektorphase */


#endif /* EMO_H */

