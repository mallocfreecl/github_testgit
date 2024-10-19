/*
 * parameters.c
 *
 *  Created on: 24.03.2015
 *      Author: daniel
 */

#include "parameters.h"
#include "MotorAPI.h"
#include "api.h"
#include "main.h"

#ifdef LIN
void lin_main_bldc_set_callback(main_bldc_set_t *frame){};
void lin_main_bldc_status_handler(main_bldc_status_t *frame){};
#endif

s16 get_vbat_maximal_multiplier(void)
{
  return driver_maximal_multiplier; // INT16_MAX;(without limit)
}
