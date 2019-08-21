/*
 * initial_sym_state.h
 *
 *  Created on: 07-May-2018
 *      Author: amit
 */

#ifndef CORESYSTEM_PLANT_MODEL_INITIAL_SYM_STATE_H_
#define CORESYSTEM_PLANT_MODEL_INITIAL_SYM_STATE_H_

#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

using namespace std;

class initial_sym_state{
	int loc_id;//initial location id
	std::list<std::string> initial_set;
	std::list<std::string> prefix_initial_set;
public:
	typedef boost::shared_ptr<initial_sym_state> ptr;

	initial_sym_state();
	initial_sym_state(int loc_id, std::list<std::string> initial_set);

	const std::list<std::string>& getInitialSet() const;
	void setInitialSet(const std::list<std::string>& initialSet);

	const std::list<std::string>& getPrefixInitialSet() const;
	void setPrefixInitialSet(const std::list<std::string>& prefixInitialSet);

	int getLocId() const;
	void setLocId(int locId);

};


#endif /* CORESYSTEM_PLANT_MODEL_INITIAL_SYM_STATE_H_ */
