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
#include <boost/algorithm/string.hpp>
#include "custom_list.h"
#include "custom_tree.h"

typedef std::array<std::string, 5> sArray5;
bool loadFiles(int argc, char* argv[], std::string *datastruct, std::ifstream *dictionary, 
		std::ifstream *textFile, std::ofstream *outputFile, const sArray5 ds);
bool loadDatastruct(std::string datastruct, std::ifstream *dictionary, 
		std::ifstream *textFile, std::ofstream *outputFile, const sArray5 ds);
bool loadCustomList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputfile);
bool loadCustomTree(std::ifstream *textFile, std::ifstream *dictionary);
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
		std::ifstream dictionary;
		std::ifstream textFile;
		std::ofstream outputFile;
		
		loadFiles(argc, argv, &datastruct, &dictionary, &textFile, &outputFile, ds);
	
		loadDatastruct(datastruct, &dictionary, &textFile, &outputFile, ds);	
	}
}

bool loadFiles(int argc, char* argv[], std::string *datastruct, std::ifstream *dictionary, 
		std::ifstream *textFile, std::ofstream *outputFile, const sArray5 ds)
{
	const int nextArg = 1;

	for(int i = 1; i < argc; i++)
	{
		if(argv[i][0] == '-')
		{
			switch(argv[i][1]) {
				case 's':
					for(int j = 0; j < (int)ds.size(); j++)
					{
						if(argv[i + nextArg] == ds[j])
						{
							*datastruct = ds[j];
						}
					}
					break;
				case 'd':
					dictionary->open(argv[i + nextArg]);
					if(!dictionary)
					{
						std::cout << "Could not open " << argv[i + nextArg]
							<< " for reading" << std::endl;
						exit(1);
					}
					break;
				case 't':
					textFile->open(argv[i + nextArg]);
					if(!textFile)
					{
						std::cout << "Could not open " << argv[i + nextArg]
							<< " for reading" << std::endl;
						exit(1);
					}
					break;
				case 'o':
					outputFile->open(argv[i + nextArg]);
					if(!outputFile)
					{
						std::cout << "Could not open " << argv[i + nextArg] 
							<< " for writting" << std::endl;
						exit(1);
					}
					break;

			}
		}
	}
	return true;
}
bool loadDatastruct(std::string datastruct, std::ifstream *dictionary, 
		std::ifstream *textFile, std::ofstream *outputFile, const sArray5 ds)
{
	if(datastruct == ds[0])
	{
		loadCustomList(textFile, dictionary, outputFile);
	}
	else if(datastruct == ds[1])
	{
		loadCustomTree(textFile, dictionary);
	}
	else if(datastruct == ds[2])
	{
		loadList(textFile, dictionary, outputFile);
	}
	else if(datastruct == ds[3])
	{
		loadSet(textFile, dictionary, outputFile);
	}
	else if(datastruct == ds[4])
	{
		loadVector(textFile, dictionary, outputFile);
	}
	return true;
}
bool loadCustomList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile) 
{
	custom_list dictionaryList;
	custom_list textList;
	
	std::string newString;
	
	typedef	boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");
	
	while(std::getline(*textFile, newString, '\n'))
	{
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			textList.addNode(*tok_iter);
		}
	}
	textFile->close();
	while(std::getline(*dictionary, newString, '\n'))
	{
		dictionaryList.addNode(newString);
	}
	dictionary->close();
	
	textList.print();
	
	dictionaryList.print();

	return true;
}
bool loadCustomTree(std::ifstream *textFile, std::ifstream *dictionary)
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
		std::cout << "\nDEBUG: " << newString << std::endl;
		dictionaryTree.addNode(newString);
	}
	dictionary->close();
	
	std::cout << "Text file list" << std::endl;
	textTree.print(textTree.getRoot());
	std::cout << "Dictionary file list" << std::endl;
	dictionaryTree.print(dictionaryTree.getRoot());

	return false;
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
					++wordCount[dictString];
				}
			}
		}
	} 
	for (std::map<std::string, int>::iterator it= wordCount.begin(); it!= wordCount.end(); ++it)
	{
    		*outputFile << it->first << ": " << it->second << '\n';
	}
	return true;
}
