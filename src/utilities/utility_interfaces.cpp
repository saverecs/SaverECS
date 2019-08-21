/*
 * utility_interfaces.cpp
 *
 *  Created on: 11-Jul-2018
 *      Author: amit
 */

#include "utility_interfaces.h"

using namespace std;

std::list<nd_parameter> convertToNDparams(std::string my_noisedata){

	std::list<nd_parameter> noise_disturbance_data;

	//Separate more than one repeated arguments
	std::list<std::string> all_args;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(my_noisedata, sep);

	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
		all_args.push_back((std::string) *tok_iter);
	}

	tokenizer::iterator tok_iter;
	std::string varname, nd_data;
	unsigned int i;//, countcomponent=0;
	//For each arguments of the the type:  "var1:[t1,t2]=>[n1,n2]" run and separate each component
	for(std::list<std::string>::iterator iter = all_args.begin(); iter!=all_args.end();iter++){
		nd_parameter nd_parm;
		nd_data = *iter;	//each parameter of the form "var1:[t1,t2]=>[n1,n2]"
		//We have five(5) components/token in nd_data if we consider separator as :[,]=>

		sep = boost::char_separator<char>(":[,]=>");
		tokens = tokenizer(nd_data, sep);
		tok_iter = tokens.begin();
		nd_parm.nd_variable_name = *tok_iter;			//First token i.e., the variable name
		tok_iter++;
		nd_parm.start_time = std::stod(*tok_iter);			//Second token i.e., the start time
		tok_iter++;
		nd_parm.end_time = std::stod(*tok_iter);			//Third token i.e., the end time
		tok_iter++;
		nd_parm.value1 = std::stod(*tok_iter);			//Fourth token i.e., the noise/disturbance lower-bound value
		tok_iter++;
		nd_parm.value2 = std::stod(*tok_iter);			//Fifth token i.e., the noise/disturbance upper-bound value

//		throw std::runtime_error("Goal Property string improper: <= or >= or > or < or (=/==) constraint expected\n");
		noise_disturbance_data.push_back(nd_parm);
	}

	return noise_disturbance_data;
}

void displayNDparams(std::list<nd_parameter> nd_params){
	std::cout<<"List of Noise/Disturbance Parameters:"<<std::endl;
	for (std::list<nd_parameter>::iterator it=nd_params.begin(); it != nd_params.end(); it++){
		nd_parameter nd = (*it);
		std::cout<<"\t\t\t"<<nd.nd_variable_name<<": ["<<nd.start_time<<","<<nd.end_time<<"] => ["<<nd.value1<<","<<nd.value2<<"]\n"<<std::endl;
	}
}

std::string remove_quotes(std::string quote_str){
	string first_char = quote_str.substr(0, 1);	//get the first chars
	unsigned int totlen = quote_str.length() - 1;
	string last_char = quote_str.substr(totlen, 1);	//get the last chars
	string ret_string;
	if (boost::iequals(first_char, "\"")) {
		//std::cout<<"It is a opening quote!!!"<<std::endl;
		ret_string = quote_str.substr(1);	//get the substring from the 2nd character position
		//std::cout<<"char without opening quote = "<<ret_string<<std::endl;
	}

	if (boost::iequals(last_char, "\"")) {
		unsigned int nos_char = ret_string.length() - 1;	//exclude one last char i.e., closing quote
		//std::cout<<"It is the closing quote!!!"<<std::endl;
		ret_string = ret_string.substr(0, nos_char);	//get the substring from the 1st character position
		//std::cout<<"char without quotes = "<<ret_string<<std::endl;
	}
	return ret_string;
}


std::list<min_max_bounds> convertTo_MinMaxBounds(std::string user_args){

	std::list<min_max_bounds> min_max_bounds_data;

	//Separate more than one repeated arguments
	std::list<std::string> all_args;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep("& ");
	tokenizer tokens(user_args, sep);

	for (tokenizer::iterator tok_iter = tokens.begin(); tok_iter != tokens.end(); ++tok_iter) {
		all_args.push_back((std::string) *tok_iter);
	}

	tokenizer::iterator tok_iter;
	std::string varname, arg_data;
	unsigned int i;//, countcomponent=0;
	//For each arguments of the the type:  "var1:[min,max]" run and separate each component
	for(std::list<std::string>::iterator iter = all_args.begin(); iter!=all_args.end();iter++){
		min_max_bounds MinMaxData;
		arg_data = *iter;	//each parameter of the form "var1:[t1,t2]"
		//We have three(3) components/token in arg_data if we consider separator as :[,]

		sep = boost::char_separator<char>(":[,]");
		tokens = tokenizer(arg_data, sep);
		tok_iter = tokens.begin();
		MinMaxData.variable_name = *tok_iter;			//First token i.e., the variable name
		tok_iter++;
		MinMaxData.minValue = std::stod(*tok_iter);			//Second token i.e., the minValue
		tok_iter++;
		MinMaxData.maxValue = std::stod(*tok_iter);			//Third token i.e., the maxValue

		min_max_bounds_data.push_back(MinMaxData);
	}

	return min_max_bounds_data;
}
void display_MinMaxBounds(std::list<min_max_bounds> MinMaxData){
	std::cout<<"List of MinMaxBounds Parameters:"<<std::endl;
	for (std::list<min_max_bounds>::iterator it=MinMaxData.begin(); it != MinMaxData.end(); it++){
		min_max_bounds minmaxBounds = (*it);
		std::cout<<"\t\t\t"<<minmaxBounds.variable_name<<": ["<<minmaxBounds.minValue<<","<<minmaxBounds.maxValue<<"]"<<std::endl;
	}
}

bool findVar_in_MinMaxBounds(std::list<min_max_bounds> min_max_bounds_structure, std::string var_name){

	for (std::list<min_max_bounds>::iterator it=min_max_bounds_structure.begin(); it != min_max_bounds_structure.end();it++){
		if (boost::iequals((*it).variable_name, var_name)) {
			return true;
		}
	}
	return false;
}
