/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 2 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/

#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H

#include <memory>
#include <iostream>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>
#include <map>
#include "edit_dist.h"

class custom_list 
{
	class node
	{
		std::unique_ptr<node> next;
		std::string data;

		public:
		node(std::string newData)
		{	
			data = newData;
			next = nullptr;
		}

		bool setNext(std::unique_ptr<node> newNode)
		{
			next = std::move(newNode);
			return true;
		}
		node *getNext()
		{
			return next.get();
		}
		std::string getData()
		{
			return data;
		}
		void release()
		{
			if(next != nullptr)
			{
				next.reset();
			}
		}
		friend custom_list;
	};
	
	std::size_t size;
	std::unique_ptr<node> head;
	std::vector<node *> node_ptr;

	public:

	custom_list()
	{
		head = nullptr;
		size = 0;
	}
	void push_front(std::string data)
	{
		boost::algorithm::to_lower(data);	
		std::unique_ptr<node> newNode = std::make_unique<node>(data);

		if(head == nullptr)
		{
			head = std::move(newNode);
			size++;
		}
		else
		{
			newNode->next = std::move(head);
			head = std::move(newNode);
			size++;
		}
	}
	
	void print()
	{
		node *current = head.get();
		while(current != nullptr)
		{
			
			std::cout << current->getData() << std::endl;
			current = current->getNext();
		}
	}
	void printSize()
	{
		std::cout << "Length of list " << size << std::endl;
	}
	node *getHead()
	{
		return head.get();
	}
	void checkList(custom_list *dict, std::ofstream *outputFile)
	{
		std::map<std::string, int> wordCount;
		std::map<std::string, int> noMatch;
		node *textCurrent = head.get();
		node *dictCurrent = dict->getHead();
		std::string textString;
		std::string dictString;
		bool match;
		
		while(textCurrent != nullptr)
		{
			node_ptr.push_back(textCurrent);
			match = false;
			textString = textCurrent->getData();
			dictCurrent = dict->getHead();
			while(dictCurrent != nullptr)
			{
				dictString = dictCurrent->getData();
				if(textString == dictString)
				{
					std::pair<std::map<std::string, int>::iterator,bool> uniqueString;
					uniqueString = wordCount.insert(std::pair<std::string, int>(textString, 1));
					if(uniqueString.second == false)
					{
						++wordCount[textString];
					}
					match = true;
					break;
				}
				dictCurrent = dictCurrent->getNext();
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
			textCurrent = textCurrent->getNext();
		}
		
		*outputFile << "Word Count\n";
		*outputFile << "==========\n";
		std::map<std::string, int>::iterator map_iter;
		for(map_iter = wordCount.begin(); map_iter != wordCount.end(); ++map_iter)
		{
			*outputFile << map_iter->first << ": " << map_iter->second << "\n";
		}
//		std::cout << noMatch.size() << std::endl;
//		*outputFile << "\n\nFuzzy word list\n";
//		*outputFile << "===============\n";
//		for( map_iter = noMatch.begin(); map_iter != noMatch.end(); ++map_iter)
//		{
//			*outputFile << map_iter->first << " was not found in the dictionary. Similar words: "  << "\n";
//		}
		fuzzyWords(dict, &noMatch, outputFile);
	}
	void freeList()
	{
		std::cout << "Free List" << std::endl;
		for(int i = node_ptr.size() - 1; i > 0; --i)
		{
			node_ptr[i]->release();
		}	
		std::cout << "Free list complete" << std::endl;
	}
	void fuzzyWords(custom_list *dict, std::map<std::string, int> *noMatch, std::ofstream *outputFile)
	{
		node *current = dict->getHead();
		std::string dictString;
		std::vector<edit_distance> edits;
		edit_distance newEdit;

		std::cout << noMatch->size() << std::endl;
		*outputFile << "\n\nFuzzy word list\n";
		*outputFile << "===============\n";
		for(std::map<std::string, int>::iterator map_iter = noMatch->begin(); map_iter != noMatch->end(); ++map_iter)
		{
			current = dict->getHead();
			while(current != nullptr)
//			for(typename datastructure::iterator dict_iter = dict->begin(); dict_iter != dict->end(); dict_iter++)
			{
				dictString = current->getData();
				std::cout << dictString << " " << map_iter->first << std::endl;
				newEdit = calculateDistance(dictString, map_iter->first);
				std::cout << newEdit.string << " " << newEdit.distance <<std::endl;
				if(edits.empty())
				{
					edits.push_back(newEdit);
				}
				else
				{
					if(edits[0].distance == newEdit.distance)
					{
						edits.push_back(newEdit);
					}
					else if(edits[0].distance < newEdit.distance)
					{
						current = current->getNext();
						continue;
					}
					else
					{
						edits.clear();
						edits.push_back(newEdit);
					}
				}
				current = current->getNext();
				std::cout << current << std::endl;
			}
			*outputFile << map_iter->first << " was not found in the dictionary. Similar words: ";
			for(size_t i = 0; i < edits.size(); ++i)
			{
				*outputFile << edits[i].string;
				if(edits.size() > 1)
				{
					*outputFile << ", ";
				}
			}
			*outputFile << " : " << edits[0].distance << std::endl;
			edits.clear();
		}
	}
};
#endif

