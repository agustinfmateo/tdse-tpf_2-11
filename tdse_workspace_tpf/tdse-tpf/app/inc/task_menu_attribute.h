/*
 * Copyright (c) 2023 Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * 3. Neither the name of the copyright holder nor the names of its
 *    contributors may be used to endorse or promote products derived from
 *    this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING
 * IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 * @file   : task_menu_attribute.h
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

#ifndef TASK_INC_TASK_MENU_ATTRIBUTE_H_
#define TASK_INC_TASK_MENU_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Menu Statechart - State Transition Table */
/* 	------------------------+-----------------------+-----------------------+-----------------------+------------------------
 * 	| Current               | Event                 |                       | Next                  |                       |
 * 	| State                 | (Parameters)          | [Guard]               | State                 | Actions               |
 * 	|=======================+=======================+=======================+=======================+=======================|
 * 	| ST_MEN_XX_IDLE        | EV_MEN_MEN_ACTIVE     |                       | ST_MEN_XX_ACTIVE      |                       |
 * 	|                       |                       |                       |                       |                       |
 * 	|-----------------------+-----------------------+-----------------------+-----------------------+-----------------------|
 * 	| ST_MEN_XX_ACTIVE      | EV_MEN_MEN_IDLE       |                       | ST_MEN_XX_IDLE        |                       |
 * 	|                       |                       |                       |                       |                       |
 * 	------------------------+-----------------------+-----------------------+-----------------------+------------------------
 */

/* Events to excite Task Menu */
typedef enum task_menu_ev {EV_BTN_ENT_DOWN,
						   EV_BTN_ENT_UP,
						   EV_BTN_NEXT_DOWN,
						   EV_BTN_NEXT_UP,
						   EV_BTN_ESC_DOWN,
						   EV_BTN_ESC_UP,
						   EV_LDR_LOW,
						   EV_LDR_ACTIVATED,
						   EV_TIM_1_MIN,
						   EV_TIME_OPEN,
						   EV_TIME_CLOSE,
						   EV_UI_TIMEOUT} task_menu_ev_t;

/* State of Task Menu */
typedef enum task_menu_st { ST_SET_UP_OPENING_1_SPIN,
							ST_SET_UP_OPENING_2_SPEED,
							ST_SET_UP_OPENING_3_TIME_CLOSE,
							ST_SET_UP_OPENING_4_TIME_PROBE,
							ST_SET_UP_OPENING_5_TIME_OK,
							ST_SET_UP_CLOCK_1,
							ST_SET_UP_TIME_OPEN_1,
							ST_SET_UP_TIME_CLOSE_1,
							ST_SET_UP_TIME_XX_21_HOURD,
							ST_SET_UP_TIME_XX_22_HOURU,
							ST_SET_UP_TIME_XX_23_MINUTED,
							ST_SET_UP_TIME_XX_24_MINUTEU,
							ST_SET_UP_TIME_XX_25_SAVE,
							ST_SET_UP_LIGHT_OPEN_1,
							ST_SET_UP_LIGHT_OPEN_2_SEL,
							ST_SET_UP_LIGHT_OPEN_3_SAVE,
							ST_SET_UP_LIGHT_CLOSE_1,
							ST_SET_UP_LIGHT_CLOSE_2_SEL,
							ST_SET_UP_LIGHT_CLOSE_3_SAVE,
							ST_SET_UP_SAVE_CONF,
							ST_SET_UP_CHECK_1_OPENCLOSE,
							ST_SET_UP_CHECK_2_CLOSEALL,
							ST_SET_UP_CHECK_3_OK,
							ST_NORMAL_MENU_1,
							ST_NORMAL_CFG_MODE_1,
							ST_NORMAL_MENU_21_OPENCLOSE,
							ST_NORMAL_MENU_22_SEL_MANUAL,
							ST_NORMAL_MENU_23_SEL_TIME,
							ST_NORMAL_MENU_24_SEL_LIGHT} task_menu_st_t;

typedef struct
{
	uint32_t		tick;
	task_menu_st_t	state;
	task_menu_ev_t	event;
	bool			flag;
} task_menu_dta_t;

//typedef enum task_motor_id {ID_MOTOR_1,
//							 ID_MOTOR_2} task_motor_id_t;

//typedef enum task_power_id {ON,
//							 OFF} task_power_id_t;

typedef enum task_spin_id {LEFT,
							 RIGHT} task_spin_id_t;

typedef enum task_mode_id {MANUAL,
							TIME,
							LIGHT} task_mode_id_t;

typedef enum task_light_id {LOW,
							MED,
							HIGH} task_light_id_t;

/*typedef struct
{
	task_motor_id_t motor_id;
	task_power_id_t Power;
	uint16_t Speed;
	task_spin_id_t Spin;
} task_motor_dta_t;*/

typedef struct
{
	uint32_t 			data_id;
	task_mode_id_t 		mode;
	uint8_t 			time_open_hour;
	uint8_t 			time_open_minute;
	uint8_t 			time_close_hour;
	uint8_t 			time_close_minute;
	task_light_id_t 	light_open;
	task_light_id_t 	light_close;
} sys_cfg_save_t;

typedef struct
{
	bool SpinRight;
	uint8_t Speed;
	uint32_t TimeOpening;
} sys_cfg_opening_t;

typedef struct
{
	sys_cfg_save_t		*sys_cfg_save;
	//sys_cfg_opening_t	*sys_cfg_op;
	bool 				open;
} sys_cfg_dta_t;

/********************** external data declaration ****************************/
extern task_menu_dta_t task_menu_dta;
extern sys_cfg_save_t *p_sys_cfg_sv;
//extern sys_cfg_opening_t *p_sys_cfg_op;
extern uint32_t time_opening;
extern bool b_spin_right;
extern uint8_t speed_opening;

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_MENU_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
