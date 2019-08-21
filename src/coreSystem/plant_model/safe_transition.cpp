/*
 * safe_transition.cpp
 *
 *  Created on: 06-May-2018
 *      Author: amit
 */

#include "safe_transition.h"

safe_transition::safe_transition(){
	;
}
safe_transition::safe_transition(int trans_id, string label, int source_id, int destination_id,
		std::list<std::string> guard, std::list<std::string> assign){
	this->trans_id = trans_id;
	this->label = label;
	this->source_location_id = source_id;
	this->destination_location_id = destination_id;
	this->guard = guard;
	this->assignment = assign;
}

const std::list<std::string>& safe_transition::getAssignment() const {
	return assignment;
}

void safe_transition::setAssignment(const std::list<std::string>& assignment) {
	this->assignment = assignment;
}

int safe_transition::getDestinationLocationId() const {
	return destination_location_id;
}

void safe_transition::setDestinationLocationId(int destinationLocationId) {
	destination_location_id = destinationLocationId;
}

const std::list<std::string>& safe_transition::getGuard() const {
	return guard;
}

void safe_transition::setGuard(const std::list<std::string>& guard) {
	this->guard = guard;
}

const std::string& safe_transition::getLabel() const {
	return label;
}

void safe_transition::setLabel(const std::string& label) {
	this->label = label;
}

int safe_transition::getSourceLocationId() const {
	return source_location_id;
}

void safe_transition::setSourceLocationId(int sourceLocationId) {
	source_location_id = sourceLocationId;
}

int safe_transition::getTransId() const {
	return trans_id;
}

void safe_transition::setTransId(int transId) {
	trans_id = transId;
}



