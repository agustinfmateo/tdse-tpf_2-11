#ifndef TASK_INC_TASK_LDR_ATTRIBUTE_H_
#define TASK_INC_TASK_LDR_ATTRIBUTE_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/


/* Events to excite Task Sensor */
typedef enum task_sensor_ev {EV_LDR_XX_THRESH_UPPER,
							EV_LDR_XX_THRESH_MID,
							EV_LDR_XX_THRESH_LOWER} task_ldr_ev_t;

/* States of Task Sensor */
typedef enum task_sensor_st {ST_LDR_XX_ON,
							 ST_LDR_XX_FALLING,
							 ST_LDR_XX_HIDDEN,
						     ST_LDR_XX_RISING} task_ldr_st_t;

/* Identifier of Task Sensor */
/* typedef enum task_sensor_id {ID_BTN_ENT,
							 ID_BTN_NEX,
							 ID_BTN_ESC} task_sensor_id_t; */
typedef struct {
	ADC_HandleTypeDef*  hadc;
	task_ldr_ev_t	signal_up;
	task_ldr_ev_t	signal_low;
	uint32_t		counter_max;
} task_ldr_cfg_t;

typedef struct {
	uint32_t		counter;
	uint32_t		open_sensitivity;
	uint32_t		close_sensitivity;
	uint32_t		accumulated;
	task_ldr_st_t	state;
	task_ldr_ev_t	event;
} task_ldr_dta_t;

/********************** external data declaration ****************************/

/********************** external functions declaration ***********************/

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* TASK_INC_TASK_SENSOR_ATTRIBUTE_H_ */

/********************** end of file ******************************************/
