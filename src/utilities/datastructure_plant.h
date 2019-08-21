/*
 * datastructure_plant.h
 *
 *  Created on: 07-May-2018
 *      Author: amit
 */

#ifndef UTILITIES_DATASTRUCTURE_PLANT_H_
#define UTILITIES_DATASTRUCTURE_PLANT_H_

#include <string>

//This data structure will be used to create the control and uncontrol variables of the plant
struct variablesTypes {
	int var_id;	//
	std::string var_name;
	double lbound;	//Lower bound value of the variable
	double ubound;	//Upper bound value of the variable
};

struct variablesContorller {
	std::string var_type;	//Data type of the variable (Example:  Int, bool, real, e.t.c.)
	std::string var_name;
	double lbound;	//Lower bound value of the variable
	double ubound;	//Upper bound value of the variable
};


/*
 * control_var: The variable that take part in the dynamic are referred as control variable (i.e., having ode)
 * uncontrol_var: The variable that does NOT take part in the dynamic of the plant are referred as un-control variable.
 * 				  However, in dReal these variables are also given zero dynamics(z'==0), otherwise dReal returns error.
 * 				  Therefore, our smt-encoding module assigns a zero dynamic on the fly, to support dReal syntax.
 */
struct plant_variables{
	std::list<struct variablesTypes> control_var;
	std::list<struct variablesTypes> uncontrol_var;
};

//This structure is used for referring to the noise and disturbance parameters
struct nd_parameter{
	double start_time;	//starting time of the noise or disturbance
	double end_time;	//ending time of the noise or disturbance
	std::string nd_variable_name;	//the noise injection or the disturbed variable in the plant
	//Note that the noise injected or the disturbed value can be fix or in range. If fixed (value1=value2)
	double value1;
	double value2;
};


//Data Structure for storing information to avoid race condition
struct parallel_data{
	int sat_unsat;	//stores 1 for sat and 0 for unsat
	double running_wall_time;	//time taken to run dReal
	int bound_value;	//Number of the unrolling depth
	std::string smt_fileName;
	std::string json_fileName;
	std::string sys_fileName;	//system generated file name to be deleted
};


//This structure is used for storing user's input parameters from the configuration file
struct min_max_bounds{
	std::string variable_name;	//variable in the plant or controller (including input/output or intermediate (if required))
	double minValue;
	double maxValue;
};



#endif /* UTILITIES_DATASTRUCTURE_PLANT_H_ */
