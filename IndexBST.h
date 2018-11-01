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
#include<cctype>
using namespace std;

class indexBST
{
	friend class IndexBST_Node;
	public:

		indexBST(string fileName)   //I belive this is the correct constructor
		/*
		* indexBST constructor
		* Default constructor for indexBST class, binary search tree object. A string is pased as a parameter, which
		* indicates the filepath of the text document that you want to process with the indexBST.
		*
		* Time Complexity:
		* T(n) = The summation of i = 0 to c, the number of characters in the .txt file, of i*w, where w is the number of words in the vector identifying words
		* 		 that already are in our binary search tree. In the worst case, our words would be very short and be added to our vector almost every iteration.
		*		 Additionally, we iterate through the file a total of c times, the number of characters in the document. As c grows larger and w grows larger, the 
		*		 the running time grows at an almost exponential rate.
		*
		* Therefore, the time complexity is close to quadratic, or O(n^2)
		*/
		{
			string content; //output of getline
			ifstream input; //name of the stream
			input.open(fileName); //opens the file stream
			string word; //the word from the line which we consider to place in the tree
			vector<string> words; //vector of words, used to remember the words that are already in the tree
			int lineNum = 0;
			bool inWords = false;
			while(getline(input,content)) //grab each line of the file
			{
				transform(content.begin(), content.end(), content.begin(), ::tolower); //slick way to make each line we grab all lower cases;
				inWords = false;
				word = "";
				lineNum++;
				for(int i = 0; i < content.length(); i++) //find words and place them into a vector
				{
					if ((content[i] == ' ' || ispunct(((int)content[i])) == true || ((content[i] == content.back()) && (ispunct((int)content[i]) == false))) && (word.length() > 0)) //if the current character is a space or punctuation, and the word length is at least 1, break off as a new word
					{
						if ((content[i] == content.back()) && (ispunct((int)content[i]) == false)) //special case for adding last characters of lines
						{
							word += content[i];
						}
						for(int j = 0; j < words.size(); j++)
						{
							if (word == words[j])
							{
								inWords = true;
							}
						}
						if (inWords == false) // if we haven't seen the word, create a node for it
						{
							words.push_back(word);
							if (rootPtr == nullptr)
							{
								rootPtr = new IndexBST_Node();
								rootPtr->word = word;
								rootPtr->wordCount++;
								rootPtr->lines.push_back(lineNum);
							}
							else
							{
								insert(word, lineNum);
							}
							//reset word string
							inWords = false;
							word = "";
						}
						else //if the word is already a word that we've seen, update its node value
						{
							IndexBST_Node* parent = new IndexBST_Node();
							parent = rootPtr;
							if(rootPtr->word == word)
							{
								if (inVec(rootPtr->lines,lineNum) == false)
								{
									rootPtr->lines.push_back(lineNum);
								}
								rootPtr->wordCount++;
							}
							else
							{
								while(parent != nullptr)
								{
									if(parent->word > word)
									{
										parent = parent->leftPtr;
									}
									else if (parent->word < word)
									{
										parent = parent->rightPtr;
									}
									else if (parent->word == word)
									{
										parent->wordCount++;
										if (inVec(parent->lines,lineNum) == false)
										{
											parent->lines.push_back(lineNum);
										}
										break;
									}
								}
							}
							word = "";
							inWords = false;
						}
					}
					else
					{
						if (ispunct((int)content[i]) == false && content[i] != ' ')
						{
							word += content[i];
						}
					}
				}
			}
		}

		void insert(string entry, int &line)
		/*
		* Insert method
		*
		* Input:
		*		entry - the word to be inserted
		*		line - the line number the entry was found on in the document
		* Output:
		*		Returns nothing, but modifies the existing indexBST object.
		*
		* Time Complexity: 
		* 		T(n) = h, where h is the height of the tree.
		*
		* Therefore, the time complexity is O(h).
		*/
		{
			if(rootPtr == nullptr)
			{
			    rootPtr = new IndexBST_Node();
				rootPtr->word= entry;
				rootPtr->wordCount++;
				rootPtr->lines.push_back(line);
			}
			else
			{
				IndexBST_Node* parent = rootPtr;
				IndexBST_Node* child = rootPtr;
				while(child != nullptr)
				{
					parent = child;
					if(parent->word > entry)
					{
						child = parent->leftPtr;
					}
					else
					{
						child =parent->rightPtr;
					}

				}
				if(parent-> leftPtr == child)
				{
					parent->leftPtr = new IndexBST_Node();
					parent->leftPtr-> word = entry;
					parent->leftPtr-> wordCount+=1;
					parent->leftPtr-> lines.push_back(line);
				}
				else
				{
					parent->rightPtr = new IndexBST_Node();
					parent->rightPtr-> word= entry;
					parent->rightPtr-> wordCount+=1;
					parent->rightPtr-> lines.push_back(line);
				}
			}
		}

		int totalNodes()
		/*
		* Total nodes method
		* A method that finds how many nodes are in the tree
		* Input:
		*		No parameters; a method for an existing Tree
		* Output:
		*		An integer value indicating the number of nodes in the tree
		*
		* Time Complexity: 
		* 		T(n) = h, where h is the height of the tree.
		*		
		*/
		{
			int number_of_nodes = 0;
			vector<IndexBST_Node*> visitedNodeStack;
			IndexBST_Node* temp = rootPtr;
			if (temp == nullptr)
			{
				return number_of_nodes;
			}
			else
			{
				number_of_nodes++;
			}
			
			visitedNodeStack.push_back(temp);
			while(temp != nullptr && visitedNodeStack.size() > 0)
			{ 
				if(temp->leftPtr != nullptr)
				{
					number_of_nodes++;
					visitedNodeStack.push_back(temp->leftPtr);
				}
				if (temp->rightPtr != nullptr)
				{
					number_of_nodes++;
					visitedNodeStack.push_back(temp->rightPtr);
				}
				visitedNodeStack.erase(visitedNodeStack.begin());
				temp = visitedNodeStack[0];
			}
			return number_of_nodes;
		}

		int height()
		/*
		* Height method
		* Method that returns the height of the binary search tree object
		* Input:
		* 		No parameters; a method for an existing Tree
		* Output: 
		*		An integer value of the height of the binary serach tree
		*
		* Time Complexity:
		*		T(n) = T(n/2) + T(n/2) = O(H)
		*/
		{
			return heightHelper(rootPtr);
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
		*
		* Time Complexity:
		*		T(n)= O(nlgn) + O(n) + O(n) + n(L) = O(nlgn)
		*/
		{
			vector<IndexBST_Node*> visitedNodeStack;
			vector<IndexBST_Node*> nodeList;
			IndexBST_Node* temp = rootPtr;
			//1. Traversal that builds up a list of nodes
			if (temp != nullptr)
			{
				nodeList.push_back(temp);
				visitedNodeStack.push_back(temp);
			}
			while(temp != nullptr && visitedNodeStack.size() > 0)
			{
				if(temp->leftPtr != nullptr)
				{
					nodeList.push_back(temp->leftPtr);
					visitedNodeStack.push_back(temp->leftPtr);
				}
				if(temp->rightPtr != nullptr)
				{
					nodeList.push_back(temp->rightPtr);
					visitedNodeStack.push_back(temp->rightPtr);
				}
				visitedNodeStack.erase(visitedNodeStack.begin());
				temp = visitedNodeStack[0];
			}
			cout << nodeList.size() << endl;
			//2. Throw list of nodes into a merge sort
			vector<IndexBST_Node*> sortedNodeList = mergeSort(nodeList);
			//3. Print all of the sorted nodes and their information
			for(int i = 0; i < sortedNodeList.size(); i++)
			{
				
				cout << sortedNodeList[i]->word << ", " << sortedNodeList[i]->wordCount << ", " << "Lines: ";
				for(int j = 0; j < sortedNodeList[j]->lines.size(); j++)
				{
					cout << sortedNodeList[i]->lines[j] << ", ";
				}
				cout << "\n";
			}
		}

		void traversal()
		/*
		* Traversal method
		* This method produces a breadth-first traversal of the BST.
		* Input:
		*		No parameters; a method for an existing Tree
		*	Output:
		*		Returns nothing, but prints to the console the traversal of the tree being operated upon.
		*
		* Time Complexity: T(n)= O(n)
		*/
		{
			vector<IndexBST_Node*> visitedNodeStack;
			IndexBST_Node* temp = rootPtr;
			if (temp == nullptr)
			{
				cout<< "No nodes in tree" << endl;
				return;
			}
			else
			{
				cout << temp->word << ", ";
				visitedNodeStack.push_back(temp);
				while(temp != nullptr && visitedNodeStack.size() > 0)
				{
					if(temp->leftPtr != nullptr)
					{
						cout << temp->leftPtr->word << ", ";
						visitedNodeStack.push_back(temp->leftPtr);
					}
					if(temp->rightPtr != nullptr)
					{
						cout << temp->rightPtr->word << ", ";
						visitedNodeStack.push_back(temp->rightPtr);
					}
					visitedNodeStack.erase(visitedNodeStack.begin());
					temp = visitedNodeStack[0];
				}
			}
			cout << "END TRAVERSAL" << "\n\n";
		}


		string maxOccurrences()
		/*
		* Max occurences method
		* Gives the words in the document which have the max occurrences.
		* Input:
		*		No parameters; a method for an existing Tree
		*	Output:
		*		Returns a string of the words which have max occurrences
		*
		* Time Complexity= O(n)
		*/
		{
			int max = 0;
			vector<string> words; //contains the words of the max occurrence value
			vector<IndexBST_Node*> visitedNodeStack;
			IndexBST_Node* temp = rootPtr;
			if (temp == nullptr)
			{
				return "Tree is Empty";
			}
			max = temp->wordCount;
			visitedNodeStack.push_back(temp);
			while(temp != nullptr && visitedNodeStack.size() > 0) //traversal loop
			{
				if(temp->leftPtr != nullptr)
				{
					visitedNodeStack.push_back(temp->leftPtr);
					if(temp->leftPtr->wordCount > max) //if the word count of the left child is greater, we update the max information
					{
						max=temp->leftPtr->wordCount;
						words.clear(); //empty the vector we had
						words.push_back(temp->leftPtr->word); //push back a single word from the new max into the vector
					}
					if(temp->leftPtr->wordCount == max) //if the word count is the same, we just push back another word into the list
					{
						if (inVec(words,temp->leftPtr->word) == false)
						{
						words.push_back(temp->leftPtr->word);
						}
					}
				}
				if(temp->rightPtr != nullptr)
				{
					visitedNodeStack.push_back(temp->rightPtr); // all same as above, but for the right child
					if(temp->rightPtr->wordCount > max)
					{
						max=temp->rightPtr->wordCount;
						words.clear();
						words.push_back(temp->rightPtr->word);	
					}
					if(temp->rightPtr->wordCount == max)
					{
						if (inVec(words,temp->rightPtr->word) == false)
						{
						words.push_back(temp->rightPtr->word);
						}
					}
				}
				visitedNodeStack.erase(visitedNodeStack.begin());
				temp = visitedNodeStack[0];
			}
			int i = 0;
			string listOfWords = "";
			while(i < words.size())
			{
					listOfWords += words[i];
					if (i != words.size()-1)
					{
						listOfWords += ", ";
					}
					i++;
			}
			return listOfWords;
		}
		

		void startsWith(int character)
		/*
		* Starts-with method
		* Prints all of the words in the document that start with a given letter.
		*	Input:
		*		character - a character which the words that are desired to be printed begin with
		* Output:
		*		Returns nothing, but prints words that begin with the passed character.
		*
		* Time Complexity: T(n)= O(H)
		*/
		{
			vector<IndexBST_Node*> visitedNodeStack;
			IndexBST_Node* temp = rootPtr;
			if (temp == nullptr)
			{
				cout<< "No words in file";
			}

			if(temp->word[0] == character)
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
			while(temp != nullptr && visitedNodeStack.size() > 0)
			{
				if(temp->leftPtr != nullptr)
				{
					visitedNodeStack.push_back(temp->leftPtr);
					if(temp->leftPtr->word[0] == character)
					{
						cout<<temp->leftPtr->word<<", "<< temp->leftPtr->wordCount<<", "<<"Lines: ";
						for(int j = 0; j < temp->leftPtr->lines.size() ; j++)
						{
							cout << temp->leftPtr->lines[j] << ", ";
						}
						cout << "\n";
					}
				}
				if (temp->rightPtr != nullptr)
				{
					visitedNodeStack.push_back(temp->rightPtr);
					if(temp->rightPtr->word[0]== character)
					{
						cout<<temp->rightPtr->word<<", "<< temp->rightPtr->wordCount<<", "<<"Lines: ";
						for(int j = 0; j < temp->rightPtr->lines.size(); j++)
						{
							cout << temp->rightPtr->lines[j] << ", ";
						}
						cout << "\n";
					}
				}
				visitedNodeStack.erase(visitedNodeStack.begin());
				temp = visitedNodeStack[0];
			}
		}
	/*-----------------------------------------------------------------------------------------------------------------------------*/
	private:
		
		IndexBST_Node* rootPtr = nullptr;
		
		int heightHelper(IndexBST_Node* root)
		//see height method
		{
			if(root == nullptr)
			{
				return 0;	
			}
			else
			{
				int leftMax= heightHelper(root->leftPtr);	
				int rightMax= heightHelper(root->rightPtr);
				if(leftMax> rightMax)
				{
					return leftMax+1;
				}
				else
				{
					return rightMax+1;
				}
			}		
		}	
		
		template<typename type>
		bool inVec(vector<type> vec, type element)
		/*
		inVec function
		Simple helper function to determine whether or not an element is in a vector. Outputs a boolean value indicating the fact.
		*/
		{
			for (int i = 0; i < vec.size(); i++)
			{
				if (vec[i] == element)
				{
					return true;
				}
			}
			return false;
		}
		
		template<typename type>
		vector<type> mergeSort(vector<type> m)
		//Merge sort used to sort the entries for printIndex
		{
		   if (m.size() <= 1)
		   {
		      return m;
		   }
		 
		   vector<type> left, right, result;
		   int middle = ((int)m.size()+ 1) / 2;
		 
		   for (int i = 0; i < middle; i++) 
		   {
		      left.push_back(m[i]);
		   }
		
		   for (int i = middle; i < (int)m.size(); i++) 
		   {
		      right.push_back(m[i]);
		   }
		 
		   left = mergeSort(left);
		   right = mergeSort(right);
		   result = merge(left, right);
		 
		   return result;
		}

		
		template<typename type>
		vector<type> merge(vector<type> left, vector<type> right)
		//Merge operation to assist merge sort
		{
		   vector<type> result;
		   while ((int)left.size() > 0 || (int)right.size() > 0) 
		   {
		      if ((int)left.size() > 0 && (int)right.size() > 0)
			  {
		         if (left.front()->word <= right.front()->word)
				 {
		            result.push_back(left.front());
		            left.erase(left.begin());
		         } 
		   		 else 
		   		 {
		            result.push_back(right.front());
		            right.erase(right.begin());
				 }
		      }  
			  else if (left.size() > 0) 
			  {
		            for (int i = 0; i < left.size(); i++)
		            {
		               result.push_back(left[i]);
		        	}
		            break;
		      }  
			  else if (right.size() > 0) 
			  {
		            for (int i = 0; i < right.size(); i++)
		            {
		               result.push_back(right[i]);
		        	}
		            break;
		      }
		   }
		   return result;
		}
		
};

#endif
