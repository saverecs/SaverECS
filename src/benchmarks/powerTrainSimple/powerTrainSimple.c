#include "powerTrainSimple.h"
typedef double real32_T;
typedef unsigned char boolean_T;

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
//void* main(INPUT_VAL* input, RETURN_VAL* ret_val)
{       

	// outputs
	double commanded_fuel_gps;
	double pressure_est;
	double integral_error;

	// plant states (Sensed)
	double engine_speed      = input->state_p_engine_speed;
	double throttle_angle    = input->state_p_throttle_angle;
	double manifold_pressure = input->state_p_manifold_pressure;
	double airbyfuel_meas    = input->state_p_airbyfuel_meas;

	//Controller Variables
	double prev_pressure_est   = input->state_p_air_estimate;
	double prev_integral_error = input->state_p_pi;

	pressure_est       = prev_pressure_est + 
	                     ( Sampling_Time   * 
	                       c1              * 
	                       (c23 * dmAf - mCf(prev_pressure_est) ) );

	integral_error     = prev_integral_error + 
	                     Sampling_Time       * 
	                     c14                 * 
	                     (c24 * airbyfuel_meas - c11);

	commanded_fuel_gps = ((1 + prev_integral_error + 
		                   (c13 * ((c24 * airbyfuel_meas) - c11))) * 
	                       mCf(prev_pressure_est)) 
	                     / c11;	

	// output to plant
	ret_val->next_c_commanded_fuel_gps = commanded_fuel_gps;
	ret_val->next_p_air_estimate       = pressure_est;
	ret_val->next_p_pi                 = integral_error;

	return (void*)0;
}