/* Zutshi et al., “Symbolic-numeric reachability analysis of 
 * closed-loopcontrol software,” in HSCC, ACM, 2016
 * https://dl.acm.org/doi/10.1145/2883817.2883819
 */
#include "thermostat.h"

#ifdef DEBUG
	#include<stdio.h>
#endif

void* controller(INPUT_VAL* input, RETURN_VAL* ret_val)
{
	int chatter_detect = 0;

	int previous_command_to_heater;
	int on_counter, off_counter;
	int command_to_heater;
	
	int chatter_limit = 5;
	
	double uVal, room_temp;
	
	double MAX_TEMP = 70.0;
	double MED_TEMP = 66.0;
	
	int NO_CHAT_FOR=5;

	room_temp = input->state_temperature;

	chatter_detect             = input->chat_detect;
	previous_command_to_heater = input->previous_cmd_to_heater;
	on_counter                 = input->on_count;
	off_counter                = input->off_count;
	command_to_heater          = input->cmd_to_heater;


	if (room_temp >= MED_TEMP && room_temp < MAX_TEMP) {

		command_to_heater = 3;
	
	} else if (room_temp >= MAX_TEMP) {

		command_to_heater = 1;
	
	} else if (room_temp < MED_TEMP) {

		command_to_heater = 2;

	} else {

		command_to_heater = previous_command_to_heater;

	}
	
	if (off_counter >= NO_CHAT_FOR || 
		on_counter  >= NO_CHAT_FOR) 
	{
		chatter_detect = 0; // reset chatter counter
	}

	if (command_to_heater != previous_command_to_heater) 
	{
		chatter_detect++; //detect chatter
	}

	if (chatter_detect >= chatter_limit) 
	{
		// mitigate chatter
		command_to_heater = previous_command_to_heater;
	}

	if (command_to_heater == 1) 
	{
		on_counter = 0;
		off_counter++; // heater off
	
	} else {
		// heater on
		on_counter++;
		off_counter = 0;

	}
	
	if (command_to_heater == 1) {
		
		uVal = 20;
	
	} else if (command_to_heater == 2) { 

		uVal = 100;

	} else if (command_to_heater == 3) {

		uVal = 70;

	}

	ret_val->next_u = uVal;

	input->cmd_to_heater          = command_to_heater;
	input->chat_detect            = chatter_detect;
	input->previous_cmd_to_heater = command_to_heater;
	input->on_count               = on_counter;
	input->off_count              = off_counter;

	return ret_val;
}