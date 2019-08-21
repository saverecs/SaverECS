// Must include controller.h
#include "smallBenchmark.h"

#ifdef DEBUG
  #include<stdio.h>
#endif

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
	double temp_x;
	double temp_next_u;
	double temp_y ;
	double temp_z ;

	temp_x = input->state_x;
	temp_y = input->state_y;
	temp_z = input->z;

	if (temp_x <= 10 )
	{
		temp_next_u = 0.2;
	}
	else if (temp_x >= 10 && temp_x <= 20)
	{
		temp_next_u = 0.1;
	}
	else 
		temp_next_u = 0.01;

//	temp_next_u = 0.6*temp_next_x;

	ret_val->next_u = temp_next_u;

  return ret_val;
}

