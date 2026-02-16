/*
 * @file   : task_eeprom.h
 */

#ifndef TASK_INC_TASK_EEPROM_H_
#define TASK_INC_TASK_EEPROM_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "task_menu_attribute.h"
#include "task_eeprom_attribute.h"

/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/
extern uint32_t g_task_eeprom_cnt;
extern volatile uint32_t g_task_eeprom_tick_cnt;

/********************** external functions declaration ***********************/
extern void task_eeprom_init(void *parameters);
extern void task_eeprom_update(void *parameters);
bool eeprom_check_and_load(task_eeprom_id_t identifier, sys_cfg_opening_t *p_data_op, sys_cfg_save_t *p_data_sv);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_ACTUATOR_H_ */

/********************** end of file ******************************************/
