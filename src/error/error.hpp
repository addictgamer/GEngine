/* Please refer to license.txt */

#pragma once

#include <vector>
#include <string>

namespace merror
{

static const int SEVERITY_IGNORE = 0;
static const int SEVERITY_WARN = 1;
static const int SEVERITY_FATAL = 2;

//Unimplemented = unimplemented code was called.
//Mostly debugging applications/code cleaning/figuring out what needs to be done next.
static const int ERRORTYPE_UNIMPLEMENTED = 0;
//Invalid input = invalud input was given.
static const int ERRORTYPE_INVALID_INPUT = 1;
//Obsolete = obsolete code was used.
//Mostly debugging applications/code cleaning.
static const int ERRORTYPE_OBSOLETE = 2;
//Unhandled exception = an unhandled exception.
static const int ERRORTYPE_UNHANDLED_EXCEPTION = 3;
//A fatal error of some sort.
//Should be accompanied by SEVERITY_FATAL.
static const int ERRORTYPE_FATAL_ERROR = 4; //I don't really see when this should be used.
//Invalid pointer = just that.
static const int ERRORTYPE_INVALID_POINTER = 5;
//This error occurs whenever a pointer that should be initialized, but is not, is encountered.
//These kinds of errors should not occur in release code.
//They shouldn't occur at all, but such mistakes are inevitable.
static const int ERRORTYPE_UNINITIALIZED_POINTER = 6;
//This error signifies corrupt memory/data.
static const int ERRORTYPE_CORRUPT = 7;
//Whenever a function fails, this is used.
static const int ERRORTYPE_FUNCTION_FAILURE = 8;
//Whenever that else that should never be reached is reached...
static const int ERRORTYPE_UNREACHABLE_ELSE_REACHED = 9;
//Some other error not defined here.
static const int ERRORTYPE_OTHER = 10;

enum ErrorType
{
	UNIMPLEMENTED = ERRORTYPE_UNIMPLEMENTED,
	INVALID_INPUT = ERRORTYPE_INVALID_INPUT,
	OBSOLETE = ERRORTYPE_OBSOLETE,
	UNHANDLED_EXCEPTION = ERRORTYPE_UNHANDLED_EXCEPTION,
	FATAL_ERROR = ERRORTYPE_FATAL_ERROR, //I don't really see when this should be used.
	INVALID_POINTER = ERRORTYPE_INVALID_POINTER,
	UNINITIALIZED_POINTER = ERRORTYPE_UNINITIALIZED_POINTER,
	CORRUPT = ERRORTYPE_CORRUPT,
	FUNCTION_FAILURE = ERRORTYPE_FUNCTION_FAILURE,
	UNREACHABLE_ELSE_REACHED = ERRORTYPE_UNREACHABLE_ELSE_REACHED,
	OTHER = ERRORTYPE_OTHER
};

class Error
{
public:
	//I just hate it when c++ does this. This HAS to be a pointer <.<
	std::string *message; //The error's message/summary/error details.

	ErrorType error_type; //The error type.

	int severity; //The severity.

	int line_number; //The line number the error occurred on.
	//Again, silly c++ and making me make this a pointer.
	std::string *filename; //The name of the file the error occurred in.

	Error();
	~Error();
};

//NOTE: Do NOT use this function to generate an error. Use the error module's same function.
//Generates an error from the info passed to it, and returns a pointer to the error.
//Parameters:
//error_type: See the Error class, variable of the same name.
//message: See the Error class, variable of the same name.
//severity: See the Error class, variable of the same name.
//line_number: See the Error class, variable of the same name.
//filename: See the Error class, variable of the same name.
Error* generateError(ErrorType error_type, std::string *message, int severity, int line_number, std::string *filename);

} //namespace merror



//The error module class.
//It handles everything in the error module and acts as an interface to the rest of the program.
class ErrorModule
{
public:
	ErrorModule();
	~ErrorModule();

	//Call this to initialize the error module.
	//Returns false on error.
	bool initialize();

	//Call this on program exit to free everything the error module is using.
	void quit(); //Exit the error module.

	//Generate an error.
	//Returns a pointer to the error.
	//Paramaters:
	//
	//Please do not generate any errors without this function.
	merror::Error* generateError(merror::ErrorType error_type, std::string *message, int severity, int line_number, std::string *filename);

	//Remove/deallocate an error. This is used to mark an error as "handled".
	//Returns true on successs, false on failure.
	bool removeError(merror::Error *error);

	//Returns the list of errors to output.
	void getListOfErrors(std::vector<merror::Error *> &output);

private:
	std::vector<merror::Error *> errors; //Vector of all the active errors. //TODO: Update this to a std::map. Maybe.
};
