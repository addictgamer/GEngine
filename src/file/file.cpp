/* Please refer to license.txt */

#include <sys/stat.h>
#include <errno.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <dirent.h>
#include <boost/filesystem.hpp>
#include <boost/regex.hpp>

#include "file.hpp"

#include "../error/error.hpp"

#include "../string/string.hpp"

#include "../internal_header.hpp"

#if OS == OS_WINDOWS
	#include <direct.h>
	#define GetCurrentDir _getCurrentWorkingDirectory
#else
	#include <unistd.h>
	#define GetCurrentDir getCurrentWorkingDirectory
#endif

namespace GEngine
{

namespace mfile
{

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
}

void FileManager::exportFile(std::string filepath, std::string output_data, bool overwrite) //Export a file.
{
	FILE *file = nullptr; //The file.

	if (overwrite) file = fopen(filepath.c_str(), "w+"); //Open the file for writing, overwriting whatever currently exists, if anything.
	else file = fopen(filepath.c_str(), "a"); //Open the file for writing. Do not overwrite, append.

	if (!file) //Error checking.
	{
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

void FileManager::getFiles(std::string path, std::vector<std::string> &files, std::string file_filter)
{
	boost::filesystem::path someDir(path); //Convert path to boost.
	boost::filesystem::directory_iterator end_iter;

	boost::regex my_filter(file_filter); //Convert filter to boost.

	if (boost::filesystem::exists(someDir) && boost::filesystem::is_directory(someDir))
	{
		for (boost::filesystem::directory_iterator dir_iter(someDir); dir_iter != end_iter; ++dir_iter)
		{
			if (boost::filesystem::is_regular_file(dir_iter->status())) //Is a file.
			{
				boost::smatch what;
				if (boost::regex_match(dir_iter->path().filename().string(), what, my_filter)) //Check if it matches the filter.
				{
					files.push_back(dir_iter->path().filename().string());
				}
			}
		}
	}
	std::sort(files.begin(), files.end()); //Sort the results.
}

void FileManager::mkDir(std::string path) //Create a directory at the specified location.
{
	namespace fs = boost::filesystem;

	//fs::filesystem_error boost_error;
	if (!fs::create_directory(path))
	{
		//TODO: Check for error and handle accordingly.
	}
}

bool FileManager::directoryExists(std::string path) //Checks if specified directory exists.
{
	return boost::filesystem::exists(path);
} //FileManager::directoryExists()

void FileManager::separatePathFromFilename(std::string &path_with_filename, std::string &path)
{
	//Loop from the back, find the /, chop off everything.

	std::string input(path_with_filename);
	std::string::iterator i = input.end()-1;
	bool done = false;
	while (!done)
	{
		//If it found where the filepath ends...
		if ((*i) != '/' && (*i) != '\\')
		{
			--i; //Keep going.
			input.pop_back(); //Delete the last character.
		}
		else
		{
			done = true;
		}
	}

	path = input;
}

void FileManager::getFolders(std::string path, std::vector<std::string> &folders) //Get all the folders in a directory.
{
	namespace fs = boost::filesystem;
	fs::path someDir(getAbsolutePath(path));
	fs::directory_iterator end_iter;

	if ( fs::exists(someDir) && fs::is_directory(someDir))
	{
		for( fs::directory_iterator dir_iter(someDir) ; dir_iter != end_iter ; ++dir_iter)
		{
			if (fs::is_directory(dir_iter->status()) )
			{
				folders.push_back(dir_iter->path().filename().string());
			}
		}
	}
} //FileManager::getFolders()

std::string FileManager::getParentDirectory(const std::string &path)
{
	std::string new_path = mstring::chopTail(path, '/');
	return new_path;
} //FileManager::getParentDirectory()

std::string FileManager::getAbsolutePath(std::string path) //Turn a relative path into an absolute path.
{
	namespace fs = boost::filesystem;
	fs::path someDir(path);

	if ( fs::exists(someDir) && fs::is_directory(someDir))
	{
		fs::path return_val = fs::absolute(path);
		return_val = fs::canonical(return_val);
		return return_val.filename().string();
	}

	return path; //Failed to convert it.
} //FileManager::getAbsolutePath()

} //namespace mfile

} //namespace GEngine
