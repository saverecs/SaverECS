/*
 * verifier.h
 *
 *  Created on: 06-May-2018
 *      Author: amit
 */

#ifndef UTILITIES_VERIFIER_H_
#define UTILITIES_VERIFIER_H_

#include <iostream>
#include "structs.h"
#include "../coreSystem/plant_model/hybrid_automata.h"
#include "datastructure_plant.h"
#include "InToPre.h"
#include "../readCommandLine/user_inputs.h"
#include "node.h"
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp> //string comparison

#include "coreSystem/controller_program/controller.h"
#include "coreSystem/controller_program/controller_parser.h"

#include "coreSystem/plant_model/plantDataStructure.h"
#include "utilities/utility_interfaces.h"


/* Module to populate details of the plant model from HASLAC into hybrid_automata class
 * control_vars: is the control variables of the plant
 * uncontrol_vars: is the uncontrol or the input variables of the plant which is modified by the Controller-Program
 *
 * */
void populateDataPlant(struct phaver* pha, hybrid_automata::ptr& hybrid_auto,
		struct plant_variables& plant_vars, user_inputs::ptr& user_Inputs);


std::string InfixToPrefix(std::string i);

void display_safe_hybrid_automata(hybrid_automata::ptr& my_ha);
void populateDataController(controller_program::ptr& control_prog, user_inputs::ptr& user_Inputs);


#endif /* UTILITIES_VERIFIER_H_ */
