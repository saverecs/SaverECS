typedef struct {

    double next_u;

} RETURN_VAL;

typedef struct {

    double state_x1;
    double state_x2;
    double state_x3;
    double state_x4;
    double state_w;

} INPUT_VAL;


void* controller(INPUT_VAL* iv, RETURN_VAL* rv);