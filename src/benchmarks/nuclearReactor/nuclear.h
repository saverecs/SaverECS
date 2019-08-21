
typedef struct{
   double next_c1;	//state of rod1 if >20 only then can be inserted into the reactor
   double next_c2;	//state of rod2 if >20 only then can be inserted into the reactor	
   int next_r1;	//rod1 
   int next_r2;	//rod2 
   int next_shutdown;

}RETURN_VAL;

typedef struct{

   double state_temperature;
   double state_c1;	//state of rod1 if >20 only then can be inserted into the reactor
   double state_c2;	//state of rod2 if >20 only then can be inserted into the reactor	
   int state_r1;	//to remember the previous state of rod1 
   int state_r2;	//to remember the previous state of rod2 
	
}INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);


