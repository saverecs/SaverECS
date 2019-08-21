/*
 * safe_transition.h
 *
 *  Created on: 06-May-2018
 *      Author: amit
 */

#ifndef CORESYSTEM_PLANT_MODEL_SAFE_TRANSITION_H_
#define CORESYSTEM_PLANT_MODEL_SAFE_TRANSITION_H_

#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

using namespace std;

class safe_transition {
	int trans_id;
	std::string label;
	int source_location_id;
	int destination_location_id;
	std::list<std::string> guard; //every & can be separated as a single guard string
	std::list<std::string> assignment;
public:
	typedef boost::shared_ptr<safe_transition> ptr;
	safe_transition();
	safe_transition(int trans_id, string label, int source_id, int destination_id,
			std::list<std::string> guard, std::list<std::string> assign);

	const std::list<std::string>& getAssignment() const;
	void setAssignment(const std::list<std::string>& assignment);
	int getDestinationLocationId() const;
	void setDestinationLocationId(int destinationLocationId);
	const std::list<std::string>& getGuard() const;
	void setGuard(const std::list<std::string>& guard);
	const std::string& getLabel() const;
	void setLabel(const std::string& label);
	int getSourceLocationId() const;
	void setSourceLocationId(int sourceLocationId);
	int getTransId() const;
	void setTransId(int transId);
};

#endif /* CORESYSTEM_PLANT_MODEL_SAFE_TRANSITION_H_ */
