#include "doubleintg.h"

#ifdef DEBUG
	#include<stdio.h>
#endif

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
	double out;
	double xtemp, vtemp;

	xtemp = input->state_x;
	vtemp = input->state_v;

	out = 10 * (1 - xtemp) + 3 * (-vtemp);

  	ret_val->next_a = out;
  
  	return (void*)0;
}


