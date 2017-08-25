/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 2 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/
/*Edit Distance
 * int m[i,j] = 0
 * for i <- 1 to |s1|
 * do m[i,0] = i
 * for j <- 1 to |s2|
 * do m[0,j] = j
 * for i <- 1 to |s2|
 * do for j <- 1 to |s2|
 * 	do m|i,j| = min{m|i-1,j-1]+ if(s1[i] = s2[j] then 0 else 1fi,
 * 	m[i - 1,j] + 1,
 * 	m[i, j - 1] + 1}
 * 	return m [|s1|,|s2|]*/
#include "edit_dist.h"
/*
 * Calculate the edit distance bewteen 2 words and return a struct of the string 
 * from the dictionary and also the edit distance between the text word and 
 * the dictionary word
 */
edit_distance calculateDistance(std::string dictString, std::string textString)
{
	int edit_dist[100][100];
	std::vector<char> dictChar(dictString.c_str(), dictString.c_str() + dictString.size());
	std::vector<char> textChar(textString.c_str(), textString.c_str() + textString.size());
	int i, j, temp, tracker;
	int dictLength = dictChar.size(), textLength = textChar.size();

	for(i = 0; i <= dictLength; ++i)
	{
		edit_dist[0][i] = i;
	}
	for(j = 0; j <= textLength; ++j)
	{
		edit_dist[j][0] = j;
	}
	for(j = 1; j <= dictLength; ++j)
	{
		for(i = 1; i <= textLength; ++i)
		{
			if(dictChar[i-1] == textChar[j-1])
			{
				tracker = 0;
			}
			else
			{
				tracker = 1;
			}
			temp = MIN((edit_dist[i-1][j]+1),(edit_dist[i][j-1]+1));
			edit_dist[i][j] = MIN(temp,(edit_dist[i-1][j-1]+tracker));
		}
	}

	edit_distance newEditDist;
	newEditDist.string = dictString;
	newEditDist.distance = edit_dist[textLength][dictLength];
	return newEditDist;
}
