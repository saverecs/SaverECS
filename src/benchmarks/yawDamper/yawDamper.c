#include "yawDamper.h"

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{

	double x1 = input->state_x1;
	double x2 = input->state_x2;
	double x3 = input->state_x3;
	double x4 = input->state_x4;
	double w  = input->state_w;

	double u;

	u = 2.34 * x2 - (2.34 * 0.2 * w);

	ret_val->next_u = u;
  
	return (void*)0;
}
