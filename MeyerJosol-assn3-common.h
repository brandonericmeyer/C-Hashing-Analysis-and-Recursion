//***************************************************************************
//  CODE FILENAME:  JosolMeyer-assn3-common.h
//  DESCRIPTION:    Global definitions 
//***************************************************************************/
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <sstream>

using namespace std;

const int NUM_RAND_INTS = 5000;
const int MIN_NUM = 1;
const int MAX_NUM = 30000;
const int MIN_HASH_SIZE = 6700;
const string QUAD_RES_TYPE = "quadRes",
		   	 DOUBLE_RES_TYPE = "doubleRes";

const int THREE = 3;
const int PRECISION1 = 21;
const int PRECISION2 = 12;
const int PRECISION3 = 35;
const int ZERO = 0;
const double TEN = 10.0;
const double ONEPOINT = 1.0;
const double TWOPOINT = 1.0;

struct chainList {
	int num;

	chainList *top, 
			  *link;
};
