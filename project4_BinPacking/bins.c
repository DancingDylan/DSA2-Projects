/*
 * bins.c :: bins.h
 *
 *  Created on: Apr 13, 2017
 *      Author: Dylan + Nathan
 *
 *  Project 4
 *  DSA2/COP4534
 */

/**
 * This is the source code for the corresponding header file: bins.h
 *
 * Containing the implementation for functions involved with solving
 * the bin-packing problem.
 */

//Corresponding Headers
#include "bins.h"

//initBins; initializes the collection of bins
BinCollectionT* initBins(int numBins, int binSize) {

	BinCollectionT* newBinCollection = (BinCollectionT*) malloc(
			sizeof(BinCollectionT));

	newBinCollection->bin = (BinNodeT**) malloc(sizeof(BinNodeT) * numBins);

	newBinCollection->numBins = 0;
	newBinCollection->binSize = binSize;

	newBinCollection->bin[0] = initBin(newBinCollection);

	return newBinCollection;
} /* END */

//initBoxCollection; initializes the collection of boxes
BoxCollectionT* initBoxCollection(int numBoxes) {

	BoxCollectionT* newBoxCollection = (BoxCollectionT*) malloc(
			sizeof(BoxCollectionT));

	newBoxCollection->box = (BoxNodeT**) malloc(sizeof(BoxNodeT) * numBoxes);

	newBoxCollection->numBoxes = numBoxes;
	newBoxCollection->unusedBoxes = 0;

	return newBoxCollection;
} /* END */

//initBox; initializes a single box node
BoxNodeT* initBox(int boxKey, int boxSize) {

	BoxNodeT* newBox = (BoxNodeT*) malloc(sizeof(BoxNodeT));

	newBox->boxKey = boxKey;
	newBox->boxSize = boxSize;
	newBox->inBin = false;

	return newBox;
} /* END */

//initBox; initializes a single box node
BinNodeT* initBin(BinCollectionT* binCollection) {

	BinNodeT* newBin = (BinNodeT*) malloc(sizeof(BinNodeT));

	newBin->binCapacity = 0;
	newBin->numBoxesInBin = 0;

	int k;
	for (k = 0; k < 20; k++)
		newBin->hasBoxKey[k] = 0;
	binCollection->bin[binCollection->numBins++] = newBin;

	return newBin;

} /* END */

//addBoxToBin; function adds a specific box to a specific bin
void addBoxToBin(BinCollectionT* tempBins, BoxCollectionT* tempBoxes, int i,
		int j) {

	// Add the box size to the bin capacity
	tempBins->bin[i]->binCapacity += tempBoxes->box[j]->boxSize;

	// Mark box as in bin
	tempBoxes->box[j]->inBin = true;

	// Increment number of boxes in the bin
	tempBins->bin[i]->numBoxesInBin++;

	// Making sure the box key is added to the right position in the bin
	size_t k = 0;
	while (tempBins->bin[i]->hasBoxKey[k] != 0) {
		k++;
	}
	tempBins->bin[i]->hasBoxKey[k] = tempBoxes->box[j]->boxKey;

} /* END */

//checkForUnused; checks the bin collection for empty bins after simulation
void checkForUnused(BinCollectionT* tempBins, FILE* fout) {

	if (fout == NULL) {
		perror("Error");
		exit(1);
	}

	int unused = 0;

	// Cycle through the bins
	int i;
	for (i = 0; i < tempBins->numBins; i++) {

		// If the bin is empty, increment unused bins
		if (tempBins->bin[i]->numBoxesInBin == 0) {
			unused++;
			continue;
		}

		// Print only the used bins and their contents
		fprintf(fout, "Bin %3d:  ", i);
		int j;
		for (j = 0; j < 10; j++) {
			fprintf(fout, "%6d  ", tempBins->bin[i]->hasBoxKey[j]);
		}

		fprintf(fout, "Currently Holding: %d   \n",
				tempBins->bin[i]->binCapacity);
	}

	fprintf(fout, "Number of used bins: %d\n", tempBins->numBins - unused);

} /* END */

//sortCollectionAscending; sorts a collection in ascending order
void sortCollectionAscending(BoxCollectionT* boxCollection) {

	if (boxCollection == NULL) {
		printf("The collection is empty.\n");
		return;
	}

	BoxCollectionT* tempCollection = boxCollection;
	BoxNodeT* tempNode;

	int i, j;
	for (i = 0; i < boxCollection->numBoxes; i++) {
		for (j = i + 1; j < boxCollection->numBoxes; j++) {
			if (tempCollection->box[i]->boxSize
					> tempCollection->box[j]->boxSize) {
				tempNode = tempCollection->box[i];
				tempCollection->box[i] = tempCollection->box[j];
				tempCollection->box[j] = tempNode;
			}
		}
	}

	boxCollection = tempCollection;

} /* END */

//sortCollectionDescending; sorts a collection in descending order
void sortCollectionDescending(BoxCollectionT* boxCollection) {

	if (boxCollection == NULL) {
		printf("The collection is empty.\n");
		return;
	}

	BoxCollectionT* tempCollection = boxCollection;
	BoxNodeT* tempNode;

	int i, j;
	for (i = 0; i < boxCollection->numBoxes; i++) {
		for (j = i + 1; j < boxCollection->numBoxes; j++) {
			if (tempCollection->box[i]->boxSize
					< tempCollection->box[j]->boxSize) {
				tempNode = tempCollection->box[i];
				tempCollection->box[i] = tempCollection->box[j];
				tempCollection->box[j] = tempNode;
			}
		}
	}

	boxCollection = tempCollection;

} /* END */

void reset(BinCollectionT* binCollection, BoxCollectionT* boxCollection) {

	int j;
	for (j = 0; j < 20; j++)
		binCollection->bin[0]->hasBoxKey[j] = 0;

	binCollection->bin[0]->numBoxesInBin = 0;
	binCollection->bin[0]->binCapacity = 0;

	int i;
	for (i = 1; i < binCollection->numBins; i++) {

		free(binCollection->bin[i]);
	}

	int k;
	for (k = 0; k < boxCollection->numBoxes; k++) {

		boxCollection->box[k]->inBin = false;
	}

	binCollection->numBins = 1;

} /* END */

void deleteBoxes(BoxCollectionT* boxCollection)
{

	int i;
	for (i = 0; i < boxCollection->numBoxes; i++)
		free(boxCollection->box[i]);

	free(boxCollection->box);
	free(boxCollection);

}

/* END BINS_H_ */
