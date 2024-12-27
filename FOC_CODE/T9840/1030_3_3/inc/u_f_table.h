#ifndef __U_F_TABLE__
#define __U_F_TABLE__

#include "ADCSample.h"
#include "api.h"
#include "bemf_control.h"
#include "commons.h"
#include "motor.h"

#define MULTIPLIER_REFERENCE_SHIFT 11
/**
 * @defgroup Motor Motor parameter
 * @ingroup OTHER
 *
 * In this module are stored all motor dependent data for sensorless commutation.
 * A frequency to voltage characteristic curve has to be deposited in a table to startup the motor without position
 * informations. Also the PID phase and rotation rate controller needs to be configurated for different motor types.
 * @{
 */
/** maximal size of the table*/
#define U_F_TABLE_SIZE 15

#if 0
/** return = a*inc + c + (startup_boost)*/
typedef const struct uf_func{
     /** counter of factor for multiplier*/                         u16 a;
     /** offset for multiplier*/                            u16 c;
     /** additional voltage for startup*/                   u16 statup_boost;
}uf_func_t;

/** Actual selected motor*/
extern const motor_t * const motors[];
#endif

/**@brief Returns for a given increment the corresponding multiplier of the table
 * @param inc       rotation rate as increment
 * @return        voltage amplitude as multiplier*/
s16 U_F_Kennlinie(s16 sinc, u16 boost, bool offset, bool divider_hw_en);

/** @} */
#endif /* __U_F_TABLE_*/
