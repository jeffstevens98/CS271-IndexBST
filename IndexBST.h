/*
Homework 5
Michelle Rowland, Jeff Stevens
Dr. Sevkli
CS 271
Due @ 10/31/18, 11:00 PM

IndexBST.h
A header file containing the IndexBST class used for processing a text file and obtaining information about
the words in the file. Specifically, the occurrences of each word and the lines they occur in. This information
is stored in a binary search tree data structure.
*/

#ifndef INDEXBST
#define INDEXBST

#include "indexBSTnode.h"
#include<iostream>
#include<fstream>
#include<string>
#include<algorithm>
#include<cmath>
#include<math.h>
using namespace std;

class indexBST
{
	friend class IndexBST_Node;
	public:

		//Constructor
		/*indexBST(string fileName)  //i believe this is wrong
		{
			string content; //output of getline
			ifstream input; //name of the stream
			input.open(fileName);
			string word;
			vector<string> words; //vector of words, used to remember the words that are already in the tree
			int lineNum = 0;
			bool inWords = false;
			while(getline(input,content)) //grab each line of the file
			{
				inWords = false;
				word = "";
				lineNum++;
				for(int i = 0; i < content.length(); i++) //find words and place them into a vector
				{
					if (content[i] == ' ')
					{
						for(int j = 0; j < words.size(); j++)
						{
							if (word == words[j])
							{
								inWords = true;
							}
						}
						if (inWords == false) // if we haven't seen the word, create a node for it
						{
							//Create a new node
							if (rootPtr == nullptr) //
							{
								cout << "assigning values to root pointer";
								rootPtr->word = word;
								rootPtr->wordCount++;
								rootPtr->lines.push_back(lineNum);
							}
							else
							{
								IndexBST_Node* temp = traversal(false);
								temp->word = word;
								temp->wordCount++;
								temp->lines.push_back(lineNum);
							}
							words.push_back(word);
							word = "";
							inWords = false;
						}
						else //if the word is already a word that we've seen, update its node value
						{
							vector<IndexBST_Node*> visitedNodeStack;
							IndexBST_Node* searchTemp = rootPtr;
							visitedNodeStack.push_back(searchTemp);
							if (searchTemp->word == word) //special case for if the word is the first in the Tree
							{
								searchTemp->wordCount++;
								searchTemp->lines.push_back(lineNum);
							}
							while(searchTemp != nullptr)
							{
								if(searchTemp->leftPtr != nullptr)
								{
									visitedNodeStack.push_back(searchTemp->leftPtr);
								}
								if (searchTemp->leftPtr->word == word)
								{
									searchTemp->leftPtr->wordCount++;
									searchTemp->lines.push_back(lineNum);
									break;
								}
								if(searchTemp->rightPtr != nullptr)
								{
									visitedNodeStack.push_back(searchTemp->rightPtr);
								}
								if (searchTemp->rightPtr->word == word)
								{
									searchTemp->rightPtr->wordCount++;
									searchTemp->lines.push_back(lineNum);
									break;
								}
								visitedNodeStack.erase(visitedNodeStack.begin());
								if (visitedNodeStack.size() >= 1)
								{
									searchTemp = visitedNodeStack[0];
								}
								else
								{
									cout << "Error: No visited nodes" << endl;
								}
							}
						}
					}
					else
					{
						word += content[i];
					}
				}
			}

			cout << rootPtr->word;

		}
*/



		indexBST(string fileName)   //I belive this is the correct constructor
		/*
		* indexBST constructor
		* Default constructor for indexBST class, binary search tree object. A string is pased as a parameter, which
		* indicates the filepath of the text document that you want to process with the indexBST.
		*/
		{
			string content; //output of getline
			ifstream input; //name of the stream
			input.open(fileName);
			string word;
			vector<string> words; //vector of words, used to remember the words that are already in the tree
			int lineNum = 0;
			bool inWords = false;
			while(getline(input,content)) //grab each line of the file
			{
				inWords = false;
				word = "";
				lineNum++;
				for(int i = 0; i < content.length(); i++) //find words and place them into a vector
				{
					if (content[i] == ' ')
					{
						for(int j = 0; j < words.size(); j++)
						{
							if (word == words[j])
							{
								inWords = true;
							}
						}
						if (inWords == false) // if we haven't seen the word, create a node for it
						{
							//Create a new node
							if (rootPtr == nullptr) //
							{
								cout << "assigning values to root pointer";
								rootPtr->word = word;
								rootPtr->wordCount++;
								rootPtr->lines.push_back(lineNum);
							}
							else
							{
								insert(word, lineNum);
							}
							words.push_back(word);
							word = "";
							inWords = false;
						}
						else //if the word is already a word that we've seen, update its node value
						{
							IndexBST_Node* parent = rootPtr;
							if(rootPtr->word== word)
							{
								rootPtr->wordCount++;
								rootPtr->lines.push_back(lineNum);
							}
							else
							{
								while(parent != nullptr)
								{
									if(parent->word > word)
									{
										parent= parent->leftPtr;
									}
									else if (parent->word < word)
									{
										parent=parent->rightPtr;
									}
									else if (parent->word== word)
									{
										parent->wordCount++;
										parent->lines.push_back(lineNum);
									}

								}
							}
						}
					}
					else
					{
						word += content[i];
					}
				}
			}
			cout << rootPtr->word;
		}





		void insert(string entry, int &line)
		/*
		* Insert method
		*
		* Input:
		*		entry -
		*		line -
		* Output:
		*		Returns nothing, but modifies the existing indexBST object.
		*/
		{
			IndexBST_Node* parent = rootPtr;
			IndexBST_Node* child = rootPtr;
			if(rootPtr== nullptr)
			{
				rootPtr->word= entry;
				rootPtr->wordCount++;
				rootPtr->lines.push_back(line);
			}
			else
			{
				while(child != nullptr)
				{
					parent= child;
					if(parent->word > entry)
					{
						child= parent->leftPtr;
					}
					else
					{
						child=parent->rightPtr;
					}

				}
				if(parent-> leftPtr== child)
				{
					parent->leftPtr-> word= entry;
					parent->leftPtr-> wordCount+=1;
					parent->leftPtr-> lines.push_back(line);
				}
				else
				{
					parent->rightPtr-> word= entry;
					parent->rightPtr-> wordCount+=1;
					parent->rightPtr-> lines.push_back(line);
				}
			}
		}





		int totalNodes()  //stays the same
		/*
		* Total nodes method
		* A method that finds how many nodes are in the tree
		* Input:
		*		No parameters; a method for an existing Tree
		* Output:
		*		An integer value indicating the number of nodes in the tree
		*/
		{
			int number_of_nodes=0;
			vector<IndexBST_Node*> visitedNodeStack;
			IndexBST_Node* temp = rootPtr;
			if (temp == nullptr)
			{
				return number_of_nodes;
			}

			number_of_nodes++;
			visitedNodeStack.push_back(temp);
			while(temp != nullptr)
			{
				if(temp->leftPtr != nullptr)
				{
					number_of_nodes++;
					visitedNodeStack.push_back(temp->leftPtr);
				}
				if(temp->rightPtr != nullptr)
				{
					number_of_nodes++;
					visitedNodeStack.push_back(temp->rightPtr);
				}
				visitedNodeStack.erase(visitedNodeStack.begin());
				temp = visitedNodeStack[0];
			}
			return number_of_nodes;
		}

		int height() //stays the same
		{
			int count= totalNodes();
			int height= log(count)/log(2);
			height= ceil(height);
		}




		void printIndex()
		/*
		* Print index method
		* A method that prints all of the words in the tree, their occurrences, and line numbers in ascending order.
		* The words are printed in order of occurrences (?).
		*	Input:
		*		No parameters; a method for an existing Tree
		* Ouput:
		*		Returns nothing, but prints to the console all of the words in the tree with associated data.
		*/
		{
			//make list of all nodes
			//modify sorting algorithtm to sort nodes based on word values
			//print word, occurence, and line numbers
		}





		void traversal()       //bool printText = true          stays almost same, commented out unecessary parts (I think)
		/*
		* Traversal method
		* This method produces a breadth-first traversal of the BST.
		* Input:
		*		No parameters; a method for an existing Tree
		*	Output:
		*		Returns nothing, but prints to the console the traversal of the tree being operated upon.
		*/
		{
			vector<IndexBST_Node*> visitedNodeStack;
			IndexBST_Node* temp = rootPtr;
			if (temp == nullptr)
				cout<<"No nodes in tree";

			//if (printText == true)
			//{
			cout << temp->word;
		//	}
			visitedNodeStack.push_back(temp);
			while(temp != nullptr)
			{
				if(temp->leftPtr != nullptr)
				{
					//if (printText == true)
						//{
						cout << temp->leftPtr->word;
					//	}
					visitedNodeStack.push_back(temp->leftPtr);
				}
				if(temp->rightPtr != nullptr)
				{
					//if (printText == true)
					//{
					cout << temp->rightPtr->word;
					//}
					visitedNodeStack.push_back(temp->rightPtr);
				}
				visitedNodeStack.erase(visitedNodeStack.begin());
				temp = visitedNodeStack[0];
			}
		}



		string maxOccurrences()    //can stay the same
		/*
		* Max occurences method
		* Gives the words in the document which have the max occurrences.
		* Input:
		*		No parameters; a method for an existing Tree
		*	Output:
		*		Returns a string of the words which have max occurrences
		*/
		{
			int max=0;
			vector<string> words;
			vector<IndexBST_Node*> visitedNodeStack;
			IndexBST_Node* temp = rootPtr;
			if (temp == nullptr)
			{
				return "Tree is Empty";
			}


			max= temp->wordCount;
			visitedNodeStack.push_back(temp);
			while(temp != nullptr)
			{
				if(temp->leftPtr != nullptr)
				{
					visitedNodeStack.push_back(temp->leftPtr);
					if(temp->leftPtr->wordCount>max)
					{
						max=temp->leftPtr->wordCount;
						words.clear();
						words.push_back(temp->leftPtr->word);
					}
					if(temp->leftPtr->wordCount==max)
					{
						words.push_back(temp->leftPtr->word);
					}
				}
				if(temp->rightPtr != nullptr)
				{
					visitedNodeStack.push_back(temp->rightPtr);
					if(temp->rightPtr->wordCount>max)
					{
						max=temp->rightPtr->wordCount;
						words.clear();
						words.push_back(temp->rightPtr->word);
					}
					if(temp->rightPtr->wordCount==max)
					{
						words.push_back(temp->rightPtr->word);
					}
				}
				visitedNodeStack.erase(visitedNodeStack.begin());
				temp = visitedNodeStack[0];
			}
			int i= 0;
			string listOfWords= "";
			while(i< words.size())
			{
					listOfWords+= words[i];
					listOfWords+=", ";
			}
			return listOfWords;

		}




		void startsWith(int character) //an integer?
		/*
		* Starts-with method
		* Prints all of the words in the document that start with a given letter.
		*	Input:
		*		character - a character which the words that are desired to be printed begin with
		* Output:
		*		Returns nothing, but prints words that begin with the passed character.
		*/
		{
			vector<IndexBST_Node*> visitedNodeStack;
			IndexBST_Node* temp = rootPtr;
			if (temp == nullptr)
			{
				cout<< "No words in file";
			}

			if(temp->word[0]== character)
			{
				cout<<temp->word<<", "<< temp->wordCount<<", "<<"Lines: ";
				for(int j;j<temp->lines.size(); j++)
				{
					cout<< temp->lines[j];
					if(j<temp->lines.size()-1)
					{
						cout<<", ";
					}
					else
					{
						cout<< endl;
					}
				}
			}
			visitedNodeStack.push_back(temp);
			while(temp != nullptr)
			{
				if(temp->leftPtr != nullptr)
				{
					visitedNodeStack.push_back(temp->leftPtr);
					if(temp->leftPtr->word[0]== character)
					{
						cout<<temp->leftPtr->word<<", "<< temp->leftPtr->wordCount<<", "<<"Lines: ";
						for(int j;j<temp->leftPtr->lines.size(); j++)
						{
							cout<< temp->leftPtr->lines[j];
							if(j<temp->leftPtr->lines.size()-1)
							{
								cout<<", ";
							}
							else
							{
								cout<< endl;
							}
						}
					}
				}
				if(temp->rightPtr != nullptr)
				{
					visitedNodeStack.push_back(temp->rightPtr);
					if(temp->rightPtr->word[0]== character)
					{
						cout<<temp->rightPtr->word<<", "<< temp->rightPtr->wordCount<<", "<<"Lines: ";
						for(int j;j<temp->rightPtr->lines.size(); j++)
						{
							cout<< temp->rightPtr->lines[j];
							if(j>temp->rightPtr->lines.size()-1)
							{
								cout<<", ";
							}
							else
							{
								cout<< endl;
							}
						}
					}
				}
				visitedNodeStack.erase(visitedNodeStack.begin());
				temp = visitedNodeStack[0];
			}
		}
	/*-----------------------------------------------------------------------------------------------------------------------------*/
	private:
		IndexBST_Node* rootPtr = nullptr;

};

#endif
