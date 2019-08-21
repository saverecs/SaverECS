/*
 * initial_sym_state.cpp
 *
 *  Created on: 07-May-2018
 *      Author: amit
 */

#include "initial_sym_state.h"

initial_sym_state::initial_sym_state(){

}
initial_sym_state::initial_sym_state(int loc_id,
		std::list<std::string> initial_set){
	this->initial_set=initial_set;
	this->loc_id = loc_id;
}

const std::list<std::string>& initial_sym_state::getInitialSet() const {
	return initial_set;
}

void initial_sym_state::setInitialSet(
		const std::list<std::string>& initialSet) {
	initial_set = initialSet;
}

const std::list<std::string>& initial_sym_state::getPrefixInitialSet() const {
	return prefix_initial_set;
}

void initial_sym_state::setPrefixInitialSet(
		const std::list<std::string>& prefixInitialSet) {
	prefix_initial_set = prefixInitialSet;
}


int initial_sym_state::getLocId() const {
	return loc_id;
}

void initial_sym_state::setLocId(int locId) {
	loc_id = locId;
}
