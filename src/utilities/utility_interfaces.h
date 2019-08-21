/*
 * utility_interfaces.h
 *
 *  Created on: 11-Jul-2018
 *      Author: amit
 */

#ifndef UTILITIES_UTILITY_INTERFACES_H_
#define UTILITIES_UTILITY_INTERFACES_H_

#include <string>
#include <list>
#include <iostream>
#include "utilities/datastructure_plant.h"

#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>

//#include "readCommandLine/user_inputs.h"


std::list<nd_parameter> convertToNDparams(std::string my_noisedata);

void displayNDparams(std::list<nd_parameter> nd_parms);

std::string remove_quotes(std::string quote_str);

std::list<min_max_bounds> convertTo_MinMaxBounds(std::string user_args);

void display_MinMaxBounds(std::list<min_max_bounds> MinMaxData);

bool findVar_in_MinMaxBounds(std::list<min_max_bounds> min_max_bounds_structure, std::string var_name);

#endif /* UTILITIES_UTILITY_INTERFACES_H_ */
