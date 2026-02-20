#ifndef TASK_INC_TASK_CLOCK_H_
#define TASK_INC_TASK_CLOCK_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/
#include "stdint.h"
#include "stm32f1xx_hal.h"
#include "stdbool.h"

/********************** macros ***********************************************/
/* TIM-CLOCK Handle */
#define APP_CLK_TIM &htim1

/********************** typedef **********************************************/

typedef enum clock_id {CLOCK,
					   TIME_OPEN,
					   TIME_CLOSE} clock_id_t;

/********************** external data declaration ****************************/
extern TIM_HandleTypeDef htim1;
extern volatile uint8_t g_clock[2];
extern bool app_sleep;
extern bool app_cfg_cplt;

/********************** external functions declaration ***********************/
void clock_init(void);
void clock_UI_Timeout_set(uint8_t ui_timeout_minutes);
void clock_UI_Timeout_reset(void);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_CLOCK_H_ */

/********************** end of file ******************************************/
