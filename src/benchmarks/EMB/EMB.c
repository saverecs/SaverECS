// Must include controller.h
#include "EMB.h"

#ifdef DEBUG
  #include<stdio.h>
#endif

#define X0 0.05
#define Samp_Time 0.001
#define K_P 10000
#define K_I 1000





void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
	double out_Voltage;
	double out_Xc;

	double I_temp, X_temp;
	double prev_Xc_temp;

	I_temp = input->state_Motor_Current;
	X_temp = input->state_Caliper_Position;

	prev_Xc_temp = input->prev_Xc;

	out_Xc = prev_Xc_temp + Samp_Time * (X0 - X_temp);
	out_Voltage = K_P*(X0 - X_temp) + K_I*out_Xc;

	input->prev_Xc = out_Xc ;

  	ret_val->next_Xc = out_Xc;
  	ret_val->next_Voltage = out_Voltage;
  
  return (void*)0;
}


