/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 1 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/
#ifndef LOAD_DATASTRUCTURES_H
#define LOAD_DATASTRUCTURES_H

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

bool loadCustomList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputfile);

bool loadCustomTree(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile);

bool loadVector(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile);

bool loadSet(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile);

bool loadList(std::ifstream *textFile, std::ifstream *dictionary, std::ofstream *outputFile);

#endif
