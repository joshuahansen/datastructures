/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 1 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/
#include "datastructures.h"

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
	std::string tempToken;
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
			tempToken = *tok_iter;
			text.push_back(tempToken);
		}
	}
	checkVector(&text, &dict, outputFile);
	return true;
}
bool loadSet(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	std::multiset<std::string> setDict;
	std::string newString;
	std::string tempToken;
	while(std::getline(*dictionary, newString, '\n'))
	{
		boost::algorithm::to_lower(newString);	
		setDict.insert(newString);
	}

	std::multiset<std::string> setText;
	typedef boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");

	while(std::getline(*textFile, newString, '\n'))
	{
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			tempToken = *tok_iter;
			boost::algorithm::to_lower(tempToken);	
			setText.insert(*tok_iter);
		}
	}
	checkSet(&setText, &setDict, outputFile);
	return true;
}
bool loadList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	std::list<std::string> dict;
	std::string newString;
	std::string tempToken;
	while(std::getline(*dictionary, newString, '\n'))
	{
		dict.push_front(newString);
	}
	std::list<std::string> text;
	typedef	boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");
	
	while(std::getline(*textFile, newString, '\n'))
	{
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			tempToken = *tok_iter;
			boost::algorithm::to_lower(tempToken);	
			text.push_front(*tok_iter);
		}
	}
	checkList(&text, &dict, outputFile);
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
    		*outputFile << it->first << ": " << it->second << '\n';
	}
	return true;
}
bool checkSet(std::multiset<std::string> *text, std::multiset<std::string> *dict, std::ofstream *outputFile)
{
	std::map<std::string, int> wordCount;
	std::string textString;
	std::string dictString;
	
	for(std::multiset<std::string>::iterator text_iter = text->begin(); text_iter != text->end(); text_iter++)
	{
		textString = *text_iter;
		for(std::multiset<std::string>::iterator dict_iter = dict->begin(); dict_iter != dict->end(); dict_iter++)
		{
			dictString = *dict_iter;
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
    		*outputFile << it->first << ": " << it->second << '\n';
	}
	return true;
}
bool checkList(std::list<std::string> *text, std::list<std::string> *dict, std::ofstream *outputFile)
{
	std::map<std::string, int> wordCount;
	std::string textString;
	std::string dictString;
	
	for(std::list<std::string>::iterator text_iter = text->begin(); text_iter != text->end(); text_iter++)
	{
		textString = *text_iter;
		for(std::list<std::string>::iterator dict_iter = dict->begin(); dict_iter != dict->end(); dict_iter++)
		{
			dictString = *dict_iter;
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
    		*outputFile << it->first << ": " << it->second << '\n';
	}
	return true;
}
