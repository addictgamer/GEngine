/* Please refer to license.txt */

#pragma once

#include <string>
#include <vector>

namespace mconfig
{

class Variable
{
public:
	std::vector<std::string> values; //The value(s) of the variable;
	std::string name; //The variable's name/identifier.

	Variable();
	~Variable();

	bool isBool(const unsigned int x); //Returns true if value[x] is a boolean value.

	//int getInt(unsigned int x); //Returns the converted integer value of value[x].

	std::string getName();
};

class CFG
{
public:
	CFG();
	~CFG();

	bool parseCFG();
};

} //namespace mconfig
