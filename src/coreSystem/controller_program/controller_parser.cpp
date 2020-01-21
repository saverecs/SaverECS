/*
 * controller_parser.cpp
 *
 *  Created on: 08-Jun-2018
 *      Author: amit
 */

#include "controller_parser.h"
#include <fstream>
#include <iomanip>
#include <sstream>
#include <iostream>
#include <stdlib.h>	//for use of system command

void generate_ssaFile(user_inputs::ptr& user_Inputs) {
	/*
	 *
	 1) clang -O1 -g -Xclang -emit-llvm -c benchmarks/mythermo1.c -o benchmarks/test.bc

	 2) opt -O1 -instnamer -mem2reg  -simplifycfg  -loops  -lcssa -loop-simplify -loop-rotate -loop-unroll -unroll-count=15
	  -unroll-allow-partial   benchmarks/test.bc  -o benchmarks/test1.bc

	 3) opt -O1  -load src/libTestPass.so -testPass benchmarks/test1.bc  -o benchmarks/test

	 *
	 */
	std::string st1, cmd1, st2, cmd2, st3, cmd3;
	int ret_flag;

	st1 = "clang -O1 -g -Xclang -emit-llvm -c ";
	cmd1.append(st1);
	st1 = user_Inputs->getControllerFilename();
	cmd1.append(st1);
	st1 = " -o lib/fmsafe_ssaFile.bc";	//Keeping the working directory and file as lib/fmsafe_ssaFile.bc
	cmd1.append(st1);
	//std::cout<<"Command 1 = "<<cmd1<<std::endl;
	//use system(cmd1) command to execute
	const char *st;
	st = cmd1.c_str();
	ret_flag = system(st); //calling clang to emit-llvm's IR of the input controller program file
	//std::cout<<"clang called: ret_flag = "<<ret_flag <<std::endl;
	/*
	 * If the command argument is a null pointer, a return value of zero indicates that no command processor is available.
	 * The return value is -1 if it wasn't possible to create the shell process, and otherwise is the status of the shell process.
	 * , for details on how this status code can be interpreted.
	 */
	if (ret_flag < 0){
		std::cout<<ret_flag<<": Error executing (clang) command for parsing Controller Program!!"<<std::endl;
		throw(new exception());
	}
	st2 = "opt -O1 -instnamer -mem2reg  -simplifycfg  -loops  -lcssa -loop-simplify -loop-rotate -loop-unroll -unroll-count=15 ";
	cmd2.append(st2);	//change "-unroll-count=3" number 3 to higher value if required
	//st2 = "-unroll-allow-partial -load lib/libControllerProgramPass.so -ssa lib/fmsafe_ssaFile.bc  -o lib/fmsafe_ssaFile";
	st2 = "-unroll-allow-partial  lib/fmsafe_ssaFile.bc  -o lib/fmsafe_ssaFile1.bc";
	cmd2.append(st2);
	//std::cout<<"Command 2 = "<<cmd2<<std::endl;
	//use system(cmd1) command to execute
	st = cmd2.c_str();
	ret_flag = system(st); //opt command for executing the optimization passes to llvm's IR and creating the bit code file
	// this output file can then be made to pass with our optimization pass.
	if (ret_flag < 0) {
		std::cout<< ret_flag<<":Error(1) executing optimization (LLVM) command for parsing Controller Program!!"<< std::endl;
		throw(new exception());
	}

	st3 = "opt -O1  -load lib/libTestPass.so -testPass lib/fmsafe_ssaFile1.bc  -o lib/fmsafe_ssaFile";

//	cmd3.append(st3);
	//std::cout<<"Command 2 = "<<cmd2<<std::endl;
	//use system(cmd1) command to execute
	//st = cmd3.c_str();
	st = st3.c_str();
	ret_flag = system(st);
	if (ret_flag < 0) {
		std::cout<< ret_flag<<":Error(2) executing optimization (LLVM) command for parsing Controller Program!!"<< std::endl;
		throw(new exception());
	}

//	cmd3.append("lli lib/fmsafe_ssaFile");
	//std::cout<<"Command 3 = "<<cmd3<<std::endl;
	//use system(cmd1) command to execute
//	st = cmd3.c_str();
//	system(st); //executing the bit code of the program. Not required for us
}

void read_ssaFile(controller_program::ptr& control_prog, user_inputs::ptr& user_Inputs) {
	int tot_intermediateVar, tot_inputVar, tot_outputVar;
	//std::string ssafile = "fmsafe_Out.ssa";
	//const char* ssafile = "fmsafe_Out.ssa";	//This is the Unoptimized fileName
	const char* ssafile = "fmsafe_optOut.ssa";		//This is the optimized fileName
	std::ifstream in(ssafile);//This is the file generated from running script to execute the libController pass

	if (in) {
		std::string line1;
		std::getline(in, line1); //Reading First Line for total intermediate, input and output variables
		std::istringstream row1(line1);
		row1 >> tot_intermediateVar; //Reading First value
		row1 >> tot_inputVar; //Reading Second value
		row1 >> tot_outputVar; //Reading Third value

		/*
		 * Reading the variable declaration lines containing "varType varName"
		 * in the order of intermediate, input and output variables in that order.
		 */
		std::string varType, varName;

		std::list<variablesContorller> intermediateVariables;

		//std::list<std::pair<std::string, std::string> > intermediateVariables;
		for (int i = 1; i <= tot_intermediateVar; i++) {
			std::getline(in, line1);
			std::istringstream data(line1);
			//std::pair<std::string, std::string> intermedVar;
			variablesContorller intermedVar;
			data >> varType;
			intermedVar.var_type = varType;
			//intermedVar.first = varType;
			data >> varName;
			//intermedVar.second = varName;
			intermedVar.var_name = varName;

			/*Note:
			 * ToDo We can think method to find out the bounds for intermediate variables also
			 * */
			intermedVar.lbound = -1 * user_Inputs->getMaxValue();
			intermedVar.ubound =  1 * user_Inputs->getMaxValue();

			intermediateVariables.push_back(intermedVar);
		}

		//std::string varType, varName;
		std::list<variablesContorller> inputVariables;
		//std::list<std::pair<std::string, std::string> > inputVariables;
		for (int i = 1; i <= tot_inputVar; i++) {
			std::getline(in, line1);
			std::istringstream data(line1);
			//std::pair<std::string, std::string> inputVar;
			variablesContorller inputVar;
			data >> varType;
			//inputVar.first = varType;
			inputVar.var_type = varType;
			data >> varName;
			//inputVar.second = varName;
			inputVar.var_name = varName;

	//Now search this variable name in our min_max_bounds data structure if found set this values otherwise set MaxValue
	//ToDo  remember our approach of aliasing variable (min_max_bounds may not have variable prefix with "next_ or state_". Need to search this as well
			std::list<min_max_bounds> mm_bounds = user_Inputs->getMinMax_Bounds();
			bool found = false;
			for (std::list<min_max_bounds>::iterator it=mm_bounds.begin(); it != mm_bounds.end();it++){
				std::string withNext =  "next_" + (*it).variable_name;
				std::string withState =  "state_" + (*it).variable_name;
				if (boost::iequals((*it).variable_name, varName) || boost::iequals(withNext, varName) || boost::iequals(withState, varName) ) {
					inputVar.lbound = (*it).minValue;
					inputVar.ubound = (*it).maxValue;
					found = true;
					break;
				}
			}
			if (!found){
				inputVar.lbound = -1 * user_Inputs->getMaxValue();
				inputVar.ubound =  1 * user_Inputs->getMaxValue();
			}
			inputVariables.push_back(inputVar);
		}

		//std::string varType, varName;
		//std::list<std::pair<std::string, std::string> > outputVariables;
		std::list<variablesContorller> outputVariables;
		for (int i = 1; i <= tot_outputVar; i++) {
			std::getline(in, line1);
			std::istringstream data(line1);
			//std::pair<std::string, std::string> outputVar;
			variablesContorller outputVar;
			data >> varType;
			//outputVar.first = varType;
			outputVar.var_type = varType;
			data >> varName;
			//outputVar.second = varName;
			outputVar.var_name = varName;

			//Now search this variable name in our min_max_bounds data structure if found set this values otherwise set MaxValue
			std::list<min_max_bounds> mm_bounds = user_Inputs->getMinMax_Bounds();
			bool found = false;
			for (std::list<min_max_bounds>::iterator it = mm_bounds.begin(); it != mm_bounds.end(); it++) {
				std::string withNext =  "next_" + (*it).variable_name;
				std::string withState =  "state_" + (*it).variable_name;
				if (boost::iequals((*it).variable_name, varName) || boost::iequals(withNext, varName) || boost::iequals(withState, varName) ) {
					outputVar.lbound = (*it).minValue;
					outputVar.ubound = (*it).maxValue;
					found = true;
					break;
				}
			}
			if (!found) {
				outputVar.lbound = -1 * user_Inputs->getMaxValue();
				outputVar.ubound = 1 * user_Inputs->getMaxValue();
			}

			outputVariables.push_back(outputVar);
		}

		control_prog->setIntermediateVariables(intermediateVariables);
		control_prog->setInputVariables(inputVariables);
		control_prog->setOutputVariables(outputVariables);

		//reading remaining Lines of SSA statements
		std::list<std::string> ssa_statements;
		int row = 0, col = 0;
		while (std::getline(in, line1)) {
			ssa_statements.push_back(line1);
		}
		control_prog->setSsaStatements(ssa_statements);
		std::cout << "\nController Program: parsing Done...\n";
	} else {
		std::cout << "\nSSA file of the Controller program not found!!!" << std::endl;
		throw(new exception());
	}
}
