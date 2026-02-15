/********************** inclusions *******************************************/
/* Project includes. */
#include "main.h"

/* Demo includes. */
#include <stdlib.h>
#include "motor.h"
//#include "board.h"

/********************** macros and definitions *******************************/

/********************** internal data declaration ****************************/

/********************** internal functions declaration ***********************/
void setPWM(TIM_HandleTypeDef *timer, uint32_t channel, uint8_t pulse);

void motorMoveAllTimeL9110S(uint8_t speed, bool spinRight);
void motorStopL9110S(void);

void motorMoveL298N(const task_actuator_cfg_t *actuator, bool spinRight);
void motorStopL298N(const task_actuator_cfg_t *actuator);

/********************** internal data definition *****************************/

/********************** external data declaration ****************************/

/********************** external functions definition ************************/

void motorMove(const task_actuator_cfg_t *actuator, bool spinRight)
{
#if DRIVER_MOTOR==DRIVER1_L9110S
	motorMove(speed, spinRight); //cambiar a la nueva logica
#endif
#if DRIVER_MOTOR==DRIVER2_L298N
	motorMoveL298N(actuator, spinRight);
#endif
}

void motorStop(const task_actuator_cfg_t *actuator)
{
#if DRIVER_MOTOR==DRIVER1_L9110S
	motorStopL9110S();
#endif
#if DRIVER_MOTOR==DRIVER2_L298N
	motorStopL298N(actuator);
#endif
}

/********************** internal functions definition ************************/
void setPWM(TIM_HandleTypeDef *timer, uint32_t channel, uint8_t pulse)
{
  HAL_TIM_PWM_Stop(timer, channel);
  TIM_OC_InitTypeDef sConfigOC;
  HAL_TIM_PWM_Init(timer);

  sConfigOC.OCMode = TIM_OCMODE_PWM1;
  sConfigOC.Pulse = PERIOD*pulse/10;
  sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
  sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
  HAL_TIM_PWM_ConfigChannel(timer, &sConfigOC, channel);
}


#if DRIVER_MOTOR==DRIVER1_L9110S
void motorMoveL9110S(uint8_t speed, bool spinRight)
{
	if(spinRight)
	{
		setPWM(MOTOR_TIM, MOTOR_CHANNEL_RIGHT, speed);
		HAL_TIM_PWM_Start(MOTOR_TIM, MOTOR_CHANNEL_RIGHT);
	}
	else
	{
		setPWM(MOTOR_TIM, MOTOR_CHANNEL_LEFT, speed);
		HAL_TIM_PWM_Start(MOTOR_TIM, MOTOR_CHANNEL_LEFT);
	}
}

void motorStopL9110S(void)
{
	if(MOTOR_spin_right) HAL_TIM_PWM_Stop(MOTOR_TIM, MOTOR_CHANNEL_RIGHT);
	else HAL_TIM_PWM_Stop(MOTOR_TIM, MOTOR_CHANNEL_LEFT);
}
#endif

#if DRIVER_MOTOR==DRIVER2_L298N
void motorMoveL298N(const task_actuator_cfg_t *actuator, bool spinRight) {
	if(spinRight) {
		setPWM(actuator->timer_handle, actuator->timer_channel, *actuator->speed);
		HAL_GPIO_WritePin(actuator->gpio_port_in1, actuator->pin_in1, GPIO_PIN_SET);
		HAL_GPIO_WritePin(actuator->gpio_port_in2, actuator->pin_in2, GPIO_PIN_RESET);
		HAL_TIM_PWM_Start(actuator->timer_handle, actuator->timer_channel);
	}
	else {
		setPWM(actuator->timer_handle, actuator->timer_channel, *actuator->speed);
		HAL_GPIO_WritePin(actuator->gpio_port_in1, actuator->pin_in1, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(actuator->gpio_port_in2, actuator->pin_in2, GPIO_PIN_SET);
		HAL_TIM_PWM_Start(actuator->timer_handle, actuator->timer_channel);
	}
}

void motorStopL298N(const task_actuator_cfg_t *actuator) {
	HAL_TIM_PWM_Stop(actuator->timer_handle, actuator->timer_channel);
}
#endif

/********************** end of file ******************************************/
