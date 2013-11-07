/* Please refer to license.txt */

/* --------------------------------------------------------------
 * Everything related to strings are defined here.
 * ----------------------------------------------------------- */

#pragma once

#include <vector>
#include <string>
#include <sstream>

namespace GEngine
{

namespace mstring
{

//Currently, there's no need to program our own version of string.
//So for now, use C++'s built-in string type.
//If at any point in time there arises the need for a custom string type, then remove this #define string and create a new string type here.
//TODO: Actually, it can be made into our own class, which just wraps the standard template library's class.
//TODO: That way, we can treat float_to_string and the others as built in functions.
//TODO: Uncommented because it causes problems currently.
//#define string std::string


//First, we have the conversion functions.


//TODO: Might be better to use template functions here.

template <typename T>
std::string toString(T value) {
    std::stringstream ss;
    ss << value;
    return ss.str();
}

//Convert a string into a float.
//The resulting float is returned.
//TODO: Write this.
float stringToFloat(std::string value);

//Convert a string into a double.
//The resulting double is returned.
//TODO: Write this.
double stringToDouble(std::string value);

//Convert a string into an int.
//The resulting int is returned.
//TODO: Write this.
int stringToInt(std::string value);

//Convert a string into a long.
//The resulting long is returned.
//TODO: Write this.
long stringToLong(std::string value);


//Now we have various other string operation functions.


//Convert a string from uppercase to lowercase.
//The result is stored in output.
void stringToLower(std::string input, std::string &output);
//Alternate version of the above, which returns the modified string rather than storing it in output.
std::string stringToLower(std::string input);

//Split the given string by the specified delimiter.
//The result is stored in result.
void splitString(std::string str, char delimeter, std::vector<std::string> &output);

//Takes a string turns it into a vector of strings putting as much into each string as it can without exceeding the characters per string limit.
//The use_newlines_in_result paramater determines if newlines will be returned with the result.
//The result is stored in output.
void formString(std::string input, unsigned int characters_per_string, bool use_newlines_in_result, std::vector<std::string> &output);

/*
 * Takes a vector of strings and concates them into one string.
 */

/*
 * Takes a vector of strings and concates them.
 * The result is stored in output.
 * mediator is whatever you want to split each word in the output string (would delimeter be the correct word here?).
 */
void formStringFromVector(std::vector<std::string> input, std::string &output, std::string mediator = "");


/*
 * Takes a string and splits it into the words that make it up.
 * The result is stored in output.
 */
void splitStringIntoWords(std::string input, std::vector<std::string> &output);

/*
 * Takes a string, starts at the end, and looks from the end to the front until it finds the delimeter and chops out everything after the delimeter.
 * Parameters:
 *	input		=	The input string
 *	delimeter	=	The delimeter character
 * NOTE: Do not give it an input string that ends with the delimeter. Get rid of the delimeter first! Use std::string::pop_back() to do such.
 * Man, redundant elaboration is funny and silly at the same time. I'll just leave it for now.
 */
std::string chopTail(const std::string &input, char delimeter);


/*
 * Takes a string and adds a tail (a character) to the end if it's not already present.
 * Useful for file operations.
 * Paramters:
 *	input	=	The input string
 *	tail	=	The tail character
 * Doesn't return anything. The input string is modified.
 */
void addTailIfNone(std::string &input, char tail);

} //namespace mstring

} //namespace GEngine
