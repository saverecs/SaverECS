/*
 * hybrid_automata.cpp
 *
 *  Created on: 06-May-2018
 *      Author: amit
 */

#include "hybrid_automata.h"

using namespace std;

hybrid_automata::hybrid_automata() {
}
/*hybrid_automata::hybrid_automata(std::map<int, safe_location::ptr>& list_locs, safe_location::ptr init_loc) {
	this->list_locations = list_locs;	//assigning a map to another map
	this->initial_loc = init_loc;
}*/

std::list<initial_sym_state::ptr>& hybrid_automata::getInitial_Location() {
	return initial_loc;
}

void hybrid_automata::addInitial_Location(std::list<initial_sym_state::ptr>& initLoc) {
	this->initial_loc = initLoc;
}

safe_location::ptr hybrid_automata::getLocation(int Loc_Id){
	assert(list_locations.count(Loc_Id)!=0);
	safe_location::ptr l;
	l = list_locations[Loc_Id];
	return l;
}

void hybrid_automata::addMapped_Locations_List(std::map<int, safe_location::ptr>& mapped_location_list){
	this->list_locations = mapped_location_list;
}

const string& hybrid_automata::getName() const {
	return name;
}

void hybrid_automata::setName(const string& name) {
	this->name = name;
}

void hybrid_automata::addLocation(safe_location::ptr& loc){
	int key = loc->getLocId();
	list_locations[key] = loc;	//storing the loc with the proper loc_id as the key
}


