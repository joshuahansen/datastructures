/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 1 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/
#include "loadDatastructures.h"

template <typename datastructure>
void check(datastructure *text, datastructure *dict, std::ofstream *outputFile)
{
	std::map<std::string, int> wordCount;
	std::map<std::string, int> noMatch;
	std::string textString;
	std::string dictString;
	bool match;
	
	for(typename datastructure::iterator text_iter = text->begin(); text_iter != text->end(); text_iter++)
	{
		textString = *text_iter;
		match = false;
		for(typename datastructure::iterator dict_iter = dict->begin(); dict_iter != dict->end(); dict_iter++)
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
				match = true;
				break;
			}
		}
		if(match == false)
		{
			std::pair<std::map<std::string, int>::iterator,bool> uniqueString;
			uniqueString = noMatch.insert(std::pair<std::string, int>(textString, 1));
			if(uniqueString.second == false)
			{
				++noMatch[textString];
			}
		}
	} 
	*outputFile << "Word Count\n";
	*outputFile << "==========\n";
	std::map<std::string, int>::iterator map_iter;
	for (map_iter = wordCount.begin(); map_iter!= wordCount.end(); ++map_iter)
	{
    		*outputFile << map_iter->first << ": " << map_iter->second << '\n';
	}
	*outputFile << "\n\nFuzzy word list\n";
	*outputFile << "===============\n";
	for( map_iter = noMatch.begin(); map_iter != noMatch.end(); ++map_iter)
	{
		*outputFile << map_iter->first << " was not found in the dictionary. Similar words: "  << "\n";
	}
}
bool loadCustomList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	auto start = std::chrono::high_resolution_clock::now();
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
	
	std::string textString;
	while(std::getline(*textFile, newString, '\n'))
	{
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			textString = *tok_iter;
			textList.push_front(textString);
		}
	}
	textFile->close();
	std::cout << "TEXT LIST" << std::endl;
	textList.printSize();

	textList.checkList(&dictionaryList, outputFile);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Time Elapsed: " << elapsed.count() << std::endl;
	textList.freeList();
	return true;
}
bool loadCustomTree(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	auto start = std::chrono::high_resolution_clock::now();
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

	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Time Elapsed: " << elapsed.count() << std::endl;
	return true;
}
bool loadVector(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::vector<std::string> dict;
	std::string newString;
	std::string tempToken;
	while(std::getline(*dictionary, newString, '\n'))
	{
		boost::algorithm::to_lower(newString);
		dict.push_back(newString);
	}

	std::vector<std::string> text;
	typedef	boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");

	while(std::getline(*textFile, newString, '\n'))
	{
		boost::algorithm::to_lower(newString);
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			tempToken = *tok_iter;
			text.push_back(tempToken);
		}
	}
	check<std::vector<std::string>>(&text, &dict, outputFile);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Time Elapsed: " << elapsed.count() << std::endl;
	return true;
}
bool loadSet(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	auto start = std::chrono::high_resolution_clock::now();
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
		boost::algorithm::to_lower(newString);
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			tempToken = *tok_iter;
			boost::algorithm::to_lower(tempToken);
			setText.insert(*tok_iter);
		}
	}
	check<std::multiset<std::string>>(&setText, &setDict, outputFile);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Time Elapsed: " << elapsed.count() << std::endl;
	return true;
}
bool loadList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile)
{
	auto start = std::chrono::high_resolution_clock::now();
	std::list<std::string> dict;
	std::string newString;
	std::string tempToken;
	while(std::getline(*dictionary, newString, '\n'))
	{
		boost::algorithm::to_lower(newString);
		dict.push_front(newString);
	}
	std::list<std::string> text;
	typedef	boost::tokenizer<boost::char_separator<char>> tokenizer;
	boost::char_separator<char> sep(" 1234567890!@#$%^&*()_+=[]{}\\|;:\'\"<>,./?");

	while(std::getline(*textFile, newString, '\n'))
	{
		boost::algorithm::to_lower(newString);
		tokenizer toks{newString, sep};
		for(tokenizer::iterator tok_iter = toks.begin(); tok_iter != toks.end(); tok_iter++)
		{
			tempToken = *tok_iter;
			boost::algorithm::to_lower(tempToken);
			text.push_front(*tok_iter);
		}
	}
	check<std::list<std::string>>(&text, &dict, outputFile);
	auto finish = std::chrono::high_resolution_clock::now();
	std::chrono::duration<double> elapsed = finish - start;
	std::cout << "Time Elapsed: " << elapsed.count() << std::endl;
	return true;
}
