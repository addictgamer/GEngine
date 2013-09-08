/* Please refer to license.txt */

/* Here we have the file manager. Its purpose is to encapsulate code that may
 * vary wildly, depending on implementation, allowing the specific code
 * implementation to be changed however it seen best without having to rewrite
 * the game. This allows for the easy porting of the game to other platforms.
 */

#pragma once

#include <string>
#include <vector>

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

	//TODO: Write this.
	void getFiles(std::string path, std::vector<std::string> &files);

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
	static bool directoryExists(std::string directory);

	/*
	 * Separates the path from the filename and stores it in path.
	 */
	static void separatePathFromFilename(std::string &path_with_filename, std::string &path);

	/*
	 * Get all the folders in a directory.
	 * Parameters:
	 * path, the path to the directory of which you want to get all the folders of.
	 * folders, a reference to the array of strings that is to have the foldernames stored in.
	 * Throws on error.
	 * TODO: Refine this to use the error module.
	 */
	static void getFolders(std::string path, std::vector<std::string> &folders);
}; //class FileManager

} //namespace mfile
