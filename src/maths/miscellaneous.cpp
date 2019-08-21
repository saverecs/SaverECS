/*
 * miscellaneous.cpp
 *
 *  Created on: 19-Jul-2018
 *      Author: amit
 */

#include "miscellaneous.h"

bool isa_Number(std::string strNum){
	std::string s = trim(strNum);
	bool has_only_digits = true;
	for (size_t n = 0; n < s.length(); n++)
	{
	  if (!isdigit( s[ n ] )) {
		  std::string st(1,s[n]), period=".";
			if (st.compare(period)) {
				has_only_digits = false;
				break;
			}
	    }
	}

	if (has_only_digits)
		return true;
	else
		return false;
}


// trim from start
std::string ltrim(std::string s) {
    s.erase(s.begin(), std::find_if(s.begin(), s.end(),
            std::not1(std::ptr_fun<int, int>(std::isspace))));
    return s;
}

// trim from end
std::string rtrim(std::string s) {
    s.erase(std::find_if(s.rbegin(), s.rend(),
            std::not1(std::ptr_fun<int, int>(std::isspace))).base(), s.end());
    return s;
}

// trim from both ends
std::string trim(std::string s) {
    return ltrim(rtrim(s));
}

