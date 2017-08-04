/*
 * packing.c :: packing.h
 *
 *  Created on: Apr 16, 2017
 *      Author: Dylan + Nathan
 *
 *  Project 4
 *  DSA2/COP4534
 */

/**
 * This is the source file for the functions
 * for solving a bin-packing simulation.
 *
 * The offline approach allows the simulation to have previous knowledge of the
 * number and sizes of boxes before starting. Which allows for sorting, and
 * determining logically the best approach
 */
#include "packing.h"

//Define macro to adjust two indexes at the same time
/* Just make it look neater and also one less line of code Muwhahahahah */
#define adjustIndex(i, j) ((i--),(j++));

void firstFit(BinCollectionT* binCollection, BoxCollectionT* boxCollection,
		FILE* fout) {

	// Check to make sure neither of the collections are empty.
	if (binCollection == NULL || boxCollection == NULL) {
		printf("The collection is empty.\n");
		return;
	}

	// Declaring temp replicas of collections
	BoxCollectionT* tempBoxes = boxCollection;
	BinCollectionT* tempBins = binCollection;

	// Cycling through all of the boxes
	size_t i = 0, j = 0;
	for (j = 0; j < tempBoxes->numBoxes; j++) {

		// Declare quick-use variables
		BinNodeT* currBin = tempBins->bin[i];
		BoxNodeT* currBox = tempBoxes->box[j];

		// If the current box wont push the current bin over its limit, add it
		if ((currBox->boxSize + currBin->binCapacity) < tempBins->binSize) {
			addBoxToBin(tempBins, tempBoxes, i, j);

			// Else, recursively check for an available bin
		} else {
			checkBin(tempBins, tempBoxes, i, j);
		}

	}

	//Check for unused boxes and print simulation results for accuracy and efficiency
	checkForUnused(tempBins, fout);
	reset(binCollection, boxCollection);

} /* END */

void bestFit(BinCollectionT* binCollection, BoxCollectionT* boxCollection,
		FILE* fout) {

	// Check to make sure neither of the collections are empty.
	if (binCollection == NULL || boxCollection == NULL) {
		printf("The collection is empty.\n");
		return;
	}

	// Create replicas of the collection
	BoxCollectionT* tempBoxes = boxCollection;
	BinCollectionT* tempBins = binCollection;

	int j, i;
	for (j = 0; j < tempBoxes->numBoxes; j++) {

		// Check to make sure the current box isn't bigger than the bins
		if (tempBoxes->box[j]->boxSize > tempBins->binSize) {
			continue;
		}

		// Check to make sure the current box isn't in a bin
		if (tempBoxes->box[j]->inBin == true) {
			continue;
		}

		int max = INT_MIN;
		int max_index = -1;

		for (i = 0; i < tempBins->numBins; i++) {

			if (tempBins->bin[i]->binCapacity + tempBoxes->box[j]->boxSize
					> tempBins->binSize) {
				initBin(tempBins);
				continue;

			} else if (tempBins->bin[i]->binCapacity
					+ tempBoxes->box[j]->boxSize > max) {

				max = tempBins->bin[i]->binCapacity
						+ tempBoxes->box[j]->boxSize;
				max_index = i;

			}

		}

		if (max_index != -1) {
			addBoxToBin(tempBins, tempBoxes, max_index, j);
		}

	}

	// Check for unused bins and print the results
	checkForUnused(tempBins, fout);
	reset(binCollection, boxCollection);

} /* END */

void nextFit(BinCollectionT* binCollection, BoxCollectionT* boxCollection,
		FILE* fout) {

	int i, j = 0;
	for (i = 0; i < boxCollection->numBoxes; i++) {

		if (j >= binCollection->numBins)
			initBin(binCollection);

		// Check to make sure the current box isn't bigger than the bins
		if (boxCollection->box[i]->boxSize > binCollection->binSize) {
			printf("Box to large for bin.... ignoring box %d\n", boxCollection->box[i]->boxKey);
			continue;

		}

		if ((boxCollection->box[i]->boxSize + binCollection->bin[j]->binCapacity)
				<= binCollection->binSize) {

			addBoxToBin(binCollection, boxCollection, j, i);

		} else {

			adjustIndex(i, j);
		}

	}

	checkForUnused(binCollection, fout);
	reset(binCollection, boxCollection);

} /* END */

//chkBin; recursive function to check for the next opening for a box
int checkBin(BinCollectionT* tempBins, BoxCollectionT* tempBoxes, int binIndex,
		int boxIndex) {

	if (binIndex >= tempBins->numBins)
		initBin(tempBins);

	// Create quick-use variables
	BinNodeT* currBin = tempBins->bin[binIndex];
	BoxNodeT* currBox = tempBoxes->box[boxIndex];

	int maxSize = tempBins->binSize;

	// Check to make sure the current box isn't in a bin or larger than the current bin
	if (currBox->inBin == true || currBox->boxSize > maxSize) {
		return -1;
	}

	// Check to see if the current box pushes the bin over its limit
	if ((currBin->binCapacity + currBox->boxSize) > maxSize) {

		// If so, recursive call to the next bin
		checkBin(tempBins, tempBoxes, binIndex + 1, boxIndex);

		// Else, everything is if; add the box to the bin
	} else {
		addBoxToBin(tempBins, tempBoxes, binIndex, boxIndex);
	}

	return 1;
} /* END */
