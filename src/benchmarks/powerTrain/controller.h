typedef struct {

	// input to the plant from the controller
	double next_c_commanded_fuel_gps;	
	double next_p_pi;
	double next_p_air_estimate;

} RETURN_VAL;

typedef struct {

	// plant states (to be sensed)
	double state_p_engine_speed;	
	double state_p_throttle_angle;	
	double state_p_throttle_flow;	
	double state_p_airbyfuel_meas;	

	// controller state variables (to be maintained)
	double state_p_pi;
	double state_p_air_estimate;

} INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);