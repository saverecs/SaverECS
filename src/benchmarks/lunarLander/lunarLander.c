#include "lunarLander.h"

#define Isp 2800
#define deltaT 0.128


void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{

  double r = input->state_position;
  double v = input->state_velocity;
  double m = input->state_mass;
  double f ;

	// get the previous Controller variables
	double t_m = input->state_tempM;
	double t_f = input->state_tempF;

	// Update mass
	t_m = t_m - (0.128/2800)*t_f ;

	//Calculate engine thrust
        f  = - 0.01*( t_f - 1.622 * (t_m - t_f * 0.00004571) ) - ( 0.6*(v+2) ) * (t_m - t_f * 0.00004571) + 1.622*(t_m - t_f*0.00004571) ;
	//f =t_m ;
	ret_val->next_tempM = t_m;
	ret_val->next_tempF = f;
	ret_val->next_FuelCommand = f;
  
  return (void*)0;
}
