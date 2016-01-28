//***************************************************************************
//  CODE FILENAME:  JosolMeyer-assn3-funcs.cpp
//  DESCRIPTION:    Functions used in guessing game program
//  DESIGNER:       Smallwood
//  FUNCTIONS:      FindClosest - finds closest guess to pick
//***************************************************************************/
#include "JosolMeyer-assn3-common.h"
#include "JosolMeyer-assn3-funcs.h"

// -------------------- (Functions) -----------------------
//*************************************************************************
//  FUNCTION:	 CreateIntegers
//  DESCRIPTION: Create's an unsorted list of 5000 random numbers (1-30000)
//					in an array.
//  INPUT:       Parameter:    none
//  OUTPUT: 	 Return value: integers[] - random numbers array
//	CALLS TO:	 none
//	IMPLEMENTED BY: Josol
//*************************************************************************
void CreateIntegers(int randomNums[]) {
	int i = 0;
	bool verified;
	int num;

	while (i < NUM_RAND_INTS) {
		do {				// Loop until duplicates gone
			num = rand() % MAX_NUM + MIN_NUM;

			verified = true;
			for (int j = 0; j < i; j++) {
				if (num == randomNums[j]) {
					verified = false;
				}
			}
		} while (!verified);

		randomNums[i] = num;
		i++;
	};

	return;
}

//*************************************************************************
//  FUNCTION:	 InitOpenAddress
//  DESCRIPTION: Initializes an open address hash table of array type.
//  INPUT:       Parameter:    openAddressList[] - hash table array
//							   hashSize - size of hash table
//  OUTPUT: 	 Return value: openAddressList[] - hash table array
//	CALLS TO:	 none
//  IMPLEMENTED BY: Josol
//*************************************************************************
void InitOpenAddress(int openAddressList[], int hashSize) {
	for (int i = 0; i < hashSize; i++) {
		openAddressList[i] = 0;
	}

	return;
}

//*************************************************************************
//  FUNCTION:	 QuadProbeRes
//  DESCRIPTION: Performs quad probe resolution until unoccupied address is
//					found.
//  INPUT:       Parameter:    &integer - integer value to be inserted
//							   probe - number to be squared
//							   hashSize - size of hash table
//  OUTPUT: 	 Return value: address - available address location
//	CALLS TO:	 none
//	IMPLEMENTED BY: Josol
//*************************************************************************
int QuadProbeRes(int address, int probe, const int hashSize) {
	int quadAddress;

	quadAddress = pow(probe, 2) + address;

	address = quadAddress;

	return address;
}

//*************************************************************************
//  FUNCTION:	 DoubleHashRes
//  DESCRIPTION: Performs double hash resolution until unoccupied address is
//					found.
//  INPUT:       Parameter:    key - actual data value
//							   hashSize - size of hash table
//  OUTPUT: 	 Return value: address - available address location
//	CALLS TO:	 none
//	IMPLEMENTED BY: Josol
//*************************************************************************
int DoubleHashRes(int key, const int hashSize) {
	int toAdd;

	cout << key << endl;

	toAdd = (key % (hashSize - 2)) + 1;

	return toAdd;
}

//*************************************************************************
//  FUNCTION:	 InsertOpenAddress
//  DESCRIPTION: Inserts values into open address hash table and performs 
//					address conflict resolutions when needed.
//  INPUT:       Parameter:    hashSize - size of hash table
//							   randomNums[] - random array of numbers
//							   openAddressList[] - hash table array
//							   resType - string to determine hash choice
//  OUTPUT: 	 Return value: openAddressList[] - hash table array
//	CALLS TO:	 QuadProbeRes, DoubleHashRes
//	IMPLEMENTED BY: Josol
//*************************************************************************
void InsertOpenAddress(int hashSize, int randomNums[], int openAddressList[],
	string resType) {
	int key,
		address,
		orgAddress,
		toAdd,
		probe;
	bool verified,
		doubleTried = false;

	for (int i = 0; i < NUM_RAND_INTS; i++) {
		address = randomNums[i] % hashSize;		// Original hash
		probe = 1;
		key = randomNums[i];
		//cout << i << endl;

		do {						// Loop until valid address found
			verified = true;

			if (openAddressList[address] != 0) {		// If not open
				verified = false;
			}

			if (!verified) {
				if (resType == QUAD_RES_TYPE) {
					address = QuadProbeRes(address, probe, hashSize);
					probe++;

					// If address greater than hash range
					if (address >= hashSize) {
						address %= hashSize;
					}
				}
				else if (resType == DOUBLE_RES_TYPE) {
					toAdd = DoubleHashRes(key, hashSize);
					address += toAdd;

					cout << address << endl;


					if (address >= hashSize) {

						address %= hashSize;
						cout << address << endl;

					}
				}
			}
		} while (!verified);

		// Insert key into hash table
		openAddressList[address] = randomNums[i];
	}

	return;
}

//*************************************************************************
//  FUNCTION:	 SearchOpenAddress
//  DESCRIPTION: Search for half of integers of odd type.
//  INPUT:       Parameter:    randomNums[] - random array of numbers
//							   openAddressList[] - hash table array
//							   hashSize - size of hash table
//							   &searchAvg - average items examined
//							   &timesExamined - total times address examined
//							   resType - string to determine hash choice
//  OUTPUT: 	 Return value: &searchAvg - average items examined
//							   &timesExamined - total times address examined
//	CALLS TO:	 QuadProbeRes, DoubleHashRes
//	IMPLEMENTED BY: Josol
//*************************************************************************
void SearchOpenAddress(int randomNums[], int openAddressList[], int hashSize,
	double& searchAvg, int& timesExamined, string resType) {
	int key,
		address,
		orgAddress,
		toAdd,
		probe;
	double listSize;
	bool verified,
		doubleTried;

	// Search half of list and only odd numbers
	for (int i = 0; i < NUM_RAND_INTS; i += 2) {
		address = randomNums[i] % hashSize;		// Orignial hash
		timesExamined++;
		probe = 1;
		key = randomNums[i];

		do {					// Loop until matching address found
			verified = true;

			if (openAddressList[address] != randomNums[i]) {
				verified = false;
				timesExamined++;
			}

			if (!verified) {
				if (resType == QUAD_RES_TYPE) {
					address = QuadProbeRes(address, probe, hashSize);
					probe++;

					// If address greater than hash range
					if (address >= hashSize) {
						address %= hashSize;
					}
				}
				else if (resType == DOUBLE_RES_TYPE) {
					toAdd = DoubleHashRes(key, hashSize);
					address += toAdd;

					if (address >= hashSize) {
						address %= hashSize;
					}
				}
			}
		} while (!verified);
	}

	// Calculate search average
	listSize = NUM_RAND_INTS / 2.0;
	searchAvg = timesExamined / listSize;

	return;
}