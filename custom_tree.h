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
#include <boost/algorithm/string.hpp>

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
			friend custom_tree;
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
		boost::algorithm::to_lower(data);
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
	void search(node *currentNode, node *searchNode, std::map<std::string, int> *wordCount,
		       	std::ofstream *outputFile, std::map<std::string, int> *noMatch)
	{
		if(currentNode->getData() == searchNode->getData())
		{
			wordCount->insert(std::pair<std::string, int>(searchNode->getData(), searchNode->getNoReps()));
		}
		else if(currentNode->getData() > searchNode->getData() && currentNode->getLeft() != nullptr)
		{
			search(currentNode->getLeft(), searchNode, wordCount, outputFile, noMatch);
		}
		else if(currentNode->getData() < searchNode->getData() && currentNode->getRight() != nullptr)
		{
			search(currentNode->getRight(), searchNode, wordCount, outputFile, noMatch);
		}
		else
		{
			noMatch->insert(std::pair<std::string, int>(searchNode->getData(), searchNode->getNoReps()));
//			*outputFile std::cout << "WORD: " << searchNode->getData() << " Not in dictionary\n";
		}
				
	}
	void checkFullTree(node *currentNode, node *dictRoot, std::map<std::string, int> *wordCount, 
			std::ofstream *outputFile, std::map<std::string, int> *noMatch)
	{
		if(currentNode != nullptr)
		{
			search(dictRoot, currentNode, wordCount, outputFile, noMatch);
		
			//print left branch
			checkFullTree(currentNode->getLeft(), dictRoot, wordCount, outputFile, noMatch);

			//print right branch
			checkFullTree(currentNode->getRight(), dictRoot, wordCount, outputFile, noMatch);
		}
	}
	void checkTree(custom_tree *text, std::ofstream *outputFile)
	{
		std::map<std::string, int> wordCount;
		std::map<std::string, int> noMatch;
		node *dictCurrent = root.get();
		node *textCurrent = text->getRoot();
		
		checkFullTree(dictCurrent, textCurrent, &wordCount, outputFile, &noMatch);
		
		std::map<std::string, int>::iterator map_iter;
		*outputFile << "Word Count\n";
		*outputFile << "==========\n";
		for(map_iter = wordCount.begin(); map_iter != wordCount.end(); ++map_iter)
		{
			*outputFile << map_iter->first << ": " << map_iter->second << "\n";
		}
		*outputFile << "\n\nFuzzy word list\n";
		*outputFile << "===============\n";
		for(map_iter = noMatch.begin(); map_iter != noMatch.end(); ++map_iter)
		{
			*outputFile << map_iter->first << " was not found in the dictionary. Similar words: "  << "\n";
		}

	}
};
#endif
