#include "controller.h"

#define Isp 2800
#define deltaT 0.128

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{

	double G    = input->state_Plasma_Glucose;
	double X    = input->state_Interstitial_Insulin;
	double I    = input->state_Plasma_Insulin;
	double g_t  = input->state_Glucose_Infusion;
	double i_t  = input->state_Bloodstream_Insulin;
	double time = input->state_global_clock;


	double temp_gt ;
	double temp_it ;

	if ( G < 6 )
	{
		temp_it = 1 + (2 / 9) * G;
	}
	
	if ( G >= 6 )
	{
		temp_it = 50/3;
	}

	if ( time <= 30 )
	{
		temp_gt = time / 60;
	}

	if ( time > 30 && time <= 120 )
	{
		temp_gt = (120 - time) / 180 ;
	}
	
	if ( time > 120 )
	{
		temp_gt = 0;
	}

	ret_val->next_Bloodstream_Insulin = temp_it;
	ret_val->next_Glucose_Infusion    = temp_gt;
  
	return (void*)0;
}