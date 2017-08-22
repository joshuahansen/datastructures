/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 1 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/
#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

#include <string>
#include <iostream>
#include <vector>

void calculateDistance(std::string dictString, std::string textString);
void compareMap(std::map<std::string, int> newEditDist);
void cleanMap();

class edit_distance
{
	std::map<std::string, int> closest;

	public:
	
	void calculateDistance(std::string dictString, std::string textString)
	{
	}
	void compareMap(std::map<std::string, int> newEditDist)
	{
		std::map<std::string, int>::iterator map_iter;
		for(map_iter = closest.begin(); map_iter != closest.end(); ++map_iter)
		{
			if(newEditDist.second =< map_iter->second)
			{
				closest.insert(newEditDist);
				break;
			}
		}
		cleanMap();

	}
	void cleanMap()
	{
		std::map<std::string, int> smallest = closest.begin();
		std::map<std::string, int>::iterator map_iter;
		for(map_iter = closest.begin(); map_iter != closest.end; ++map_iter)
		{
			if(smallest.second > map_iter->second)
			{
				smallest = *map_iter;
			}
		}
		for(map_iter = closest.begin(); map_iter != closest.end; ++map_iter)
		{
			if(map_iter->second > smallest.second)
			{
				closest.erase(map_iter->first);
			}
		}
	}
}	

#endif
