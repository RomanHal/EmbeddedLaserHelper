#include <stdint.h>
#include "main.h"

typedef enum
{
	StepperPath,
	StepperBarrier
} Steppers;


void makeStep(Steppers stepper, uint8_t direction);
