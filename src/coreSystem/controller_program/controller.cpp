/*
 * controller.cpp
 *
 *  Created on: 08-Jun-2018
 *      Author: amit
 */

#include "controller.h"

controller_program::controller_program() {
	;
}

const std::list<variablesContorller>& controller_program::getInputVariables() const {
	return inputVariables;
}

void controller_program::setInputVariables(
		const std::list<variablesContorller>& inputVariables) {
	this->inputVariables = inputVariables;
}

const std::list<variablesContorller>& controller_program::getIntermediateVariables() const {
	return intermediateVariables;
}

void controller_program::setIntermediateVariables(
		const std::list<variablesContorller>& intermediateVariables) {
	this->intermediateVariables = intermediateVariables;
}

const std::list<variablesContorller>& controller_program::getOutputVariables() const {
	return outputVariables;
}

void controller_program::setOutputVariables(
		const std::list<variablesContorller>& outputVariables) {
	this->outputVariables = outputVariables;
}

const std::list<std::string>& controller_program::getSsaStatements() const {
	return ssaStatements;
}

void controller_program::setSsaStatements(
		const std::list<std::string>& ssaStatements) {
	this->ssaStatements = ssaStatements;
}

void controller_program::displayController() {

	std::cout << "\nController Program: " << std::endl;
	std::cout << "\tIntermediate Variables: " << std::endl;
	for (std::list<variablesContorller>::iterator it =
			intermediateVariables.begin(); it != intermediateVariables.end();
			it++) {
		std::cout << "\t\t" << (*it).var_type << "\t" << (*it).var_name << "  ["
				<< (*it).lbound << " , " << (*it).ubound << "]" << std::endl;
	}
	std::cout << "\n\tInput Variables: " << std::endl;
	for (std::list<variablesContorller>::iterator it = inputVariables.begin();
			it != inputVariables.end(); it++) {
		std::cout << "\t\t" << (*it).var_type << "\t" << (*it).var_name << "  ["
				<< (*it).lbound << " , " << (*it).ubound << "]" << std::endl;
	}
	std::cout << "\n\tOutput Variables: " << std::endl;
	for (std::list<variablesContorller>::iterator it = outputVariables.begin();
			it != outputVariables.end(); it++) {
		std::cout << "\t\t" << (*it).var_type << "\t" << (*it).var_name << "  ["
				<< (*it).lbound << " , " << (*it).ubound << "]" << std::endl;
	}
	std::cout << "\n\n\tSSA Statements: " << std::endl;
	for (std::list<std::string>::iterator it = ssaStatements.begin();
			it != ssaStatements.end(); it++) {
		std::cout << "\t\t" << (*it) << std::endl;
	}

}
