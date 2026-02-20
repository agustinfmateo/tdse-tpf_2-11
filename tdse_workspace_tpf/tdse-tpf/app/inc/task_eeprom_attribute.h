/*
 * @file   : task_eeprom_attribute.h
 */

#ifndef TASK_INC_TASK_EEPROM_ATTRIBUTE_H_
#define TASK_INC_TASK_EEPROM_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include <stdbool.h>
#include "task_menu_attribute.h"
/********************** macros ***********************************************/

/********************** typedef **********************************************/
/* Events to excite Task EEPROM */
typedef enum task_eeprom_ev {EV_EEPROM_NONE,
							 EV_EEPROM_SAVE_OPENING,
							 EV_EEPROM_SAVE_CYCLIC,
							 EV_EEPROM_ERASE_ALL,
							 EV_EEPROM_LOAD_REQ} task_eeprom_ev_t;

/* States of Task EEPROM */
typedef enum task_eeprom_st {ST_EEPROM_IDLE,
							 ST_EEPROM_WAIT_TX,
							 ST_EEPROM_WAIT_RX,
							 ST_EEPROM_WRITE_CYCLE,
							 ST_EEPROM_ERASE_RUNNING} task_eeprom_st_t;

/* Identifier of Task Actuator */
typedef enum task_eeprom_id {ID_EEPROM} task_eeprom_id_t;

/* Configuration of the EEPROM Hardware */
typedef struct {
    uint8_t       i2c_addr;
    uint16_t	  mem_addr;
    uint16_t      page_size;
    uint32_t      tick_write_delay;
} task_eeprom_cfg_t;

/* Runtime Data */
typedef struct {
    uint32_t           tick;
    task_eeprom_st_t   state;
    task_eeprom_ev_t   event;
    uint16_t           wr_addr;
    uint8_t* 		   wr_ptr;
    uint16_t           wr_bytes_left;
    uint32_t           current_id;
    uint16_t           current_slot_id;
} task_eeprom_dta_t;


/********************** external data declaration ****************************/
extern task_eeprom_dta_t task_eeprom_dta_list[];
extern sys_cfg_save_t sys_cfg;
extern sys_cfg_opening_t sys_op;

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_EEPROM_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
