/*
 * location.cpp
 *
 *  Created on: 06-May-2018
 *      Author: amit
 */

#include "safe_location.h"

safe_location::safe_location(){

}
safe_location::safe_location(int loc_id, string name, list<flow_equation> derivatives, list<string> invariant, std::list<safe_transition::ptr> trans){
	this->loc_id = loc_id;
	this->Name = name;
	this->derivatives = derivatives;
	this->invariant = invariant;
	this->out_going_transitions = trans;
}


const list<flow_equation>& safe_location::getDerivatives() const {
	return derivatives;
}

void safe_location::setDerivatives(const list<flow_equation>& derivatives) {
	this->derivatives = derivatives;
}

const list<string>& safe_location::getInvariant() const {
	return invariant;
}

void safe_location::setInvariant(const list<string>& invariant) {
	this->invariant = invariant;
}

int safe_location::getLocId() const {
	return loc_id;
}

void safe_location::setLocId(int locId) {
	loc_id = locId;
}

const string& safe_location::getName() const {
	return Name;
}

void safe_location::setName(const string& name) {
	Name = name;
}

const std::list<safe_transition::ptr>& safe_location::getOutGoingTransitions() const {
	return out_going_transitions;
}

void safe_location::setOutGoingTransitions(
		const std::list<safe_transition::ptr>& outGoingTransitions) {
	out_going_transitions = outGoingTransitions;
}

const list<string>& safe_location::getPrefixDerivatives() const {
	return prefix_derivatives;
}

void safe_location::setPrefixDerivatives(
		const list<string>& prefixDerivatives) {
	prefix_derivatives = prefixDerivatives;
}
