// Must include controller.h
#include "smallBenchmarkLyap.h"

#ifdef DEBUG
  #include<stdio.h>
#endif

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
	double temp_x;
	double temp_next_u;
	double temp_y ;
	double temp_z ;
	double temp_v ;

	temp_x = input->state_x;
	temp_y = input->state_y;
	temp_z = input->z;
	temp_v = input->state_v;
	//temp_next_u = 0.6*temp_x;
	temp_next_u = -2*temp_y-2;

	// if (temp_x <= 10 )
	// {
	// 	temp_next_u = 0.2;
	// }
	// else if (temp_x >= 10 && temp_x <= 20)
	// {
	// 	temp_next_u = 0.1;
	// }
	// else 
	// 	temp_next_u = 0.01;

//	temp_next_u = 15;

	ret_val->next_u = temp_next_u;

  return ret_val;
}

