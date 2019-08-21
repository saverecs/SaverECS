/*
 * miscellaneous.h
 *
 *  Created on: 19-Jul-2018
 *      Author: amit
 */

#ifndef MATHS_MISCELLANEOUS_H_
#define MATHS_MISCELLANEOUS_H_


#include <cctype>
#include <ctype.h>
#include <string>
#include <iostream>


// *********** Header files for ltrim, rtrim, trim ****************
//https://stackoverflow.com/questions/216823/whats-the-best-way-to-trim-stdstring
#include <algorithm>
#include <functional>
#include <cctype>
#include <locale>
// *********** ****************

bool isa_Number(std::string s);

std::string ltrim(std::string s);
std::string rtrim(std::string s);
std::string trim(std::string s);



#endif /* MATHS_MISCELLANEOUS_H_ */
