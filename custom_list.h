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
	}

	bool addNode(std::string data)
	{
		node *current, *previous = nullptr;
		transform(data.begin(), data.end(), data.begin(),::tolower);
		std::unique_ptr<node> newNode = std::make_unique<node>(data);

		if(head == nullptr)
		{
			head = std::move(newNode);
			size++;
			return true;
		}

		current = head.get();

		while(current && current->getData() < data)
		{
			previous = current;
			current = current->getNext();
		}
		if(previous == nullptr)
		{
			newNode->setNext(std::move(head));
			head = std::move(newNode);
		}
		else if(current == nullptr)
		{
			previous->setNext(std::move(newNode));
		}
		else
		{
			newNode->setNext(std::move(previous->getNextPointer()));
			previous->setNext(std::move(newNode));
		}
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
	bool search(std::string searchString)
	{
		//find node and print
		return true;
	}
	node *getHead()
	{
		return head.get();
	}
	node *getNextNode(node* current)
	{
		return current->getNext();
	}
	void checkList(custom_list *dict, std::ofstream *wordCountFile)
	{
		std::map<std::string, int> wordCount;
		node *textCurrent = head.get();
		node *dictCurrent = dict->getHead();
		std::string textString;
		std::string dictString;

		while(textCurrent != nullptr)
		{
			textString = textCurrent->getData();
			dictCurrent = dict->getHead();
			while(dictCurrent != nullptr)
			{
				dictString = dictCurrent->getData();
				transform(textString.begin(), textString.end(), textString.begin(),::tolower);
				if(textString == dictString)
				{
					std::pair<std::map<std::string, int>::iterator,bool> uniqueString;
					uniqueString = wordCount.insert(std::pair<std::string, int>(textString, 1));
					if(uniqueString.second == false)
					{
						++wordCount[textString];
					}
				}
				dictCurrent = dictCurrent->getNext();
			}
			textCurrent = textCurrent->getNext();
		}
		for(std::map<std::string, int>::iterator it = wordCount.begin(); it != wordCount.end(); ++it)
		{
			*wordCountFile << it->first << ": " << it->second << "\n";
		}
	}
};
#endif

