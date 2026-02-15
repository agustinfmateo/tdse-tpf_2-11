/* Project includes. */
#include "main.h"
#include <stdbool.h>

/* App includes. */
#include "app.h"
#include "logger.h"
#include "ldr.h"
#include "task_ldr.h"
#include "task_ldr_attribute.h"
#include "task_menu_attribute.h"
#include "task_menu_interface.h"

/* Application includes. */

/********************** macros and definitions *******************************/
#define G_TASK_SEN_CNT_INIT			0ul
#define G_TASK_SEN_TICK_CNT_INI		0ul

#define COUNTER_INIT				0ul
#define COUNTER_MIN					0ul
#define COUNTER_MAX					1ul

/********************** external data declaration *****************************/
uint32_t g_task_ldr_cnt;
volatile uint32_t g_task_ldr_tick_cnt;

/********************** external functions definition ************************/

/********************** internal data declaration ****************************/
const char *p_task_ldr 		    = "Task LDR (Sensor LDR)";
const char *p_task_ldr_ 		= "Non-Blocking & Update By Time Code";

const task_ldr_cfg_t task_ldr_cfg_list[] = {
	{&hadc1,  EV_LDR_ACTIVATED,  EV_LDR_LOW, COUNTER_MAX},
};

#define LDR_CFG_QTY	(sizeof(task_ldr_cfg_list)/sizeof(task_ldr_cfg_t))

task_ldr_dta_t task_ldr_dta_list[] = {
	{COUNTER_INIT, OPEN_SENSITIVITY_M, CLOSE_SENSITIVITY_M, 0, ST_LDR_XX_RISING, EV_LDR_XX_THRESH_MID},
};

#define LDR_DTA_QTY	(sizeof(task_ldr_dta_list)/sizeof(task_ldr_dta_t))

static volatile bool b_measuring = false;
static task_light_id_t aux_open_sstv = MED;
static task_light_id_t aux_close_sstv = MED;

/********************** internal data definition *****************************/

/********************** internal functions definitions ***********************/

/********************** internal functions declaration ***********************/
void task_ldr_init(void *parameters){
	uint32_t index;
	task_ldr_dta_t *p_task_ldr_dta;
	task_ldr_st_t state;
	task_ldr_ev_t event;

	/* Print out: Task Initialized */
	LOGGER_LOG("  %s is running - %s\r\n", GET_NAME(task_ldr_init), p_task_ldr);
	LOGGER_LOG("  %s is a %s\r\n", GET_NAME(task_ldr), p_task_ldr_);

	g_task_ldr_cnt = G_TASK_SEN_CNT_INIT;

	/* Print out: Task execution counter */
	LOGGER_LOG("   %s = %lu\r\n", GET_NAME(g_task_ldr_cnt), g_task_ldr_cnt);

	for (index = 0; LDR_DTA_QTY > index; index++)
	{
		/* Update Task Sensor Data Pointer */
		p_task_ldr_dta = &task_ldr_dta_list[index];

		/* Print out: Index & Task execution FSM */
		LOGGER_LOG("   %s = %lu", GET_NAME(index), index);

		state = p_task_ldr_dta->state;
		LOGGER_LOG("   %s = %lu", GET_NAME(state), (uint32_t)state);

		event = p_task_ldr_dta->event;
		LOGGER_LOG("   %s = %lu\r\n", GET_NAME(event), (uint32_t)event);
	}
	g_task_ldr_tick_cnt = G_TASK_SEN_TICK_CNT_INI;
}

void task_ldr_update(void *parameters)
{
	uint32_t index;
	const task_ldr_cfg_t *p_task_ldr_cfg;
	task_ldr_dta_t *p_task_ldr_dta;
	bool b_time_update_required = false;

	/* Update Task Sensor Counter */
	g_task_ldr_cnt++;

	/* Protect shared resource (g_task_sensor_tick_cnt) */
	__asm("CPSID i");	/* disable interrupts*/
    if (G_TASK_SEN_TICK_CNT_INI < g_task_ldr_tick_cnt)
    {
    	g_task_ldr_tick_cnt--;
    	b_time_update_required = true;
    }
    __asm("CPSIE i");	/* enable interrupts*/

    b_time_update_required = true;

    while (b_time_update_required)
    {
		/* Protect shared resource (g_task_sensor_tick_cnt) */
		__asm("CPSID i");	/* disable interrupts*/
		if (G_TASK_SEN_TICK_CNT_INI < g_task_ldr_tick_cnt)
		{
			g_task_ldr_tick_cnt--;
			b_time_update_required = true;
		}
		else
		{
			b_time_update_required = false;
		}
		__asm("CPSIE i");	/* enable interrupts*/

    	for (index = 0; LDR_DTA_QTY > index; index++)
		{
    		/* Update Task Sensor Configuration & Data Pointer */
			p_task_ldr_cfg = &task_ldr_cfg_list[index];
			p_task_ldr_dta = &task_ldr_dta_list[index];

			if(aux_close_sstv != p_sys_cfg_sv->light_close)
			{
				aux_close_sstv = p_sys_cfg_sv->light_close;

				switch(p_sys_cfg_sv->light_close)
				{
					case LOW:
						p_task_ldr_dta->close_sensitivity = CLOSE_SENSITIVITY_L;
						break;

					case MED:
						p_task_ldr_dta->close_sensitivity = CLOSE_SENSITIVITY_M;
						break;

					case HIGH:
						p_task_ldr_dta->close_sensitivity = CLOSE_SENSITIVITY_H;
						break;
				}
			}

			if(aux_open_sstv != p_sys_cfg_sv->light_open)
			{
				aux_open_sstv = p_sys_cfg_sv->light_open;

				switch(p_sys_cfg_sv->light_open)
				{
					case LOW:
						p_task_ldr_dta->open_sensitivity = OPEN_SENSITIVITY_L;
						break;

					case MED:
						p_task_ldr_dta->open_sensitivity = OPEN_SENSITIVITY_M;
						break;

					case HIGH:
						p_task_ldr_dta->open_sensitivity = OPEN_SENSITIVITY_H;
						break;
				}
			}

			LDR_Update(p_task_ldr_cfg->hadc);

			if(LDR_Is_Data_Ready()){
				b_measuring = false;
				uint16_t ldr_val = LDR_Get_Average_Value();

				//LOGGER_LOG("LDR Promediado: %u\n", ldr_val);

				if(ldr_val > p_task_ldr_dta->open_sensitivity){
					p_task_ldr_dta->event =	EV_LDR_XX_THRESH_UPPER;
				}
				else if(ldr_val < p_task_ldr_dta->close_sensitivity){
					p_task_ldr_dta->event =	EV_LDR_XX_THRESH_LOWER;
				}
				else p_task_ldr_dta->event = EV_LDR_XX_THRESH_MID;

				switch (p_task_ldr_dta->state) {

					case ST_LDR_XX_ON:

						if (EV_LDR_XX_THRESH_LOWER == p_task_ldr_dta->event){
							p_task_ldr_dta->counter = p_task_ldr_cfg->counter_max;
							p_task_ldr_dta->state = ST_LDR_XX_FALLING;
						}

						break;

					case ST_LDR_XX_FALLING:

						p_task_ldr_dta->counter--;
						p_task_ldr_dta->accumulated+=ldr_val;
						if (COUNTER_MIN == p_task_ldr_dta->counter) {
							if (EV_LDR_XX_THRESH_LOWER == p_task_ldr_dta->event &&
								p_task_ldr_dta->accumulated/p_task_ldr_cfg->counter_max <= p_task_ldr_dta->close_sensitivity) {
								put_event_task_menu(p_task_ldr_cfg->signal_low);
								p_task_ldr_dta->state = ST_LDR_XX_HIDDEN;
							}
							else {
							p_task_ldr_dta->state = ST_LDR_XX_RISING;
							}
							p_task_ldr_dta->accumulated=0;
						}

						break;

					case ST_LDR_XX_HIDDEN:

						if (EV_LDR_XX_THRESH_UPPER == p_task_ldr_dta->event) {
							p_task_ldr_dta->state = ST_LDR_XX_RISING;
							p_task_ldr_dta->counter = p_task_ldr_cfg->counter_max;
						}

						break;

					case ST_LDR_XX_RISING:

						p_task_ldr_dta->counter--;
						p_task_ldr_dta->accumulated+=ldr_val;
						if (COUNTER_MIN == p_task_ldr_dta->counter) {
							if (EV_LDR_XX_THRESH_UPPER == p_task_ldr_dta->event && p_task_ldr_dta->accumulated/p_task_ldr_cfg->counter_max >= p_task_ldr_dta->open_sensitivity) {
								put_event_task_menu(p_task_ldr_cfg->signal_up);
								p_task_ldr_dta->state = ST_LDR_XX_ON;
								p_task_ldr_dta->counter = p_task_ldr_cfg->counter_max;
							}
							else {
							p_task_ldr_dta->state = ST_LDR_XX_FALLING;
							}
							p_task_ldr_dta->accumulated = 0;
						}

						break;

					default:
						p_task_ldr_dta->counter  = COUNTER_MIN;
						p_task_ldr_dta->state = ST_LDR_XX_FALLING;
						p_task_ldr_dta->event = EV_LDR_XX_THRESH_UPPER;

					break;
				}

			}

			//Si no se está midiendo empezar
			if (!b_measuring) {
				b_measuring = true;
				LDR_Request();

			}
		}
    }
}

/********************** end of file ******************************************/
