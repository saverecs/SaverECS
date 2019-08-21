/*
 * readCommandLine.h
 *
 *  Created on: 03-May-2018
 *      Author: amit
 */

#ifndef READCOMMANDLINE_H_
#define READCOMMANDLINE_H_


// *********** Command Line Boost Program Options ********
#include <boost/program_options/config.hpp>
#include "boost/program_options.hpp"
#include <boost/config.hpp>
#include <boost/program_options/detail/config_file.hpp>
#include <boost/program_options/parsers.hpp>
#include <boost/algorithm/string.hpp> //string comparison
// *********** Command Line Boost Program Options ********

#include "user_inputs.h"


void readCommandLine(int argc, char *argv[], user_inputs::ptr& userInputs);


#endif /* READCOMMANDLINE_H_ */
