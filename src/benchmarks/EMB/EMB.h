
typedef struct{
   double next_Xc;
   double next_Voltage;

}RETURN_VAL;

typedef struct{

	double state_Motor_Current;
	double state_Caliper_Position;

	double prev_Xc ;
	
	
}INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);


