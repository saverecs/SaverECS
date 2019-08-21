/*
 * controller_parser.h
 *
 *  Created on: 08-Jun-2018
 *      Author: amit
 */

#ifndef CORESYSTEM_CONTROLLER_PROGRAM_CONTROLLER_PARSER_H_
#define CORESYSTEM_CONTROLLER_PROGRAM_CONTROLLER_PARSER_H_

#include "controller.h"
#include "readCommandLine/user_inputs.h"
#include "utilities/datastructure_plant.h"

void generate_ssaFile(user_inputs::ptr& user_Inputs);

void read_ssaFile(controller_program::ptr& control_prog, user_inputs::ptr& user_Inputs);



#endif /* CORESYSTEM_CONTROLLER_PROGRAM_CONTROLLER_PARSER_H_ */
