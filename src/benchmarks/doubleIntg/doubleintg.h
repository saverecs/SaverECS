
typedef struct {

   double next_a;

} RETURN_VAL;

typedef struct {

   double state_x;
   double state_v;
   
} INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);