/*
 * smtScript.h
 *
 *  Created on: 24-May-2018
 *      Author: Jay Thakkar
 */

#ifndef SMTSCRIPT_H_
#define SMTSCRIPT_H_

#include <string>
#include <iostream>     // std::cout
#include <fstream>      // std::ofstream
#include <list>

// ************ More Header files *************************
#include "utilities/datastructure_plant.h"
#include "readCommandLine/user_inputs.h"
#include "utilities/verifier.h"

#include "coreSystem/controller_program/controller.h"

void print_header(std::ofstream &outputfile);

void print_declaration(std::ofstream &outputfile, user_inputs::ptr& userInputs,
		int bound, struct plant_variables plant_vars,
		controller_program::ptr& control_prog);

void initialize_Noiseparameters(user_inputs::ptr& userInputs);

void print_flowEquation(hybrid_automata::ptr& my_ha, std::ofstream &outputfile,
		struct plant_variables plant_vars);

void print_initialState(hybrid_automata::ptr& my_ha, std::ofstream &outputfile,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog);

void print_firstLoop(std::ofstream &outputfile, hybrid_automata::ptr& my_ha,
		user_inputs::ptr& userInputs, struct plant_variables plant_vars);

void print_nextLoops(std::ofstream &outputfile, hybrid_automata::ptr& my_ha,
		int bound, user_inputs::ptr& userInputs,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog);

int smt_generator(hybrid_automata::ptr& my_ha, user_inputs::ptr& userInputs,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog, int bound,
		string output_filename);

void print_specification(std::ofstream &outputfile, int bound,
		user_inputs::ptr& userInputs, struct plant_variables plant_vars);

void print_footer(std::ofstream &outputfile);

int IsPlantVar(std::string Varname, struct plant_variables plant_vars);

string processInitSet(string init_set_string,
		struct plant_variables plant_vars);

std::string ProcessGoalProperty(string init_set_string,
		struct plant_variables plant_vars, int index);

#endif /* SMTSCRIPT_H_ */
