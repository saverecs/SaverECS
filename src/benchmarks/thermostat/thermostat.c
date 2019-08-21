// Must include controller.h
#include "thermostat.h"

#ifdef DEBUG
  #include<stdio.h>
#endif

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
	int chatter_detect;
	int previous_command_to_heater;
	int on_counter, off_counter;
	int command_to_heater;

	int chatter_limit=2;
	double uVal, room_temp;
	double MAX_TEMP=70.0, MED_TEMP=66.0;

//	int NO_HEAT=1, NORMAL_HEAT = 3, FAST_HEAT = 2;

 room_temp = input->state_temperature;

 chatter_detect = input->chat_detect;
 previous_command_to_heater = input->previous_cmd_to_heater;
 on_counter = input->on_count;
 off_counter = input->off_count;
 command_to_heater = input->cmd_to_heater;


	if(room_temp >= MED_TEMP && room_temp < MAX_TEMP)
		command_to_heater = 3;
	else if(room_temp >= MAX_TEMP)
		command_to_heater = 1;
	else if(room_temp < MED_TEMP)
		command_to_heater = 2;
	else
		command_to_heater = previous_command_to_heater;

	if(off_counter >= 5 || on_counter >= 5)
		chatter_detect = 0;

	if(command_to_heater != previous_command_to_heater)
		chatter_detect++;

	if(chatter_detect >= chatter_limit)
		command_to_heater = previous_command_to_heater;

	if(command_to_heater == 1) {
		on_counter = 0;
		off_counter++;
	} else {
		on_counter++;
		off_counter = 0;
	}

	if (command_to_heater==1) 
		uVal = 20;
	else if (command_to_heater==2) 
		uVal = 100;
	else if (command_to_heater==3) 
		uVal = 70;

	ret_val->next_u = uVal;

  input->cmd_to_heater = command_to_heater;
  input->chat_detect = chatter_detect;
  input->previous_cmd_to_heater = command_to_heater;
  input->on_count = on_counter;
  input->off_count = off_counter;

  return ret_val;
}

