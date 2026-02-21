#ifndef LDR_INC_LDR_H_
#define LDR_INC_LDR_H_

/********************** CPP guard ********************************************/
#ifdef __cplusplus
extern "C" {
#endif

/********************** inclusions *******************************************/

/********************** macros ***********************************************/

/********************** typedef **********************************************/

/********************** external data declaration ****************************/
extern ADC_HandleTypeDef hadc1;

/********************** external functions declaration ***********************/
void LDR_Request(ADC_HandleTypeDef *hadc);
void LDR_Update(ADC_HandleTypeDef *hadc);
bool LDR_Is_Data_Ready(void);
uint16_t LDR_Get_Average_Value(void);

/********************** End of CPP guard *************************************/
#ifdef __cplusplus
}
#endif

#endif /* LDR_INC_LDR_H_ */

/********************** end of file ******************************************/
