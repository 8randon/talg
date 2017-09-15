// stdafx.h : include file for standard system include files,
// or project specific include files that are used frequently, but
// are changed infrequently
//

#pragma once

#include "targetver.h"

#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <vector>
#include <math.h>
#include <fstream>

using namespace std;

// TODO: reference additional headers your program requires here


//Element position struct
struct Pos {
	int globalpos;
	int localpos [2];
	double xycoor[2];

}pos;

//Matrix element struct
struct Elem {
	Pos p;
	int val;
}elem;

//Matrix level struct
struct Level {
	std::vector<Elem> elements;
	Elem corners [3]; // Each level struct has an array of the 3 elements
					  // at its corners, except for the first level, as it has not "corner" elements.
}level;


//Triangular matrix class
class Tmatrix {
public:
	/*Tmatrix(int lv = 0)
		: mlv(lv)
	{}*/
	Tmatrix();
	Tmatrix(int lv);
	//Tmatrix(int lv);//constructor

	Tmatrix(const Tmatrix &t) // Copy constructor
	{
		cout << "Copy constructor called " << endl;
	}
	Tmatrix& operator = (const Tmatrix &t) // Assignment operator
	{
		cout << "Assignment operator called " << endl;
	}
	~Tmatrix(); // Destructor
	
	int fill(int *values); //fills matrix with provided values; will be in the form of an array.
						   //Returns 1 or 0 for success or failure, respectively.
	void getinfo() {
		cout << mlv << endl << mnumElem << endl;
		if (mlv != 0) {
			cout << mlevels[0].elements[0].val << endl;
			cout << mlevels[1].corners[0].val << endl;
		}
	}
	void calculateCoor();
private:
	
	int mlv;
	int mnumElem;
	std::vector<Level> mlevels;

}tmatrix;