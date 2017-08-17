/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 1 2017
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

		bool setNext(std::unique_ptr<node> && newNode)
		{
			next = std::move(newNode);
			return true;
		}
		node *getNext()
		{
			return next.get();
		}
		std::unique_ptr<node> &getNextPointer()
		{
			return next;
		}
		std::string getData()
		{
		return data;
		}
		friend custom_list;
	};
	
	std::size_t size;
	std::unique_ptr<node> head;

	public:

	custom_list()
	{
		head = nullptr;
		size = 0;
	}
	bool push_front(std::string data)
	{
		boost::algorithm::to_lower(data);	
		std::unique_ptr<node> newNode = std::make_unique<node>(data);

		if(head == nullptr)
		{
			head = std::move(newNode);
			size++;
			return true;
		}

		newNode->setNext(std::move(head));
		head = std::move(newNode);
		size++;
		return true;
	}
	void print(std::ofstream *outputFile)
	{
		if(outputFile->is_open())
		{
			node *current = head.get();
			while(current != nullptr)
			{
			
			*outputFile << current->getData() << "\n";
			current = current->getNext();
			}
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
	node *getNextNode(node* current)
	{
		return current->getNext();
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
//			std::cout << match << " " << textString << " "  << dictString << std::endl;
			if(match == false)
			{
				std::pair<std::map<std::string, int>::iterator,bool> uniqueString;
				uniqueString = noMatch.insert(std::pair<std::string, int>(textString, 1));
				if(uniqueString.second == false)
				{
					++noMatch[textString];
				}
			//	*outputFile << textString << " not found\n";
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
		*outputFile << "\n\nFuzzy word list\n";
		*outputFile << "===============\n";
		for( map_iter = noMatch.begin(); map_iter != noMatch.end(); ++map_iter)
		{
			*outputFile << map_iter->first << " was not found in the dictionary. Similar words: "  << "\n";
		}

	}
};
#endif

