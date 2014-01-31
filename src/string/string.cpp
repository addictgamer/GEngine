/* Please refer to license.txt */

#include "string.hpp"

namespace GEngine
{

namespace mstring
{

void stringToLower(std::string input, std::string &output) //Convert a string from uppercase to lowercase.
{
	for (unsigned long i = 0; i < input.size(); ++i) //Loop through the string and lowercase every character.
	{
		output += tolower(input[i]);
	}
}

std::string stringToLower(std::string input)
{
	std::string result; //Stores the result.
	for (unsigned long i = 0; i < input.size(); ++i) //Loop through the string and lowercase every character.
	{
		result += tolower(input[i]);
	}

	return result; //Return the result.
}

void splitString(std::string str, char delimeter, std::vector<std::string> &output) //Split the given string by the specified delimiter.
{
	std::string new_string = ""; //The new string.

	for (unsigned int i = 0; i < str.size(); ++i)
	{
		//TODO: Change this to work with multiple character delimeters.
		if (str[i] != delimeter) //Make sure the current character is not the delimeter.
		{
			new_string += str[i]; //Save the current character.
		}
		else //Reached delimeter.
		{
			output.push_back(new_string); //Save the new string.
			new_string = ""; //Reset the new string.
		}
	}
	if (new_string != "") //This makes sure to save any unsaved data.
	{
		output.push_back(new_string);
	}
}

void splitStringIntoWords(std::string input, std::vector<std::string> &output) //Takes a string and splits it into the words that make it up, and returns that.
{
	std::string temp = input;
	std::vector<std::string> first_words;
	splitString(temp, ' ', first_words); //Split up the string with space as a delimeter.

	for (unsigned long i = 0; i < first_words.size(); ++i)
	{
		std::string current_word = ""; //The current word.

		std::string word_being_parsed = first_words[i];

		for (unsigned int a = 0; a < word_being_parsed.size(); ++a)
		{
			if (word_being_parsed[a] == '\n') //If a newline.
			{
				if (current_word != "") //If the current word exists.
				{
					output.push_back(current_word); //Save the current word.
					current_word = ""; //Reset this.
				}
				output.push_back("\n"); //Save the new line.
			}
			else
			{
				current_word += word_being_parsed[a]; //Save the current character.
			}
		}

		if (current_word != "") //If a word awaits adding...
		{
			output.push_back(current_word); //Save it.
		}
	}
}

class StringRun
{
public:
	unsigned int character_count; //Its character count.
	std::vector<std::string> words; //The words used in the string run.

	StringRun() //Constructor.
	{
		character_count = 0;
	}

	void concate(std::string &output) //Combines all the word into a string.
	{
		if (words.size() < 1)
		{
			output = ""; //Nullify output.
			return; //Nothing to concate.
		}

		output += words[0];

		for (unsigned long i = 1; i < words.size(); ++i)
		{
			output += " "; //Add a space before the word.
			output += words[i];
		}
	}
};

void formString(std::string input, unsigned int characters_per_string, bool use_newlines_in_result, std::vector<std::string> &output) //A large concation function, essentially.
{
	std::vector<std::string> words;
	splitStringIntoWords(input, words); //Split the string into the words that make it up.

	std::vector<StringRun> string_runs; //The string runs.

	{
		StringRun *new_run = nullptr; //The new string run.

		//bool split_word_across_the_lines; //should a word be split across the lines?

		//int characters_so_far = 0; //The number of characters in the current run.

		for (unsigned long i = 0; i < words.size(); ++i) //Loop through words.
		{
			if (words[i] == "\n") //If a newline.
			{
				if (!new_run) //If the new run does not exist.
				{
					new_run = new StringRun; //Allocate memory for it.
				}
				new_run->words.push_back(words[i]); //Save this word.
				string_runs.push_back(*new_run); //Save the new run.
				delete new_run; //Delete the new run.
				new_run = nullptr; //Reset it.
			}
			else //Is not a newline. Good.
			{
				if (!new_run) //If the new run does not exist, allocate memory for it.
				{
					new_run = new StringRun; //Allocate memory for it.
				}

				if (words[i].size() > characters_per_string) //If the current word is too big...
				{
					if (characters_per_string > 1)
					{
						if (new_run->character_count + 1 >= characters_per_string) //First it has to be smaller than character count to fit at least one more character. The +1 ensures that it can also fit the hyphen that splits the word. Actually, this if in particular checks if it's too long, the word. Not if it fits.
						{
							string_runs.push_back(*new_run); //Save what it's got so far for this run.

							delete new_run; //Delete the new run. Or rather, now the previous run.
							new_run = new StringRun; //Allocate memory for the new run.

							new_run->words.push_back("\n"); //Save this word.
							string_runs.push_back(*new_run); //Save the new run.
							delete new_run; //Delete the new run.
							new_run = new StringRun; //Reset it.
						}

						bool done = false;
						while (!done) //This splits the word.
						{
							unsigned int characters_for_this_run = characters_per_string - 1 - new_run->character_count; //The number of characters permitted in this run. First it sets it as the characters per string, then it subtracts one for the hyphen, and then it subtracts the number of characters used.

							bool all_characters_fit = false; //If all the characters fit, then this loop is done.

							std::string first_string = ""; //All the characters that can fit in this run (with a hyphen at the end, which is added after the characters are put here).
							std::string second_string = ""; //All the characters that can't.

							if (words[i].size() <= characters_for_this_run) all_characters_fit = true; //Check if all the characters fit.

							if (!all_characters_fit) //If all the characters did not fit.
							{
								unsigned int index = 0; //It's int i in the for loop, but we need it to persist across two for loops.
								for (; index < characters_for_this_run; ++index) //Now go through all the characters it can and add them.
								{
									first_string += words[i][index]; //Save the current character.
								}

								for (; index < words[i].size(); ++index) //Loop through the rest of the word and add it into the second string.
								{
									second_string += words[i][index]; //Save the current character.
								}

								words[i] = second_string; //Make words[i] equal the current string so that the next loop of this while function will handle the second string.

								first_string += "-"; //Add the hyphen to the end of the first string.
								new_run->words.push_back(first_string); //Save the first string.
								string_runs.push_back(*new_run); //Save the new run.

								delete new_run; //Delete the new run, that is, the previous run.
								new_run = new StringRun; //Allocate memory for the new run.

								new_run->words.push_back("\n"); //Save the first string.
								string_runs.push_back(*new_run); //Save the new run.
								delete new_run; //Delete the new run, that is, the previous run.
								new_run = new StringRun; //Allocate memory for the new run.
							}
							else
							{
								new_run->words.push_back(words[i]); //Save the current word.
								new_run->character_count += words[i].size(); //Add to the character count.

								words[i] = "";

								done = true;
							}

							if (all_characters_fit)
							{
								done = true; //Done!
							}
						}
					}
					else
					{
						//TODO: This one sometimes does this (OH: Might be because it counts the newline as part of it or something.):
						/*
						B
						l
						a
						r
						g
						.
						 T
						h
						i
						s
						 i
						s
						 s
						e
						n
						t
						e
						n
						c
						e
						 t
						w
						o
						.
						 B
						L
						A
						R
						G
						 B
						L
						A
						R
						G
						 P
						O
						O
						T
						I
						S
						 P
						O
						O
						T
						I
						S
						.
						 H
						i
						p
						p
						o
						p
						a
						t
						a
						u
						m
						.

						A
						b
						i
						g
						 s
						t
						e
						g
						a
						s
						a
						u
						r
						o
						s
						s
						c
						o
						p
						e
						.
						*/
						//Fix it.
						if (new_run->character_count >= characters_per_string) //First it has to be smaller than character count to fit at least one more character. The +1 ensures that it can also fit the hyphen that splits the word. Actually, this if in particular checks if it's too long, the word. Not if it fits.
						{
							string_runs.push_back(*new_run); //Save what it's got so far for this run.

							delete new_run; //Delete the new run. Or rather, now the previous run.
							new_run = new StringRun; //Allocate memory for the new run.

							new_run->words.push_back("\n"); //Save this word.
							string_runs.push_back(*new_run); //Save the new run.
							delete new_run; //Delete the new run.
							new_run = new StringRun; //Reset it.
						}

						bool done = false;
						while (!done) //This splits the word.
						{
							unsigned int characters_for_this_run = characters_per_string - new_run->character_count; //The number of characters permitted in this run. First it sets it as the characters per string, then it subtracts one for the hyphen, and then it subtracts the number of characters used.

							bool all_characters_fit = false; //If all the characters fit, then this loop is done.

							std::string first_string = ""; //All the characters that can fit in this run (with a hyphen at the end, which is added after the characters are put here).
							std::string second_string = ""; //All the characters that can't.

							if (words[i].size() <= characters_for_this_run)
							{
								all_characters_fit = true; //Check if all the characters fit.
							}

							if (!all_characters_fit) //If all the characters did not fit.
							{
								unsigned int index = 0;
								for (; index < characters_for_this_run; ++index) //Now go through all the characters it can and add them.
								{
									first_string += words[i][index]; //Save the current character.
								}

								for (; index < words[i].size(); ++index) //Loop through the rest of the word and add it into the second string.
								{
									second_string += words[i][index]; //Save the current character.
								}

								words[i] = second_string; //Make words[i] equal the current string so that the next loop of this while function will handle the second string.

								new_run->words.push_back(first_string); //Save the first string.
								string_runs.push_back(*new_run); //Save the new run.

								delete new_run; //Delete the new run, that is, the previous run.
								new_run = new StringRun; //Allocate memory for the new run.

								new_run->words.push_back("\n"); //Save the first string.
								string_runs.push_back(*new_run); //Save the new run.
								delete new_run; //Delete the new run, that is, the previous run.
								new_run = new StringRun; //Allocate memory for the new run.
							}
							else
							{
								new_run->words.push_back(words[i]); //Save the current word.
								new_run->character_count += words[i].size(); //Add to the character count.

								words[i] = "";

								done = true;
							}

							if (all_characters_fit)
							{
								done = true; //Done!
							}
						}
					}
				}

				//Do the words that are not too big, and the words that stretch off the line.

				if (new_run->character_count + words[i].size() >= characters_per_string) //Check to make sure it can fit the word.
				{
					string_runs.push_back(*new_run); //Save what it's got so far for this run.
					delete new_run; //Delete the new run. Or rather, now the previous run.
					new_run = new StringRun; //Allocate memory for the new run.

					new_run->words.push_back("\n"); //Save this word.
					string_runs.push_back(*new_run); //Save the new run.
					delete new_run; //Delete the new run.
					new_run = new StringRun; //Reset it.

					new_run->words.push_back(words[i]); //Add the word to the new run.
					new_run->character_count += words[i].size(); //Add to the character count.
				}
				else
				{
					if (words[i] != "") //Make sure it doesn't add an empty string.
					{
						new_run->words.push_back(words[i]); //Add the word to the new run.
						new_run->character_count += words[i].size(); //Add to the character count.
					}
				}
			}
		}

		if (new_run)
		{
			if (new_run->words.size() > 0) //If there are words still waiting.
			{
				string_runs.push_back(*new_run); //Save the new run.
				delete new_run;
				new_run = nullptr;
			}
		}
	}

	//Now turn the StringRuns into a vector of strings.

	for (unsigned long i = 0; i < string_runs.size(); ++i)
	{
		std::string tempstring = "";
		string_runs[i].concate(tempstring);
		if (tempstring == "\n")
		{
			if (use_newlines_in_result) //If the result should include newlines. It is not included in cases like a TTF render function and blarg.
			{
				std::string push_back; //Exists only to grab the result of concate().
				string_runs[i].concate(push_back); //Grab the result.
				output.push_back(push_back); //Add them to the strings vector.
			}
		}
		else
		{
			std::string push_back; //Exists only to grab the result of concate().
			string_runs[i].concate(push_back); //Grab the result.
			output.push_back(push_back); //Add them to the strings vector.
		}
	}
} //formString()

void formStringFromVector(std::vector<std::string> input, std::string &output, std::string mediator)
{
	std::vector<std::string>::iterator i; //Vector iterator.

	for (i = input.begin(); i != input.end(); ++i)
	{
		//Add the mediator only if it's not on the first element so that we don't end up getting things like " THIS IS SOMETHING" instead of "THIS IS SOMETHING".
		if (i != input.begin())
		{
			output += mediator;
		}
		output += *i;
	}
}

std::string chopTail(const std::string &input, char delimeter)
{
	std::string result = input;

	unsigned location = input.find_last_of(delimeter);

	if (location != std::string::npos)
	{
		result = input.substr(0, location);
	}

	return result;
}

void addTailIfNone(std::string &input, char tail)
{
	unsigned location = input.find_last_of(tail); //First look to see if the tail's already in the string.
	if (location != std::string::npos) //It is in the string.
	{
		std::string::iterator iter = input.begin() + location; //Convert location to an iter which we can use.
		if (iter == input.end()) //Check to see if the last character is the tail character.
		{
			//It is. Return, we have nothing to do here.
			return;
		}
	}

	//Tail not last character, append it.
	input += tail;
	return;
}

} //namespace mstring

} //namespace GEngine
