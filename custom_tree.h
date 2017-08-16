/***********************************************************************
*	COSC1254 - PROGRAMMING USING C++
*	SEMESTER 1 2017
*	ASSIGNMENT 1 - DATA STRUCTURES
*	NAME:		JOSHUA HANSEN
*	STUDENT NUMBER: S3589185
************************************************************************/

#ifndef CUSTOM_TREE_H
#define CUSTOM_TREE_H

#include <memory>
#include <iostream>

class custom_tree
{
	class node
	{
		std::unique_ptr<node> lChild;
		std::unique_ptr<node> rChild;
		std::string data;
		int NoReps;

		public:
			node (std::string newData)
			{
				lChild = nullptr;
				rChild = nullptr;
				data = newData;
				NoReps = 1;
			}
			void addRep()
			{
				NoReps++;
			}
			bool setLeft(std::unique_ptr<node> &&node)
			{
				lChild = std::move(node);
				return true;
			}
			bool setRight(std::unique_ptr<node> &&node)
			{
				rChild = std::move(node);
				return true;
			}
			std::string getData()
			{
				return data;
			}
			node *getLeft()
			{
				return lChild.get();
			}
			node *getRight()
			{
				return rChild.get();
			}
			int getNoReps()
			{
				return NoReps;
			}
	};

	std::unique_ptr<node> root;

	public:
	custom_tree()
	{
		root = nullptr;
	}
	node *getRoot()
	{
		return root.get();
	}

	bool addNode(std::string data)
	{
		node *current;
		std::unique_ptr<node> newNode = std::make_unique<node>(data);

		if(root == nullptr)
		{
			root = std::move(newNode);
			return true;
		}

		current = root.get();
		bool added = false;
		
		while(!added)
		{
			if(data == current->getData())
			{
				current->addRep();
				added = true;
				return true;
			}
			else if(data < current->getData())
			{
				if(current->getLeft() == nullptr)
				{
					current->setLeft(std::move(newNode));
					added = true;
					return true;
				}
				else
				{
					current = current->getLeft();
				}
			}
			else
			{
				if(current->getRight() == nullptr)
				{
					current->setRight(std::move(newNode));
					added = true;
					return true;
				}
				else
				{
					current = current->getRight();
				}
			}
		}
		return true;
	}
	void printNode(std::string data)
	{
		std::cout << data << std::endl;
	}
	void print(node *currentNode)
	{
		if(currentNode != nullptr)
		{
			std::cout << currentNode->getData() << " " << currentNode->getNoReps()
				<< std::endl;
			//print left branch
			print(currentNode->getLeft());

			//print right branch
			print(currentNode->getRight());
		}
	}
	bool search()
	{
		return false;
	}
};
#endif
