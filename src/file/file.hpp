/* Please refer to license.txt */

/* Here we have the file manager. Its purpose is to encapsulate code that may
 * vary wildly, depending on implementation, allowing the specific code
 * implementation to be changed however it seen best without having to rewrite
 * the game. This allows for the easy porting of the game to other platforms.
 */

#pragma once

#include <string>
#include <vector>

namespace GEngine
{

namespace mfile
{

class FileManager
{
public:
	FileManager();
	~FileManager();

	//Export a file.
	//The first parameter asks for the filepath, and the second parameter asks for the data to export.
	//The third parameter asks if the file should be overwritten or appended to. True and false, respectively.
	//Throws on error.
	//TODO: Refine to use the error module.
	void exportFile(std::string filepath, std::string output_data, bool overwrite);

	//This function will create all directories that don't exist in the path passed to it.
	//Paramaters: Path.
	//Eg:
	/*
	recursively_make_directories("./data/save/save1/characters/bob/");
	*/
	//Where only the folders data and save currently exist, thus causing the function to create the directories characters and bob.
	//Throws on error.
	//TODO: Write it.
	void recursivelyMakeDirectories(std::string path);

	//TODO: Write this.
	void separateFilenameFromPath(std::string path, std::string &filename);

	//TODO: Write this.
	void separateFilenameFromFileExtension(std::string filename_with_extension, std::string &filename);

	/*
	 * Get all the files in a directory.
	 * Parameters:
	 *	path		=	the directory's path
	 *	files		=	the vector to store the files in
	 *	file_filter	=	the filter to return only the files we are looking for (take that, Obi Wan!)
	 */
	static void getFiles(std::string path, std::vector<std::string> &files, std::string file_filter = "*");

	/*
	 * Get all the folders in a directory.
	 * Parameters:
	 * path, the path to the directory of which you want to get all the folders of.
	 * folders, a reference to the array of strings that is to have the foldernames stored in.
	 * Throws on error.
	 * TODO: Refine this to use the error module.
	 */
	static void getFolders(std::string path, std::vector<std::string> &folders);

	/*
	 * Create a directory at the specified location.
	 * Throws on error.
	 * TODO: Refine to use the error module.
	 */
	static void mkDir(std::string path);

	/*
	 * Checks to see if a directory exists.
	 * Returns true if exist, false if does not.
	 * Arguments: Directory path.
	 * Example: ./folders/blarg/does_this_folder_exist
	 */
	static bool directoryExists(std::string path);

	/*
	 * Checks to see if a file exists.
	 * Returns true if it exists, false if it does not.
	 * Arguments: File path.
	 * Example: ./folders/blarg/does_this_file_exist
	 */
	static bool fileExists(std::string path);

	/*
	 * Separates the path from the filename and stores it in path.
	 */
	static void separatePathFromFilename(std::string &path_with_filename, std::string &path);

	/*
	 * Equivalent to "cd .."
	 * Parameters:
	 *	path	=	Path to the starting directory.
	 * Returns a string with the new path.
	 * Returns what it was given if it's already at the highest level directory. //TODO: Is this a good idea? At least give a warning, maybe?
	 */
	static std::string getParentDirectory(const std::string &path);

	/*
	 * Turns a relative path into an absolute path.
	 * Eg: "." into "/home/who/programs/MyProgram/"
	 * Parameters:
	 *	path	=	The relative path to make into an absolute path.
	 */
	static std::string getAbsolutePath(std::string path);
}; //class FileManager

} //namespace mfile

} //namespace GEngine
