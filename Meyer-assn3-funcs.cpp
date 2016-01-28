//*************************************************************************
//  FUNCTION:	 InsertChained
//  DESCRIPTION: Inserts values into chained hash table and performs 
//					address conflict resolutions when needed.
//  INPUT:       Parameter:    integers[] - random numbers array
//                             hashTableSize - hash table size
//  OUTPUT: 	 Return value: chainHashTable[] - open addressing hash table
//	CALLS TO:	 SepChainRes
//	IMPLEMENTED BY: Meyer
//*************************************************************************
void insertChained(const int &hashSize, chainList *chainHashTable[],
	int randomNums[]) { // Actual hashing function
	const int NEGONE = -1;
	const int MAXINTSIZE = 5000;
	const int ZERO = 0;

	int index = 0;
	int hash = 0;
	string key;
	stringstream ss;

	for (int i = ZERO; i < MAXINTSIZE; i++) {
		ss << randomNums[i] << endl;

		//******HASH SECTION*********
		key = ss.str(); // key to be hashed

		ss.str("");

		// ASCII method for summing a hash
		for (int j = ZERO; j < key.length(); j++) {
			hash = hash + (int)key[j];
		}

		index = hash % hashSize;

		//******PLACEMENT/RESOLUTION SECTION*********

		// If chainlist is empty, place integer in that place.
		if (chainHashTable[index]->num == NEGONE) {
			chainHashTable[index]->num = randomNums[i];
		}
		else { // create a new node
			// Method resolution
			sepChainRes(chainHashTable, randomNums, index, i);

		} // end else
	} // end for
}

//*************************************************************************
//  FUNCTION:	 InitChained
//  DESCRIPTION: Initializes a chained address hash table of linked list type.
//  INPUT:       Parameter:    hashTableSize - hash table size
//  OUTPUT: 	 Return value: chainHashTable[] - chained hash table
//                             programExit - if memory allocation fails, signal to exit.
//	CALLS TO:	 none
//	IMPLEMENTED BY: Meyer
//*************************************************************************
void initChained(const int &hashSize, chainList *chainHashTable[],
	bool &programExit) { // Initializes linked list
	const string DISPLAY_MEMORY_PROBLEMS = "Error - Cannot allocate memory! "
		"Program will not exit.";

	chainList *newNode;
	const int ONE = 1;
	const int NEGONE = -1;
	const int ZERO = 0;

	// Goes through array and initializes every bucket to 0.
	for (int i = ZERO; i < hashSize; i++) {
		newNode = new (nothrow)chainList;

		if (newNode == NULL) {  // Checking for allocation
			cout << endl << DISPLAY_MEMORY_PROBLEMS << endl;

			i = hashSize;

			programExit = true;
		}
		else {
			chainHashTable[i] = newNode;

			chainHashTable[i]->num = NEGONE;

			chainHashTable[i]->link = NULL;

			programExit = false;
		}
	} // end for
}

//*************************************************************************
//  FUNCTION:	 SepChainRes
//  DESCRIPTION: Performs separate chain resolution until unoccupied address is
//					found.
//  INPUT:       Parameter:    integers - integer value to be inserted
//							   chainHashTable[] - open addressing hash table
//							   index - index collision to be resolved.
//							   bucket - holds currect bucket for integer array.
//  OUTPUT: 	 Return value: address - available address location
//	CALLS TO:	 none
//	IMPLEMENTED BY: Meyer
//*************************************************************************
void sepChainRes(chainList *chainHashTable[], int randomNums[],
	const int &index, const int &bucket) { // Collision resolution
	chainList* top = chainHashTable[index]; // points to top bucket

	chainList* temp = new chainList; // new node to hold integer

	temp->num = randomNums[bucket];  // set equal to integer

	temp->link = NULL;

	while (top->link != NULL) { //Traverse list until we find the last item.
		top = top->link;
	} // end while

	top->link = temp; // last item in the list now points to new item/integer.
}

//*************************************************************************
//  FUNCTION:	 SearchChained
//  DESCRIPTION: Search for half of integers of odd type.
//  INPUT:       Parameter:    chainHashTable[] - chained hash table
//                             hashTableSize - size of the hash table.
//  OUTPUT: 	 Return value: numOfItems - number of items examined
//	CALLS TO:	 none
//	IMPLEMENTED BY: Meyer
//*************************************************************************
void searchChained(const int &hashSize, chainList *chainHashTable[],
	int randomNums[], int & numOfItems) {
	const int NEGONE = -1;
	const int ONE = 1;

	chainList* temp = NULL;
	bool foundItem = false;
	int bucket = 0;
	int hash = 0;
	int count = 0; // Keeps track of how many items are examined.
	string key;
	stringstream ss;

	for (int i = ZERO; i < NUM_RAND_INTS; i++) { // Keys only the even values.
		ss << randomNums[i] << endl;

		//******HASH SECTION*********
		key = ss.str(); // key to be hashed

		ss.str("");

		// ASCII method for summing a hash
		for (int j = ZERO; j < key.length(); j++) {
			hash = hash + (int)key[j];
		}

		bucket = hash % hashSize;

		temp = chainHashTable[bucket]; // points to top bucket for that index

		while (temp != NULL && foundItem != true) {
			if (temp->num) {
				foundItem = true;
			}

			count++;

			temp = temp->link;
		}

		i++; // Key only even values.

		numOfItems = numOfItems + count;

		count = ZERO;

		foundItem = false;

	} // end for
}
