/* Copyright Ciprian Ilies */

#include "file.hpp"

#include "../error/error.hpp"

#include "../string/string.hpp"

#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
//#include <iostream>
#include <string.h>
#include <dirent.h>

namespace mfile
{

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

void FileManager::mkDir(std::string path) //Create a directory at the specified location.
{
	#if OS == OS_WINDOWS //If the operating system is windows.
		if (mkdir(path.c_str()) == -1) //Create the directory.
		{
			//throw strerror(errno); //Throw an error. //TODO: Refine the error to use the error module.
			std::string *error_message = new std::string; //The error message.
			*error_message = mstring::toString(strerror(errno)); //Convert the char* that is strerror to a string.
			std::string *filename = new std::string; //The filename.
			*filename = mstring::toString(__FILE__); //Convert the char* that is filename to a string.
			merror::Error *error = generateError(merror::FUNCTION_FAILURE, error_message, merror::SEVERITY_IGNORE, __LINE__, filename);
			throw error;
		}
	#else //OS is not windows.
		if (mkdir(path.c_str(), 0777) == -1)//creating a directory
		{
			//throw strerror(errno); //Throw an error. //TODO: Refine the error to use the error module.
			std::string *error_message = new std::string; //The error message.
			*error_message = mstring::toString(strerror(errno)); //Convert the char* that is strerror to a string.
			std::string *filename = new std::string; //The filename.
			*filename = mstring::toString(__FILE__); //Convert the char* that is filename to a string.
			merror::Error *error = generateError(merror::FUNCTION_FAILURE, error_message, merror::SEVERITY_IGNORE, __LINE__, filename);
			throw error;
		}
	#endif
}

bool FileManager::directoryExists(std::string path) //Checks if specified directory exists.
{
	//This function could probably be done better with a call to an external library's superoptimised directory_exists() function.
	//But, until such a time that we have such a library, this will be used.

	//TODO: This portion probably can be put into an external function.

	//This portion of code determines the path to the directory the directory we're looking for is in.

	bool start_saving = false; //Start saving the characters from the string?
	std::string folderpath = ""; //The folderpath.
	std::string temp_string = ""; //Folderpath is initially read into this, backwards. Used for ordering it correctly.
	std::string directory_name_reverse = ""; //The name of the folder it's looking for. Reversed. This is used because the path is read backwards and everything after the slash is chopped off, thus determining the directory we're looking for's name.
	std::string directory_name = ""; //The name of the folder it's looking for.
	for (int i = path.length() - 1; i >= 0; --i) //Loop through and extract the folderpath. Pretty much the folder the folder is in.
	{
		if (!start_saving && (path[i] == '\\' || path[i] == '/')) //If not already saving the characters...Check if it's a / or \ character.
		{
			start_saving = true; //Yay, end of filename found, now we can extract the folderpath.
			directory_name_reverse += path[i];
		}
		else if (start_saving) //Ok, it is saving the characters.
		{
			temp_string += path[i]; //Save the character.
		}
	}
	for (int i = temp_string.length() - 1; i >= 0; --i) //Now reverse the order of characters so that the folderpath is no longer backwards.
	{
		folderpath += temp_string[i]; //Save the character.
	}
	for (int i = directory_name_reverse.length() - 1;  i >= 0; --i)
	{
		if (directory_name_reverse[i] != '\\' && directory_name_reverse[i] != '/') directory_name += directory_name_reverse[i];
	}
	//TODO: End portion that can be put in external function.

	//This portion of code looks at all the contents in the directory of the directory we're checking the existence of, and looks to see if the directory exists.
	//If it does, then return true. Else return false.

	std::vector<std::string> folders; //Stores all the folder names it finds.

	getFolders(folderpath, folders); //Grabs all the folders in the folder containing the folder which we're checking the existence of.
		
	if (folders.size() == 0)
	{
		return false; //If it found nothing...The directory definitely does not exist!
	}

	for (unsigned int i = 0; i < folders.size(); ++i)
	{
		if (folders[i] == directory_name) return true; //Yes, directory exists.
	}

	return false; //Default case: does not exist.
} //FileManager::directoryExists()


void FileManager::exportFile(std::string filepath, std::string output_data, bool overwrite) //Export a file.
{
	FILE *file = nullptr; //The file.

	if (overwrite) file = fopen(filepath.c_str(), "w+"); //Open the file for writing, overwriting whatever currently exists, if anything.
	else file = fopen(filepath.c_str(), "a"); //Open the file for writing. Do not overwrite, append.

	if (!file) //Error checking.
	{
		//cout << "Failed to open file: \"" << filepath << "\".\n"; //Let the user know there was an error.
		//cout << "Attempting to create folder...\n"; //Let the user know we're trying to create the directory.

		//TODO: This portiong needs to be put into a "make_directories_until()" function.

		//TODO: This needs to be adjusted to recursively make the missing folders.

		bool start_saving = false; //Start saving the characters from the string?
		std::string folderpath = ""; //The folderpath.
		std::string temp_string = ""; //Folderpath is initially read into this, backwards. Used for ordering it correctly.
		for (int i = filepath.length() - 1; i >= 0; --i) //Loop through and extract the folderpath
		{
			if (!start_saving && (filepath[i] == '\\' || filepath[i] == '/')) //If not already saving the characters...Check if it's a / or \ character.
			{
				start_saving = true; //Yay, end of filename found, now we can extract the folderpath.
			}
			if (start_saving) //Ok, it is saving the characters.
			{
				temp_string += filepath[i]; //Save the character.
			}
		}
		for (int i = temp_string.length() - 1; i >= 0; --i) //Now reverse the order of characters so that the folderpath is no longer backwards.
		{
			folderpath += temp_string[i]; //Save the character.
		}

		try
		{
			mkDir("./" + folderpath); //Create the folder. With error checking.
		}
		catch (...)
		{
			std::string *filename = new std::string; //The filename.
			*filename = mstring::toString(__FILE__); //Convert the char* that is filename to a string.
			std::string *message = new std::string;
			*message = "Failed to create directory: \"";
			*message += folderpath;
			*message += "\".";
			merror::Error *error = generateError(merror::FUNCTION_FAILURE, message, merror::SEVERITY_IGNORE, __LINE__, filename);
			throw error;
		}

		if (overwrite) file = fopen(filepath.c_str(), "w+"); //Open the file for writing, overwriting any currently existing file.
		else file = fopen(filepath.c_str(), "a"); //Open the file for writing. Do not overwrite, append.

		if (!file) //Error checking.
		{
			std::string *filename = new std::string; //The filename.
			*filename = mstring::toString(__FILE__); //Convert the char* that is filename to a string.
			std::string *message = new std::string;
			*message = "Failed to create file.";
			merror::Error *error = generateError(merror::FUNCTION_FAILURE, message, merror::SEVERITY_IGNORE, __LINE__, filename);
			throw error; //Failure.
		}

		//TODO: End portion that needs being put into a "make_directories_until()" function.
	}

	fprintf(file, output_data.c_str());  //Write out the string.

	fclose(file); //Close the file.
} //FileManager::exportFile()

void FileManager::getFolders(std::string path, std::vector<std::string> &folders) //Get all the folders in a directory.
{
	#if OS == OS_WINDOWS
		struct stat s; //Required for the Windows version of the code 
	#endif

	DIR *dir ; //Open the bases folder.

	if ((dir = opendir(path.c_str())) == nullptr) //Open directory. With error checking.
	{
		std::string *filename = new std::string; //The filename.
		*filename = mstring::toString(__FILE__); //Convert the char* that is filename to a string.
		std::string *message = new std::string;
		*message = "Failed to open directory.";
		merror::Error *error = generateError(merror::FUNCTION_FAILURE, message, merror::SEVERITY_IGNORE, __LINE__, filename);
		throw error;
	}

	struct dirent *entry = readdir(dir); //The current directory entry

	while (entry != NULL) //Loop through all the folders (and files) in this directory.
	{
		#if OS == OS_WINDOWS

			//TODO: Test this to see if it works in Windows.

			stat(entry->d_name, &s);
			if (s.st_mode & S_IFDIR)
			{
				if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) //Make sure it's not the current directory, or the one containing this directory!
				{
					folders.push_back(entry->d_name);
				}
			}

			entry = readdir(dir); //Load in the next entry.

		#else

			if (entry->d_type == DT_DIR) //If the entry type is a folder.
			{
				if (strcmp(entry->d_name, ".") != 0 && strcmp(entry->d_name, "..") != 0) //Make sure it's not the current directory, or the one containing this directory!
				{
					folders.push_back(entry->d_name);
				}
			}

		#endif
	}

	closedir(dir);
} //FileManager::getFolders()

} //namespace mfile
