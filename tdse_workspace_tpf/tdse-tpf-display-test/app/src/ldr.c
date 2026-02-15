/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"
#include <stdbool.h>

/* App includes. */
#include "ldr.h"
#include "logger.h"

/* Application includes. */

/********************** macros and definitions *******************************/
#define SAMPLES_SIZE 20

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/
//uint16_t LDR_Read_Average(ADC_HandleTypeDef *hadc);
//HAL_StatusTypeDef ADC_Poll_Read(ADC_HandleTypeDef *hadc, uint16_t *value);

/********************** internal data definition *****************************/
static volatile uint16_t sample_array[SAMPLES_SIZE];
static volatile uint16_t sample_idx = 0;
static volatile bool b_is_running = false;
static volatile bool b_done = false;
static volatile uint16_t ldr_average = 0;

/********************** external data declaration *****************************/

/********************** external functions definition ************************/
void LDR_Request(void) {
	if(b_is_running) return;
	sample_idx = 0;
	b_done = false;
	b_is_running = true;
}

void LDR_Update(ADC_HandleTypeDef *hadc) {

	if (b_is_running && sample_idx == 0) {
		HAL_ADC_Start_IT(hadc);
	}

	if(b_done){
		uint32_t sum = 0;
		for (int i = 0; i < SAMPLES_SIZE; i++) {
			sum += sample_array[i];
		}
		ldr_average = sum / SAMPLES_SIZE;
	}
}

bool LDR_Is_Data_Ready(void) {
    return b_done;
}

uint16_t LDR_Get_Average_Value(void) {
    return ldr_average;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

	sample_array[sample_idx++] = HAL_ADC_GetValue(hadc);

	//LOGGER_LOG("ADC sample %u\n", sample_array[sample_idx-1]);

	if (sample_idx >= SAMPLES_SIZE) {
		HAL_ADC_Stop_IT(hadc);
	    b_done = true;
	    b_is_running = false;
	}
}


/********************** internal functions definitions ***********************/

/********************** end of file ******************************************/
