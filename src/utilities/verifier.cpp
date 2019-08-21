/*
 * verifier.cpp
 *
 *  Created on: 06-May-2018
 *      Author: amit
 */

#include "verifier.h"
#include <iostream>
#include <stdio.h>
#include <boost/algorithm/string.hpp>
#include <string>

#include "maths/miscellaneous.h"

//#define MAIN_DEBUG_ON

using namespace std;

void populateDataPlant(struct phaver* pha, hybrid_automata::ptr& hybrid_auto,
		struct plant_variables& plant_vars, user_inputs::ptr& user_Inputs) {
	std::list<struct variablesTypes> control_vars, uncontrol_vars;
	int control_flag_once = 1, uncontrol_flag_once = 1;
	struct condition* params = pha->params;
	struct automaton* ha = pha->ha;
	struct identifier* contr_vars = ha->contr_vars;
	struct identifier* synclabs = ha->synclabs;
	struct identifier* var_inputs = ha->var_inputs;
	struct location* loc = ha->locations;
	struct condition* invariant = NULL;
	struct condition* derivative = NULL;
	struct transition* transitions = NULL;
	struct condition* when = NULL;
	struct condition* reset = NULL;
	struct initial* init = pha->init;
	struct identifier* init_locs = pha->init->init_locs;
	struct condition* init_conds = pha->init->init_conds;
	/*	printf("//--------------PARAMETERS------------------\n");
	 while(params!=NULL){
	 printf("%s %s %s;\n",params->LHS,":=",params->RHS);
	 params=params->next;
	 }*/

	hybrid_auto->setName(string(ha->name));

	int counter = 0;
	while (contr_vars != NULL) { //Todo::Need to separate control variables with uncontrol/input variables
		hybrid_auto->insert_to_map(string(contr_vars->name), counter);
		counter++;
		contr_vars = contr_vars->next;
	}

	/*printf("synclabs: ");
	 while(synclabs!=NULL){
	 if(synclabs->next == NULL){
	 printf("%s;\n",synclabs->name);
	 } else printf("%s,",synclabs->name);
	 synclabs=synclabs->next;
	 }*/
	/*if(var_inputs!=NULL) printf("var_inputs: ");	//This actually not implemented in ForFET
	 while(var_inputs!=NULL){
	 if(var_inputs->next == NULL){
	 printf("%s;\n",var_inputs->name);
	 } else printf("%s, ",var_inputs->name);
	 var_inputs=var_inputs->next;
	 }*/

// **************** Creating Locations *****************
	//create a list of unique location ID as required for source_loc_id ----> destination_loc_id while creating the automata graph
	std::map<int, safe_location::ptr> map_loc_list, map_location_list; //mapping of the key loc_id to safe_location::ptr
	int loc_counter = 0; //counter variable for counting total number of locations, also used to denote location ID[0 to n-1]:
	//Also create a map of location id with name for quick search
	std::map<std::string, int> loc_name_map_id; //here name is used as a Key for ease of search
	while (loc != NULL) {
		safe_location::ptr my_locs = safe_location::ptr(new safe_location());
		my_locs->setLocId(loc_counter);
		my_locs->setName(string(loc->name));

		loc_name_map_id[my_locs->getName()] = my_locs->getLocId(); //key is location name
		map_loc_list[loc_counter] = my_locs;
		loc_counter++;
		loc = loc->next;
	}
#ifdef MAIN_DEBUG_ON	//Verifying the location-name-id mapping
	std::cout<<"Mapping Verifying "<<std::endl;
	for (std::map<std::string,int>::iterator k=loc_name_map_id.begin();k!=loc_name_map_id.end();k++) {
		cout<<"Location Name = "<<(*k).first<<"  Loc-ID=" <<(*k).second<<std::endl;
	}
#endif
	hybrid_auto->addMapped_Locations_List(map_loc_list); //This will be replaced later after detailed information has been populated
// **************** Locations Created *****************

	loc = ha->locations; //reseting the pointer to the start of the Location
	int trans_counter = 0; //this maintains a unique ID for all transitions of the hybrid automata
	while (loc != NULL) {
		control_flag_once = 1;
		uncontrol_flag_once = 1; //To support next Location (for multi-location plant)
		int loc_id = loc_name_map_id[string(loc->name)]; //obtain loc_id from the temporary mapping of name-loc_id
		safe_location::ptr my_location = safe_location::ptr(
				new safe_location());
		my_location = map_loc_list[loc_id];	//accessing from the map data structure to create a new location with same ID and name
		//and fill up the remaining details and replace the hybrid_automata with this new detailed location
		my_location->setLocId(loc_id);
		my_location->setName(string(loc->name));

		invariant = loc->invariant;
		std::list<std::string> my_inv;		//collect the list of invariant
		while (invariant != NULL) {
			std::string inv_str = "";
			if (invariant->op == -1) {//Todo: clarify: to my understanding if op==-1 indicate there is no invariant of this location
				//my_location->setInvariant(my_inv);//throwing NULL need to catch it
				break;//should be break here
			} else {
				inv_str.append(invariant->LHS);
				inv_str.append(" ");
				inv_str.append(phOperatorMap(invariant->op));
				inv_str.append(" ");
				inv_str.append(invariant->RHS);
				my_inv.push_back(inv_str);
			}
			invariant = invariant->next;
		}
		my_location->setInvariant(my_inv);//throwing NULL in case of empty: need to catch it

		derivative = loc->derivative;
		//std::list<std::string> my_derivative;
		std::list<std::string> prefix_derivative;//collect the list of derivative
		std::list<flow_equation> myderivatives;
		int count_controll_var = 0; //to keep track of the control and uncontrol variables
		while (derivative != NULL) { //assuming that every location will have at least a control variable and it's derivative
			flow_equation myderiv;
			std::string deriv_str = "", prefix_deriv_str = "";

			deriv_str.append(derivative->LHS);
			deriv_str.append(" ");
			deriv_str.append(phOperatorMap(derivative->op));
			deriv_str.append(" ");
			deriv_str.append(derivative->RHS);
			string rhsExp = string(derivative->RHS);

			//For a variable name, remove character ' from derivation
			std::string temp_str = derivative->LHS;
			myderiv.varName = temp_str.substr(0, temp_str.size() - 1);

			myderiv.RHSexpression = derivative->RHS;
			myderiv.derivative = deriv_str;

			if (isa_Number(rhsExp)) {
				myderiv.isConstant_dynamic = true;
			} else
				myderiv.isConstant_dynamic = false;

			//std::cout<<"Right side="<<derivative->RHS<<std::endl;

			prefix_deriv_str = InfixToPrefix(deriv_str); //Prefix notation for dReal solver with (= d/dt [x] (....))

			if (control_flag_once == 1) { //computing the control variable only once
				std::string var_with_dot = derivative->LHS, var_without_dot;
				var_without_dot = var_with_dot.substr(0,
						var_with_dot.length() - 1); //discard the last character i.e., the dot
				struct variablesTypes my_control_var;
				my_control_var.var_name = var_without_dot;
				my_control_var.var_id = hybrid_auto->get_index(
						my_control_var.var_name);
				//std::cout<<"var_id ="<<my_control_var.var_id<<"\n";

				//Now search the min_max_bounds data supplied by user if found set with that otherwise with MaxValue
				std::list<min_max_bounds> mmbounds = user_Inputs->getMinMax_Bounds();
				if (findVar_in_MinMaxBounds(mmbounds, my_control_var.var_name)){	//return true if found
					for (std::list<min_max_bounds>::iterator it = mmbounds.begin(); it != mmbounds.end(); it++) {
						if (boost::iequals((*it).variable_name, my_control_var.var_name)) {
							my_control_var.lbound = (*it).minValue;
							my_control_var.ubound = (*it).maxValue;
							break;
						}
					}
				}else{
					my_control_var.lbound = -1 * user_Inputs->getMaxValue();
					my_control_var.ubound = 1 * user_Inputs->getMaxValue();
				}
				control_vars.push_back(my_control_var);
			}

			myderivatives.push_back(myderiv);

			//	my_derivative.push_back(deriv_str);

			prefix_derivative.push_back(prefix_deriv_str);

			derivative = derivative->next;
			count_controll_var++;
		}
		control_flag_once = 2; //invalidating
		my_location->setDerivatives(myderivatives);
		//my_location->setDerivatives(my_derivative);//throwing NULL in case of empty: need to catch it
		my_location->setPrefixDerivatives(prefix_derivative);

		if (uncontrol_flag_once == 1) {	//computing the uncontrol variable only once
			for (unsigned int i = 0; i < hybrid_auto->map_size(); i++) {
				std::string my_var = hybrid_auto->get_varname(i);
				struct variablesTypes my_uncontrol_var;
				int flag_unControlVariable = 1;
				for (std::list<struct variablesTypes>::iterator it_control_var =
						control_vars.begin();
						it_control_var != control_vars.end();
						it_control_var++) {
					if (boost::iequals(my_var, (*it_control_var).var_name)) {
						flag_unControlVariable = 0;
						break;	//present in the control-Variable-list
					}
				}
				if (flag_unControlVariable) {//indicating it is not in control variable data structure
					my_uncontrol_var.var_name = my_var;
					my_uncontrol_var.var_id = hybrid_auto->get_index(my_uncontrol_var.var_name);

					//Now search the min_max_bounds data supplied by user if found set with that otherwise with MaxValue
					std::list<min_max_bounds> mmbounds = user_Inputs->getMinMax_Bounds();
					if (findVar_in_MinMaxBounds(mmbounds, my_uncontrol_var.var_name)){	//return true if found
						for (std::list<min_max_bounds>::iterator it = mmbounds.begin(); it != mmbounds.end(); it++) {
							if (boost::iequals((*it).variable_name, my_uncontrol_var.var_name)) {
								my_uncontrol_var.lbound = (*it).minValue;
								my_uncontrol_var.ubound = (*it).maxValue;
								break;
							}
						}
					}else{
						my_uncontrol_var.lbound = -1 * user_Inputs->getMaxValue();
						my_uncontrol_var.ubound = 1 * user_Inputs->getMaxValue();
					}
					uncontrol_vars.push_back(my_uncontrol_var);
				}
			}
			plant_vars.control_var = control_vars;
			plant_vars.uncontrol_var = uncontrol_vars;
			uncontrol_flag_once = 2; //invalidating the only once flag
		}

		//OUTGOING TRANSITIONS
		transitions = loc->transitions;
		std::list<safe_transition::ptr> out_going_transitions; //list of out-going-transitions of this location
#ifdef MAIN_DEBUG_ON	//Verifying the location-name-id mapping
		if(transitions ==NULL) cout<<"Transition is NULL"<<std::endl;
#endif
		while (transitions != NULL) {
			when = transitions->when;
			reset = transitions->reset;
			safe_transition::ptr my_transition = safe_transition::ptr(
					new safe_transition());
			my_transition->setTransId(trans_counter);
			my_transition->setLabel(transitions->sync);
//			std::cout<<"Trans Id = "<<my_transition->getTransId()<<std::endl;
//			std::cout<<"Trans Name/sync = "<<my_transition->getLabel()<<std::endl;
			my_transition->setSourceLocationId(my_location->getLocId()); //current ID is in loc_counter
			int dest_loc = loc_name_map_id[transitions->gotoLoc];
			my_transition->setDestinationLocationId(dest_loc);
//			std::cout<<"Destination Location = "<<my_transition->getDestinationLocationId()<<std::endl;

			std::list<std::string> my_guard;	//collect the list of invariant
			//if(when==NULL) cout<<"guard is NULL"<<std::endl;
			while (when != NULL) {
				std::string guard_str = "";
				if (boost::iequals(when->LHS, "true"))
					guard_str = "true";
				else {
					guard_str.append(when->LHS);
					guard_str.append(" ");
					guard_str.append(phOperatorMap(when->op));
					guard_str.append(" ");
					guard_str.append(when->RHS);
				}
				//std::cout<<"guard_str = "<<guard_str<<std::endl;
				my_guard.push_back(guard_str);
				when = when->next;
			}
			my_transition->setGuard(my_guard);//Todo::need more time to think about universal guard(how to represent in smt2), due to smt2 approach
			//Todo take this as Assignment which may be absent in our case
			/*while (reset != NULL) {
			 printf("%s %s %s", reset->LHS, "==", reset->RHS);
			 if (reset->next != NULL) {
			 printf(" & ");
			 } else {
			 printf(" }\n\t\t\t");
			 }
			 reset = reset->next;
			 }*/

			transitions = transitions->next;
			trans_counter++;		//next unique transition ID
			out_going_transitions.push_back(my_transition);
		}		//if there is no transition, throws exception need to catch

		my_location->setOutGoingTransitions(out_going_transitions);
		std::list<safe_transition::ptr> myOutGoingTrans =
				my_location->getOutGoingTransitions();
		/*	std::cout<<"======Verify list of transitions======\n";
		 for (std::list<safe_transition::ptr>::iterator it = myOutGoingTrans.begin();
		 it != myOutGoingTrans.end(); it++) {
		 std::cout << "\t\t\t Trans-ID =" << (*it)->getTransId() << std::endl;
		 std::cout << "\t\t\t Sync Label=" << (*it)->getLabel() << std::endl;
		 std::cout << "\t\t\t From =" << (*it)->getSourceLocationId()<< "  To = "<<(*it)->getDestinationLocationId() << std::endl;
		 std::list<std::string> guard_str = (*it)->getGuard();
		 std::cout<<"\t\t\t Guard: "<<std::endl;
		 for (std::list<std::string>::iterator it_guard = guard_str.begin();
		 it_guard != guard_str.end(); it_guard++) {
		 std::cout << "\t\t\t\t\t" << (*it_guard) << std::endl;
		 }
		 }
		 std::cout<<"======list of transitions======\n";*/

		map_location_list[my_location->getLocId()] = my_location;//creates a map of list of locations
		loc = loc->next;
	}
	hybrid_auto->addMapped_Locations_List(map_location_list); //Todo:: verify if this replaces the previous or not

	std::list<initial_sym_state::ptr> my_initial_locations;
	while (init != NULL) {
		initial_sym_state::ptr my_init_loc = initial_sym_state::ptr(
				new initial_sym_state());
		int init_loc_id = loc_name_map_id[init_locs->name];
		my_init_loc->setLocId(init_loc_id); //creating new initial location with the same loc_id

		init_locs = init->init_locs;
		init_conds = init->init_conds;

		std::list<std::string> my_initial_set, prefix_initial_set;
		while (init_conds != NULL) {
			std::string init_set_str = "", prefix_init_set_str = "";
			init_set_str.append(init_conds->LHS);
			init_set_str.append(" ");
			init_set_str.append(phOperatorMap(init_conds->op));
			init_set_str.append(" ");
			init_set_str.append(init_conds->RHS);

			prefix_init_set_str.append(phOperatorMap(init_conds->op));
			prefix_init_set_str.append(" ");
			prefix_init_set_str.append(init_conds->LHS);
			prefix_init_set_str.append(" ");
			prefix_init_set_str.append(init_conds->RHS);

			my_initial_set.push_back(init_set_str);	//infix notation
			prefix_initial_set.push_back(prefix_init_set_str);//prefix notation
			init_conds = init_conds->next;
		}
		my_init_loc->setInitialSet(my_initial_set);	//infix notation
		my_init_loc->setPrefixInitialSet(prefix_initial_set);

		my_initial_locations.push_back(my_init_loc);
		init = init->next;
	}
	hybrid_auto->addInitial_Location(my_initial_locations);
	std::cout << "\nPlant model: parsing Done...\n";
}

std::string InfixToPrefix(std::string s) {
	std::string st;
	std::string s1 = s.substr(s.find("==") + 2);//RHS i.e. equation part (infix format)
	//cout<<"s1 = "<<s1<<endl;
	std::string s2 = "(= d/dt[" + s.substr(0, s.find("\'")) + "] ";	//LHS i.e. Variable,which has flow (infix format)
	//cout<<"s2 = "<<s2<<endl;
	vector<string> infix, prefix;
	typedef boost::tokenizer<boost::char_separator<char> > tokenizer;
	boost::char_separator<char> sep { " ", "+-/^$*)(" };
	tokenizer tok { s1, sep };
	for (tokenizer::iterator t = tok.begin(); t != tok.end(); t++) {
		infix.push_back(string(*t));
//		 std::cout<<*t<<endl;
	}
	prefix.resize(infix.size());
	infixtoprefix(infix, prefix);		//converting RHS in postfix format
	/*	for(string c:prefix){
	 st +=c;
	 std::cout <<c<<std::endl;
	 }*/
	//std::cout<<"Before parenthesis = " <<st<<std::endl;
	st = parenthesize(prefix);
//	std::cout<<"After parenthesis = " <<st<<std::endl;
	return s2 + st + ")";				//Returning LHS and RHS in prefix format
}

void display_safe_hybrid_automata(hybrid_automata::ptr& my_ha) {
	std::cout
			<< "\n\n===================Displaying Plant Model==================="
			<< std::endl;
	/*	printf("//--------------PARAMETERS------------------\n");
	 while(params!=NULL){
	 printf("%s %s %s;\n",params->LHS,":=",params->RHS);
	 params=params->next;
	 }*/

	std::cout << "Automaton name=" << my_ha->getName() << std::endl;
	my_ha->print_var_mapping();
	std::cout << "List of Locations of the automata" << std::endl;
	for (unsigned int i = 0; i < my_ha->getTotalLocations(); i++) {
		std::cout << "loc_id=" << i << " Loc Name="
				<< my_ha->getLocation(i)->getName() << std::endl;
		safe_location::ptr my_loc = my_ha->getLocation(i);
		std::cout << "Invariants: " << std::endl;
		std::list<std::string> inv_str = my_loc->getInvariant();
		for (std::list<std::string>::iterator it = inv_str.begin();
				it != inv_str.end(); it++) {
			std::cout << "\t\t" << (*it) << std::endl;
		}
		std::cout << "Flow Equations: " << std::endl;
		/*std::list<std::string> deriv_str = my_loc->getDerivatives();
		 for (std::list<std::string>::iterator it=deriv_str.begin();it!=deriv_str.end();it++){
		 std::cout<<"\t Infix: " << (*it)<< std::endl;
		 std::cout<<"\t Prefix: " << InfixToPrefix((*it)) << std::endl;
		 }*/

		std::list<flow_equation> deriv_str = my_loc->getDerivatives();
		for (std::list<flow_equation>::iterator it = deriv_str.begin();
				it != deriv_str.end(); it++) {
			std::cout << "\t Infix: " << (*it).derivative << std::endl;
		}
		std::list<std::string> pre_deriv_str = my_loc->getPrefixDerivatives();
		for (std::list<std::string>::iterator it = pre_deriv_str.begin();
				it != pre_deriv_str.end(); it++) {
			std::cout << "\t Prefix: " << (*it) << std::endl;
		}

		std::cout << "Transitions: " << std::endl;
		std::list<safe_transition::ptr> out_going_transitions;//list of out-going-transitions of this location
		out_going_transitions = my_loc->getOutGoingTransitions();
		for (std::list<safe_transition::ptr>::iterator it =
				out_going_transitions.begin();
				it != out_going_transitions.end(); it++) {
			std::cout << "\t\t Trans-ID =" << (*it)->getTransId() << std::endl;
			std::cout << "\t\t Sync Label=" << (*it)->getLabel() << std::endl;
			std::cout << "\t\t From =" << (*it)->getSourceLocationId()
					<< "  To = " << (*it)->getDestinationLocationId()
					<< std::endl;
			std::list<std::string> guard_str = (*it)->getGuard();
			std::cout << "\t\t Guard: " << std::endl;
			for (std::list<std::string>::iterator it_guard = guard_str.begin();
					it_guard != guard_str.end(); it_guard++) {
				std::cout << "\t\t\t" << (*it_guard) << std::endl;
			}
		}
		std::cout
				<< "Assignment: it is kept empty now for controller-program 's output.\n"
				<< std::endl;
	}

	std::cout << "Initial Symbolic state(s): " << std::endl;
	std::list<initial_sym_state::ptr> init_sym_states =
			my_ha->getInitial_Location();
	for (std::list<initial_sym_state::ptr>::iterator it =
			init_sym_states.begin(); it != init_sym_states.end(); it++) {
		std::cout << "\t\t Initial Loc-ID: " << (*it)->getLocId() << std::endl;
		std::list<std::string> init_Set_str = (*it)->getInitialSet();
		std::cout << "\t\t Initial Set (Infix): " << std::endl;
		for (std::list<std::string>::iterator it_init_set =
				init_Set_str.begin(); it_init_set != init_Set_str.end();
				it_init_set++) {
			std::cout << "\t\t\t\t" << (*it_init_set) << std::endl;
		}

		std::list<std::string> prefix_init_Set_str =
				(*it)->getPrefixInitialSet();
		std::cout << "\n\t\t Initial Set (Prefix): " << std::endl;
		for (std::list<std::string>::iterator it_init_set =
				prefix_init_Set_str.begin();
				it_init_set != prefix_init_Set_str.end(); it_init_set++) {
			std::cout << "\t\t\t\t" << (*it_init_set) << std::endl;
		}
	}
}

void populateDataController(controller_program::ptr& control_prog,
		user_inputs::ptr& user_Inputs) {

	generate_ssaFile(user_Inputs);//Run the script(system command) to create the SSA file "fmsafe_Out.ssa".
	read_ssaFile(control_prog, user_Inputs);	//Remember throws exception if SSA file "fmsafe_Out.ssa" not found.

}

