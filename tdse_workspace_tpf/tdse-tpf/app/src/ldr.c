/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"
#include "stdbool.h"

/* App includes. */
#include "ldr.h"
//#include "logger.h"

/* Application includes. */

/********************** macros and definitions *******************************/
#define SAMPLES_SIZE 20

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/

/********************** internal data definition *****************************/
static volatile uint16_t sample_array[SAMPLES_SIZE];
static volatile uint16_t sample_idx = 0;
static volatile bool b_reading = false;
static volatile bool b_data_ready = false;
static volatile uint16_t ldr_average = 0;

/********************** external data declaration *****************************/

/********************** external functions definition ************************/
void LDR_Request(ADC_HandleTypeDef *hadc) {
	if(b_reading) return;
	sample_idx = 0;
	b_reading = true;
	b_data_ready = false;

	HAL_ADC_Start_IT(hadc);
}

void LDR_Update(ADC_HandleTypeDef *hadc) {

	if (b_reading || b_data_ready|| sample_idx != SAMPLES_SIZE) {
		return;
	}

	uint32_t sum = 0;

	for (int i = 0; i < SAMPLES_SIZE; i++) {
		sum += sample_array[i];
	}

	ldr_average = sum / SAMPLES_SIZE;
	b_data_ready = true;
	sample_idx = 0;
}

bool LDR_Is_Data_Ready(void) {
    return b_data_ready;
}

uint16_t LDR_Get_Average_Value(void) {
	b_data_ready = false;
    return ldr_average;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc) {

	sample_array[sample_idx++] = HAL_ADC_GetValue(hadc);

	if(sample_idx < SAMPLES_SIZE){
		HAL_ADC_Start_IT(hadc);
	}

	else {
		HAL_ADC_Stop_IT(hadc);
		b_reading = false;
	}
}


/********************** internal functions definitions ***********************/

/********************** end of file ******************************************/
