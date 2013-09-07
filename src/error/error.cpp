/* Please refer to license.txt */

#include "error.hpp"

#include <string>

namespace merror
{

Error::Error()
{
	//message = new mstring::string;
	//*message = "";
	message = nullptr;

	severity = SEVERITY_IGNORE;

	line_number = 0;
	//filename = new mstring::string;
	//*filename = "";
	filename = nullptr;
}

Error::~Error()
{
	if(message)
	{
		delete message;
		message = nullptr;
	}

	if(filename)
	{
		delete filename;
		filename = nullptr;
	}
}

Error* generateError(ErrorType error_type, std::string *message, int severity, int line_number, std::string *filename)
{
	Error *result = new Error;

	result->error_type = error_type;
	result->message = new std::string;
	*result->message = *message;
	result->severity = severity;
	result->line_number = line_number;
	result->filename = new std::string;
	*result->filename = *filename;

	return result;
}

} //namespace merror
