/*
 * @file   : task_eeprom_interface.c
 */

/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"

/* Demo includes. */
//#include "logger.h"
#include "dwt.h"

/* Application & Tasks includes. */
#include "app.h"
#include "task_eeprom_attribute.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/

/********************** external data declaration ****************************/

/********************** external functions definition ************************/
void put_event_task_eeprom(task_eeprom_ev_t event, task_eeprom_id_t identifier)
{
	task_eeprom_dta_t *p_task_eeprom_dta;
	p_task_eeprom_dta = &task_eeprom_dta_list[identifier];
    p_task_eeprom_dta->event = event;
}

/********************** end of file ******************************************/
