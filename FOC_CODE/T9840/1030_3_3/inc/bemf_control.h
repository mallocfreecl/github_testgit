#ifndef __BEMF_CONTROL__
#define __BEMF_CONTROL__

#include "api.h"
#include "commons.h"
#include "motor.h"
#include "pi_controller.h"
#include "u_f_table.h"

/**
 * @defgroup Controller Controller module
 * @ingroup OTHER
 *
 * This module consist of a phase (phase_pi_controller) and a speed controller (inc_pi_controller). The phase controller
 * tries to hold the motor at the optimal phase. The speed controller is responsible for the applied voltage and can
 * control with the help of the phase controller the speed. Depending on the operational state of the controller the
 * applied voltage and rotation rate is set manual, forced or sensed.
 *
 * @{
 */

/** Absolute value*/
#define ABS(x) (((x) < 0) ? -(x) : (x))
/** Maximal step for speedup or slowdown of the increment in forced operational mode*/
#define DELTA_MAX 200
/** The pi factors for the phase controller depends on the rotation rate.
 * At NORM_DREHZAHL the error is multiplied with the unadopted factor.*/
#define NORM_DREHZAHL 200

/** Scaling for increment output value to have PI factors higher than one*/
#define SCALE_INC 15
/** Scaling for the multiplier output value to have PI factors higher than one*/
#define SCALE_MULT 15
/***/
#define ACCELERATION_NGAIN 8
/** Only if forced commutation speeds up to this value, closed loop control will start*/
#define WINDMILL_INC_MAX_START UINT16_MAX
#define WINDMILL_START_WITH_PHASE_RESERVE 30

#define CLOSED_TO_IDLE_AT_INC 100 //
#define PHASE_PI_DEAD (DEFAULT_INC)
#define PHASE_PI_DEAD_SHIFT ((s32)(PHASE_PI_DEAD << SCALE_INC))

// after 3sek in the oob barrier the start is valid
#define START_SUCCES_UNKNOWN_DURATION 300
// maximal 3 gain steps to do perform a sucessfull start
#define START_FAILURE_NO_SUCCES_MAX_GAIN 3

/*******************************************************************************
 * Typedefs
 *******************************************************************************/

/** Type of operational mode*/
typedef enum
{
  /** Idle, driver is set to idle*/ mode_idle,
  /** Sensed, pre_pwm inc and mult is changed measured phase errors*/ mode_closed,
  /** Forced, pre_pwm inc and mult is changed via u_f_table*/ mode_open,
  /** Manual, pre_pwm inc and mult change only per user*/ mode_manuell,
  mode_invalid,
} bemf_control_mode_t;

/** Operational state of the controller.*/
// On startup is current.speed = 0 and target.speed the final velocity
typedef struct
{
  /** Actual mode*/ bemf_control_mode_t mode;
  /** Actual setpoint for the speed*/ s16 speed;
  /** Actual setpoint for the speed*/ s32 speed_shifted;
} bemf_control_current_state_t;

/** Desired operational mode and speed*/
typedef struct
{
  /** Demanded mode*/ bemf_control_mode_t mode;
  /** Target of the speed*/ s16 speed;
} bemf_control_target_state_t;

/* 更改结构体定义位置 2023.10.29 by lxs */
typedef struct
{
  u16 Sup;
  u16 U_H;
  u16 U_L;
  u16 V;
  u16 W;
} OpenLoadDiagVoltage_t;

/*******************************************************************************
 * Prototypes
 *******************************************************************************/
/**@brief Reset both controllers.*/
void bemf_control_reset(s16 inc, s16 mult);

/**@brief In case of a overcurrent this function should be called.*/
void bemf_control_oc_shutdown_unsafe(void);

/**@brief Controls the acceleration to adjust the rotation rate.
 * param  accel Acceleration speed.*/
/* 修改形参名，保持一致  2023.10.17 by lxs */
void Motor_SpeedRamp(u16 Acc);

extern bool Motor_IsSpeedUp(void);

/**@brief Updates the controller mode.*/
void Motor_ModeStateMachine(void);

/**@brief Update the controller with a new measured phase difference.
 * In sensed mode the controller changes his state from the open-loop controlled, which is equivalent to the forced
 * mode, into closed-loop control, if the detection of the zerocrosssing is stable enough.
 * @param phase_diff      Phase difference in basephases
 * @param index         Index of the zerocrossing
 * @retval            Corrected Phase difference in basephases.*/
 /* 消除polyspace警告，修改形参名字 2023.10.17  by lxs */
void bemf_control_call(s16 phase_diff, u8 index_number);

/**@brief Sets the desired operation mode of the controller idle, manual, forced or sensed.
 *  @param new_mode      Desired operational mode*/
void Motor_SetTargetMode(bemf_control_mode_t new_mode);

/**@brief Returns the operation mode of the controller idle, manual, forced or sensed.
 *  @retval      Actual operational mode*/
bemf_control_mode_t bemf_control_get_mode(void);

/**@brief Updates the integral factor for the phase controller dynamically depending on speedup or slowdown. */
void bemf_control_variable_inc_Ki();

/*******************************************************************************
 * Callback-Functions - have to be implemented inside demo.c
 *******************************************************************************/
/**@brief If the controller changes his operational mode this function is called.*/
// void bemf_control_mode_changed_callback( void );

/**@brief If the controller changes the speed or applied voltage this function is called.*/
void bemf_control_inc_scale_changed_callback(void);
void Motor_ChangeModeTo(bemf_control_mode_t next_mode);

u16 pre_pwm_rotation_angle(void);
s32 pre_pwm_get_speed(void);
s32 pre_pwm_get_torque(void);
void pre_pwm_set_torque(s16 mult);
void pre_pwm_set_rotation_speed(s16 inc);
void Motor_BreakEnable(bool enable);

extern pi_ctrl_data_t mult_controller;
extern pi_ctrl_data_t inc_controller;

extern bool enable_current_loop;

extern u16 FilteredBat;

/**Actual operational mode and speed retval bemf_control_state_t object.*/
// Only used for the menu. Use the function calls.
extern bemf_control_target_state_t target;
extern bemf_control_current_state_t current;

s16 inc_controller_fun(s16 phase_diff);
/* 消除polyspace警告，修改形参名字 2023.10.17  by lxs*/
s16 mult_controller_fun(u16 index_number, s16 new_inc, s16 phase_diff);

extern bool Motor_IsWindmillPresent(void);

extern bool Motor_StillStateDiag(void);
extern bool Motor_OffStateShortDiag(void);

/** @} */
#endif /* __BEMF_CONTROL__ */
