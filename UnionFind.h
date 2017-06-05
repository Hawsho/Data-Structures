/*________________________________________________________________
	Author: ISSA G MALKE
	Date: January 21, 2015
	Description: An implementation of Union-Find data structure
________________________________________________________________*/

#ifndef UNIONFIND_H
#define	UNIONFIND_H

#include<string>
#include<iostream>

/*
using std::cout;
using std::cin;
using std::string;
using std::endl;
*/
using namespace std;

class UnionFind{

 //______ DTATA (private)______//
 private:
	int data;  // Integer type variable that indicates the number of the elements from 1 -> N 
	int* identifier;  // Integer pointer, which will used to creat an array that will save the numbers, which correspond to the parents/roots of connected elements & corresponding elements
	int* size;	// Integer pointer, which will used to creat an array that will track the size of each grouped elements

 //______ Methods ______//
 public:
	UnionFind(int x);	// Class Constructor
	~UnionFind();		// Destructor
	int Find(int y);	// Quick Find Method
	//int FindRoot(int g);
	void QUnion(int x, int y);	// QUnion Method
	bool IsConnected(int h, int j); // IsConnected Method
	void print();			//Helper Method to print the list of elements

	void WQUnion(int x, int y);	//Weighted Union Method
	int WQUPCfind(int x);		//Find Method with Path Comprasion

  };
#endif	/* UNIONFIND_H */
