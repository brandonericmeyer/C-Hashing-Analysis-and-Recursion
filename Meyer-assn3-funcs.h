//***************************************************************************
//  CODE FILENAME:  MeyerJosol-assn3-funcs.h
//  DESCRIPTION:    Prototypes of functions 
//  FUNCTIONS:      CreateIntegers - create's an unsorted list of 5000 random 
//						numbers (1-30000) in an array.
//					QuadProbeRes - performs quad probe resolution until 
//						unoccupied address is found.
//					DoubleHashRes - performs double hash resolution until 
//						unoccupied address is found.
//					InsertOpenAddress - Inserts values into open address hash 
//						table and performs address conflict resolutions when 
//						needed.
//					SearchOpenAddress - search for half of integers of odd type.
//					InsertChained - inserts values into chained hash table and 
//						performs address conflict resolutions when needed.
//					InitChained - initializes a chained address hash table of 
//						linked list type.
//					SepChainRes - performs separate chain resolution until 
//						unoccupied address is found.
//					SearchChained - search for half of integers of odd type.
//***************************************************************************/
void insertChained(const int &hashSize, chainList *chainHashTable[],
	int randomNums[]);
void initChained(const int &hashSize, chainList *chainHashTable[],
	bool &programExit);
void sepChainRes(chainList *chainHashTable[], int randomNums[],
	const int &index, const int &bucket);
void searchChained(const int &hashSize, chainList *chainHashTable[],
	int randomNums[], int & numOfItems);