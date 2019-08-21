// Must include controller.h
#include "anotherBenchmarkLyap.h"

#ifdef DEBUG
  #include<stdio.h>
#endif

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
	double temp_x;
	double temp_next_u;
	double temp_u ;
	double temp_v;

	temp_x = input->state_x;
	temp_u = input->state_u;
	temp_next_u = -temp_x+temp_u;
	temp_v = input->state_v;

	ret_val->next_u = temp_next_u;

  return ret_val;
}

