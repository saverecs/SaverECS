typedef struct {

	double next_u;

} RETURN_VAL;

typedef struct {

	double state_temperature;

	int chat_detect;
	int previous_cmd_to_heater;
	int on_count;
	int off_count;
	int cmd_to_heater;

} INPUT_VAL;

void* controller(INPUT_VAL* iv, RETURN_VAL* rv);