//============================================================================
// Name        : SafeVerPC.cpp
// Tool Name   :  SaVerECS (Safety Verification of Embedded Control Software)
// Author      : Amit Gurung
// Version     :
// Copyright   : Copyright (C) 2018 : Formal Methods Laboratory, IIT Kharagpur, India
// Description : Testing project
//============================================================================

#ifndef MAX_STR_LENGTH
#define MAX_STR_LENGTH 1024
#endif

#define MAIN_DEBUG_ON

#include <iostream>
#include <omp.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <float.h>
#include <math.h>
#include "haslacParser.tab.h"
//#include "featureParser.tab.h"
//#include "spaceExOutputParser.tab.h"
//#include "drhParser.tab.h"
//#include "drhOutParser.tab.h"
//#include "featureCompute.h"
#include "structs.h"

// ************ More Header files for SafeVerPC *************************
#include "readCommandLine/readCommandLine.h"
#include "readCommandLine/user_inputs.h"
#include "utilities/verifier.h"
#include "coreSystem/plant_model/hybrid_automata.h"
#include "utilities/datastructure_plant.h"
#include "smtEncoding/smtScript.h"
#include "utilities/input_output.h"
#include "boost/timer/timer.hpp"
#include "coreSystem/controller_program/controller.h"

#include "utilities/utility_interfaces.h"
// ************ Header files:SafeVerPC *************************

extern FILE* haslacin;
//extern FILE* haslacout;
extern int haslacparse(void);

extern struct phaver* HA;
//extern struct feature* sysFeature;
//extern struct interval* featureRange;
//extern int kValue;
//struct phaver* featureHA;
struct identifier* modelList;
//struct identifier* featureList;

float maxNumber;

using namespace std;

int main(int argc, char *argv[]) {

	user_inputs::ptr user_Inputs = user_inputs::ptr(new user_inputs());
	try {
		std::cout << std::endl;
		std::cout
				<< "**** Running tool SaVerECS (Safety Verification of Embedded Control Software) ... ****"
				<< std::endl;
		readCommandLine(argc, argv, user_Inputs);
		//	std::cout<< "SafeVerPC command-line options successful!!!\n";
	} catch (...) {
		std::cout
				<< "\nTerminating SafeVerPC, caused due to error in command-line inputs.\n";
		std::cout
				<< "Try SafeVerPC --help to see the valid command-line options\n";
		exit(0);
	}

	//----------------------------------   Local Declarations  -----------------------------------
	int param_id;
	double samplingTime = 0.0F;
	double timeHorizon = 0.0F;
	char choice[2];
	char* featureName;
	char var[MAX_STR_LENGTH];
	struct identifier* id;
	char* syncLabel;
	int scenario = 1;
	int finalLocID = 0;

	//------------------------------    Choose from Model Library    -----------------------------

	char fileName[MAX_STR_LENGTH];
	//Take input of the input file from commandline
	std::strcpy(fileName, user_Inputs->getPlantFilename().c_str());

#ifdef MAIN_DEBUG_ON
	printf("[FV]: fileName = %s\n", fileName);
#endif

	haslacin = fopen(fileName, "r");
	setbuf(stdout, NULL);

#ifdef MAIN_DEBUG_ON
	printf("Model File Selected for reading!!\n");
#endif
	//---------------------------------------------------------------------------------------------
	//Parse the Hybrid Automaton as a HASLAC File
#ifdef MAIN_DEBUG_ON
	std::cout << "HASLAC input model: parsing ... " << std::endl;
#endif
	haslacparse();
	fclose(haslacin);
#ifdef MAIN_DEBUG_ON
	printf(
			"--------------------AUTOMATON H1: Before Splitting ----------------------\n");
	//	displayAutomaton(HA);
	printf(
			"--------------------AUTOMATON H1: Printed Successfully ------------------\n");
#endif
#ifdef  MAIN_DEBUG_ON
	std::cout
			<< "--------------------Displaying user's input parameters ----------------------\n";
	std::cout << "Maximum bound value for variables = "
			<< user_Inputs->getMaxValue() << std::endl;
	std::cout << "Sampling Time = " << user_Inputs->getSampleTime()
			<< std::endl;
	std::cout << "Release Time = " << user_Inputs->getReleaseTime()
			<< std::endl;
	std::cout << "Sampling Jitter = " << user_Inputs->getSamplingJitter()
			<< std::endl;
	std::cout << "Time horizon = " << user_Inputs->getTimeHorizon()
			<< std::endl;
	std::cout << "Precision = " << user_Inputs->getPrecision() << std::endl;

	std::cout << "Noise Data:" << std::endl;
	displayNDparams(user_Inputs->getNoiseData());
	std::cout << "Disturbance Data:" << std::endl;
	displayNDparams(user_Inputs->getDisturbanceData());

	std::cout << "Upper bound = " << user_Inputs->getUpperBound() << std::endl;
	std::cout << "Lower bound = " << user_Inputs->getLowerBound() << std::endl;

	std::cout << "deadline_miss : " << user_Inputs->getDeadlineMiss_m()
			<< " out of " << user_Inputs->getDeadlineMiss_n() << std::endl;

	display_MinMaxBounds(user_Inputs->getMinMax_Bounds());

	std::cout << "Plant file name = " << user_Inputs->getPlantFilename()
			<< std::endl;
	std::cout << "Controller file name = "
			<< user_Inputs->getControllerFilename() << std::endl;
	std::cout << "Configuration file name = "
			<< user_Inputs->getConfigFilename() << std::endl;
	std::list<std::string> infixGoal = user_Inputs->getGoalProperty_infix();
	std::list<std::string> prefixGoal = user_Inputs->getGoalProperty_prefix();

	std::cout << "Goal constraints(Infix):" << std::endl;
	for (std::list<std::string>::iterator itgoal = infixGoal.begin();
			itgoal != infixGoal.end(); itgoal++) {
		std::cout << "\t\t\t" << (*itgoal) << std::endl;
	}
	std::cout << "Goal constraints(Prefix):" << std::endl;
	for (std::list<std::string>::iterator itgoal = prefixGoal.begin();
			itgoal != prefixGoal.end(); itgoal++) {
		std::cout << "\t\t\t" << (*itgoal) << std::endl;
	}
	std::cout << "output file name = " << user_Inputs->getOutputFilename()
			<< std::endl;

	std::cout << "-------------Parameters Parsed Successfully -------------"
			<< std::endl;
#endif

//Try exploring the dynamics from the location
	hybrid_automata::ptr plant_ha = hybrid_automata::ptr(new hybrid_automata());

	struct plant_variables plant_vars;
	//std::list<struct variablesTypes> control_vars, uncontrol_vars;
	//populateDataPlant(HA, plant_ha, control_vars, uncontrol_vars, user_Inputs);//Plant_ha populated from HASLAC input file

	populateDataPlant(HA, plant_ha, plant_vars, user_Inputs);//Plant_ha populated from HASLAC input file

	try {
		/*
		 * Validating the user's input for correct variable names on:
		 * Goal property, noise-paramater and disturbance.
		 * ToDo
		 */

	} catch (...) {

	}

#ifdef MAIN_DEBUG_ON
	std::list<struct variablesTypes> plant_conVar, plant_unconVar;
	plant_conVar = plant_vars.control_var;
	plant_unconVar = plant_vars.uncontrol_var;
	std::cout << "List of Control Variables:" << std::endl;
	for (std::list<struct variablesTypes>::iterator it = plant_conVar.begin();
			it != plant_conVar.end(); it++) {
		std::cout << "\t\t" << (*it).var_name << "  [" << (*it).lbound << " , "
				<< (*it).ubound << "]" << std::endl;
	}
	std::cout << "List of UnControl Variables:" << std::endl;
	for (std::list<struct variablesTypes>::iterator it = plant_unconVar.begin();
			it != plant_unconVar.end(); it++) {
		std::cout << "\t\t" << (*it).var_name << "  [" << (*it).lbound << " , "
				<< (*it).ubound << "]" << std::endl;
	}

	display_safe_hybrid_automata(plant_ha);	//displaying the Plant Model
#endif

	controller_program::ptr control_prog = controller_program::ptr(
			new controller_program());
	try {
		populateDataController(control_prog, user_Inputs);//module to generate appropriate data structures for the controller program

#ifdef MAIN_DEBUG_ON
		control_prog->displayController();//displaying the Controller program in SSA form with detailed Variables
#endif

	} catch (...) {
		std::cout
				<< "\nTerminating tool FMSafe, caused due to error in conversion of Controller program into SSA file.\n";
		exit(0);
	}
	int lbound = user_Inputs->getLowerBound(), ubound =
			user_Inputs->getUpperBound();
	//int file_counter=1;
boost::timer::cpu_timer total_runTime;
total_runTime.start();//starting cpu timer to calculate total run time
	for (int bound = lbound; bound <= ubound; bound++) {
		int ch;
		string fileName = user_Inputs->getOutputFilename() + "_"
				+ std::to_string(bound) + ".smt2";
		smt_generator(plant_ha, user_Inputs, plant_vars, control_prog, bound,
				fileName);//main module that takes in ha and controller details to generate smt2 clauses
		ch = call_dReal(user_Inputs, fileName);
		if (ch) {	//satisfied indicate that it will generate Counter-example
			std::cout << "\nSafety violation detected in unrolling(bound): "
					<< bound << std::endl;
			string jsonFile = fileName + ".json";
			std::cout << "\nOutput file(" << jsonFile
					<< ") generated. To view the trace of counter example, visualize data.json in ODE_Visualization folder."
					<< std::endl;
			string vis_cmd= "cp "+jsonFile+" ../ODE_visualization/data.json & cd ../ODE_visualization; ./run_websvr.sh & echo Open localhost:8000. Once visualized, run ./shut_websvr.sh";
			int succ = system(vis_cmd.c_str());
	
			break;
		} else {
			std::cout << "\nSystem is SAFE for unrolling(bound): " << bound
					<< std::endl;
			string rm_json= "rm "+fileName + ".json";
			system(rm_json.c_str());
		}
	}
	total_runTime.stop();

	std::cout << "\nTotal Running Time (in seconds): "<<total_runTime.elapsed().wall / 1000000;
	return 0;
} //end of function main

