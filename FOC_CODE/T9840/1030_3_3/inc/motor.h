/*
 * motor.h
 *
 *  Created on: Aug 4, 2014
 *      Author: daniel
 */

#ifndef MOTOR_H_
#define MOTOR_H_

#include "api.h"
#include "driver_52350.h"

#if 1
// TODO MOTCU2
/*parameter for open loop*/
/* 水泵极对数为2 23.09.06 by lxs */
#define MOTOR_POLE_PAIRS 2 // number of polepairs of the motor

/*parameter for open loop*/
#define MOTOR_OPEN_VF_ACCEL 1000 // acceleration of the motor for open and closed loop

/* 减小开环占空比，减小堵转电流 24.03.12 by lxs */
#define MOTOR_OPEN_VF_OFFSET 100  // applied voltage amplitude for zero rotationrate
/* 改为300，使开环相电流波形较为平缓 23.09.08 by lxs */
#define MOTOR_OPEN_VF_SLOPE 300   // 300//800//Torque
#define MOTOR_OPEN_VF_BOOST 0     // additional applied voltage in case of speedup
#define MOTOR_CLOSED_MIN_MULT 160 // minimal applied voltage for detent torque and controller

/*parameter for closed loop*/
/* 减小切闭环的转速，减小堵转电流 24.03.12 by lxs */
#define MOTOR_CLOSED_START_CONTROL 500 // 400//minimal speed in inc to start closed loop
#define MOTOR_CLOSED_STOP_CONTROL 200  // speed in inc to go back to open loop

#define MOTOR_CLOSED_INC_CTRL_KP                                                                                       \
  3000 // 3000//6400//sets the proportional gain to control the rotor angle by changing the speed
#define MOTOR_CLOSED_INC_CTRL_KI                                                                                       \
  256 // 200//800//sets the integrational gain to control the rotor angle by changing the speed
#define MOTOR_CLOSED_MULT_CTRL_KP                                                                                      \
  500 // 200//sets the proportional gain to control the produced current/torque/speed by changing the voltage amplitude
#define MOTOR_CLOSED_MULT_CTRL_KI                                                                                      \
  3000 // 2000//sets the integrational gain to control the produced current/torque/speed by changing the voltage
       // amplitude

#define MOTOR_CLOSED_SETPOINT 0       //-30//-360//-50
#define MOTOR_CLOSED_DYN_SETPOINT 500 // 300
#define MOTOR_CLOSED_MAX_ROT 10000    // 2890//sets the maximal rotation rate for stall/error detection

/*start of advanced settings*/
#ifndef MOTOR_CLOSED_SETPOINT
#define MOTOR_CLOSED_SETPOINT 0 // changes the phase controller setpoint of the window value
#endif
#ifndef MOTOR_CLOSED_DYN_SETPOINT
#define MOTOR_CLOSED_DYN_SETPOINT 0 // changes the phase controller setpoint of the window value dynamically by inc
#endif

#ifndef MOTOR_CLOSED_ACCEL_UP
#define MOTOR_CLOSED_ACCEL_UP 2000 // MOTOR_OPEN_VF_ACCEL
#endif
#ifndef MOTOR_CLOSED_ACCEL_DOWN
/* 增加闭环降速的加速度 24.03.12 by lxs */
#define MOTOR_CLOSED_ACCEL_DOWN 2000 // MOTOR_OPEN_VF_ACCEL/2
#endif

#endif

// default as csv config
// motor_t m = {3,   1000, 125, 3700, 350,  50,       100, 20,   1000,1000   1500, 300, 200, 5000,   5000, 0, 0};

// enable #define CSVMOTORCONFIG to define the config via csv directly in motor.c
// accel = (a[rpm/sek]*pole*256)/(5.51*100);

/** Configuration data to support different motors*/
typedef struct motor
{
  // other
  /** number of pole pairs*/ volatile u8 pole_pairs;

  // open loop
  /** acceleration in inc units in open loop*/ volatile u16 accel_open;
  /** counter of factor for multiplier*/ volatile u16 uf_offset;
  /** offset for multiplier*/ volatile u16 uf_slope;
  /** additional voltage for startup*/ volatile u16 uf_boost;
  /** minimal voltage for startup*/ volatile u16 uf_min;

  // closed loop
  /** sensed mode inc_start. Depends on START_NO_SUCCES_MAX_GAIN*/ volatile u16 start_control;
  /** sensed mode inc_start*/ volatile u16 stop_control;
  /** acceleration in inc units in closed loop*/ volatile u16 accel_closed_up;
  /** acceleration in inc units in closed loop*/ volatile u16 accel_closed_down;
#if 0
  /** proportional factor for phase controller*/                    const u16 pKp;
    /** integral     factor for phase controller*/                    const u16 pKi;
    /** proportional factor for speed controller*/                    const u16 iKp;
    /** integral    factor for speed controller in case of speedup*/  const u16 iKi;
#else
  /** proportional factor for phase controller*/ volatile u16 pKp;
  /** integral     factor for phase controller*/ volatile u16 pKi;
  /** proportional factor for speed controller*/ volatile u16 iKp;
  /** integral    factor for speed controller in case of speedup*/ volatile u16 iKi;
#endif
  /** max_rotatation_rate in inc units*/ volatile u16 max_rot;
  /** increase shift_setpint dynamically to the speed*/ volatile s16 dynamic_setpoint; // not used
  /** setpoint for angle reference*/ volatile s16 maximal_setpoint;                    // not used

} motor_t;

// per default
#ifndef CSVMOTORCONFIG
#define PHASE_REFERENCE_DIRECT              // the phase shift is done straight
#define FORWARD_PHASE_REFERENCE_TO_SETPOINT // the phase shift is done per setpoint
//#define DISABLE_OC_ERROR_STOP //enabled early stop at about 10A
#endif

/*Enable conversion*/
#define CONVERT_SETTINGS_FROM_52305_TO_52352
//#define CONVERT_SETTINGS_FROM_52352_TO_52305

#ifdef T52350
#ifdef CONVERT_SETTINGS_FROM_52305_TO_52352
#define VF_CON_F 1 // 0.265466297
#else
#define VF_CON_F 1
#endif
#endif

extern motor_t m;
#endif /* MOTOR_H_ */
