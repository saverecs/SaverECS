/*
 * controller.h
 *
 *  Created on: 08-Jun-2018
 *      Author: amit
 */

#ifndef CORESYSTEM_CONTROLLER_PROGRAM_CONTROLLER_H_
#define CORESYSTEM_CONTROLLER_PROGRAM_CONTROLLER_H_

#include <iostream>
#include <string>
#include <list>
#include <boost/shared_ptr.hpp>

#include "utilities/datastructure_plant.h"


using namespace std;

class controller_program{

	/*std::list<std::pair<std::string, std::string> > intermediateVariables;
	std::list<std::pair<std::string, std::string> > inputVariables;
	std::list<std::pair<std::string, std::string> > outputVariables;*/

	std::list<variablesContorller> intermediateVariables;
	std::list<variablesContorller> inputVariables;
	std::list<variablesContorller> outputVariables;


	std::list<std::string> ssaStatements;
public:
	typedef boost::shared_ptr<controller_program> ptr;
	controller_program();
	/*const std::list<std::pair<std::string, std::string> >& getInputVariables() const;
	void setInputVariables(const std::list<std::pair<std::string, std::string> >& inputVariables);
	const std::list<std::pair<std::string, std::string> >& getIntermediateVariables() const;
	void setIntermediateVariables(const std::list<std::pair<std::string, std::string> >& intermediateVariables);
	const std::list<std::pair<std::string, std::string> >& getOutputVariables() const;
	void setOutputVariables(const std::list<std::pair<std::string, std::string> >& outputVariables);*/

	const std::list<variablesContorller >& getInputVariables() const;
	void setInputVariables(const std::list<variablesContorller >& inputVariables);
	const std::list<variablesContorller >& getIntermediateVariables() const;
	void setIntermediateVariables(const std::list<variablesContorller >& intermediateVariables);
	const std::list<variablesContorller>& getOutputVariables() const;
	void setOutputVariables(const std::list<variablesContorller >& outputVariables);

	const std::list<std::string>& getSsaStatements() const;
	void setSsaStatements(const std::list<std::string>& ssaStatements);

	void displayController();
};



#endif /* CORESYSTEM_CONTROLLER_PROGRAM_CONTROLLER_H_ */
