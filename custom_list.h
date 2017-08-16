#ifndef CUSTOM_LIST_H
#define CUSTOM_LIST_H

#include <memory>
#include <iostream>
#include <boost/tokenizer.hpp>

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
			while(current != NULL)
			{
			
			*outputFile << current->getData() << "\n";
			current = current->getNext();
			}
		}
	}
	void print()
	{
		node *current = head.get();
		while(current != NULL)
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
};
#endif

