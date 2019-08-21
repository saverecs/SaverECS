/*
 * plantDataStructure.h
 *
 *  Created on: 19-Jul-2018
 *      Author: amit
 */

#ifndef CORESYSTEM_PLANT_MODEL_PLANTDATASTRUCTURE_H_
#define CORESYSTEM_PLANT_MODEL_PLANTDATASTRUCTURE_H_

#include <string>
#include <iostream>

struct flow_equation{
	bool isConstant_dynamic;
	std::string varName;	// contains the LHS of the flow equation
	std::string RHSexpression;	//if RHSexpression is number then  isConstant_dynamic will be TRUE
	std::string derivative;
};



#endif /* CORESYSTEM_PLANT_MODEL_PLANTDATASTRUCTURE_H_ */
