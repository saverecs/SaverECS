#define Sampling_Time 0.01

#define thetaHat (c6 + c7 * throttle_angle             + \
                  c8 * throttle_angle * throttle_angle + \
                  c9 * throttle_angle * throttle_angle * throttle_angle)

#define dmAf       (2 * thetaHat * \
                    (c20 * manifold_pressure * manifold_pressure + \
                     c21 * manifold_pressure                     + \
                     c22))

#define mCf(x)     (c2                        + \
                    c3 * engine_speed * x     + \
                    c4 * engine_speed * x * x + \
                    c5 * engine_speed * engine_speed * x)

#define dmC (c12 * mCf(manifold_pressure))

#define c1	  0.41328
#define c2	 -0.366
#define c3	  0.08979
#define c4	 -0.0337
#define c5	  0.0001
#define c6	  2.821
#define c7	 -0.05231
#define c8	  0.10299
#define c9	 -0.00063
#define c10	  1.0
#define c11	  14.7
#define c11P  12.5
#define c12	  0.9
#define c13	  0.04
#define c14	  0.14
#define c15	  13.893
#define c16	 -35.2518
#define c17	  20.7364
#define c18	  2.6287
#define c19	 -1.592
#define c20	 -2.3421
#define c21   2.7799
#define c22	 -0.3273
#define c23	  1.0
#define c24	  1.0
#define c25	  1.0
#define c26   4.0

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
	double state_p_manifold_pressure;	
	double state_p_airbyfuel_meas;		

	//controller variables (to be maintained)
	double state_p_pi;			
	double state_p_air_estimate;		

} INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);