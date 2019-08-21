/*
 * readCommandLine.cpp
 *
 *  Created on: 03-May-2018
 *      Author: amit
 */

#include <iostream>
#include "readCommandLine.h"

using namespace std;
namespace po = boost::program_options;

void readCommandLine(int argc, char *argv[], user_inputs::ptr& userInputs) {

	//po::options_description desc("SafeVerPC options");
	po::options_description desc("SaVerECS options");
	po::variables_map vm;

	if (argc == 1) { //No argument::
		std::cout << "Missing arguments!\n";
		throw(new exception());
	}

	desc.add_options()("help,h", "produce help message")("max-value,m",
			po::value<double>(),
			"Assumed maximum [-m, +m] constant value that the plant and the controller can take")(
			"sampling-time,t", po::value<double>(),
			"Sets the sampling time of the controller")("release-time,r",
			po::value<double>()->default_value(0.0),
			"Sets the Sampling Jitter time of the controller")("sampling-jitter,d",
			po::value<double>(), "Sets the sensing time of the controller")(
			"precision", po::value<double>()->default_value(0.001),
			"set precision for the SMT solver (default 0.001)")("upper-bound,u",
			po::value<int>()->default_value(0),
			"Set the depth or upper-bound of exploration for unrolling")(
			"lower-bound,l", po::value<int>()->default_value(0),
			"Set the depth or lower-bound of exploration for unrolling")(
			"time-horizon,Z", po::value<double>(),
			"Set the global time horizon of computation.")("goal,F",
			po::value<std::string>(),
			"Goal property to test, syntax: 'expr-1 & expr-2'; For e.g. expr-1 is x>=2") //

	//("noise-timebound", po::value<std::string>(), "Sets the [start, end] time duration for injecting noise in the Plant. Syntax: 't1,t2' where t1 and t2 are start and end time")
	//("noise,N", po::value<std::string>(), "Noise injection to plant variables, syntax: 'expr-1 & expr-2'; For e.g. expr-1 is x1=2") //

	("noise-params", po::value<std::string>(),
			"Sets the noise injecting parameters, syntax: 'var1:[t1,t2]=>[n1,n2] & ...'"
					"where t1 and t2 are start and end time duration of the noise on var1 and the noise values can be fix [n1,n1] or range [n1,n2]")

	("disturbance", po::value<std::string>(),
			"Sets the disturbance parameters, syntax: 'var1:[t1,t2]=>[d1,d2] & ...'"
					"where t1 and t2 are start and end time duration the disturbance on var1 and the disturbance values can be fix [d1,d1] or range [d1,d2]")
	//Note that for the same variable we can repeat as "var1:[t3,t4]=>[d3,d3]" followed by "& var2:[t2,t4]=>[d4,d5]", etc...

//Remove 	("include-path,I", po::value<std::string>(), "include file path")
	("plant-file,p", po::value<std::string>(), "include plant model file")(
			"controller-file,c", po::value<std::string>(),
			"include controller C program file")("config-file,g",
			po::value<std::string>(),
			"include configuration file (for future use)")("output-file,o",
			po::value<std::string>(),
			"output file name for redirecting the outputs (example .smt2 file)");

	po::store(po::parse_command_line(argc, argv, desc), vm);
	po::notify(vm);

	std::string fileName;

	if (vm.count("help")) {
		std::cout << desc << "\n";
		exit(0);
		//return 0; //Just displaying the Help options and terminating the Project
	}

	if (vm.count("max-value")) {
		userInputs->setMaxValue((vm["max-value"].as<double>()));
		if (userInputs->getMaxValue() <= 0) { //for 0 or negative sampling-time
			std::cout
					<< "Invalid max-value option specified. A positive non-zero Maximum possible value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("sampling-time")) {
		userInputs->setSampleTime((vm["sampling-time"].as<double>()));
		if (userInputs->getSampleTime() <= 0) { //for 0 or negative sampling-time
			std::cout
					<< "Invalid sampling-time option specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("release-time")) {
		userInputs->setReleaseTime((vm["release-time"].as<double>()));
		if (userInputs->getReleaseTime() < 0) { //for 0 or negative sampling-time
			std::cout
					<< "Invalid release-time option specified. A zero or a positive value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("sampling-jitter")) {
		userInputs->setSamplingJitter((vm["sampling-jitter"].as<double>()));
		if (userInputs->getSamplingJitter() <= 0) { //for 0 or negative sampling-time
			std::cout
					<< "Invalid sampling-jitter option specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("precision")) {
		userInputs->setPrecision((vm["precision"].as<double>()));
		if (userInputs->getPrecision() <= 0) { //for 0 or negative precision
			std::cout
					<< "Invalid precision value specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("upper-bound")) {
		userInputs->setUpperBound((vm["upper-bound"].as<int>()));
		if (userInputs->getUpperBound() < 0) { //for 0 or negative sampling-time
			std::cout
					<< "Invalid upper-bound option specified. A zero or a positive value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("lower-bound")) {
		userInputs->setLowerBound((vm["lower-bound"].as<int>()));
		if (userInputs->getLowerBound() < 0) { //for 0 or negative sampling-time
			std::cout
					<< "Invalid lower-bound option specified. A zero or a positive value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("time-horizon")) {
		userInputs->setTimeHorizon((vm["time-horizon"].as<double>()));
		if (userInputs->getTimeHorizon() <= 0) { //for 0 or negative sampling-time
			std::cout
					<< "Invalid time-horizon option specified. A positive non-zero value expected.\n";
			throw(new exception());
		}
	}
	if (vm.count("goal")) {
		userInputs->setGoalProperty(vm["goal"].as<std::string>());
	}

	if (vm.count("noise-params")) {
		userInputs->setNoiseInjection(vm["noise-params"].as<std::string>());
	}

	if (vm.count("disturbance")) {
		userInputs->setDisturbance(vm["disturbance"].as<std::string>());
	}

	if (vm.count("deadline_miss_m")) {
			userInputs->setDeadlineMiss_m((vm["deadline_miss_m"].as<double>()));
	}

	if (vm.count("deadline_miss_n")) {
				userInputs->setDeadlineMiss_n((vm["deadline_miss_n"].as<double>()));
		}

	if (vm.count("plant-file")) {
		userInputs->setPlantFilename(vm["plant-file"].as<std::string>());
	} else {
		std::cout << "Missing Plant model file \n";
		throw(new exception());
	}
	if (vm.count("controller-file")) {
		userInputs->setControllerFilename(
				vm["controller-file"].as<std::string>());
	} else {
		std::cout << "Missing Controller C-program file \n";
		throw(new exception());
	}

	if (vm.count("config-file")) {
		userInputs->setConfigFilename(vm["config-file"].as<std::string>());
	}
	if (vm.count("output-file")) {
		userInputs->setOutputFilename(vm["output-file"].as<std::string>());
	} else {
		fileName = "out.smt2";
		userInputs->setOutputFilename(fileName); //default file is set to out.smt2
	}

	// ********************** Setting for Output file **********************************
//Note this should be used to include path for all input files but "paths are taken care by default by the OS"
	/*
	 std::string fullPath, fileWithPath;
	 const char *stFileNameWithPath;
	 if (vm.count("include-path")) {
	 fullPath = vm["include-path"].as<std::string>();
	 } else {
	 fullPath = "./"; //default file path
	 }
	 fileWithPath.append(fullPath);

	 if (vm.count("output-file")) {
	 fileName = vm["output-file"].as<std::string>();
	 userInputs.setOutputFilename(fileName);
	 } else {
	 fileName = "out.smt2";
	 userInputs.setOutputFilename(fileName);
	 }
	 fileWithPath.append(fileName);
	 stFileNameWithPath = fileWithPath.c_str(); //This can be used for setting inputs
	 */

	// ********************** Setting for Output file Done **********************************
	//--------

}
