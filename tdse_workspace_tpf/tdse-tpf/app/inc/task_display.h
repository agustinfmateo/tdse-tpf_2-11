/*
 * @file   : task_display.h
 */

#ifndef TASK_INC_TASK_DISPLAY_H_
#define TASK_INC_TASK_DISPLAY_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "task_display_attribute.h"

/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/
extern uint32_t g_task_display_cnt;
extern volatile uint32_t g_task_display_tick_cnt;

/********************** external functions declaration ***********************/
extern void task_display_init(void *parameters);
extern void task_display_update(void *parameters);

extern void displayCharPositionWrite(uint8_t charPositionX, uint8_t charPositionY);
extern void displayStringWrite(const char *str);
extern void displayClear(void);
extern bool displayIsQueueEmpty(void);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_DISPLAY_H_ */

/********************** end of file ******************************************/
