#include "nuclear.h"

#include <stdbool.h>

#ifdef DEBUG
	#include<stdio.h>
#endif

#define VAL1  510
#define VAL2  550


void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
	int    out_r1, out_r2;
	double out_c1, out_c2;
	double temp;
	double count_r1;
	double count_r2;

	bool in_state_r1, in_state_r2;

	int out_shut_down;	

	temp = input->state_temperature;
	count_r1 = input->state_c1;
	count_r2 = input->state_c2;

	if ( input->state_r1 == 1 )
		in_state_r1 = true;
	else 
		in_state_r1 = false;

	if ( input->state_r2 == 1 )
		in_state_r2 = true;
	else 
		in_state_r2 = false;

	out_shut_down = 0;

	out_c1 = count_r1;
	out_c2 = count_r2;

	if (( temp        <= VAL2 ) && 
		( in_state_r1 == 0    ) && 
		( in_state_r2 == 0    )) 
	{
			out_r1 = 0;
			out_r2 = 0;
	} 
	else if (( temp     >=  VAL2 ) && 
		     ( count_r1 >= 20    )) 
	{
			out_r1 = 1;
			out_r2 = 0;
	} 
	else if (( temp     >= VAL2 ) && 
		     ( count_r2 >= 20   )) 
	{
			out_r1 = 0;
			out_r2 = 1;
	} 
	else if (( temp     >= VAL2 ) && 
		     ( count_r1 <  20   ) && 
		     ( count_r2 <  20   )) 
	{
			out_shut_down = 1;
			out_r1 = 0;
			out_r2 = 1;
	} 
	else if (( temp        <= VAL1  ) && 
		     ( in_state_r1 == 1     )) 
	{
			out_r1 = 0;
			out_r2 = 0;
			out_c1 = 0;
	} 
	else if (( temp        <= VAL1 ) && 
		     ( in_state_r2 == 1    )) 
	{
			out_r1 = 0;
			out_r2 = 0;
			out_c2 = 0;
	} 
	else if (( temp       >= VAL1 ) && 
		     (in_state_r1 == 1    )) 
	{
			out_r1 = 1;
			out_r2 = 0;
	} 
	else if (( temp        >= VAL1 ) && 
		     ( in_state_r2 == 1    )) 
	{
			out_r1 = 0;
			out_r2 = 1;
	}

	ret_val->next_r1 = out_r1;
	ret_val->next_r2 = out_r2;
	ret_val->next_c1 = out_c1;
	ret_val->next_c2 = out_c2;
	ret_val->next_shutdown = out_shut_down;

	return (void*)0;
}