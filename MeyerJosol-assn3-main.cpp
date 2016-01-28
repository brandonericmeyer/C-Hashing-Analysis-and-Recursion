//***************************************************************************
//  FILENAME:	 JosolMeyer-assn3-main.cpp
//  DESCRIPTION: This program will utilize hashing by creating 2 open address 
//					list arrays and 1 chain hash linked list.  Then analyze the
//					3 different collision resolution methods of Quadratic 
//					probing, Double hashing, and Chain hashing to search for its
//					key and display the results.
//  CLASS/DATE:  Adv Programming & Algorithms/Su8w2-Week 4
//  DESIGNER:	 Jeffrey Josol/Brandon Meyer
//***************************************************************************
#include <iostream>
#include <string>
#include <iomanip>
#include <stdlib.h>
#include <math.h>
#include <cmath>
#include <sstream>
#include "MeyerJosol-assn3-common.h"      // global definitions
#include "MeyerJosol-assn3-funcs.h"		// function definition

using namespace std;

// ---------------------------- (Main) -----------------------------
int main() {
	// Variables
	int randomNums[NUM_RAND_INTS],
		hashSize,
		timesExamined1 = 0,
		timesExamined2 = 0;
		
	int *openAddressList1,
		*openAddressList2;
		
	double loadFactor,
		   searchAvg1,
		   searchAvg2,
		   knuthPred1,
		   knuthPred2,
		   knuthPred3,
		   avgCount = 0;
		   
	bool programExit = false;
	int index = 0,
		bucket = 0,
		numOfItems = 0;
		
	// Begin
	CreateIntegers(randomNums);
		
	// Get hash table size
	do {
		cout << "What is the hash size of your table?: ";
		cin >> hashSize;
		
		if(hashSize < MIN_HASH_SIZE) {
			cout << "Error - hash size must be " << MIN_HASH_SIZE 
				 << " or greater, try again." << endl << endl;
		}
	} while(hashSize < MIN_HASH_SIZE);
	cout << endl << endl;
	
	// Open addressing
	openAddressList1 = new int[hashSize];
	openAddressList2 = new int[hashSize];
	
	// Initialize hash tables
	InitOpenAddress(openAddressList1, hashSize);
	InitOpenAddress(openAddressList2, hashSize);
	
	// Insert keys to hash table
	InsertOpenAddress(hashSize, randomNums, openAddressList1, QUAD_RES_TYPE);
	InsertOpenAddress(hashSize, randomNums, openAddressList2, DOUBLE_RES_TYPE);
	
	// Chained linked list
	chainList **chainHashTable = new chainList*[hashSize];
	initChained(hashSize, chainHashTable, programExit);
	
	if (programExit == true) {
		cout << endl << "Good-Bye." << endl;
		return 5;
	}

	insertChained(hashSize, chainHashTable, randomNums);
	searchChained(hashSize, chainHashTable, randomNums, numOfItems);
	
	// ------------------ (Begin Output Display) ------------------------
	cout << "--------------------- Hash Table ------------------------------"
		 << endl << endl;
		 
	cout << NUM_RAND_INTS << " items loaded into a " << hashSize << " element "
		 << "hash table" << endl;
		
	loadFactor = NUM_RAND_INTS / (hashSize * 1.0);
	
	cout << setw(PRECISION2) << "Load Factor = " << loadFactor << endl << endl;
	
	cout << "Results for searching for " << NUM_RAND_INTS / 2 << " items:" 
		 << endl << endl;
		 
	// Formatting
	cout.setf(ios::fixed);
	cout.setf(ios::showpoint);
	cout.precision(THREE);
		 
	// Quadratic Probing Section
	knuthPred1 = 1 - log(1 - loadFactor) - (loadFactor / 2);
	
	SearchOpenAddress(randomNums, openAddressList1, hashSize, searchAvg1, 
		timesExamined1, QUAD_RES_TYPE);
	
	cout << setw(PRECISION1) << "Quadratic Probing" << endl;
	cout << setw(PRECISION2) << timesExamined1 << " items examined (avg = " 
		 << searchAvg1 << " items examined per search)" << endl;
	cout << setw(PRECISION3) << "vs Knuth predicted avg = " << knuthPred1 
		 << " items examined per search" << endl << endl;
		 
	// Double Hashing Section
	knuthPred2 = - log ( 1 - loadFactor);
	
	SearchOpenAddress(randomNums, openAddressList2, hashSize, searchAvg2,
		timesExamined2, DOUBLE_RES_TYPE);

	cout << setw(PRECISION1) << "Double Hashing" << endl;
	cout << setw(PRECISION2) << timesExamined2 << " items examined (avg = " 
		 << searchAvg2 << " items examined per search)" << endl;
	cout << setw(PRECISION3) << "vs Knuth predicted avg = " << knuthPred2 
		 << " items examined per search" << endl << endl;
		 
	// Chained Linked List Section
	loadFactor = ceil(TEN * NUM_RAND_INTS / (double)hashSize) / TEN;
	avgCount = ONEPOINT + (numOfItems / (double)hashSize);
	knuthPred3 = ONEPOINT + (loadFactor / TWOPOINT);
	
	cout << setw(PRECISION1) << " Chained Hashing" << endl;
	cout << setw(PRECISION2) << numOfItems << " items examined (avg = " 
		 << avgCount << " items examined per search)";
	cout << endl << setw(PRECISION3) << "vs Knuth predicted avg = " 
		 << knuthPred3 << " items examined per search" << endl << endl;

	cout << endl << endl;
	system("Pause");
	return 0;
}
