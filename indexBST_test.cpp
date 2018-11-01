/*
Homework 5
Michelle Rowland, Jeff Stevens
Dr. Sevkli
CS 271
Due @ 10/31/18, 11:00 PM

Code for an executable file that is used to test the indexBST class
*/

#include<iostream>
#include<string>
#include "IndexBST.h"

using namespace std;

int main()
{

  string textFile = "ProgramDefects.txt";
  indexBST testTree = indexBST(textFile);
  cout << "Total nodes in " << textFile << " tree: " << testTree.totalNodes() << endl;
  cout << "Tree height: " << testTree.height() << endl;
  cout << "Print index: " << endl;
  testTree.printIndex();
  cout << "Bread-first traversal: " << endl;
  testTree.traversal();
  cout << "Max occurrences:\n" << testTree.maxOccurrences() << "\n\n";
  cout << "Starts with:" << endl;
  testTree.startsWith('l');
  
  return 0;

}
