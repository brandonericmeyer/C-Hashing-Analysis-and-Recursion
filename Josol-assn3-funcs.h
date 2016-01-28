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
void CreateIntegers(int randomNums[]);
int QuadProbeRes(int address, int probe, const int hashSize);
int DoubleHashRes(int key, const int hashSize);
void InsertOpenAddress(int hashSize, int randomNums[], int openAddressList[],
	string resType);
void SearchOpenAddress(int randomNums[], int openAddressList[], int hashSize,
	double& searchAvg, int& timesExamined, string resType);