/*
 * smtScript.c
 *
 *  Created on: 24-May-2018
 *      Author: Jay Thakkar
 */
#include <iterator>

// ************ More Header files *************************
#include "smtScript.h"
#include "smtController.h"
#include "coreSystem/controller_program/controller.h"
#include "coreSystem/plant_model/initial_sym_state.h"
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include <cmath>

//#define SMT_Encoding_Debug_On

typedef boost::tokenizer<boost::char_separator<char> > tokenizer;

std::list<nd_parameter> NoiseData_var;
std::string NoiseDataVar_StateVarName;
double NoiseDataVar_StartIteration;
double NoiseDataVar_EndIteration;
double NoiseDataVar_MinValue;
double NoiseDataVar_MaxValue;
double Sampling_Jitter;

using namespace std;

int smt_generator(hybrid_automata::ptr& my_ha, user_inputs::ptr& userInputs,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog, int bound,
		string output_filename) {

	//string output_filename = userInputs->getOutputFilename();
	//int bound = userInputs->getUpperBound();

	//Jay: Creating a SMT-constraints file

	ofstream smtfile;

	smtfile.open(output_filename.c_str());
	
	//Jay: Make sure that file has been created properly

	if (smtfile.is_open()) {

		std::cout << "\nFile " << output_filename << " created .....\n";

	} else {
		std::cout << "Error opening file: " << output_filename;
	}

	//This array stores the number of version required for each controller intermediate variable required

	//Controller Var: u, command_to_heater, off_counter, on_counter, chatter_detect

	//Jay: Generating SMT Coding

	initialize_Noiseparameters(userInputs);

	print_header(smtfile);

	print_declaration(smtfile, userInputs, bound, plant_vars, control_prog);

	print_flowEquation(my_ha, smtfile, plant_vars);

	print_initialState(my_ha, smtfile, plant_vars, control_prog);

	print_firstLoop(smtfile, my_ha, userInputs, plant_vars);

	print_nextLoops(smtfile, my_ha, bound, userInputs, plant_vars,
			control_prog);

	print_specification(smtfile, bound, userInputs, plant_vars);

	print_footer(smtfile);

	smtfile.close();

	return 1;

}

void print_header(ofstream &outputfile) {

	//Jay: Head section of SMT file

	outputfile << "(set-logic QF_NRA_ODE)\n";

}

void print_declaration(std::ofstream &outputfile, user_inputs::ptr& userInputs,
		int bound, struct plant_variables plant_vars,
		controller_program::ptr& control_prog) {

	int index_var;
	int i;

	//Jay: Print Control and Uncontrolled variables of Plant

	std::list<struct variablesTypes>::iterator it_control_var;

	int lower_bound;
	double upper_bound;

	//Variable Initialization for Sampling Jitter
	Sampling_Jitter = userInputs->getSamplingJitter();

#ifdef SMT_Encoding_Debug_On
	cout << " Sampling Jitter:: " << Sampling_Jitter
	<< endl;
#endif

	for (it_control_var = plant_vars.control_var.begin();
			it_control_var != plant_vars.control_var.end(); ++it_control_var) {
		outputfile << "(declare-fun " << (*it_control_var).var_name
				<< " () Real [" << (*it_control_var).lbound << ", "
				<< (*it_control_var).ubound << "])\n";

		//Storing bound in temp_var
		//lower_bound = (*it_control_var).lbound;
		//upper_bound = (*it_control_var).ubound;
	}

	for (it_control_var = plant_vars.uncontrol_var.begin();
			it_control_var != plant_vars.uncontrol_var.end();
			++it_control_var) {
		outputfile << "(declare-fun " << (*it_control_var).var_name
				<< " () Real [" << (*it_control_var).lbound << ", "
				<< (*it_control_var).ubound << "])\n";
	}

	//Jay: Print Clock variables

	outputfile << "(declare-fun lt () Real [0.000000, "
			<< (userInputs->getSampleTime() + Sampling_Jitter) << "])\n";
	outputfile << "(declare-fun gt () Real [0.000000, "
			<< userInputs->getTimeHorizon() << "])\n";

	for (index_var = 0; index_var <= bound; index_var++) {

		//Declaration of Control Program variables
		std::list<variablesContorller> interVar;
		interVar = control_prog->getIntermediateVariables();

		//Intermediate Variables
		for (std::list<variablesContorller>::iterator it = interVar.begin();
				it != interVar.end(); it++) {
			//std::cout <<"\t\t" <<(*it).first << "\t" <<(*it).second << std::endl;
			outputfile << "(declare-fun " << (*it).var_name << "_" << index_var
					<< " () " << (*it).var_type << " [" << (*it).lbound << ", "
					<< (*it).ubound << "] )\n";
		}

		std::list<variablesContorller> inputVar;
		inputVar = control_prog->getInputVariables();

		//Input Variables
		for (std::list<variablesContorller>::iterator it = inputVar.begin();
				it != inputVar.end(); it++) {
			//std::cout <<"\t\t" <<(*it).first << "\t" <<(*it).second << std::endl;

			//Print only if it's not a plant variable
			if (IsPlantVar((*it).var_name, plant_vars) == 0) {
				outputfile << "(declare-fun " << (*it).var_name << "_"
						<< index_var << " () " << (*it).var_type << " ["
						<< (*it).lbound << ", " << (*it).ubound << "] )\n";
			}

		}

		std::list<variablesContorller> outputVar;
		outputVar = control_prog->getOutputVariables();

		//Output Variables
		for (std::list<variablesContorller>::iterator it = outputVar.begin();
				it != outputVar.end(); it++) {

			//Print only if it's not a plant variable
			if (IsPlantVar((*it).var_name, plant_vars) == 0) {
				outputfile << "(declare-fun " << (*it).var_name << "_"
						<< index_var << " () " << (*it).var_type << " ["
						<< (*it).lbound << ", " << (*it).ubound << "] )\n";
			}

		}

		for (it_control_var = plant_vars.control_var.begin();
				it_control_var != plant_vars.control_var.end();
				++it_control_var) {
			outputfile << "(declare-fun " << (*it_control_var).var_name << "_"
					<< index_var << "_0 () Real [" << (*it_control_var).lbound
					<< ", " << (*it_control_var).ubound << "])\n";
			outputfile << "(declare-fun " << (*it_control_var).var_name << "_"
					<< index_var << "_t () Real [" << (*it_control_var).lbound
					<< ", " << (*it_control_var).ubound << "])\n";
		}

		for (it_control_var = plant_vars.uncontrol_var.begin();
				it_control_var != plant_vars.uncontrol_var.end();
				++it_control_var) {
			outputfile << "(declare-fun " << (*it_control_var).var_name << "_"
					<< index_var << "_0 () Real [" << (*it_control_var).lbound
					<< ", " << (*it_control_var).ubound << "])\n";
			outputfile << "(declare-fun " << (*it_control_var).var_name << "_"
					<< index_var << "_t () Real [" << (*it_control_var).lbound
					<< ", " << (*it_control_var).ubound << "])\n";
		}

		//Jay: Time Variables

		outputfile << "(declare-fun lt_" << index_var
				<< "_0 () Real [0.000000, "
				<< (userInputs->getSampleTime() + Sampling_Jitter) << "])\n";
		outputfile << "(declare-fun lt_" << index_var
				<< "_t () Real [0.000000, "
				<< (userInputs->getSampleTime() + Sampling_Jitter) << "])\n";
		outputfile << "(declare-fun gt_" << index_var
				<< "_0 () Real [0.000000, " << userInputs->getTimeHorizon()
				<< "])\n";
		outputfile << "(declare-fun gt_" << index_var
				<< "_t () Real [0.000000, " << userInputs->getTimeHorizon()
				<< "])\n";

		//Jay: Last iteration time variable,
		//rest all have value same as Sampling time

		if (index_var == bound) {

			outputfile << "(declare-fun time_" << index_var
					<< " () Real [0.000000, "
					<< (userInputs->getSampleTime() + Sampling_Jitter)
					<< "])\n";
		} else if (index_var == 0) {
			outputfile << "(declare-fun time_" << index_var << " () Real ["
					<< (userInputs->getReleaseTime() - Sampling_Jitter) << ", "
					<< (userInputs->getReleaseTime() + Sampling_Jitter)
					<< "])\n";
		} else {
			outputfile << "(declare-fun time_" << index_var << " () Real ["
					<< (userInputs->getSampleTime() - Sampling_Jitter) << ", "
					<< (userInputs->getSampleTime() + Sampling_Jitter)
					<< "])\n";

		}
		//Jay: Mode Variable
		//Assumption: For single mode continuous plant this is valid,
		//will be dynamic for multi-mode systems

		outputfile << "(declare-fun mode_" << index_var
				<< " () Real [1.000000, 1.000000])\n";

		//Variable for Noise parameter
		if ((index_var >= NoiseDataVar_StartIteration)
				&& (index_var <= NoiseDataVar_EndIteration)) {
			outputfile << "(declare-fun Noise_" << NoiseDataVar_StateVarName
					<< "_" << (index_var - 1) << " () Real ["
					<< NoiseDataVar_MinValue << ", " << NoiseDataVar_MaxValue
					<< "])\n";
		}

	}

}

void initialize_Noiseparameters(user_inputs::ptr& userInputs) {

	NoiseData_var = userInputs->getNoiseData();
	double SamplingTime = userInputs->getSampleTime();

	for (std::list<nd_parameter>::iterator it = NoiseData_var.begin();
			it != NoiseData_var.end(); it++) {

		nd_parameter nd = (*it);

		NoiseDataVar_StateVarName = nd.nd_variable_name;
		NoiseDataVar_StartIteration = floor((nd.start_time) / SamplingTime);
		NoiseDataVar_EndIteration = ceil((nd.end_time) / SamplingTime);
		NoiseDataVar_MinValue = nd.value1;
		NoiseDataVar_MaxValue = nd.value2;

	}
#ifdef SMT_Encoding_Debug_On

	cout << " Noise parameters:" << endl << " StateVarName::  "
	<< NoiseDataVar_StateVarName << " StartIteration:: "
	<< NoiseDataVar_StartIteration << " EndIteration:: "
	<< NoiseDataVar_EndIteration << " MinValue:: "
	<< NoiseDataVar_MinValue << " MaxValue:: " << NoiseDataVar_MaxValue
	<< endl;

#endif

}

void print_flowEquation(hybrid_automata::ptr& my_ha, std::ofstream &outputfile,
		struct plant_variables plant_vars) {

	std::list<struct variablesTypes>::iterator it_control_var;

//Definition of Flow Equation

//Constant dynamics for clock variables
	outputfile << "(define-ode flow_1 ((= d/dt[gt] 1) (= d/dt[lt] 1) ";

//std::cout << "Automaton name=" << my_ha->getName() << std::endl;
//my_ha->print_var_mapping();
//std::cout<<"List of Locations of the automata"<<std::endl;
	for (unsigned int i = 0; i < my_ha->getTotalLocations(); i++) {
		//std::cout << "loc_id=" << i << " Loc Name="
		//		<< my_ha->getLocation(i)->getName() << std::endl;
		safe_location::ptr my_loc = my_ha->getLocation(i);

#ifdef SMT_Encoding_Debug_On
		std::cout << "Flow Equations: " << std::endl;

#endif
		std::list<flow_equation> infix_deriv = my_loc->getDerivatives();
		for (std::list<flow_equation>::iterator it = infix_deriv.begin();
				it != infix_deriv.end(); it++) {
			outputfile << InfixToPrefix((*it).derivative) << " ";
		}

		/*std::list<std::string> deriv_str = my_loc->getDerivatives();
		 for (std::list<std::string>::iterator it = deriv_str.begin();
		 it != deriv_str.end(); it++) {
		 outputfile << InfixToPrefix((*it)) << " ";
		 }*/
	}

//outputfile << "(= d/dt[temperature] (* 0.5 (- u temperature))) ";

//Zero Dynamics for Un-controlled Variable
	for (it_control_var = plant_vars.uncontrol_var.begin();
			it_control_var != plant_vars.uncontrol_var.end();
			++it_control_var) {
		outputfile << "(= d/dt[" << (*it_control_var).var_name << "] 0)";
	}

	outputfile << "))\n";

}

void print_initialState(hybrid_automata::ptr& my_ha, std::ofstream &outputfile,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog) {

	std::list<struct variablesTypes>::iterator it_control_var;

	std::list<struct variablesTypes>::iterator it_uncontrol_var;

//Initial State

	outputfile << "(assert (and ";

//Clock variables are initialized with zero
	outputfile << "(= lt_0_0 0) (= gt_0_0 0) ";

//Jay: Missing Initial values of Plant variables
//Fixing: Initial state value

// Initial Symbolic state(s):

	std::list<initial_sym_state::ptr> init_sym_states =
			my_ha->getInitial_Location();
	for (std::list<initial_sym_state::ptr>::iterator it =
			init_sym_states.begin(); it != init_sym_states.end(); it++) {
		//std::cout << "\t\t Initial Loc-ID: " << (*it)->getLocId() << std::endl;
		std::list<std::string> init_Set_str = (*it)->getInitialSet();

		std::list<std::string> prefix_init_Set_str =
				(*it)->getPrefixInitialSet();
		//std::cout << "\n\t\t Initial Set (Prefix): " << std::endl;
		for (std::list<std::string>::iterator it_init_set =
				prefix_init_Set_str.begin();
				it_init_set != prefix_init_Set_str.end(); it_init_set++) {
			//std::cout << "\t\t\t\t" << (*it_init_set) << std::endl;

			string processed_string = processInitSet((*it_init_set),
					plant_vars);

			outputfile << "(" << processed_string << ")";

		}
	}

//Print mode:
	outputfile << "(= mode_0 1) ";

//Initializing Control Program variables Input variables(those are not part of plant state

	std::string temp_variable_name;
	std::list<variablesContorller> inputVar;
	inputVar = control_prog->getInputVariables();
	for (std::list<variablesContorller>::iterator var_it = inputVar.begin();
			var_it != inputVar.end(); var_it++) {
		temp_variable_name = (*var_it).var_name;

		if (AliasedPlantVar(temp_variable_name, plant_vars) == "No_match") {
			outputfile << "(= " << temp_variable_name << "_0 0 ) ";
		}

	}

	/*std::list<std::pair<std::string, std::string> > interVar;
	 interVar = control_prog->getIntermediateVariables();

	 //Jay: Intermediate variable should not assign any initial value

	 std::list<std::pair<std::string, std::string> > inputVar;
	 inputVar = control_prog->getInputVariables();

	 //Input Variables
	 for (std::list<std::pair<std::string, std::string> >::iterator it =
	 inputVar.begin(); it != inputVar.end(); it++) {
	 //Jay: Input variable also contains Plant state variables,
	 //don't initialize them with zero value

	 if (IsPlantVar((*it).second, plant_vars) == 0) {
	 outputfile << "(= " << (*it).second << "_0 0 ) ";

	 }

	 }

	 std::list<std::pair<std::string, std::string> > outputVar;
	 outputVar = control_prog->getOutputVariables();

	 //Jay: No need to give Initial value to output variable*/

//outputfile << " )) \n";
	outputfile << " \n ";
}

void print_firstLoop(std::ofstream &outputfile, hybrid_automata::ptr& my_ha,
		user_inputs::ptr& userInputs, struct plant_variables plant_vars) {

	std::list<struct variablesTypes>::iterator it_control_var;

	std::list<struct variablesTypes>::iterator it_uncontrol_var;

//outputfile << "(assert (and ";

//For k=0

//Jay: Fixme: Assuming single flow equation

//Flow()

//Constraints for constant dynamics

	outputfile << "(= lt_0_t (+ lt_0_0 (* 1 " << userInputs->getReleaseTime()
			<< "))) ";
	outputfile << "(= gt_0_t (+ gt_0_0 (* 1 " << userInputs->getReleaseTime()
			<< "))) ";

	for (unsigned int i = 0; i < my_ha->getTotalLocations(); i++) {

		safe_location::ptr my_loc = my_ha->getLocation(i);

		std::list<flow_equation> infix_deriv = my_loc->getDerivatives();
		for (std::list<flow_equation>::iterator it = infix_deriv.begin();
				it != infix_deriv.end(); it++) {
			if ((*it).isConstant_dynamic) {

				outputfile << "(= " << (*it).varName << "_0_t (+ "
						<< (*it).varName << "_0_0 (* " << (*it).RHSexpression
						<< " " << userInputs->getReleaseTime() << ")))";
			}
		}

	}

	for (it_uncontrol_var = plant_vars.uncontrol_var.begin();
			it_uncontrol_var != plant_vars.uncontrol_var.end();
			++it_uncontrol_var) {

		outputfile << "(= " << (*it_uncontrol_var).var_name << "_0_t (+ "
				<< (*it_uncontrol_var).var_name << "_0_0 (* 0 "
				<< userInputs->getReleaseTime() << ")))";

	}

//outputfile << " ))\n";
	outputfile << " \n ";

//outputfile << "(assert ";

	outputfile << "(= [gt_0_t lt_0_t ";

//Controlled variable

	for (it_control_var = plant_vars.control_var.begin();
			it_control_var != plant_vars.control_var.end(); ++it_control_var) {
		outputfile << (*it_control_var).var_name << "_0_t ";
	}

	for (it_uncontrol_var = plant_vars.uncontrol_var.begin();
			it_uncontrol_var != plant_vars.uncontrol_var.end();
			++it_uncontrol_var) {
		outputfile << (*it_uncontrol_var).var_name << "_0_t ";
	}

	outputfile << "]";

	outputfile << " (integral 0. time_0 [gt_0_0 lt_0_0 ";

//Controlled variable
	for (it_control_var = plant_vars.control_var.begin();
			it_control_var != plant_vars.control_var.end(); ++it_control_var) {
		outputfile << (*it_control_var).var_name << "_0_0 ";
	}

	for (it_uncontrol_var = plant_vars.uncontrol_var.begin();
			it_uncontrol_var != plant_vars.uncontrol_var.end();
			++it_uncontrol_var) {
		outputfile << (*it_uncontrol_var).var_name << "_0_0 ";
	}

	outputfile << "]";

	outputfile << " flow_1)) ";

//outputfile << ") \n";
	outputfile << " \n ";

//Jay: 	In first iteration, plant flow shall continue with initial state
//		till Actuation Release(Delay) time of controller

//Invariant

//Jay: Commented Invariant as time variable has been already constraints
	/*

	 outputfile << "(assert (and ";

	 outputfile << "(forall_t 1 [0 time_0] (<= lt_0_t "
	 << userInputs->getReleaseTime() << ")) (<= lt_0_t "
	 << userInputs->getReleaseTime() << ") (<= lt_0_0 "
	 << userInputs->getReleaseTime() << ") ";

	 outputfile << " )) \n";
	 */

}

void print_nextLoops(std::ofstream &outputfile, hybrid_automata::ptr& my_ha,
		int bound, user_inputs::ptr& userInputs,
		struct plant_variables plant_vars,
		controller_program::ptr& control_prog) {

//Variables used for Indexing
	int index_var;
	int i;

	std::list<struct variablesTypes>::iterator it_control_var;
	std::list<struct variablesTypes>::iterator it_uncontrol_var;

//Condition -

	for (i = 1; i <= bound; i++) {
		//Transition

		//outputfile << "(assert (and ";

		//Guard Condition and resets
		if (i == 1) {

			//Jay: 	In first iteration, plant flow shall continue with initial state
			//		till Actuation Release(Delay) time of controller
			outputfile << "(= mode_" << i << " 1) (= lt_" << (i - 1) << "_t "
					<< userInputs->getReleaseTime() << ") (= gt_" << i
					<< "_0 gt_" << (i - 1) << "_t) (= lt_" << i << "_0 0) ";
		} else {
			//Jay: 	For rest of the iterations, plant flow shall continue with initial state
			//		till Actuation Release(Delay) time of controller
			outputfile << "(= mode_" << i << " 1) (<= lt_" << (i - 1) << "_t "
					<< (userInputs->getSampleTime() + Sampling_Jitter)
					<< ") (= gt_" << i << "_0 gt_" << (i - 1) << "_t) (= lt_"
					<< i << "_0 0) ";

		}

		//outputfile << " ))\n";
		outputfile << " \n ";

		//outputfile << "(assert (and ";

		for (it_control_var = plant_vars.control_var.begin();
				it_control_var != plant_vars.control_var.end();
				++it_control_var) {

			//Maintain plant state variable for next iteration with
			//reset function

			//Do not reset plant variable
			//(if its also output of controller i.e. counter variable)

			if (IsVariable((*it_control_var).var_name, control_prog) != 3
					&& IsVariable(("next_" + (*it_control_var).var_name),
							control_prog) != 3) {

				if ((NoiseDataVar_StateVarName == (*it_control_var).var_name)
						&& (i >= NoiseDataVar_StartIteration)
						&& (i <= NoiseDataVar_EndIteration)) {
					outputfile << "(= " << (*it_control_var).var_name << "_"
							<< i << "_0 (+ " << (*it_control_var).var_name
							<< "_" << i - 1 << "_t Noise_"
							<< NoiseDataVar_StateVarName << "_" << i - 1
							<< " ) )";
				} else {
					outputfile << "(= " << (*it_control_var).var_name << "_"
							<< i << "_0 " << (*it_control_var).var_name << "_"
							<< i - 1 << "_t)";
				}
			}
		}

		//outputfile << " ))\n";
		outputfile << " \n ";

		//Controller Execution: constraints in SSA form

		print_ControllerConstraints(outputfile, i, plant_vars, control_prog);

		//Flow constraint

		//Jay - Assumption: Single Flow constraints

		//outputfile << "(assert (and ";

		//For k=0

		//Jay: Fixme: Assuming single flow equation

		//Flow()

		//Constraints for constant dynamics

		outputfile << "(= lt_" << i << "_t (+ lt_" << i << "_0 (* 1 time_" << i
				<< " ))) ";
		outputfile << "(= gt_" << i << "_t (+ gt_" << i << "_0 (* 1 time_" << i
				<< " ))) ";

		for (unsigned int i = 0; i < my_ha->getTotalLocations(); i++) {

			safe_location::ptr my_loc = my_ha->getLocation(i);

			std::list<flow_equation> infix_deriv = my_loc->getDerivatives();
			for (std::list<flow_equation>::iterator it = infix_deriv.begin();
					it != infix_deriv.end(); it++) {
				if ((*it).isConstant_dynamic) {

					if (i == bound) {
						outputfile << "(= " << (*it).varName << "_" << i
								<< "_t (+ " << (*it).varName << "_" << i
								<< "_0 (* " << (*it).RHSexpression << " "
								<< userInputs->getSampleTime() << " )))";
					} else {
						outputfile << "(= " << (*it).varName << "_" << i
								<< "_t (+ " << (*it).varName << "_" << i
								<< "_0 (* " << (*it).RHSexpression << " time_"
								<< i << " )))";
					}
				}
			}

		}

		for (it_uncontrol_var = plant_vars.uncontrol_var.begin();
				it_uncontrol_var != plant_vars.uncontrol_var.end();
				++it_uncontrol_var) {

			if (i == bound) {

				outputfile << "(= " << (*it_uncontrol_var).var_name << "_" << i
						<< "_t (+ " << (*it_uncontrol_var).var_name << "_" << i
						<< "_0 (* 0 " << userInputs->getSampleTime() << " )))";
			} else {
				outputfile << "(= " << (*it_uncontrol_var).var_name << "_" << i
						<< "_t (+ " << (*it_uncontrol_var).var_name << "_" << i
						<< "_0 (* 0 time_" << i << " )))";
			}

		}

		//outputfile << " ))\n";
		outputfile << " \n ";

		//outputfile << "(assert ";

		outputfile << "(= [gt_" << i << "_t lt_" << i << "_t ";

		//Controlled variable

		for (it_control_var = plant_vars.control_var.begin();
				it_control_var != plant_vars.control_var.end();
				++it_control_var) {
			outputfile << (*it_control_var).var_name << "_" << i << "_t ";
		}

		for (it_uncontrol_var = plant_vars.uncontrol_var.begin();
				it_uncontrol_var != plant_vars.uncontrol_var.end();
				++it_uncontrol_var) {
			outputfile << (*it_uncontrol_var).var_name << "_" << i << "_t ";
		}

		outputfile << "]";

		outputfile << " (integral 0. time_" << i << " [gt_" << i << "_0 lt_"
				<< i << "_0 ";

		//Controlled variable
		for (it_control_var = plant_vars.control_var.begin();
				it_control_var != plant_vars.control_var.end();
				++it_control_var) {
			outputfile << (*it_control_var).var_name << "_" << i << "_0 ";
		}

		for (it_uncontrol_var = plant_vars.uncontrol_var.begin();
				it_uncontrol_var != plant_vars.uncontrol_var.end();
				++it_uncontrol_var) {
			outputfile << (*it_uncontrol_var).var_name << "_" << i << "_0 ";
		}

		outputfile << "]";

		outputfile << " flow_1)) ";

		//outputfile << " )\n";
		outputfile << " \n ";

		//Jay: Invariant has been removed except last iteration

		//(forall_t 1 [0 time_1] (<= lt_1_t 0.2))

		if (i == bound) {

			//outputfile << "(assert (and ";

			outputfile << "(forall_t 1 [0 time_" << i << "] (<= lt_" << i
					<< "_t " << (userInputs->getSampleTime() + Sampling_Jitter)
					<< ")) ";

			//outputfile << " ))\n";
			outputfile << "  \n ";
		}

		//Condition -

		//(<= lt_1_t 0.2) (<= lt_1_0 0.2) (= mode_2 1)

		//outputfile << "(assert (and ";

		if (i == bound) {
			outputfile << "(<= lt_" << i << "_t "
					<< (userInputs->getSampleTime() + Sampling_Jitter)
					<< ") (<= lt_" << i << "_0 "
					<< (userInputs->getSampleTime() + Sampling_Jitter)
					<< ") (= mode_" << i << " 1) ";
		} else {
			outputfile << "(<= lt_" << i << "_t "
					<< (userInputs->getSampleTime() + Sampling_Jitter)
					<< ") (<= lt_" << i << "_0 "
					<< (userInputs->getSampleTime() + Sampling_Jitter)
					<< ") (= mode_" << i + 1 << " 1) ";
		}

		//outputfile << " ))\n";
		outputfile << " \n ";

	}

}

void print_specification(std::ofstream &outputfile, int bound,
		user_inputs::ptr& userInputs, struct plant_variables plant_vars) {

	std::list<std::string> prefixGoal = userInputs->getGoalProperty_prefix();

//outputfile << "(assert (and ";

	for (std::list<std::string>::iterator itgoal = prefixGoal.begin();
			itgoal != prefixGoal.end(); itgoal++) {

		std::string processed_goal_str = ProcessGoalProperty((*itgoal),
				plant_vars, bound);

		outputfile << processed_goal_str;

	}

	outputfile << " ))\n ";

//infixtoprefix(userInputs->getGoalProperty(), PreStr);
//cout << "\nGoal (Prefix ): " << PreStr<<std::endl;

//outputfile << "( " << userInputs->getGoalProperty() << " )\n";

//	outputfile << "(>= gt_" << bound << "_t " << userInputs->getSampleTime()
//			<< " ) )))\n";
//outputfile << "(< temperature_" << bound << "_t 52 ) )))\n";

}

void print_footer(std::ofstream &outputfile) {
	outputfile << "(check-sat)\n";
	outputfile << "(exit)";

}

int IsPlantVar(std::string Varname, struct plant_variables plant_vars) {

	std::list<struct variablesTypes>::iterator it_control_var;

//Controlled variable
	for (it_control_var = plant_vars.control_var.begin();
			it_control_var != plant_vars.control_var.end(); ++it_control_var) {

		if (Varname == (*it_control_var).var_name) {
			return 1;
		}
	}

	std::list<struct variablesTypes>::iterator it_uncontrol_var;

//Un-Controlled variable
	for (it_uncontrol_var = plant_vars.uncontrol_var.begin();
			it_uncontrol_var != plant_vars.uncontrol_var.end();
			++it_uncontrol_var) {

		if (Varname == (*it_uncontrol_var).var_name) {
			return 2;
		}
	}

	return 0;
}

string processInitSet(string init_set_string,
		struct plant_variables plant_vars) {

	std::string processed_str;

//Use space as a separator
	boost::char_separator<char> sep(" ");

	tokenizer tok(init_set_string, sep);

	for (tokenizer::iterator tok_it = tok.begin(); tok_it != tok.end();
			++tok_it) {
		//cout << *beg << "\n";

		std::string tok_str = (*tok_it);

		//Check if it's ==, then replace it with =

		if (tok_str == "==") {
			tok_str = "=";
		} else if (IsPlantVar(tok_str, plant_vars)) {
			tok_str += "_0_0";

		}

		processed_str += tok_str + " ";
	}

	return processed_str;

}

std::string ProcessGoalProperty(string init_set_string,
		struct plant_variables plant_vars, int index) {

	std::string index_str = boost::lexical_cast<std::string>(index);

	std::string processed_str = "(";

//Use space as a separator
	boost::char_separator<char> sep(" ");

	tokenizer tok(init_set_string, sep);

	for (tokenizer::iterator tok_it = tok.begin(); tok_it != tok.end();
			++tok_it) {
		//cout << *beg << "\n";

		std::string tok_str = (*tok_it);

		//Check if it's ==, then replace it with =

		if (IsPlantVar(tok_str, plant_vars) || tok_str == "gt"
				|| tok_str == "lt") {
			tok_str = tok_str + "_" + index_str + "_t";

		}

		processed_str = processed_str + tok_str + " ";
	}

	processed_str += " )";

	return processed_str;

}
