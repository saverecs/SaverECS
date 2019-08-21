/*
 * user_inputs.h
 *
 *  Created on: 04-May-2018
 *      Author: amit
 */

#ifndef READCOMMANDLINE_USER_INPUTS_H_
#define READCOMMANDLINE_USER_INPUTS_H_

#include <string>
#include <list>
#include <iostream>
#include <boost/shared_ptr.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/tokenizer.hpp>
#include "utilities/datastructure_plant.h"
#include "utilities/utility_interfaces.h"



class user_inputs {
private:
	double max_value;
	std::list<min_max_bounds> MinMax_Bounds;	//min and max bounds for all variables supplied by the user
	double sample_time;			//used to store for sampling time
	double release_time;		//used to store for release time
	double sensing_time;		//used to store for delt_1
	double precision;			//used to store for precision for solver dReal
	int upper_bound;			//maximum upper bound for unrolling
	int lower_bound;			//lower bound for unrolling
	double time_horizon;		//total time bound
	std::string goal_property;	//string variable that will hold the goal property (for simple goal), for more complex property property can be used

	std::string noise_parameter;	//string inputed from the Command Line
	std::string disturbance_parameter;	//string inputed from the Command Line

	std::list<nd_parameter> noise_data;
	std::list<nd_parameter> disturbance_data;

	double deadline_miss_m;
	double deadline_miss_n;

	std::string plant_filename;
	std::string controller_filename;
	std::string config_filename;	//output file for future use
	std::string output_filename;	//output file that will hold the smt2 clauses
public:
	typedef boost::shared_ptr<user_inputs> ptr;
	const std::string& getConfigFilename() const;
	void setConfigFilename(const std::string& configFilename);
	const std::string& getControllerFilename() const;
	void setControllerFilename(const std::string& controllerFilename);

	std::list<std::string> getGoalProperty_infix();
	std::list<std::string> getGoalProperty_prefix();
	/*
	 * These set GoalProperty/NoiseInjection/Disturbance setter is to take input from the command line
	 */
	void setGoalProperty(const std::string& goalProperty);
	void setNoiseInjection(const std::string& noiseParams);
	void setDisturbance(const std::string& disturbanceParams);


	void setMinMax_Bounds(const std::list<min_max_bounds> MinMax_data);
	std::list<min_max_bounds> getMinMax_Bounds();

/*
 * These getter function can be use to access the formated Data structure for noise and disturbance for SMT encoding
 */	const std::list<nd_parameter>& getDisturbanceData() const;
	const std::list<nd_parameter>& getNoiseData() const;
	/*
	 * These set DisturbanceData and NoiseData are the private setter for the formated Data structure
	 */
	void setDisturbanceData(const std::list<nd_parameter>& disturbanceData);
	void setNoiseData(const std::list<nd_parameter>& noiseData);

	int getLowerBound() const;
	void setLowerBound(int lowerBound);
	const std::string& getOutputFilename() const;
	void setOutputFilename(const std::string& outputFilename);
	std::string getPlantFilename();
	void setPlantFilename(std::string plantFilename);
	double getSampleTime() const;
	void setSampleTime(double sampleTime);
	double getSamplingJitter() const;
	void setSamplingJitter(double sensingTime);
	double getTimeHorizon() const;
	void setTimeHorizon(double timeHorizon);
	int getUpperBound() const;
	void setUpperBound(int upperBound);
	double getMaxValue() const;
	void setMaxValue(double maxValue);
	double getReleaseTime() const;
	void setReleaseTime(double releaseTime);
	double getPrecision() const;
	void setPrecision(double precision);
	void setDeadlineMiss_m(double setdeadlinemiss_m);
	double getDeadlineMiss_m() const ;
	void setDeadlineMiss_n(double setdeadlinemiss_n);
	double getDeadlineMiss_n() const ;

};


#endif /* READCOMMANDLINE_USER_INPUTS_H_ */
