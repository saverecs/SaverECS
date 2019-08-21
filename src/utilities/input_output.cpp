/*
 * input_output.cpp
 *
 *  Created on: 03-Jul-2018
 *      Author: amit
 */

#include "input_output.h"
#include "utilities/datastructure_plant.h"
#include <string>
#include <iostream>
#include <fstream>      // std::ofstream
#include "boost/timer/timer.hpp"
#include <boost/algorithm/string.hpp>

#include <iomanip>
#include <sstream>
#include <stdlib.h>	//for use of system command


using namespace std;

/*
int call_dReal(user_inputs::ptr user_Inputs, std::string fileName, int bound) {

	std::string st1, cmd1;

	//system("touch sys_generated_tempfile.txt");

	st1 = "./bin/dReal ";
	cmd1.append(st1);
	//st1 = user_Inputs->getOutputFilename();
	st1 = fileName;
	cmd1.append(st1);
	st1 = " --visualize --precision ";
	cmd1.append(st1);
	st1 = std::to_string(user_Inputs->getPrecision());
	cmd1.append(st1);
	string sys_fileName;
	cmd1.append(" >> ");
	sys_fileName = "sys_generated_tempfile"+std::to_string(bound)+".txt";	//output of dReal re-directed to the file sys_generated_tempfile.txt
	cmd1.append(sys_fileName);
//	found_for_bound.sys_fileName = sys_fileName;
//	std::cout << "dReal Command  = " << cmd1 << std::endl;
	//use system(cmd1) command to execute
	const char *st;
	st = cmd1.c_str();
	//std::cout << "Running solver please wait ... " << std::endl;

	int sat_unsat;
//	boost::timer::cpu_timer dReal_runtime;
//	dReal_runtime.start();
	std::cout<<"Before calling dReal... "<<endl;
	system(st); //calling dReal solver to solve the SMT generated
//	dReal_runtime.stop();
	std::cout<<"st = "<<st<<endl;
	//const char* ssafile = "sys_generated_tempfile.txt";
//	const char* ssafile = sys_fileName;
//	std::ifstream in(ssafile); //This is the file generated from dReal output

	std::ifstream in(sys_fileName.c_str());

	std::string dReal_result;
	if (in) {
		std::string line1;
		std::getline(in, line1); //Reading First Line for total intermediate, input and output variables
		std::istringstream row1(line1);
		row1 >> dReal_result; //Reading First value
		std::cout<<"dReal_result = "<<dReal_result<<std::endl;
	}else{
		cout<<"File Opening Error!!!"<<std::endl;
	}
	if (boost::iequals(dReal_result, "unsat")){
		sat_unsat = 0;
	} else {
		sat_unsat = 1;
	}


	st1 = "rm " + sys_fileName;
	std::cout<<"st1 = "<<st1<<endl;
	//system("rm sys_generated_tempfile.txt");
	system(st1.c_str());


//	double wall_clock, user_clock, system_clock;
//	wall_clock = dReal_runtime.elapsed().wall / 1000000; //convert nanoseconds to milliseconds
//	user_clock = dReal_runtime.elapsed().user / 1000000;
//	system_clock = dReal_runtime.elapsed().system / 1000000;
//
//	double running_time = wall_clock / (double) 1000;	//convert milliseconds to seconds
//	found_for_bound.running_wall_time = running_time;
//	std::cout << "Boost/Wall clock time  taken: (in Seconds) = " << running_time;

	return sat_unsat;

}
*/


int call_dReal(user_inputs::ptr user_Inputs, std::string fileName) {

	std::string st1, cmd1;

	//system("touch sys_generated_tempfile.txt");

	st1 = "./bin/dReal ";
	cmd1.append(st1);
	//st1 = user_Inputs->getOutputFilename();
	st1 = fileName;
	cmd1.append(st1);
	st1 = " --visualize --precision ";
	cmd1.append(st1);
	st1 = std::to_string(user_Inputs->getPrecision());
	cmd1.append(st1);
	st1 = " >> sys_generated_tempfile.txt";	//output of dReal re-directed to the file sys_generated_tempfile.txt
	cmd1.append(st1);

//	std::cout << "dReal Command  = " << cmd1 << std::endl;
	//use system(cmd1) command to execute
	const char *st;
	st = cmd1.c_str();
	std::cout << "Running solver please wait ... " << std::endl;

	int sat_unsat;
	boost::timer::cpu_timer dReal_runtime;
	dReal_runtime.start();
	system(st); //calling dReal solver to solve the SMT generated
	dReal_runtime.stop();

	const char* ssafile = "sys_generated_tempfile.txt";
	std::ifstream in(ssafile); //This is the file generated from dReal output
	std::string dReal_result;
	if (in) {
		std::string line1;
		std::getline(in, line1); //Reading First Line for total intermediate, input and output variables
		std::istringstream row1(line1);
		row1 >> dReal_result; //Reading First value
	}

	if (boost::iequals(dReal_result, "unsat")){
		sat_unsat = 0;
	} else {
		sat_unsat = 1;
	}
	system("rm sys_generated_tempfile.txt");
	double wall_clock, user_clock, system_clock;
	wall_clock = dReal_runtime.elapsed().wall / 1000000; //convert nanoseconds to milliseconds
	user_clock = dReal_runtime.elapsed().user / 1000000;
	system_clock = dReal_runtime.elapsed().system / 1000000;

	double running_time = wall_clock / (double) 1000;	//convert milliseconds to seconds
	std::cout << "Boost/Wall clock time  taken: (in Seconds) = " << running_time;

	return sat_unsat;

}
