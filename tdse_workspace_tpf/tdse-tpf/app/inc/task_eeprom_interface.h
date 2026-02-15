/*
 * @file   : task_eeprom_interface.h
 */

#ifndef TASK_INC_TASK_EEPROM_INTERFACE_H_
#define TASK_INC_TASK_EEPROM_INTERFACE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

#include "task_eeprom_attribute.h"

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

extern void put_event_task_eeprom(task_eeprom_ev_t event, task_eeprom_id_t identifier);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_EEPROM_INTERFACE_H_ */

/********************** end of file ******************************************/
