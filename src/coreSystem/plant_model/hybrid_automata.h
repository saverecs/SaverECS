/*
 * automata.h
 *
 *  Created on: 06-May-2018
 *      Author: amit
 */

#ifndef CORESYSTEM_PLANT_MODEL_HYBRID_AUTOMATA_H_
#define CORESYSTEM_PLANT_MODEL_HYBRID_AUTOMATA_H_

#include "var_mapping.h"
#include <boost/shared_ptr.hpp>
#include "initial_sym_state.h"
#include "safe_location.h"

class hybrid_automata : public var_mapping {
	std::map<int, safe_location::ptr> list_locations;//mapping a list of locations based on the key=loc_id
	std::list<initial_sym_state::ptr> initial_loc;//can be a list of initial_symbolic states
	std::string name; //Name of the automata, not essential
public:
	typedef boost::shared_ptr<hybrid_automata> ptr;
	hybrid_automata();
	//hybrid_automata(std::map<int, safe_location::ptr>& list_locs, safe_location::ptr init_loc);

	void addInitial_Location(std::list<initial_sym_state::ptr>& init_sym_states);
	std::list<initial_sym_state::ptr>& getInitial_Location();

	//returns the location from the list of locations with location_ID as the input parameter
	safe_location::ptr getLocation(int Loc_ID);

	void addMapped_Locations_List(std::map<int, safe_location::ptr>& mapped_location_list);

	void addLocation(safe_location::ptr& loc);	//inserts location into its correctly mapped key
	/* Returns the total number of Locations in the hybrid automata with ID = 1 to returned size */
	int getTotalLocations(){
		return list_locations.size();
	}
	const string& getName() const;
	void setName(const string& name);
};


#endif /* CORESYSTEM_PLANT_MODEL_HYBRID_AUTOMATA_H_ */
