/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 2 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/
#ifndef EDIT_DISTANCE_H
#define EDIT_DISTANCE_H

#include <string>
#include <iostream>
#include <vector>
#include <math.h>
#define MIN(x,y) ((x) < (y) ? (x) : (y))

/*
 * Difine edit_distance struct as a type
 */
typedef struct edit_distance
{
	std::string string;
	int distance;
}
edit_distance;

edit_distance calculateDistance(std::string dictString, std::string textString);
	
#endif
