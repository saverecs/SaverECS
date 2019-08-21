#include <stdio.h>
#define MAX_TEMP (70.0)
#define MIN_TEMP (66.0)
#define CHATTER_LIMIT (2)

#define NO_HEAT 1
#define NORMAL_HEAT 2
#define FAST_HEAT 3

int controller(double room_temp){
	static int on_ctr, off_ctr, chatter_detect_ctr;
	static int previous_command, command, u;

	if (room_temp >= MIN_TEMP && room_temp < MAX_TEMP)
		command = NORMAL_HEAT;
	else if (room_temp >= MAX_TEMP)
		command = NO_HEAT;
	else if (room_temp < MIN_TEMP)
		command = FAST_HEAT;
	else 
		command = previous_command;

	if (off_ctr >= 5 || on_ctr >= 5)
		chatter_detect_ctr=0;

	if (command != previous_command)
		chatter_detect_ctr++;

	if (chatter_detect_ctr > CHATTER_LIMIT)
		command = previous_command;

	if (command == NO_HEAT){
		on_ctr=0;	
		off_ctr++;
	} else {
		on_ctr++;
		off_ctr=0;
	}

	if (command==NO_HEAT) 
		u = 20;
	if (command==FAST_HEAT) 
		u = 100;
	if (command==NORMAL_HEAT) 
		u = 70;

	return u;
}

