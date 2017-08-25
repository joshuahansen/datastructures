/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 2 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/
#ifndef DATASTRUCTURES_H
#define DATASTRUCTURES_H

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <list>
#include <set>
#include <map>
#include <chrono>
#include <boost/program_options.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include "custom_list.h"
#include "custom_tree.h"
#include "loadDatastructures.h"
#include "edit_dist.h"

typedef std::array<std::string, 5> sArray5;

bool loadFiles(std::ifstream *dictionary, std::string dictOpt, std::ifstream *textFile,
	       	std::string textOpt, std::ofstream *outputFile, std::string outputOpt);

bool loadDatastruct(std::string datastruct, std::ifstream *dictionary, 
		std::ifstream *textFile, std::ofstream *outputFile, const sArray5 ds);

#endif
