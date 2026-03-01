/*
 * @file   : task_display_attribute.h
 */

#ifndef TASK_INC_TASK_DISPLAY_ATTRIBUTE_H_
#define TASK_INC_TASK_DISPLAY_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include <stdint.h>
#include <stdbool.h>

/********************** macros ***********************************************/
#define DISPLAY_TX_BUF_SIZE 128

/********************** typedef **********************************************/

/* States of Task Display */
typedef enum task_display_st {
    ST_DISP_IDLE,
    ST_DISP_BUSY
} task_display_st_t;

/* Identifier of Task Display */
typedef enum task_display_id {
    ID_DISPLAY
} task_display_id_t;

/* Runtime Data */
typedef struct {
    task_display_st_t state;
    bool              initial8BitCommunicationIsCompleted;
    uint8_t           tx_buffer[DISPLAY_TX_BUF_SIZE];
    bool              tx_type[DISPLAY_TX_BUF_SIZE];
    uint16_t          head;
    uint16_t          tail;
} task_display_dta_t;

/********************** external data declaration ****************************/
extern task_display_dta_t task_display_dta_list[];

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_DISPLAY_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
