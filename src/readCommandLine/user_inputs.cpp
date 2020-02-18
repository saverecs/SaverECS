/*
 * user_inputs.cpp
 *
 *  Created on: 04-May-2018
 *      Author: amit
 */


#include "user_inputs.h"
#include "maths/miscellaneous.h"
#include <fstream>

using namespace std;

const std::string& user_inputs::getConfigFilename() const {
	return config_filename;
}

void user_inputs::setConfigFilename(const std::string& configFilename) {
	config_filename = configFilename;

	/*
	 * #Possible values here are:
	 * 1) --MinMax-bounds of variables (plant and controller) 2)comments line begin with # or // 3) --max-value
	 * 4) --sampling-time 5) --release-time 6) --sampling-jitter  7) --upper-bound  8) --lower-bound
	 * 9) --time-horizon 10)  --goal   11) --noise-params 12 )  --disturbance
	 *
	 * Example file format:

		max-value = 100
		MinMax-bounds = "temperature:[0,100] & u:[20,100]"
		MinMax-bounds = "chat_detect:[0,10] & previous_cmd_to_heater:[0,5] & on_count:[0,25] & off_count:[0,25] & cmd_to_heater:[0,5]"
		sampling-time = 0.01
		release = 0.01
		sampling-jitter = 0.001
		time-horizon = 3
		upper-bound = 10
		lower-bound = 1
		noise-params ="temperature:[0.2,0.3]=>[7,19]"
		disturbance = "temperature:[0.2,0.3]=>[7,19]"
		goal ="temperature>52"
	 *
	 */


	const char* myfile = configFilename.c_str();
	std::ifstream in(myfile);
	std::list<std::string> eachline;//eachline is a single user's input parameter
	if (in) {
		std::string line1, emptyStr;
		//std::cout << "Configuration File's Output:" << std::endl;
		while (std::getline(in, line1)) {
			//if the first character is # or the first two characters is // then, skip this line
			string comment_char = line1.substr(0, 1);//if the first chars is "#"
			string comment_char2 = line1.substr(0, 2);//if the first two chars is "//"
			emptyStr = trim(line1);
			if (boost::iequals(comment_char, "#")) {
				// std::cout<<"Fount a Comment line: "<<line1<<std::endl;
			} else if (boost::iequals(comment_char2, "//")) {
				// std::cout<<"Fount a Comment line: "<<line1<<std::endl;
			} else if (emptyStr.length() != 0){
				eachline.push_back(trim(line1));
				//std::cout<<trim(line1)<<std::endl;
			}
		}
		//std::cout << "\nTotal parameters= "<<eachline.size()<<std::endl;
	} else {
		std::cout << "\nConfiguration file format is invalid!!!" << std::endl;
		throw(new exception());
	}

	std::list<min_max_bounds> MinMaxBounds, MinMaxBounds_temp;
	//Parsing each line (or user's argument) from the configuration file.
	bool found_first_time=true;
	for (std::list<std::string>::iterator it = eachline.begin(); it != eachline.end(); it++) {
		//std::cout<<(*it)<<std::endl;
		string user_args = (*it);
		//From the user_args find the first "=" sign and separate the args as LHS and RHS
		unsigned int pos_of_equal = user_args.find("=",0);	//Finds the first "=" sign in the string user_args starting from position 0
		string args_name = trim(user_args.substr(0,pos_of_equal));	// Since "pos_of_equal" gives one less than the size of the LHS word
		//std::cout<<"user_arg = "<<args_name<<std::endl;
		unsigned int start_pos = pos_of_equal+1;
		string args_value = trim(user_args.substr(start_pos));	//std::cout<<"user_value = "<<args_value<<std::endl;

		if (boost::iequals(args_name, "max-value")) {
			setMaxValue(std::stod(remove_quotes(args_value)));
		} else if (boost::iequals(args_name, "minmax-bounds")) {
			MinMaxBounds_temp = convertTo_MinMaxBounds(remove_quotes(args_value));
			if (found_first_time){//	found first time is true
				MinMaxBounds = MinMaxBounds_temp;
				found_first_time=false;
			}else{	//Append the min-max-bounds data if they occur more than once in the configuration file
				MinMaxBounds.insert(MinMaxBounds.end(), MinMaxBounds_temp.begin(), MinMaxBounds_temp.end());
			}
		} else if (boost::iequals(args_name, "sampling-time")) {
			setSampleTime(std::stod(args_value));
		} else if (boost::iequals(args_name, "release-time")) {
			setReleaseTime(std::stod(args_value));
		} else if (boost::iequals(args_name, "sampling-jitter")) {
			setSamplingJitter((std::stod(args_value)));
		} else if (boost::iequals(args_name, "sensing-time")) {
			setSamplingJitter((std::stod(args_value)));
		} else if (boost::iequals(args_name, "time-horizon")) {
			setTimeHorizon(std::stod(args_value));
		} else if (boost::iequals(args_name, "upper-bound")) {
			setUpperBound(std::stoi(args_value));
		} else if (boost::iequals(args_name, "lower-bound")) {
			setLowerBound(std::stoi(args_value));
		} else if (boost::iequals(args_name, "noise-params")) {
			setNoiseInjection(remove_quotes(args_value));
		} else if (boost::iequals(args_name, "disturbance")) {
			setDisturbance(remove_quotes(args_value));
		}
		else if (boost::iequals(args_name, "deadline_miss_m")) {
			setDeadlineMiss_m(std::stod(args_value));
						}
		else if (boost::iequals(args_name, "precision")) {
					setPrecision(std::stod(args_value));
								}
		else if (boost::iequals(args_name, "deadline_miss_n")) {
					setDeadlineMiss_n(std::stod(args_value));
								}
		else if (boost::iequals(args_name, "goal")) {
			setGoalProperty(remove_quotes(args_value));
		}

	}	//All user's arguments from the configuration file read
	setMinMax_Bounds(MinMaxBounds);

	std::cout << "\nConfiguration File: parsing Done...\n";
}

void user_inputs::setMinMax_Bounds(const std::list<min_max_bounds> MinMax_data){
	MinMax_Bounds = MinMax_data;
}
std::list<min_max_bounds> user_inputs::getMinMax_Bounds(){
	return MinMax_Bounds;
}

const std::string& user_inputs::getControllerFilename() const {
	return controller_filename;
}

void user_inputs::setControllerFilename(const std::string& controllerFilename) {
	controller_filename = controllerFilename;
}

std::list<std::string> user_inputs::getGoalProperty_infix() {
	std::list<std::string> infixGoal;
	std::string goalSt = goal_property;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(goalSt, sep);

	for (tokenizer::iterator tok_iter = tokens.begin();
			tok_iter != tokens.end(); ++tok_iter) {
		infixGoal.push_back((std::string) *tok_iter);
	}
	return infixGoal;
}
std::list<std::string> user_inputs::getGoalProperty_prefix() {
	std::string goalSt = goal_property;
	std::list<std::string> prefixGoal;

	std::list<std::string> all_args;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(goalSt, sep);

	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
		all_args.push_back((std::string) *tok_iter);
	}

	tokenizer::iterator tok_iter;
	std::string varname, tokString;
	unsigned int i;
	for(std::list<std::string>::iterator iter = all_args.begin(); iter!=all_args.end();iter++){
		tokString = *iter;	//each constraints
		std::string prefixStr;
		string operatorStr;
		if (tokString.find("<=")!=std::string::npos ){ // less than equal to constraint
			sep = boost::char_separator<char>("<=");
			operatorStr = " <= ";
		}else if (tokString.find(">=") != std::string::npos) { // greater than equal to constraint
			sep = boost::char_separator<char>(">=");
			operatorStr = " >= ";
		}else if (tokString.find(">") != std::string::npos) { // greater than equal to constraint
			sep = boost::char_separator<char>(">");
			operatorStr = " > ";
		}
		else if (tokString.find("<") != std::string::npos) { // greater than equal to constraint
			sep = boost::char_separator<char>("<");
			operatorStr = " < ";
		}
		else if (tokString.find("=") != std::string::npos) { // greater than equal to constraint
			sep = boost::char_separator<char>("=");
			operatorStr = " = ";
		}
		else if (tokString.find("==") != std::string::npos) { // greater than equal to constraint
			sep = boost::char_separator<char>("==");
			operatorStr = " = ";
		}
		else{
			throw std::runtime_error("Goal Property string improper: <= or >= or > or < or (=/==) constraint expected\n");
		}
		tokens = tokenizer(tokString, sep);
		tok_iter = tokens.begin();
		varname = *tok_iter;
		prefixStr.append(operatorStr);
		prefixStr.append(" ");
		prefixStr.append(varname);
		tok_iter++;
		prefixStr.append(" ");
		prefixStr.append((*tok_iter));
		prefixGoal.push_back(prefixStr);
	}
	return prefixGoal;
}


void user_inputs::setGoalProperty(const std::string& goalProperty) {
	goal_property = goalProperty;
}

void user_inputs::setNoiseInjection(const std::string& noiseParams) {
	noise_parameter = noiseParams;
//Also parse the string and populate the values in my_noisedata below.
	std::list<nd_parameter> my_noisedata;

	my_noisedata = convertToNDparams(noiseParams);
	setNoiseData(my_noisedata);//Call this to setNoiseData
}

void user_inputs::setDisturbance(const std::string& disturbanceParams) {
	disturbance_parameter = disturbanceParams;

	std::list<nd_parameter> my_disturbanceData;

	my_disturbanceData = convertToNDparams(disturbanceParams);
	setDisturbanceData(my_disturbanceData);//Call this to setNoiseData

}


const std::list<nd_parameter>& user_inputs::getDisturbanceData() const {
	return disturbance_data;
}

void user_inputs::setDisturbanceData(
		const std::list<nd_parameter>& disturbanceData) {
	disturbance_data = disturbanceData;
}

const std::list<nd_parameter>& user_inputs::getNoiseData() const {
	return noise_data;
}

void user_inputs::setNoiseData(const std::list<nd_parameter>& noiseData) {
	noise_data = noiseData;
}

int user_inputs::getLowerBound() const {
	return lower_bound;
}

void user_inputs::setLowerBound(int lowerBound) {
	lower_bound = lowerBound;
}

const std::string& user_inputs::getOutputFilename() const {
	return output_filename;
}

void user_inputs::setOutputFilename(const std::string& outputFilename) {
	output_filename = outputFilename;
}

std::string user_inputs::getPlantFilename() {
	return plant_filename;
}

void user_inputs::setPlantFilename(std::string plantFilename) {
	plant_filename = plantFilename;
}

double user_inputs::getSampleTime() const {
	return sample_time;
}

void user_inputs::setSampleTime(double sampleTime) {
	sample_time = sampleTime;
}

double user_inputs::getSamplingJitter() const {
//	cout<< "Delay= "<<sensing_time<<"\n";
	return sensing_time;
}

void user_inputs::setSamplingJitter(double sensingTime) {
//	cout<< "Delay is= "<<sensing_time<<"\n";
	sensing_time = sensingTime;
}

double user_inputs::getTimeHorizon() const {
	return time_horizon;
}

void user_inputs::setTimeHorizon(double timeHorizon) {
	time_horizon = timeHorizon;
}

int user_inputs::getUpperBound() const {
	return upper_bound;
}

double user_inputs::getMaxValue() const {
	return max_value;
}

void user_inputs::setMaxValue(double maxValue) {
	max_value = maxValue;
}

void user_inputs::setUpperBound(int upperBound) {
	upper_bound = upperBound;
}

double user_inputs::getReleaseTime() const {
	return release_time;
}

double user_inputs::getPrecision() const {
	return precision;
}

void user_inputs::setDeadlineMiss_m(double setdeadlinemiss_m) {
	deadline_miss_m = setdeadlinemiss_m;
}

double user_inputs::getDeadlineMiss_m() const {
	return deadline_miss_m;
}

void user_inputs::setDeadlineMiss_n(double setdeadlinemiss_n) {
	deadline_miss_n = setdeadlinemiss_n;
}

double user_inputs::getDeadlineMiss_n() const {
	return deadline_miss_n;
}

void user_inputs::setPrecision(double precision) {
	this->precision = precision;
}

void user_inputs::setReleaseTime(double releaseTime) {
	release_time = releaseTime;
}
