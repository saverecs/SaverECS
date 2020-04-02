
typedef struct{
	double next_u;
}RETURN_VAL;

typedef struct{
	double state_v;
	double state_z;

}INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);

