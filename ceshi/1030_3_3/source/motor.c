/*
 * motor.c
 *
 *  Created on: Aug 6, 2014
 *      Author: daniel
 */
#include "motor.h"

/*build the struct for the software*/
motor_t m = {MOTOR_POLE_PAIRS,

             MOTOR_OPEN_VF_ACCEL,
             MOTOR_OPEN_VF_OFFSET *VF_CON_F,
             MOTOR_OPEN_VF_SLOPE *VF_CON_F,
             MOTOR_OPEN_VF_BOOST *VF_CON_F,
             MOTOR_CLOSED_MIN_MULT *VF_CON_F,

             MOTOR_CLOSED_START_CONTROL,
             MOTOR_CLOSED_STOP_CONTROL,

             MOTOR_CLOSED_ACCEL_UP,
             MOTOR_CLOSED_ACCEL_DOWN,

             MOTOR_CLOSED_INC_CTRL_KP,
             MOTOR_CLOSED_INC_CTRL_KI,
             MOTOR_CLOSED_MULT_CTRL_KP *VF_CON_F,
             MOTOR_CLOSED_MULT_CTRL_KI *VF_CON_F,

             MOTOR_CLOSED_MAX_ROT,
             MOTOR_CLOSED_SETPOINT,
             MOTOR_CLOSED_DYN_SETPOINT};
