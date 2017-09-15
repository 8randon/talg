#pragma once

#include "stdafx.h"

Tmatrix::Tmatrix() {
	mlv = 0;
	cout << "matrix initialized" << endl;
}

Tmatrix::Tmatrix(int lv = 0) { //create separate matrix builder function, so default constructor can pass in 1 as a default
	mlv = lv;
	int i = 0;
	int j = 0;
	Level newlevel;
	Elem newelem;
	int hold = 0;
	int globalp = 0;
	mnumElem = 1;

	for (i = 0; (i < lv ) || (lv == 1); i++) {
		hold = mnumElem;
		mnumElem += 3 * i;
		cout << mnumElem << endl;
		mlevels.push_back(newlevel);

		for (j = 0; (j < 3 * i) || (j == 0); j++) {
			
			globalp += 1;

			newelem.val = globalp;

			newelem.p.globalpos = globalp;

			newelem.p.localpos[0] = i;
			newelem.p.localpos[1] = j+1;

			mlevels[i].elements.push_back(newelem);


			if (mnumElem == 1) {
				mlevels[i].corners[0] = newelem;
				mlevels[i].corners[1] = newelem;
				mlevels[i].corners[2] = newelem;
			}
			else {
				if (globalp == hold + 1) {
					mlevels[i].corners[0] = newelem;
				}
				if (globalp == hold + i+1) {
					mlevels[i].corners[1] = newelem;
				}
				if (globalp == mnumElem - i + 1) {
					mlevels[i].corners[2] = newelem;
				}
			}
		}
	}
	
}

Tmatrix::~Tmatrix() {

	if (mlv != 0) {
		std::vector<Level>().swap(mlevels);
	}
}

int Tmatrix::fill(int *values){
	return *values;
}

void Tmatrix::calculateCoor() {
	int i;
	int j;
	int z;
	double deg = 3.14159265 / 180;
	ofstream coordinates;

	coordinates.open("Coordinates10.txt");

	for (i = 0; i < mlv; i++) {
			
			mlevels[i].corners[1].p.xycoor[0] = double(-(3 * i)) / 2;
			mlevels[i].corners[1].p.xycoor[1] = double(-(3 * i)) / 2 / tan(60*deg);

			mlevels[i].elements[mlevels[i].corners[1].p.localpos[1] - 1].p.xycoor[0] = mlevels[i].corners[1].p.xycoor[0];
			mlevels[i].elements[mlevels[i].corners[1].p.localpos[1] - 1].p.xycoor[1] = mlevels[i].corners[1].p.xycoor[1];

			cout << mlevels[i].corners[1].p.xycoor[0] << endl;
			cout << mlevels[i].corners[1].p.xycoor[1] << endl;

			mlevels[i].corners[2].p.xycoor[0] = double((3 * i)) / 2;
			mlevels[i].corners[2].p.xycoor[1] = double(-(3 * i)) / 2 / tan(60 * deg);

			mlevels[i].elements[mlevels[i].corners[2].p.localpos[1] - 1].p.xycoor[0] = mlevels[i].corners[2].p.xycoor[0];
			mlevels[i].elements[mlevels[i].corners[2].p.localpos[1] - 1].p.xycoor[1] = mlevels[i].corners[2].p.xycoor[1];

			cout << mlevels[i].corners[2].p.xycoor[0] << endl;
			cout << mlevels[i].corners[2].p.xycoor[1] << endl;

			mlevels[i].corners[0].p.xycoor[0] = 0;
			mlevels[i].corners[0].p.xycoor[1] = double(mlevels[i].corners[2].p.xycoor[0]) / sin(60 * deg);

			mlevels[i].elements[mlevels[i].corners[0].p.localpos[1] - 1].p.xycoor[0] = mlevels[i].corners[0].p.xycoor[0];
			mlevels[i].elements[mlevels[i].corners[0].p.localpos[1] - 1].p.xycoor[1] = mlevels[i].corners[0].p.xycoor[1];

			cout << endl << mlevels[i].elements[mlevels[i].corners[0].p.localpos[1] - 1].p.xycoor[1] << endl;

			cout << mlevels[i].corners[0].p.xycoor[0] << endl;
			cout << mlevels[i].corners[0].p.xycoor[1] << endl;


		//	for (j = 0; j < mlevels[i].elements.size() && (i > 1); j++) {
				for (z = 1; z <= (i - 1); z++) {//there is always one less inter-point than there are connecting segments
					mlevels[i].elements[mlevels[i].corners[1].p.localpos[1] + z - 1].p.xycoor[0] = mlevels[i].corners[1].p.xycoor[0] + z*(mlevels[i].corners[2].p.xycoor[0] - mlevels[i].corners[1].p.xycoor[0]) / i;  //calc x coors of bottom
					mlevels[i].elements[mlevels[i].corners[1].p.localpos[1] + z - 1].p.xycoor[1] = mlevels[i].corners[1].p.xycoor[1]; //calc y coors of bottom

					//mlevels[i].elements[mlevels[i].corners[0].p.localpos[1] + z - 1].p.xycoor[0] = mlevels[i].corners[1].p.xycoor[0] - sin(30 * deg)*z*(mlevels[i].corners[1].p.xycoor[0]) / (i-1); //calc x coors of right side
					//mlevels[i].elements[mlevels[i].corners[0].p.localpos[1] + z - 1].p.xycoor[1] = mlevels[i].corners[1].p.xycoor[1] + cos(30 * deg)*z*(i+1) / (i-1); //calc y coors of right side

					//mlevels[i].elements[mlevels[i].corners[2].p.localpos[1] + z - 1].p.xycoor[0] = mlevels[i].corners[2].p.xycoor[0] + sin(30 * deg)*z*(mlevels[i].corners[1].p.xycoor[0]) / (i-1); //calc x coors of left side
					//mlevels[i].elements[mlevels[i].corners[2].p.localpos[1] + z - 1].p.xycoor[1] = mlevels[i].corners[2].p.xycoor[1] + cos(30 * deg)*z*(i+1) / (i-1); //calc y coors of left side
					
					  mlevels[i].elements[mlevels[i].corners[0].p.localpos[1] + z - 1].p.xycoor[0] = mlevels[i].corners[1].p.xycoor[0] + z*(mlevels[i].corners[0].p.xycoor[0] - mlevels[i].corners[1].p.xycoor[0]) / (i); //calc x coors of right side
					  mlevels[i].elements[mlevels[i].corners[0].p.localpos[1] + z - 1].p.xycoor[1] = mlevels[i].corners[1].p.xycoor[1] + z*(mlevels[i].corners[0].p.xycoor[1] - mlevels[i].corners[1].p.xycoor[1]) / (i); //calc y coors of right side

					  mlevels[i].elements[mlevels[i].corners[2].p.localpos[1] + z - 1].p.xycoor[0] = mlevels[i].corners[2].p.xycoor[0] - z*(mlevels[i].corners[0].p.xycoor[0] - mlevels[i].corners[1].p.xycoor[0]) / (i); //calc x coors of left side
					  mlevels[i].elements[mlevels[i].corners[2].p.localpos[1] + z - 1].p.xycoor[1] = mlevels[i].corners[2].p.xycoor[1] + z*(mlevels[i].corners[0].p.xycoor[1] - mlevels[i].corners[1].p.xycoor[1]) / (i); //calc y coors of left side
				}
			//}

				for (z = 0; z < mlevels[i].elements.size(); z++) {
					coordinates << mlevels[i].elements[z].p.xycoor[0] << "," << mlevels[i].elements[z].p.xycoor[1] << endl;
				}

	}

	coordinates.close();
}