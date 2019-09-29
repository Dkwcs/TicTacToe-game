#include <iostream>
#include <string>
#include <cctype>
#include <algorithm>



inline int isNumber(const std::string& s)
{
	return !s.empty() && std::find_if(s.begin(),
		s.end(), [](char c) { return !std::isdigit(c); }) == s.end();
}
