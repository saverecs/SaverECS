typedef struct {

    double next_voltage;

} RETURN_VAL;

typedef struct {

    double state_angVal;
    double state_error_i_previous;
    
} INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);