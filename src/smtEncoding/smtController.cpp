#include <iterator>
#include <iostream>
#include <string>
#include <cstddef>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/replace.hpp>
#include <regex>

// ************ More Header files *************************
#include "smtScript.h"
#include "smtController.h"
#include "coreSystem/controller_program/controller.h"

using namespace std;

//#define Controller_SMT_Encoding_Debug_On

void print_ControllerConstraints(std::ofstream &outputfile, int index,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog) {

	aliasing_controller_input(outputfile, index, plant_vars, control_prog);

	//outputfile << "(assert ";

	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

	//cout << "\n\n ---- Indexed Controller Constraints ---\n\n";
	//Convert Integer to String for Index variable
	std::string index_str = boost::lexical_cast<std::string>(index);

	std::string prev_index_str = boost::lexical_cast<std::string>(index - 1);

	std::string Program_stmt;

	std::string Indexed_Program_stmt;

	std::string Indexed_Program;

	int token_counter;

	int line_counter = 1;

	//outputfile << " (and ";

	std::list<std::string> ssaStmts = control_prog->getSsaStatements();

	for (std::list<std::string>::iterator Program_it = ssaStmts.begin();
			Program_it != ssaStmts.end(); Program_it++) {

		Program_stmt = (*Program_it);

		token_counter = 0;

#ifdef Controller_SMT_Encoding_Debug_On
		cout << "\t" << Program_stmt << " \n";
#endif

		//boost::char_separator<char> sep(" ;)");

		//Use space as a separator
		boost::char_separator<char> sep(" ");

		tokenizer tok(Program_stmt, sep);
		std::string prev_tok_str;


		//cout << "\nTokens in a statement:\t";

		for (tokenizer::iterator tok_it = tok.begin(); tok_it != tok.end();
				++tok_it) {
			//cout << *beg << "\n";

			std::string tok_str = (*tok_it);

			token_counter++;

			//cout << "\t " << tok_str;

			if (IsFirstInputVar(tok_str, prev_tok_str, control_prog,
					line_counter, token_counter) == 1) {

				tok_str = AddIndexToToken(tok_str, index_str);

			} else if (IsVariable(tok_str, control_prog) != 0) {

				tok_str = AddIndexToToken(tok_str, prev_index_str);

			}

			Indexed_Program_stmt += tok_str + " ";

#ifdef Controller_SMT_Encoding_Debug_On
			cout << "\n  Indexed Program stmt:  " << Indexed_Program_stmt << "\n";
#endif

			prev_tok_str = tok_str;

		}

		Indexed_Program += Indexed_Program_stmt + "\n";

		//outputfile << Indexed_Program_stmt << " ";

		Indexed_Program_stmt.clear();

		line_counter++;

	}

	/*//Replacement for Input Variables

	 std::string variable_name;

	 std::list<std::pair<std::string, std::string> > inputVar;
	 inputVar = control_prog->getInputVariables();
	 for (std::list<std::pair<std::string, std::string> >::iterator var_it =
	 inputVar.begin(); var_it != inputVar.end(); var_it++) {

	 variable_name = (*var_it).second;

	 //boost::replace_first_copy( Indexed_Program, variable_name , variable_name + "_" + prev_index_str);

	 //boost::ireplace_first_copy( Indexed_Program, variable_name , variable_name + "_" + index_str);

	 }*/

#ifdef Controller_SMT_Encoding_Debug_On
	cout << "Indexed Program Final String: \n\n " << Indexed_Program;
#endif

	outputfile << Indexed_Program << " ";

#ifdef Controller_SMT_Encoding_Debug_On
	cout << ")\n";
#endif

	//outputfile << ")";

	//outputfile << " )\n";
	outputfile << " \n ";

	aliasing_controller_output(outputfile, index, plant_vars, control_prog);

}

int IsVariable(std::string InputToken, controller_program::ptr& control_prog) {

	std::string temp_variable_name;
	std::string temp2_variable_name;

	//Replacement for Intermediate Variables
	std::list<variablesContorller> interVar;
	interVar = control_prog->getIntermediateVariables();
	for (std::list<variablesContorller>::iterator var_it =
			interVar.begin(); var_it != interVar.end(); var_it++) {

		temp_variable_name = (*var_it).var_name;

		if (InputToken == temp_variable_name) {

			//cout << "\n\t Keyword match - token: " << InputToken << " and Var: "
			//		<< temp_variable_name << "\n";

			return 1;
		}
	}

	//Replacement for Output Variables
	std::list<variablesContorller> output;
	output = control_prog->getOutputVariables();
	for (std::list<variablesContorller>::iterator var_it =
			output.begin(); var_it != output.end(); var_it++) {
		temp2_variable_name = (*var_it).var_name;

		if (InputToken == temp2_variable_name) {

			//cout << "\n\t Keyword match - token: " << InputToken << " and Var: "
			//		<< temp2_variable_name << "\n";

			return 3;
		}

	}

	//Replacement for Input Variables
	std::list<variablesContorller> inputVar;
	inputVar = control_prog->getInputVariables();
	for (std::list<variablesContorller>::iterator var_it =
			inputVar.begin(); var_it != inputVar.end(); var_it++) {
		temp_variable_name = (*var_it).var_name;

		if (InputToken == temp_variable_name)
			return 2;

	}

	//Not a variable
	return 0;

}

std::string ReplaceExactString(std::string &subject, const std::string& search,
		const std::string& replace) {
	// Regular expression to match words beginning with 'search'
	std::regex e("(\\b(" + search + "))([^) ]*)");
	std::string mod_subject = std::regex_replace(subject, e, replace);

	return mod_subject;

}

std::string AddIndexToToken(std::string tok_str, std::string index_str) {
	return tok_str + "_" + index_str;

}

int IsFirstInputVar(std::string tok_str, std::string prev_tok_str,
		controller_program::ptr& control_prog, int line_counter,
		int token_counter) {

	//Replacement for Input Variables
	//Dont replace Input variable
	std::list<variablesContorller> inputVar;
	std::list<variablesContorller> outputVar;

	std::string variable_name;

	inputVar = control_prog->getInputVariables();
	outputVar = control_prog->getOutputVariables();


	int no_of_InputVar = inputVar.size();


#ifdef Controller_SMT_Encoding_Debug_On
	cout << "\n Token & Prev_Token : " << tok_str << " " << prev_tok_str << endl ;

	cout << "\n Token counter : " << token_counter << endl;
#endif

	//cout << "\nNo of Input Variable : " << no_of_InputVar;

	for (std::list<variablesContorller>::iterator var_it =
			inputVar.begin(); var_it != inputVar.end(); var_it++) {
		variable_name = (*var_it).var_name;


		//Jay:
		//Need to check whether it's initial assignment
		//Check is done by looking at whether it's assignment of variable
		//if (tok_str == variable_name && line_counter <= (no_of_InputVar + 5))
		if (tok_str == variable_name && prev_tok_str == "(="
				&& token_counter == 2) {

#ifdef Controller_SMT_Encoding_Debug_On
			cout << "\nAssignment stmt of Variable: " << tok_str << endl;
#endif
			return 1;
		}

	}

	for (std::list<variablesContorller>::iterator var_it =
				outputVar.begin(); var_it != outputVar.end(); var_it++) {
			variable_name = (*var_it).var_name;


			//Jay:
			//Need to check whether it's initial assignment
			//Check is done by looking at whether it's assignment of variable
			//if (tok_str == variable_name && line_counter <= (no_of_InputVar + 5))
			if (tok_str == variable_name && prev_tok_str == "(="
					&& token_counter == 2) {

#ifdef Controller_SMT_Encoding_Debug_On
				cout << "\nAssignment stmt of Variable: " << tok_str << endl;
#endif

				return 1;
			}

		}

	return 0;

}

void aliasing_controller_input(std::ofstream &outputfile, int index,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog) {

	std::string index_str = boost::lexical_cast<std::string>(index);

	std::string prev_index_str = boost::lexical_cast<std::string>(index - 1);

	//outputfile << "(assert (and ";

	std: string temp_variable_name;

	//Input Variables
	std::list<variablesContorller> inputVar;
	inputVar = control_prog->getInputVariables();
	for (std::list<variablesContorller>::iterator var_it =
			inputVar.begin(); var_it != inputVar.end(); var_it++) {
		temp_variable_name = (*var_it).var_name;

		if (AliasedPlantVar(temp_variable_name, plant_vars) != "No_match") {
			outputfile << "(= " << (temp_variable_name + "_" + prev_index_str)
					<< " "
					<< AliasedPlantVar(temp_variable_name, plant_vars) + "_"
							+ prev_index_str + "_t ) ";
		}

	}

	//outputfile << " ))\n";
	outputfile << " \n ";

}

void aliasing_controller_output(std::ofstream &outputfile, int index,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog) {

	std::string index_str = boost::lexical_cast<std::string>(index);

	std::string prev_index_str = boost::lexical_cast<std::string>(index - 1);

	//outputfile << "(assert (and ";

	std: string temp_variable_name;

	//Output Variables
	std::list<variablesContorller> outputVar;
	outputVar = control_prog->getOutputVariables();
	for (std::list<variablesContorller>::iterator var_it =
			outputVar.begin(); var_it != outputVar.end(); var_it++) {
		temp_variable_name = (*var_it).var_name;

		if (AliasedPlantVar(temp_variable_name, plant_vars) != "No_match") {
			outputfile << "(= " << (temp_variable_name + "_" + index_str) << " "
					<< AliasedPlantVar(temp_variable_name, plant_vars) + "_"
							+ index_str + "_0 ) ";
		}

	}

	//outputfile << " ))\n";
	outputfile << " \n ";

}

std::string AliasedPlantVar(std::string Varname,
		struct plant_variables plant_vars) {

	std::list<struct variablesTypes>::iterator it_control_var;

	//Controlled variable
	for (it_control_var = plant_vars.control_var.begin();
			it_control_var != plant_vars.control_var.end(); ++it_control_var) {

		if (Varname == ("state_" + (*it_control_var).var_name)
				|| Varname == ("next_" + (*it_control_var).var_name)) {
			return (*it_control_var).var_name;
		}
	}

	std::list<struct variablesTypes>::iterator it_uncontrol_var;

	//Un Controlled variable
	for (it_uncontrol_var = plant_vars.uncontrol_var.begin();
			it_uncontrol_var != plant_vars.uncontrol_var.end();
			++it_uncontrol_var) {

		if (Varname == ("state_" + (*it_uncontrol_var).var_name)
				|| Varname == ("next_" + (*it_uncontrol_var).var_name)) {
			return (*it_uncontrol_var).var_name;
		}
	}

#ifdef Controller_SMT_Encoding_Debug_On
	cout << "\n\n Error : Could not find aliased name for controller argument: "
	<< Varname << "\n\n";
#endif

	return "No_match";
}
