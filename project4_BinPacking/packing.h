/*
 * packing.c :: packing.h
 *
 *  Created on: Apr 16, 2017
 *      Author: Dylan + Nathan
 *
 *  Project 4
 *  DSA2/COP4534
 */

#ifndef PACKING_H_
#define PACKING_H_

#include <stdio.h>
#include <stdlib.h>

#include "bins.h"
#include <limits.h>

/** firstFit function
 *
 * This function takes in the collection of boxes and bins, then solves the problem.
 * Placing a box within the first bin it can fit into.
 *
 * @param: binCollection; the collection of bins
 * @param: boxCollection; the collection of boxes
 */
void firstFit(BinCollectionT* binCollection, BoxCollectionT* boxCollection, FILE* fout);

/** bestFit function
 *
 * This function takes in the collection of boxes and bins, then solves the problem.
 * Placing a box within the best bin it can fit into, i.e. the most optimal bin to be
 * placed in without wasting space.
 *
 * @param: binCollection; the collection of bins
 * @param: boxCollection; the collection of boxes
 */
void bestFit(BinCollectionT* binCollection, BoxCollectionT* boxCollection, FILE* fout);

void nextFit(BinCollectionT* binCollection, BoxCollectionT* boxCollection, FILE* fout);

int checkBin(BinCollectionT* tempBins, BoxCollectionT* tempBoxes, int binIndex,
		int boxIndex);

#endif /* PACKING_H_ */
