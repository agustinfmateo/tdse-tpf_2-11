/*
 * @file   :system_cfg_attribute.h
 */


#ifndef SYSTEM_CFG_ATTRIBUTE_H_
#define SYSTEM_CFG_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

#include <stdint.h>
#include <stdbool.h>

/********************** macros ***********************************************/

/********************** typedef **********************************************/

typedef enum task_spin_id {LEFT,
							 RIGHT} task_spin_id_t;

typedef enum task_mode_id {MANUAL,
							TIME,
							LIGHT} task_mode_id_t;

typedef enum task_light_id {LOW,
							MED,
							HIGH} task_light_id_t;

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


/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* SYSTEM_CFG_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
