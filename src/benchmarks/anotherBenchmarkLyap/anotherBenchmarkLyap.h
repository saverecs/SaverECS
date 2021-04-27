typedef struct {

	double next_u;

} RETURN_VAL;

typedef struct {

	double state_x;
	double state_u;
	double state_v;
	
} INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);

