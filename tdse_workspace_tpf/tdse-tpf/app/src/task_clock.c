/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"

/* Demo includes. */
#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "task_clock.h"
#include "task_menu_attribute.h"
#include "task_menu_interface.h"
#include "task_ldr.h"
#include "task_ldr_attribute.h"
#include "ldr.h"
#include "task_eeprom.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/
static uint8_t APP_UI_Timeout;
static uint8_t APP_UI_Timeout_cnt;
uint32_t WCET_clock;

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

sys_cfg_save_t *p_sys_cfg_sv = &sys_cfg;

/********************** external data declaration ****************************/
volatile uint8_t g_clock[2];
bool app_sleep;
bool app_cfg_cplt;

/********************** external functions definition ************************/
void clock_init(void)
{
	HAL_NVIC_SetPriority(TIM1_UP_IRQn, 0, 0);
	HAL_NVIC_EnableIRQ(TIM1_UP_IRQn);

	__asm("CPSID i");	/* disable interrupts*/
	g_clock[0] = 0;
	g_clock[1] = 0;
	APP_UI_Timeout_cnt = 0;
    __asm("CPSIE i");	/* enable interrupts*/

    app_sleep = false;
    app_cfg_cplt = false;

	if(HAL_TIM_Base_Start_IT(APP_CLK_TIM) != HAL_OK)
	{
		Error_Handler();
	}
}

void clock_UI_Timeout_set(uint8_t ui_timeout_minutes)
{
	APP_UI_Timeout = ui_timeout_minutes*60;
}

void clock_UI_Timeout_reset(void)
{
	APP_UI_Timeout_cnt = 0;
}

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	cycle_counter_reset();

	static uint32_t cnt_sec = 0;
	static uint32_t cycle_counter_time_us;

	cnt_sec++;

	if(!app_sleep)
	{
		APP_UI_Timeout_cnt++;
		if((APP_UI_Timeout_cnt == APP_UI_Timeout))
		{
			put_event_task_menu(EV_UI_TIMEOUT);
		}
	}

	if((cnt_sec%60) == 0)
	{
		/* Clock Update */
		if(g_clock[1] < 59) g_clock[1]++;
		else if(g_clock[0] < 23)
		{
			g_clock[1] = 0;
			g_clock[0]++;
		}
		else
		{
			g_clock[1] = 0;
			g_clock[0] = 0;
		}
		put_event_task_menu(EV_TIM_1_MIN);

		/* Open/Close check */
		if(app_cfg_cplt && p_sys_cfg_sv->mode == TIME)
		{

			if((g_clock[1] == p_sys_cfg_sv->time_open_minute) && (g_clock[0] == p_sys_cfg_sv->time_open_hour))
			{
				put_event_task_menu(EV_TIME_OPEN);
			}
			if((g_clock[1] == p_sys_cfg_sv->time_close_minute) && (g_clock[0] == p_sys_cfg_sv->time_close_hour))
			{
				put_event_task_menu(EV_TIME_CLOSE);
			}
		}

		if(app_sleep)
		{
			HAL_ResumeTick();
			HAL_PWR_DisableSleepOnExit();
		}
	}

	cycle_counter_time_us = cycle_counter_time_us();
	if (WCET_clock < cycle_counter_time_us)
	{
		WCET_clock = cycle_counter_time_us;
	}
}
/********************** internal functions definition ************************/

/********************** end of file ******************************************/
