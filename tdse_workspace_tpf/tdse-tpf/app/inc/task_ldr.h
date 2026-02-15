#ifndef TASK_INC_TASK_LDR_H_
#define TASK_INC_TASK_LDR_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/
extern ADC_HandleTypeDef hadc1;
extern uint32_t g_task_ldr_cnt;
extern volatile uint32_t g_task_ldr_tick_cnt;

/********************** external functions declaration ***********************/
void task_ldr_init(void *parameters);
void task_ldr_update(void *parameters);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_LDR_H_ */

/********************** end of file ******************************************/
