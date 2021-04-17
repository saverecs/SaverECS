typedef struct {

    double next_tempM;
    double next_tempF;
    double next_FuelCommand;

} RETURN_VAL;

typedef struct {

    double state_position;
    double state_velocity;
    double state_mass;
    double state_FuelCommand;
    double state_tempM;
    double state_tempF;

} INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);