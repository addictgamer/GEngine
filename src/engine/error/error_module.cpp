/* Copyright Ciprian Ilies */

#include "error.hpp"

ErrorModule::ErrorModule()
{
}

ErrorModule::~ErrorModule()
{
}

//Initialize the error module.
bool ErrorModule::initialize()
{
	return true; //Success.
}

//Quit the error module.
void ErrorModule::quit()
{
	//Loop through all the errors.
	while(errors.size() > 0)
	{
		delete errors[0]; //Delete the error we're currently on.
		errors.erase(errors.begin()); //Erase the current error.
	}
}

//Generate an error.
merror::Error* ErrorModule::generateError(merror::ErrorType error_type, std::string *message, int severity, int line_number, std::string *filename)
{
	//First, create the error.
	merror::Error *error = merror::generateError(error_type, message, severity, line_number, filename);

	//Next, add it to the error list.
	errors.push_back(error);

	//Finally, return the error.
	return error;
}

//Remove an error.
bool ErrorModule::removeError(merror::Error *error)
{
	if(!error)
	{
		return false; //Can't check a null pointer.
	}

	for(unsigned long i = 0; i < errors.size(); ++i) //Loop through all the errors.
	{
		if(errors[i] == error) //Check if the error has been found.
		{
			delete error; //Free the memory.
			errors.erase(errors.begin() + i); //Erase the vector entry.

			return true; //Success!
		}
	}

	return false; //Failure, aww.
}

void ErrorModule::getListOfErrors(std::vector<merror::Error *> &output)
{
	//This had better not be assigning output as a pointer to errors. I want it to make a copy.
	output = errors; //Ya, that's it. Pretty simple.
}
