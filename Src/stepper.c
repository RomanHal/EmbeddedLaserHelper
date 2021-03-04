#include "stm32f1xx_hal.h"
#include "cmsis_os.h"
#include "main.h"
#include "FreeRTOS.h"
#include "stepper.h"



#define pathStepPin GPIO_PIN_3
#define pathPort GPIOA

#define barrierStepPin GPIO_PIN_4
#define barrierDirectionPin GPIO_PIN_5
#define barrierPort GPIOA

void setDirection(GPIO_TypeDef * GPIOx,uint16_t pin,uint8_t direction);
void makeStepInternal(GPIO_TypeDef * GPIOx,uint16_t pin);

void makeStep(Steppers stepper, uint8_t direction)
{
	if(stepper==StepperPath)
	{
		makeStepInternal(pathPort,pathStepPin);
    }
	else 
	{
		setDirection(barrierPort,barrierDirectionPin,direction);
		makeStepInternal(barrierPort,barrierStepPin);
	}
	//SetDirection(GPIOB,GPIO_PIN_8,direction);
	//MakeStepInternal(GPIOB,GPIO_PIN_6);
}

void makeStepInternal(GPIO_TypeDef * GPIOx,uint16_t pin)
{
	HAL_GPIO_TogglePin(GPIOx,pin);
	vTaskDelay(5);
	HAL_GPIO_TogglePin(GPIOx,pin);
	vTaskDelay(5);
}

void setDirection(GPIO_TypeDef * GPIOx,uint16_t pin,uint8_t direction)
{
	if(direction==0)HAL_GPIO_WritePin(GPIOx,pin,0);
	else HAL_GPIO_WritePin(GPIOx,pin,1);
}