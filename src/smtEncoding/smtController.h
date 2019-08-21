#include <string>
#include <iostream>     // std::cout
#include <fstream>      // std::ofstream
#include <list>

// ************ More Header files *************************
#include "utilities/datastructure_plant.h"
#include "readCommandLine/user_inputs.h"
#include "coreSystem/controller_program/controller.h"

void print_ControllerConstraints(std::ofstream &outputfile, int index,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog);
int IsVariable(std::string InputToken, controller_program::ptr& control_prog);
std::string ReplaceExactString(std::string &subject, const std::string& search,
		const std::string& replace);
std::string AddIndexToToken(std::string tok_str, std::string index_str);
int IsFirstInputVar(std::string tok_str, std::string prev_tok_str,
		controller_program::ptr& control_prog, int line_counter,
		int token_counter);
void aliasing_controller_input(std::ofstream &outputfile, int index,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog);
void aliasing_controller_output(std::ofstream &outputfile, int index,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog);
std::string AliasedPlantVar(std::string Varname,
		struct plant_variables plant_vars);

