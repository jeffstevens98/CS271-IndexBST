/*
Homework 5
Michelle Rowland, Jeff Stevens
Dr. Sevkli
CS 271
Due @ 10/31/18, 11:00 PM

indexBSTnode.h
This file contains a class that is used as nodes in a binary search tree for the indexBST class.
*/

#ifndef IndexBST_Node_H
#define IndexBST_Node_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class IndexBST_Node {
   friend class indexBST;
public:
   IndexBST_Node() //constructor
   {
	word = "hello world!";
   }
   //NODETYPE getData() const {return data;}
private:
   IndexBST_Node* leftPtr{nullptr};
   IndexBST_Node* rightPtr{nullptr};

   //word storage
   string word;
   int wordCount = 0;
   vector<int> lines;
};

#endif
