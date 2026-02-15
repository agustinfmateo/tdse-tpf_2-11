#ifndef TASK_INC_TASK_LDR_H_
#define TASK_INC_TASK_LDR_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/
//Open/Close Sensitivity
#define OPEN_SENSITIVITY_L 1200ul
#define OPEN_SENSITIVITY_M 1300ul
#define OPEN_SENSITIVITY_H 1500ul

#define CLOSE_SENSITIVITY_L 300ul
#define CLOSE_SENSITIVITY_M 500ul
#define CLOSE_SENSITIVITY_H 700ul

/********************** typedef **********************************************/

/********************** external data declaration ****************************/
extern ADC_HandleTypeDef hadc1;
extern uint32_t g_task_ldr_cnt;
extern volatile uint32_t g_task_ldr_tick_cnt;

/********************** external functions declaration ***********************/
void task_ldr_init(void *parameters);
void task_ldr_update(void *parameters);
void task_ldr_set_open_sensitivity(uint32_t open_sensitivity);
void task_ldr_set_close_sensitivity(uint32_t close_sensitivity);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_LDR_H_ */

/********************** end of file ******************************************/
