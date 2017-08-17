/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 1 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <boost/tokenizer.hpp>
#include <boost/program_options.hpp>
#include <boost/algorithm/string.hpp>
#include "custom_list.h"
#include "custom_tree.h"

typedef std::array<std::string, 5> sArray5;
bool loadFiles(std::ifstream *dictionary, std::string dictOpt, std::ifstream *textFile,
	       	std::string textOpt, std::ofstream *outputFile, std::string outputOpt);
bool loadDatastruct(std::string datastruct, std::ifstream *dictionary, 
		std::ifstream *textFile, std::ofstream *outputFile, const sArray5 ds);
bool loadCustomList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputfile);
bool loadCustomTree(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile);
bool loadVector(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile);
bool loadSet(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile);
bool loadList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile);
bool checkVector(std::vector<std::string> *text, std::vector<std::string> *dict, std::ofstream *outputFile);

int main(int argc, char* argv[])
{
	const int numArgs = 9;
	const sArray5 ds = {"custom_list", "custom_tree", "list", "set", "vector"};
	if(argc != numArgs)
	{
		std::cout << "Incorrect amount of arguments" << std::endl;
		std::cout << "Please enter in the folowing format" << std::endl;
		std::cout << "./test_datastructures structure [datastructure] dict [dictionary] text [textfile] output [outputfile]" << std::endl;
		exit(1);
	}
	else
	{
		std::string datastruct;
		std::string dictOpt;
		std::string textOpt;
		std::string outputOpt;
		std::ifstream dictionary;
		std::ifstream textFile;
		std::ofstream outputFile;

		boost::program_options::options_description progOpt("Options");
		progOpt.add_options()
			(",s", boost::program_options::value<std::string>(&datastruct)->required(), "Datastructure")
			(",d", boost::program_options::value<std::string>(&dictOpt)->required(), "Dictionary File")
			(",t", boost::program_options::value<std::string>(&textOpt)->required(), "Text File")
			(",o", boost::program_options::value<std::string>(&outputOpt)->required(), "Output File")
			;
		boost::program_options::variables_map vm;
		boost::program_options::store(parse_command_line(argc, argv, progOpt), vm);
		notify(vm);
		
		loadFiles(&dictionary, dictOpt, &textFile, textOpt, &outputFile, outputOpt);
	
		loadDatastruct(datastruct, &dictionary, &textFile, &outputFile, ds);	
	}
	std::cout << "DEBUG: COMPLETE" << std::endl;
}
bool loadFiles(std::ifstream *dictionary, std::string dictOpt,
		std::ifstream *textFile, std::string textOpt, std::ofstream *outputFile, std::string outputOpt)
{
	dictionary->open(dictOpt);
	if(!dictionary)
	{
		std::cout << "Could not open " << dictOpt
			<< " for reading" << std::endl;
		exit(1);
	}
	textFile->open(textOpt);
	if(!textFile)
	{
		std::cout << "Could not open " << textOpt
			<< " for reading" << std::endl;
		exit(1);
	}

	outputFile->open(outputOpt);
	if(!outputFile)
	{
		std::cout << "Could not open " << outputOpt
			<< " for writting" << std::endl;
		exit(1);
	}
	return true;
}
bool loadDatastruct(std::string datastruct, std::ifstream *dictionary, 
		std::ifstream *textFile, std::ofstream *outputFile, const sArray5 ds)
{
	if(datastruct == ds[0])
	{
		return loadCustomList(textFile, dictionary, outputFile);
	}
	else if(datastruct == ds[1])
	{
		return loadCustomTree(textFile, dictionary, outputFile);
	}
	else if(datastruct == ds[2])
	{
		return loadList(textFile, dictionary, outputFile);
	}
	else if(datastruct == ds[3])
	{
		return loadSet(textFile, dictionary, outputFile);
	}
	else if(datastruct == ds[4])
	{
		return loadVector(textFile, dictionary, outputFile);
	}
	std::cout << "DEBUG DATASTRUCTURE COMPLETE" << std::endl;
	return false;
}
bool loadCustomList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile) 
{
	custom_list dictionaryList;
	custom_list textList;
	std::map<std::string, int> wordCount;
	
	std::string newString;
	
	typedef	boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");
	
	while(std::getline(*dictionary, newString, '\n'))
	{
		dictionaryList.push_front(newString);
	}
	dictionary->close();
	std::cout << "DICTIONARY LIST" << std::endl;
	dictionaryList.printSize();

	while(std::getline(*textFile, newString, '\n'))
	{
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			textList.push_front(*tok_iter);
		}
	}
	textFile->close();
	std::cout << "TEXT LIST" << std::endl;
	textList.printSize();

	textList.checkList(&dictionaryList, outputFile);
	return true;
}
bool loadCustomTree(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	custom_tree textTree;
	custom_tree dictionaryTree;
	
	std::string newString;
	typedef	boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");
	
	while(std::getline(*textFile, newString, '\n'))
	{
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			textTree.addNode(*tok_iter);
		}
	}
	textFile->close();
	while(*dictionary >> newString)
	{
		dictionaryTree.addNode(newString);
	}
	dictionary->close();
	
	textTree.checkTree(&dictionaryTree, outputFile);

	return true;
}
bool loadVector(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	std::vector<std::string> dict;
	std::string newString;
	while(std::getline(*dictionary, newString, '\n'))
	{
		dict.push_back(newString);
	}
	
	std::vector<std::string> text;
	typedef	boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");
	
	while(std::getline(*textFile, newString, '\n'))
	{
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			text.push_back(*tok_iter);
		}
	}
	checkVector(&text, &dict, outputFile);
	return true;
}
bool loadSet(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	std::cout << "DEBUG: LIST RINNING" << std::endl;
	std::multiset<std::string> setDict;
	std::string newString;
	while(std::getline(*dictionary, newString, '\n'))
	{
		setDict.insert(newString);
	}

	std::multiset<std::string> setText;
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");

	while(std::getline(*textFile, newString, '\n'))
	{
		std::cout << "DEBUG: " << newString << std::endl;
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			setText.insert(*tok_iter);
		}
	}
	std::cout << "DEBUG: DICTIONARY SET" << std::endl;
	std::cout << "DEBUG:===================================================" << std::endl;
	for(std::multiset<std::string>::iterator set_iter = setDict.begin(); set_iter != setDict.end(); set_iter++)
	{
		std::cout << *set_iter << std::endl;
	}
	std::cout << "DEBUG: TEXT SET" << std::endl;
	std::cout << "DEBUG:===================================================" << std::endl;
	for(std::multiset<std::string>::iterator set_iter = setText.begin(); set_iter != setText.end(); set_iter++)
	{
		std::cout << *set_iter << std::endl;
	}
	return true;
}
bool loadList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	std::cout << "DEBUG: RUN LIST" << std::endl;
	std::list<std::string> dict;
	std::string newString;
	while(std::getline(*dictionary, newString, '\n'))
	{
		std::cout << "DEBUG: ADD TO DICTIONARY" << std::endl;
		dict.push_front(newString);
	}
	std::list<std::string> text;
	typedef	boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");
	
	while(std::getline(*textFile, newString, '\n'))
	{
		std::cout << "DEBUG: ADD TO TEXT" << std::endl;
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			std::cout << "DEBUG: TOKENIZE TEXT" << std::endl;
			text.push_back(*tok_iter);
		}
	}
	
	std::cout << "DEBUG: DICT LIST" << std::endl;
	std::cout << "DEBUG:===================================================" << std::endl;
	for(std::list<std::string>::iterator list_iter = dict.begin(); list_iter != dict.end(); list_iter++)
	{
		std::cout << *list_iter << std::endl;
	}
	
	std::cout << "DEBUG: TEXT LIST" << std::endl;
	std::cout << "DEBUG:===================================================" << std::endl;
	for(std::list<std::string>::iterator list_iter = text.begin(); list_iter != text.end(); list_iter++)
	{
		std::cout << *list_iter << std::endl;
	}
	return true;
}
bool checkVector(std::vector<std::string> *text, std::vector<std::string> *dict, std::ofstream *outputFile)
{
	std::map<std::string, int> wordCount;
	std::string textString;
	std::string dictString;
	
	std::ofstream wordCountFile;
       	wordCountFile.open("word_count.csv");	
	if(!wordCountFile)
	{
		std::cout << "Could not open word_count.csv for writing" << std::endl;
		exit(0);
	}

	for(size_t i = 0; i < text->size(); i++)
	{
		textString = (*text)[i];
		transform(textString.begin(), textString.end(), textString.begin(),::tolower);
		for(size_t i = 0; i < dict->size(); i++)
		{
			dictString = (*dict)[i];
			if(textString == dictString)
			{
				std::pair<std::map<std::string,int>::iterator,bool> uniqueString;
				uniqueString = wordCount.insert(std::pair<std::string, int>(textString, 1));
				if(uniqueString.second == false)
				{
					++wordCount[textString];
				}
			}
		}
	} 
	for (std::map<std::string, int>::iterator it= wordCount.begin(); it!= wordCount.end(); ++it)
	{
    		wordCountFile << it->first << ": " << it->second << '\n';
	}
	return true;
}
