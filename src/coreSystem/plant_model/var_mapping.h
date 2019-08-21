/*
 * var_mapping.h
 *
 *  Created on: 05-May-2018
 *      Author: amit
 */

#ifndef CORESYSTEM_VAR_MAPPING_H_
#define CORESYSTEM_VAR_MAPPING_H_

#include <iostream>
#include <map>
#include <string>
//#include <utility>
#include <boost/shared_ptr.hpp>


class var_mapping {
public:
	typedef boost::shared_ptr< std::map<std::string, unsigned int> > ptr;

	var_mapping();

	/* Returns the variable name with the given index */
	std::string get_varname(unsigned int index);

	/* Returns the index of the parameter var_name in the variable name to dimension index mapping */
	unsigned int get_index(std::string var_name){
		unsigned int index = var_mapping_ptr->at(var_name);
		return index;
	}
	/* Inserts a varname, dimension index into the map. */
	void insert_to_map(std::string name, unsigned int val)
	{
		var_mapping_ptr->insert(std::pair<std::string, unsigned int>(name,val));
	}

	/* Sets this-> map to the new map passed as parameter */
	void set_map(ptr m){
		var_mapping_ptr = m;
	}

	/*Prints the var_to_index map in the console*/
	void print_var_mapping();


	/**
	 * Returns True if the variable exists in the mapping list.
	 */
	bool isaVariable(std::string varName);


	virtual ~var_mapping();

	/** Return the size of the map */
	unsigned int map_size();
	static ptr var_mapping_ptr;

};



#endif /* CORESYSTEM_VAR_MAPPING_H_ */
