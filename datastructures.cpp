/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 2 2017
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
	return 0;
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
	else
	{
		std::cout << "DEBUG DATASTRUCTURE COMPLETE" << std::endl;
		return false;
	}
}
