/*
 * location.h
 *
 *  Created on: 06-May-2018
 *      Author: amit
 */

#ifndef CORESYSTEM_PLANT_MODEL_SAFE_LOCATION_H_
#define CORESYSTEM_PLANT_MODEL_SAFE_LOCATION_H_

#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

#include "plantDataStructure.h"
#include "safe_transition.h"

using namespace std;

class safe_location {
private:
	int loc_id;
	string Name;
	//list<pair<bool,string> > derivatives;
	list<flow_equation> derivatives;
	list<string> prefix_derivatives;
	list<string> invariant;
	std::list<safe_transition::ptr> out_going_transitions;

public:
	typedef boost::shared_ptr<safe_location> ptr;
	safe_location();
	safe_location(int loc_id, string Name, list<flow_equation> derivatives, list<string> invariant, std::list<safe_transition::ptr> trans);
	//transition::ptr getTransition(int trans_id);	//returns a specific transition for a given trans_id

	const list<flow_equation>& getDerivatives() const;
	void setDerivatives(const list<flow_equation>& derivatives);


	const list<string>& getInvariant() const;
	void setInvariant(const list<string>& invariant);
	int getLocId() const;
	void setLocId(int locId);
	const string& getName() const;
	void setName(const string& name);
	const std::list<safe_transition::ptr>& getOutGoingTransitions() const;
	void setOutGoingTransitions(const std::list<safe_transition::ptr>& outGoingTransitions);

	const list<string>& getPrefixDerivatives() const;
	void setPrefixDerivatives(const list<string>& prefixDerivatives);
};

#endif /* CORESYSTEM_PLANT_MODEL_SAFE_LOCATION_H_ */
