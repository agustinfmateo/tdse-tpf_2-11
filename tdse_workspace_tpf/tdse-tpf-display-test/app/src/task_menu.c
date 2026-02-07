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
 *
 * @file   : task_menu.c
 * @date   : Set 26, 2023
 * @author : Juan Manuel Cruz <jcruz@fi.uba.ar> <jcruz@frba.utn.edu.ar>
 * @version	v1.0.0
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "board.h"
#include "app.h"
#include "task_menu_attribute.h"
#include "task_menu_interface.h"
#include "task_actuator_attribute.h"
#include "task_actuator_interface.h"
#include "task_clock.h"
#include "display.h"
#include "EEPROM.h"
#include "math.h"

/********************** macros and definitions *******************************/
#define G_TASK_MEN_CNT_INI			0ul
#define G_TASK_MEN_TICK_CNT_INI		0ul

#define DEL_MEN_XX_MIN				0ul
#define DEL_MEN_XX_MED				50ul
#define DEL_MEN_XX_MAX				500ul
#define DEL_MEN_SAVE                3ul

#define EEP_PAG_CFG_OP				0
#define EEP_PAG_SAVE_START			1
#define EEP_OFF_CFG_OP_SPIN			0
#define EEP_OFF_CFG_OP_SPEED		1
#define EEP_OFF_CFG_OP_TIME			2
#define EEP_OFF_CFG_OP_FLAG			6
#define EEP_OFF_CFG_SAVE_ADD		10
#define EEP_SIZE_SPIN				1
#define EEP_SIZE_SPEED				1
#define EEP_SIZE_TIME				4
#define EEP_SIZE_FLAG				4
#define EEP_SIZE_SAVE_ADD			2

#define MASK_ADDRESS_PAGE			0x7fc0
#define MASK_ADDRESS_OFFSET			0x003f

typedef enum clock_id {CLOCK,
						TIME_OPEN,
						TIME_CLOSE} clock_id_t;

/********************** internal data declaration ****************************/
task_menu_dta_t task_menu_dta =
	{DEL_MEN_XX_MIN, ST_SET_UP_OPENING_1_SPIN, EV_BTN_ENT_UP, false};


#define MENU_DTA_QTY	(sizeof(task_menu_dta)/sizeof(task_menu_dta_t))

/********************** internal functions declaration ***********************/
void task_display_refresh(void);
void task_display_menu_1(void);
void task_display_menu_help(task_menu_st_t state);

bool check_memory_empty(void);
void memory_save_cfg(sys_cfg_save_t *config);
void memory_save_op_spin(uint8_t spin);
void memory_save_op_speed(uint8_t speed);
void memory_save_op_time(uint32_t time);
void memory_get_cfg(sys_cfg_save_t *config);
void memory_get_op_spin(uint8_t *spin);
void memory_get_op_speed(uint8_t *speed);
void memory_get_op_time(uint32_t *time);

void motor_open_test(void);
void motor_close_test(void);
void motorOpen(sys_cfg_dta_t *cfg);
void motorClose(sys_cfg_dta_t *cfg);

/********************** internal data definition *****************************/
const char *p_task_menu 		= "Task Menu (Interactive Menu)";
const char *p_task_menu_ 		= "Non-Blocking & Update By Time Code";

bool r_spin;
uint8_t aux_speed;
uint32_t aux_timer;
sys_cfg_save_t 			sys_cfg_save;
sys_cfg_opening_t 		sys_cfg_opening = {&r_spin, &aux_speed, &aux_timer};
sys_cfg_dta_t sys_cfg_dta = {&sys_cfg_save, &sys_cfg_opening, false};

clock_id_t clock_id;

//task_motor_dta_t motor_1 = {ID_MOTOR_1, OFF, 0, LEFT};
//task_motor_dta_t motor_2 = {ID_MOTOR_2, OFF, 0, LEFT};

//char *motor_list[] = {"MOTOR 1","MOTOR 2"};
//char *power_list[] = {"ON","OFF"};
//char *spin_list[] = {"L","R"};

//char motor = 0;
//uint8_t aux_spin = LEFT;
//char aux_power = ON;
static bool mem_empty;
static uint8_t clk_array[4] = {0, 0, 0, 0};

const uint16_t size_sys_cfg_save = sizeof(sys_cfg_save_t);

/********************** external data declaration ****************************/
uint32_t g_task_menu_cnt;
volatile uint32_t g_task_menu_tick_cnt;
sys_cfg_save_t *p_sys_cfg = &sys_cfg_save;
sys_cfg_opening_t *p_sys_cfg_op = &sys_cfg_opening;

uint32_t time_opening;
bool b_spin_right;
uint8_t speed_opening;
/********************** external functions definition ************************/
void task_menu_init(void *parameters)
{
	task_menu_dta_t *p_task_menu_dta;
	sys_cfg_dta_t *p_sys_cfg_dta;
	task_menu_st_t	state;
	task_menu_ev_t	event;
	bool b_event;

	/* Print out: Task Initialized */
	LOGGER_LOG("  %s is running - %s\r\n", GET_NAME(task_menu_init), p_task_menu);
	LOGGER_LOG("  %s is a %s\r\n", GET_NAME(task_menu), p_task_menu_);

	g_task_menu_cnt = G_TASK_MEN_CNT_INI;

	/* Print out: Task execution counter */
	LOGGER_LOG("   %s = %lu\r\n", GET_NAME(g_task_menu_cnt), g_task_menu_cnt);

	init_queue_event_task_menu();

	/* Update Task Actuator Configuration & Data Pointer */
	p_task_menu_dta = &task_menu_dta;
	p_sys_cfg_dta = &sys_cfg_dta;

	/* Print out: Task execution FSM */
	state = p_task_menu_dta->state;
	LOGGER_LOG("   %s = %lu", GET_NAME(state), (uint32_t)state);

	event = p_task_menu_dta->event;
	LOGGER_LOG("   %s = %lu", GET_NAME(event), (uint32_t)event);

	b_event = p_task_menu_dta->flag;
	LOGGER_LOG("   %s = %s\r\n", GET_NAME(b_event), (b_event ? "true" : "false"));

	cycle_counter_init();
	cycle_counter_reset();

	displayInit( DISPLAY_CONNECTION_GPIO_4BITS );
	clock_UI_Timeout_set(3);

    displayCharPositionWrite(0, 0);
	displayStringWrite("   Inicio de    ");
	displayCharPositionWrite(0, 1);
	displayStringWrite("   sistema...   ");
	HAL_Delay(1000);
	mem_empty = check_memory_empty();
	if(mem_empty)
	{
		displayCharPositionWrite(0, 0);
		displayStringWrite("Configuracion de");
		displayCharPositionWrite(0, 1);
		displayStringWrite("sentido de giro ");
		HAL_Delay(5000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("En un momento se");
		displayCharPositionWrite(0, 1);
		displayStringWrite("movera el motor ");
		HAL_Delay(5000);
		//motor_open_test();

		task_display_menu_help(p_task_menu_dta->state);

		displayCharPositionWrite(0, 0);
		displayStringWrite(" Abrio o cerro? ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("Cerro      Abrio");
		clock_UI_Timeout_reset();
	}
	else
	{
		p_task_menu_dta->state = ST_SET_UP_CHECK_1_OPENCLOSE;
		memory_get_cfg(p_sys_cfg_dta->sys_cfg_save);

		task_display_menu_help(p_task_menu_dta->state);

		displayCharPositionWrite(0, 0);
		displayStringWrite("   Esta abierta? ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("NO -A medias- SI");
		clock_UI_Timeout_reset();
	}
	g_task_menu_tick_cnt = G_TASK_MEN_TICK_CNT_INI;
	HAL_NVIC_DisableIRQ(EXTI9_5_IRQn);
}


void task_menu_update(void *parameters)
{
	task_menu_dta_t *p_task_menu_dta;
	sys_cfg_dta_t *p_sys_cfg_dta;
	clock_id_t *p_clock_id = &clock_id;
	bool b_time_update_required = false;
	char menu_str[20];

	/* Update Task Menu Counter */
	g_task_menu_cnt++;

	/* Protect shared resource (g_task_menu_tick) */
	__asm("CPSID i");	/* disable interrupts*/
    if (G_TASK_MEN_TICK_CNT_INI < g_task_menu_tick_cnt)
    {
    	g_task_menu_tick_cnt--;
    	b_time_update_required = true;
    }
    __asm("CPSIE i");	/* enable interrupts*/

    while (b_time_update_required)
    {
		/* Protect shared resource (g_task_menu_tick) */
		__asm("CPSID i");	/* disable interrupts*/
		if (G_TASK_MEN_TICK_CNT_INI < g_task_menu_tick_cnt)
		{
			g_task_menu_tick_cnt--;
			b_time_update_required = true;
		}
		else
		{
			b_time_update_required = false;
		}
		__asm("CPSIE i");	/* enable interrupts*/

    	/* Update Task Menu Data Pointer */
		p_task_menu_dta = &task_menu_dta;
		p_sys_cfg_dta = &sys_cfg_dta;

    	if (DEL_MEN_XX_MIN < p_task_menu_dta->tick)
		{
			p_task_menu_dta->tick--;
		}
		else
		{
			p_task_menu_dta->tick = DEL_MEN_XX_MAX;

			if (true == any_event_task_menu())
			{
				p_task_menu_dta->flag = true;
				p_task_menu_dta->event = get_event_task_menu();
			}

			switch (p_task_menu_dta->state)
			{
				case ST_SET_UP_OPENING_1_SPIN:

					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_OPENING_2_SPEED;

						memory_save_op_spin((uint8_t)RIGHT);
						clock_UI_Timeout_reset();

						displayCharPositionWrite(0, 0);
						displayStringWrite("Configuracion de");
						displayCharPositionWrite(0, 1);
						displayStringWrite("    velocidad   ");
						HAL_Delay(5000);

						//task_display_menu_help(p_task_menu_dta->state);
						aux_speed = 1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Velocidad = 1   ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("Test  -OK-   +  ");
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_OPENING_2_SPEED;
						memory_save_op_spin((uint8_t)LEFT);
						clock_UI_Timeout_reset();

						displayCharPositionWrite(0, 0);
						displayStringWrite("Configuracion de");
						displayCharPositionWrite(0, 1);
						displayStringWrite("    velocidad   ");
						HAL_Delay(5000);

						//task_display_menu_help(p_task_menu_dta->state);
						aux_speed = 1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Velocidad = 1   ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("Test  -OK-   +  ");
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						task_display_menu_help(p_task_menu_dta->state);
						displayCharPositionWrite(0, 0);
						displayStringWrite(" Abrio o cerro? ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("Cerro      Abrio");
						clock_UI_Timeout_reset();
					}
					break;

				case ST_SET_UP_OPENING_2_SPEED:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						if(aux_speed >= 10) aux_speed = 1;
						else aux_speed++;
						sprintf(menu_str,"Velocidad = %d  ",aux_speed);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						clock_UI_Timeout_reset();
						//motor_close_test();
					}
					else if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_OPENING_3_TIME_CLOSE;

						memory_save_op_speed(aux_speed);
						clock_UI_Timeout_reset();

						displayCharPositionWrite(0, 0);
						displayStringWrite("Configuracion de");
						displayCharPositionWrite(0, 1);
						displayStringWrite("    apertura    ");
						HAL_Delay(5000);

						task_display_menu_help(p_task_menu_dta->state);

						displayCharPositionWrite(0, 0);
						displayStringWrite("Presione 'Next' ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("para comenzar   ");
					}
/*					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						task_display_menu_help(p_task_menu_dta->state);
						sprintf(menu_str,"Velocidad = %d  ",aux_speed);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("Test  -OK-   +  ");
					}*/
					break;

				case ST_SET_UP_OPENING_3_TIME_CLOSE:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_OPENING_4_TIME_PROBE;

						aux_timer = HAL_GetTick();
						clock_UI_Timeout_reset();

						displayCharPositionWrite(0, 1);
						displayStringWrite("para terminar   ");
						//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						task_display_menu_help(p_task_menu_dta->state);

						displayCharPositionWrite(0, 0);
						displayStringWrite("Presione 'Next' ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("para comenzar   ");
						clock_UI_Timeout_reset();
					}
					break;

				case ST_SET_UP_OPENING_4_TIME_PROBE:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_OPENING_5_TIME_OK;

						//op_motor_stop
						//op_open_blinds
						//op_close_blinds
						//HAL_Delay(1000)
						//op_open_blinds

						aux_timer = HAL_GetTick() - aux_timer;
						clock_UI_Timeout_reset();
						displayCharPositionWrite(0, 0);
						displayStringWrite("Cerro y abrio  ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("correctamente?");
						HAL_Delay(3000);

						displayCharPositionWrite(0, 0);
						displayStringWrite("Enter - SI      ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("Escape - No     ");
						HAL_Delay(3000);

						displayCharPositionWrite(0, 0);
						displayStringWrite(" Cerro y Abrio? ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("  NO        SI  ");
					}
					break;

				case ST_SET_UP_OPENING_5_TIME_OK:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

						//op_set_opening_time
						//reset_clock

						memory_save_op_time(aux_timer);
						p_sys_cfg_dta->sys_cfg_save->mode = MANUAL;
						p_sys_cfg_dta->sys_cfg_save->light_close = LOW;
						p_sys_cfg_dta->sys_cfg_save->light_open = LOW;
						p_sys_cfg_dta->sys_cfg_save->time_close_hour = 0;
						p_sys_cfg_dta->sys_cfg_save->time_close_minute = 0;
						p_sys_cfg_dta->sys_cfg_save->time_open_hour = 0;
						p_sys_cfg_dta->sys_cfg_save->time_open_minute = 0;
						g_clock[0] = 0;
						g_clock[1] = 0;
						displayCharPositionWrite(0, 0);
						displayStringWrite("Configuraciones ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("    generales   ");
						HAL_Delay(5000);

						displayCharPositionWrite(0, 0);
						displayStringWrite("   Configurar   ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("      reloj     ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_OPENING_3_TIME_CLOSE;

						clock_UI_Timeout_reset();
						displayCharPositionWrite(0, 0);
						displayStringWrite("Presione 'Next' ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("para comenzar   ");
					}
					break;

				case ST_SET_UP_CLOCK_1:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Configurar hora ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("  de apertura   ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty)
						{
							p_task_menu_dta->state = ST_SET_UP_SAVE_CONF;

							displayCharPositionWrite(0, 0);
							displayStringWrite("   Terminar?    ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  NO        SI  ");
						}
						else
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;
							task_display_menu_1();
						}
						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_XX_21_HOURD;

						clock_UI_Timeout_reset();

						*p_clock_id = CLOCK;
						clk_array[0] = g_clock[0] / 10;
						clk_array[1] = g_clock[0] % 10;
						clk_array[2] = g_clock[1] / 10;
						clk_array[3] = g_clock[1] % 10;
						task_display_refresh();
						sprintf(menu_str,"%d               ", clk_array[0]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						sprintf(menu_str, " %d:%d%d", clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 1);
						displayStringWrite(menu_str);
						displayCharPositionWrite(8, 1);
						displayStringWrite("guardar");
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open)//op_close_blinds
						{
							HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
							p_sys_cfg_dta->open = false;
						}
					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open)//op_open_blinds
						{
							HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET);
							p_sys_cfg_dta->open = true;
						}
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							clock_UI_Timeout_reset();
							task_display_menu_1();
						}
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_TIME_OPEN_1:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_CLOSE_1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Configurar hora ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("   de cierre    ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty)
						{
							p_task_menu_dta->state = ST_SET_UP_SAVE_CONF;

							displayCharPositionWrite(0, 0);
							displayStringWrite("  Guardar confi.?");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  NO        SI  ");
						}
						else
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_XX_21_HOURD;

						*p_clock_id = TIME_OPEN;
						clk_array[0] = p_sys_cfg_dta->sys_cfg_save->time_open_hour / 10;
						clk_array[1] = p_sys_cfg_dta->sys_cfg_save->time_open_hour % 10;
						clk_array[2] = p_sys_cfg_dta->sys_cfg_save->time_open_minute / 10;
						clk_array[3] = p_sys_cfg_dta->sys_cfg_save->time_open_minute % 10;
						task_display_refresh();
						sprintf(menu_str,"%d               ", clk_array[0]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						sprintf(menu_str," %d:%d%d   ", clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 1);
						displayStringWrite(menu_str);
						displayCharPositionWrite(8, 1);
						displayStringWrite("guardar");

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();

							clock_UI_Timeout_reset();
						}
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_TIME_CLOSE_1:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_OPEN_1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Conf. luminusi- ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("-dad de apertura");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty)
						{
							p_task_menu_dta->state = ST_SET_UP_SAVE_CONF;

							displayCharPositionWrite(0, 0);
							displayStringWrite("  Guardar confi.?");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  NO        SI  ");
						}
						else
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}
						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_XX_21_HOURD;

						*p_clock_id = TIME_CLOSE;
						clk_array[0] = p_sys_cfg_dta->sys_cfg_save->time_close_hour / 10;
						clk_array[1] = p_sys_cfg_dta->sys_cfg_save->time_close_hour % 10;
						clk_array[2] = p_sys_cfg_dta->sys_cfg_save->time_close_minute / 10;
						clk_array[3] = p_sys_cfg_dta->sys_cfg_save->time_close_minute % 10;
						task_display_refresh();
						sprintf(menu_str,"%d               ", clk_array[0]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						sprintf(menu_str," %d:%d%d", clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 1);
						displayStringWrite(menu_str);
						displayCharPositionWrite(8, 1);
						displayStringWrite("guardar");
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();

							clock_UI_Timeout_reset();
						}
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_TIME_XX_21_HOURD:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_XX_22_HOURU;

						task_display_refresh();
						sprintf(menu_str," %d              ", clk_array[1]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						sprintf(menu_str,"%d :%d%d", clk_array[0], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 1);
						displayStringWrite(menu_str);
						displayCharPositionWrite(8, 1);
						displayStringWrite("guardar");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(*p_clock_id == CLOCK)
						{
							p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("   Configurar   ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("      reloj     ");
						}
						else if(*p_clock_id == TIME_OPEN)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  de apertura   ");
						}
						else if(*p_clock_id == TIME_CLOSE)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_CLOSE_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("   de cierre    ");
						}
						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						if(clk_array[0] >= 2) clk_array[0] = 0;
						else clk_array[0]++;
						sprintf(menu_str,"%d", clk_array[0]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}
						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_TIME_XX_22_HOURU:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_XX_23_MINUTED;

						task_display_refresh();
						sprintf(menu_str,"   %d            ", clk_array[2]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						sprintf(menu_str,"%d%d: %d", clk_array[0], clk_array[1], clk_array[3]);
						displayCharPositionWrite(0, 1);
						displayStringWrite(menu_str);
						displayCharPositionWrite(8, 1);
						displayStringWrite("guardar");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(*p_clock_id == CLOCK)
						{
							p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("   Configurar   ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("      reloj     ");
						}
						else if(*p_clock_id == TIME_OPEN)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  de apertura   ");
						}
						else if(*p_clock_id == TIME_CLOSE)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("   de cierre    ");
						}
						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						if(clk_array[1] >= 9) clk_array[1] = 0;
						else if(clk_array[1] < 3) clk_array[1]++;
						else if(clk_array[0] >= 2) clk_array[1] = 0;
						else clk_array[1]++;
						sprintf(menu_str,"%d", clk_array[1]);
						displayCharPositionWrite(1, 0);
						displayStringWrite(menu_str);

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_TIME_XX_23_MINUTED:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_XX_24_MINUTEU;

						task_display_refresh();
						sprintf(menu_str,"    %d           ", clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						sprintf(menu_str,"%d%d:%d", clk_array[0], clk_array[1], clk_array[2]);
						displayCharPositionWrite(0, 1);
						displayStringWrite(menu_str);
						displayCharPositionWrite(8, 1);
						displayStringWrite("guardar");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(*p_clock_id == CLOCK)
						{
							p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("   Configurar   ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("      reloj     ");
						}
						else if(*p_clock_id == TIME_OPEN)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  de apertura   ");
						}
						else if(*p_clock_id == TIME_CLOSE)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("   de cierre    ");
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						if(clk_array[2] >= 5) clk_array[2] = 0;
						else clk_array[2]++;
						sprintf(menu_str,"%d", clk_array[2]);
						displayCharPositionWrite(3, 0);
						displayStringWrite(menu_str);

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}


						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_TIME_XX_24_MINUTEU:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_XX_25_SAVE;

						task_display_refresh();
						displayCharPositionWrite(0, 0);
						displayStringWrite("        guardar");
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 1);
						displayStringWrite(menu_str);

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(*p_clock_id == CLOCK)
						{
							p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("   Configurar   ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("      reloj     ");
						}
						else if(*p_clock_id == TIME_OPEN)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  de apertura   ");
						}
						else if(*p_clock_id == TIME_CLOSE)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("   de cierre    ");
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						if(clk_array[3] >= 9) clk_array[3] = 0;
						else clk_array[3]++;
						sprintf(menu_str,"%d", clk_array[3]);
						displayCharPositionWrite(4, 0);
						displayStringWrite(menu_str);

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_TIME_XX_25_SAVE:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_TIME_XX_21_HOURD;

						task_display_refresh();
						sprintf(menu_str,"%d               ", clk_array[0]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						sprintf(menu_str," %d:%d%d", clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 1);
						displayStringWrite(menu_str);
						displayCharPositionWrite(8, 1);
						displayStringWrite("guardar");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(*p_clock_id == CLOCK)
						{
							p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("   Configurar   ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("      reloj     ");
						}
						else if(*p_clock_id == TIME_OPEN)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  de apertura   ");
						}
						else if(*p_clock_id == TIME_CLOSE)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("   de cierre    ");
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(*p_clock_id == CLOCK)
						{
							p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

							//op_set_clock
							displayCharPositionWrite(0, 0);
							displayStringWrite("   Configurar   ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("      reloj     ");
						}
						else if(*p_clock_id == TIME_OPEN)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							//op_set_time_open
							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  de apertura   ");
						}
						else if(*p_clock_id == TIME_CLOSE)
						{
							p_task_menu_dta->state = ST_SET_UP_TIME_OPEN_1;

							//op_set_time_close
							displayCharPositionWrite(0, 0);
							displayStringWrite("Configurar hora ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("   de cierre    ");
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_LIGHT_OPEN_1:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_CLOSE_1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Conf. luminusi- ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("-dad de cierre  ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty)
						{
							p_task_menu_dta->state = ST_SET_UP_SAVE_CONF;

							displayCharPositionWrite(0, 0);
							displayStringWrite("  Guardar conf.? ");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  NO        SI  ");
						}
						else
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();

							clock_UI_Timeout_reset();
						}
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_OPEN_2_SEL;

						displayCharPositionWrite(0, 0);
						displayStringWrite("     Elegir     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("BAJA -MED.- ALTA");

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_LIGHT_OPEN_2_SEL:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_OPEN_3_SAVE;

						p_sys_cfg_dta->sys_cfg_save->light_open = MED;
						displayCharPositionWrite(0, 0);
						displayStringWrite("     Seguro?     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite(" NO          SI ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_OPEN_3_SAVE;

						p_sys_cfg_dta->sys_cfg_save->light_open = LOW;
						displayCharPositionWrite(0, 0);
						displayStringWrite("     Seguro?     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite(" NO          SI ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_OPEN_3_SAVE;

						p_sys_cfg_dta->sys_cfg_save->light_open = HIGH;
						displayCharPositionWrite(0, 0);
						displayStringWrite("     Seguro?     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite(" NO          SI ");

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							//sprintf(menu_str,"%s", get_clock_string())
							//get_clock(clk_array)
							task_display_refresh();
							sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
							displayCharPositionWrite(0, 0);
							displayStringWrite(menu_str);
							displayCharPositionWrite(0, 1);
							displayStringWrite("    -Conf.- Sel.");
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_LIGHT_OPEN_3_SAVE:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_OPEN_2_SEL;

						displayCharPositionWrite(0, 0);
						displayStringWrite("     Elegir     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("BAJA -MED.- ALTA");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_OPEN_1;

						//op_set_open_light
						displayCharPositionWrite(0, 0);
						displayStringWrite("Conf. luminusi- ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("-dad de apertura");

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_LIGHT_CLOSE_1:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("   Configurar   ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("      reloj     ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty)
						{
							p_task_menu_dta->state = ST_SET_UP_SAVE_CONF;

							displayCharPositionWrite(0, 0);
							displayStringWrite("  Guardar confi.?");
							displayCharPositionWrite(0, 1);
							displayStringWrite("  NO        SI  ");
						}
						else
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_CLOSE_2_SEL;

						displayCharPositionWrite(0, 0);
						displayStringWrite("     Elegir     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("BAJA -MED.- ALTA");

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							//sprintf(menu_str,"%s", get_clock_string())
							//get_clock(clk_array)
							task_display_refresh();
							sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
							displayCharPositionWrite(0, 0);
							displayStringWrite(menu_str);
							displayCharPositionWrite(0, 1);
							displayStringWrite("    -Conf.- Sel.");
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_LIGHT_CLOSE_2_SEL:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_CLOSE_3_SAVE;

						p_sys_cfg_dta->sys_cfg_save->light_close = MED;
						displayCharPositionWrite(0, 0);
						displayStringWrite("     Seguro?     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite(" NO          SI ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_CLOSE_3_SAVE;

						p_sys_cfg_dta->sys_cfg_save->light_close = LOW;
						displayCharPositionWrite(0, 0);
						displayStringWrite("     Seguro?     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite(" NO          SI ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_CLOSE_3_SAVE;

						p_sys_cfg_dta->sys_cfg_save->light_close = HIGH;
						displayCharPositionWrite(0, 0);
						displayStringWrite("     Seguro?     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite(" NO          SI ");

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;


				case ST_SET_UP_LIGHT_CLOSE_3_SAVE:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_CLOSE_2_SEL;

						displayCharPositionWrite(0, 0);
						displayStringWrite("     Elegir     ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("BAJA -MED.- ALTA");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_LIGHT_CLOSE_1;

						//op_set_open_light
						displayCharPositionWrite(0, 0);
						displayStringWrite("Conf. luminusi- ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("-dad de cierre  ");

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(!mem_empty)
						{
							p_task_menu_dta->state = ST_NORMAL_MENU_1;

							task_display_menu_1();
						}

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_SAVE_CONF:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("   Configurar   ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("      reloj     ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//op_save_cfg
						task_display_menu_1();

						clock_UI_Timeout_reset();
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_SET_UP_CHECK_1_OPENCLOSE:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CHECK_2_CLOSEALL;

						//op_close_blind
						displayCharPositionWrite(0, 0);
						displayStringWrite("Presione 'Next' ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("para terminar   ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

						p_sys_cfg_dta->open = false;
						task_display_menu_1();

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

						p_sys_cfg_dta->open = true;
						task_display_menu_1();

						clock_UI_Timeout_reset();
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						task_display_menu_help(p_task_menu_dta->state);

						displayCharPositionWrite(0, 0);
						displayStringWrite("   Esta abierta? ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("NO -A medias- SI");

						clock_UI_Timeout_reset();
					}
					break;

				case ST_SET_UP_CHECK_2_CLOSEALL:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CHECK_3_OK;

						//op_stop_motor
						displayCharPositionWrite(0, 0);
						displayStringWrite("    Cerro bien?  ");
						displayCharPositionWrite(0, 1);
						displayStringWrite(" No          Si ");
					}
					break;

				case ST_SET_UP_CHECK_3_OK:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

						//reset_clock

						displayCharPositionWrite(0, 0);
						displayStringWrite("   Configurar   ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("      reloj     ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CHECK_3_OK;

						//op_open_blinds
						displayCharPositionWrite(0, 0);
						displayStringWrite("   Esta abierta? ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("NO -A medias- SI");

						clock_UI_Timeout_reset();
					}
					break;

				case ST_NORMAL_MENU_1:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_CFG_MODE_1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Configuraciones ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("    generales   ");

						clock_UI_Timeout_reset();
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_21_OPENCLOSE;

						task_display_refresh();
						displayCharPositionWrite(0, 0);
						displayStringWrite("  ABRIR/CERRAR  ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("                ");

						clock_UI_Timeout_reset();
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(mem_empty);
						else if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						HAL_NVIC_DisableIRQ(D10_EXTI_IRQn);
						HAL_NVIC_DisableIRQ(D11_EXTI_IRQn);
						app_sleep = true;
						clock_UI_Timeout_reset();
						HAL_PWR_EnableSleepOnExit();
						HAL_PWR_EnterSLEEPMode(PWR_MAINREGULATOR_ON, PWR_SLEEPENTRY_WFI);
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_NORMAL_CFG_MODE_1:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_SET_UP_CLOCK_1;

						displayCharPositionWrite(0, 0);
						displayStringWrite("   Configurar   ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("      reloj     ");
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_NORMAL_MENU_21_OPENCLOSE:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_22_SEL_MANUAL;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Selec. modo de  ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("apertura manual ");
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;

						if(p_sys_cfg_dta->open)
						{
							p_sys_cfg_dta->open = false;
							//op_close_blinds
						}
						else
						{
							p_sys_cfg_dta->open = true;
							//op_open_blinds
						}
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_NORMAL_MENU_22_SEL_MANUAL:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_23_SEL_TIME;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Selec. modo de  ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("apertu. por hora");
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						p_sys_cfg_dta->sys_cfg_save->mode = MANUAL;
						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_NORMAL_MENU_23_SEL_TIME:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_24_SEL_LIGHT;

						displayCharPositionWrite(0, 0);
						displayStringWrite("Selec. modo de  ");
						displayCharPositionWrite(0, 1);
						displayStringWrite("apertura por luz");
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						p_sys_cfg_dta->sys_cfg_save->mode = TIME;
						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

				case ST_NORMAL_MENU_24_SEL_LIGHT:
					if(!p_task_menu_dta->flag) break;

					if(EV_BTN_NEXT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_21_OPENCLOSE;

						task_display_refresh();
						displayCharPositionWrite(0, 0);
						displayStringWrite("  ABRIR/CERRAR  ");
					}
					else if(EV_BTN_ESC_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;


						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_BTN_ENT_DOWN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;

						p_sys_cfg_dta->sys_cfg_save->mode = LIGHT;

						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_LDR_LOW == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds

					}
					else if(EV_LDR_ACTIVATED == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(LIGHT != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_OPEN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(!p_sys_cfg_dta->open);//op_open_blinds
					}
					else if(EV_TIME_CLOSE == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						if(TIME != p_sys_cfg_dta->sys_cfg_save->mode);
						else if(p_sys_cfg_dta->open);//op_close_blinds
					}
					else if(EV_UI_TIMEOUT == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						p_task_menu_dta->state = ST_NORMAL_MENU_1;


						//sprintf(menu_str,"%s", get_clock_string())
						//get_clock(clk_array)
						task_display_refresh();
						sprintf(menu_str,"     %d%d:%d%d", clk_array[0], clk_array[1], clk_array[2], clk_array[3]);
						displayCharPositionWrite(0, 0);
						displayStringWrite(menu_str);
						displayCharPositionWrite(0, 1);
						displayStringWrite("    -Conf.- Sel.");
					}
					else if(EV_TIM_1_MIN == p_task_menu_dta->event)
					{
						p_task_menu_dta->flag = false;
						//op_time_1_min
					}
					break;

			}
		}
	}
}


void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	if(BTN_ENT_PIN == GPIO_Pin)
	{
		HAL_NVIC_DisableIRQ(D10_EXTI_IRQn);
		HAL_NVIC_DisableIRQ(D11_EXTI_IRQn);
		app_sleep = false;
		clock_UI_Timeout_reset();
		HAL_PWR_DisableSleepOnExit();
		HAL_Delay(500);
	}
	else if(BTN_NEX_PIN == GPIO_Pin)
	{
		HAL_NVIC_DisableIRQ(D10_EXTI_IRQn);
		HAL_NVIC_DisableIRQ(D11_EXTI_IRQn);
		app_sleep = false;
		clock_UI_Timeout_reset();
		HAL_PWR_DisableSleepOnExit();
		HAL_Delay(500);
	}
	else if(BTN_A_PIN == GPIO_Pin)
	{
		for (int i=0; i<PAGE_NUM; i++)
		{
			EEPROM_PageErase(i);
		}
		HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);
		while(1)
		{
			//Reset
		}
	}

}

/********************** internal functions definition ************************/
void task_display_menu_1(void) {
	char menu_str[20];
	sprintf(menu_str,"     %02d:%02d", g_clock[0], g_clock[1]);
	task_display_refresh();
	displayCharPositionWrite(0, 0);
	displayStringWrite(menu_str);
	displayCharPositionWrite(0, 1);
	displayStringWrite("    -Conf.- Sel.");
}

void task_display_refresh(void)
{
	char menu_str[16] = "                ";
	displayCharPositionWrite(0, 0);
	displayStringWrite(menu_str);
	displayCharPositionWrite(0, 1);
	displayStringWrite(menu_str);
}

void task_display_menu_help(task_menu_st_t state)
{
	if(state == ST_SET_UP_OPENING_1_SPIN)
	{
		displayCharPositionWrite(0, 0);
		displayStringWrite("Indique lo que  ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("sucedio con la  ");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("    Persiana    ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("                ");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("ENTER = abrio   ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("ESCAPE = cerro  ");
		HAL_Delay(5000);
	}
	else if(state == ST_SET_UP_OPENING_3_TIME_CLOSE)
	{
		displayCharPositionWrite(0, 0);
		displayStringWrite("Presione NEXT   ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("y la cortina    ");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("y la cortina    ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("bajara hasta que");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("bajara hasta que");
		displayCharPositionWrite(0, 1);
		displayStringWrite("lo presione nue-");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("lo presione nue-");
		displayCharPositionWrite(0, 1);
		displayStringWrite("-vamente        ");
		HAL_Delay(3000);
	}
	else if(state == ST_SET_UP_CHECK_1_OPENCLOSE)
	{
		displayCharPositionWrite(0, 0);
		displayStringWrite("Indique el      ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("estado de la    ");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("persiana:abierta");
		displayCharPositionWrite(0, 1);
		displayStringWrite(" o cerrada      ");
		HAL_Delay(5000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("Si la persiana  ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("esta medio abi- ");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("esta medio abi- ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("-erta al apretar");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("-erta al apretar");
		displayCharPositionWrite(0, 1);
		displayStringWrite("NEXT la persiana");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("NEXT la persiana");
		displayCharPositionWrite(0, 1);
		displayStringWrite("se cerrara hasta");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("se cerrara hasta");
		displayCharPositionWrite(0, 1);
		displayStringWrite("que vuelva a    ");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("que vuelva a    ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("apretar NEXT    ");
		HAL_Delay(3000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("Enter = ABIERTA ");
		displayCharPositionWrite(0, 1);
		displayStringWrite("Escape = CERRADA");
		HAL_Delay(5000);

		displayCharPositionWrite(0, 0);
		displayStringWrite("Escape = CERRADA");
		displayCharPositionWrite(0, 1);
		displayStringWrite("Next = A MEDIAS ");
		HAL_Delay(5000);
	}
}



bool check_memory_empty(void)
{
	uint32_t flag_empty;
	uint32_t time;
	EEPROM_Read(EEP_PAG_CFG_OP, EEP_OFF_CFG_OP_TIME, (uint8_t *)&time, EEP_SIZE_TIME);
	EEPROM_Read(EEP_PAG_CFG_OP, EEP_OFF_CFG_OP_FLAG, (uint8_t *)&flag_empty, EEP_SIZE_FLAG);
	return (0 == memcmp(&flag_empty, &time, EEP_SIZE_FLAG));
}

void memory_get_cfg(sys_cfg_save_t *config)
{
	uint16_t page;
	uint16_t offset;
	uint16_t save_add;
	int shift_page = log(PAGE_SIZE)/log(2);

	EEPROM_Read(EEP_PAG_CFG_OP, EEP_OFF_CFG_SAVE_ADD, (uint8_t *)&save_add, EEP_SIZE_SAVE_ADD);
	page = (save_add & MASK_ADDRESS_PAGE) >> shift_page;
	offset = save_add & MASK_ADDRESS_OFFSET;
	EEPROM_Read(page, offset, (uint8_t *)config, size_sys_cfg_save);
}

void memory_get_op_spin(uint8_t *spin)
{
	EEPROM_Read(EEP_PAG_CFG_OP, EEP_OFF_CFG_OP_SPIN, spin, EEP_SIZE_SPIN);
}

void memory_get_op_speed(uint8_t *speed)
{
	EEPROM_Read(EEP_PAG_CFG_OP, EEP_OFF_CFG_OP_SPEED, speed, EEP_SIZE_SPEED);
}

void memory_get_op_time(uint32_t *time)
{
	EEPROM_Read(EEP_PAG_CFG_OP, EEP_OFF_CFG_OP_TIME, (uint8_t *)time, EEP_SIZE_TIME);
}

void memory_save_op_spin(uint8_t spin)
{
	EEPROM_Write(EEP_PAG_CFG_OP, EEP_OFF_CFG_OP_SPIN, &spin, EEP_SIZE_SPIN);
}

void memory_save_op_speed(uint8_t speed)
{
	EEPROM_Write(EEP_PAG_CFG_OP, EEP_OFF_CFG_OP_SPEED, &speed, EEP_SIZE_SPEED);
}

void memory_save_op_time(uint32_t time)
{
	EEPROM_Write(EEP_PAG_CFG_OP, EEP_OFF_CFG_OP_TIME, (uint8_t *)&time, EEP_SIZE_TIME);
}

void memory_save_cfg(sys_cfg_save_t *config)
{
	uint16_t page;
	uint16_t offset;
	uint16_t save_add;
	int shift_page = log(PAGE_SIZE)/log(2);

	EEPROM_Read(EEP_PAG_CFG_OP, EEP_OFF_CFG_SAVE_ADD, (uint8_t *)&save_add, EEP_SIZE_SAVE_ADD);
	page = (save_add & MASK_ADDRESS_PAGE) >> shift_page;
	offset = save_add & MASK_ADDRESS_OFFSET;

	if((offset + size_sys_cfg_save) >= PAGE_SIZE) page++;
	offset = (offset + size_sys_cfg_save) % PAGE_SIZE;

	if((offset + size_sys_cfg_save) <= PAGE_SIZE)
	{
		EEPROM_Write(page, offset, (uint8_t *)config, size_sys_cfg_save);
	}
	else if(page < (PAGE_SIZE-1))
	{
		EEPROM_Write(page, offset, (uint8_t *)config, size_sys_cfg_save);
	}
	else
	{
		page = EEP_PAG_SAVE_START;
		offset = 0;
		EEPROM_Write(page, offset, (uint8_t *)config, size_sys_cfg_save);
	}

	save_add = (page << shift_page) | offset;
	EEPROM_Write(EEP_PAG_CFG_OP, EEP_OFF_CFG_SAVE_ADD, (uint8_t *)&save_add, EEP_SIZE_SAVE_ADD);
}



/*void motor_open_test(void)
{
	motorMoveRight(1, 1000);
}

void motor_close_test(void)
{
	motorMoveLeft(1, 1000);
}

void motorOpen(sys_cfg_dta_t *cfg)
{
	if(cfg->Spin == RIGHT) motorMoveRight(cfg->Speed, cfg->TimeOpening);
	else motorMoveLeft(cfg->Speed, cfg->TimeOpening);
}

void motorClose(sys_cfg_dta_t *cfg)
{
	if(cfg->Spin == RIGHT) motorMoveLeft(cfg->Speed, cfg->TimeOpening);
	else motorMoveRight(cfg->Speed, cfg->TimeOpening);
}*/


/********************** end of file ******************************************/
