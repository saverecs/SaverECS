/*
 * input_output.h
 *
 *  Created on: 03-Jul-2018
 *      Author: amit
 */

#ifndef UTILITIES_INPUT_OUTPUT_H_
#define UTILITIES_INPUT_OUTPUT_H_

#include "readCommandLine/user_inputs.h"

/*
 * Returns 1 if it is satisfied and there exists a Counter-Example
 * Returns 0 when un-satisfied and there does not exists any Counter-Example
 */
//int call_dReal(user_inputs::ptr user_Inputs, std::string fileName, int bound);	//, std::vector<parallel_data>& found_for_bound);

int call_dReal(user_inputs::ptr user_Inputs, std::string fileName);


#endif /* UTILITIES_INPUT_OUTPUT_H_ */
