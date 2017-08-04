/*
 * bins.h :: bins.c
 *
 *  Created on: Apr 13, 2017
 *      Author: Dylan + Nathan
 *
 *  Project 4
 *  DSA2/COP4534
 */

/**
 * This is the header file that will contain the ADT for
 * solving the bin packing problem.
 *
 * Solely the online version, which entails retaining the
 * information of all the boxes before placing them within
 * bins.
 */

#ifndef BINS_H_
#define BINS_H_

//Standard Includes
#include "stdlib.h"
#include "stdio.h"

//Defining Boolean
typedef int bool;
enum { false, true };

/**
 * Structure for individual bin nodes.
 */
typedef struct BinNodeADT {

	int binCapacity; // The total used area within a bin
	int numBoxesInBin; // The number of boxes within a bin
	int hasBoxKey[20]; // The box keys within a  bin

} BinNodeT;

/**
 * Structure for individual box nodes, held within bins.
 */
typedef struct BoxNodeADT {

	int boxKey; // A Specific boxes key
	int boxSize; // The specific boxes size

	bool inBin;

} BoxNodeT;

/**
 * Structure to hold all of the bins.
 */
typedef struct BinCollectionADT {

	BinNodeT** bin; // The collection of bins

	int numBins; // The total number of bins alloted
	int binSize; // The total area of a bin

} BinCollectionT;

/**
 * Structure for the collection of boxes
 */
typedef struct BoxCollectionADT {

	BoxNodeT** box; // The collection of boxes

	int unusedBoxes; // The total number of unused boxes
	int numBoxes; // The total number of allowed boxes

} BoxCollectionT;

/** initBins function
 *
 * This function takes in the number of bins used, and the size of the bins. *All the bins will be the same sizes*
 *
 * @param: numBins; the number of bins
 * @param: dx; the bin width
 * @param: dy; the bin height
 */
BinCollectionT* initBins(int numBins, int binSize);

/** initBoxCollection function
 *
 * This function will initialize the collection of boxes.
 * Useful for the online approach to the bin-packing problem.
 *
 * @param: capacity; the capacity of the collection, number of boxes used
 *
 * #returns the new collection
 */
BoxCollectionT* initBoxCollection(int numBoxes);

/** initBox function
 *
 * This function will initialize a single box to be added to the collection.
 *
 * @param: boxKey; the key of the box
 * @param: boxSize; the size of the box
 *
 * #returns the new box
 */
BoxNodeT* initBox(int boxKey, int boxSize);

/** initBin function
 *
 * This function will initialize a single bin to be added to the collection.
 *
 * @param: binCollection: the collection of bins
 *
 * #returns the new bin
 */
BinNodeT* initBin(BinCollectionT* binCollection);

/** addBoxToBin function
 *
 * This function takes in the two collections, and a specific index of a box to add to a bin.
 *
 * @param: tempBins; the collection of bins
 * @param: tempBoxes; the collection of boxes
 * @param: i; the index of a bin
 * @param: j; the index of a box
 */
void addBoxToBin(BinCollectionT* tempBins, BoxCollectionT* tempBoxes, int i, int j);

/** checkForUnused function
 *
 * This function checks a bin collection for empty bins after each simulation.
 *
 * @param: tempBins; the bin collection needing to be check for unused bins
 */
void checkForUnused(BinCollectionT* tempBins, FILE* fout);

/** sortCollectionAscending function
 *
 * This function takes in the collection of boxes and sorts them in ascending order.
 *
 * @param: boxCollection; the collection of boxes
 */
void sortCollectionAscending(BoxCollectionT* boxCollection);

/** sortCollectionDescending function
 *
 * This function takes in the collection of boxes and sorts them in descending order.
 *
 * @param: boxCollection; the collection of boxes
 */
void sortCollectionDescending(BoxCollectionT* boxCollection);
/** reset function
 *
 * This function resets the box and bin data to zero.
 *
 * @param: binCollection; the collection of bins
 * @param: boxCollection; the collection of boxes
 */
void reset(BinCollectionT* binCollection, BoxCollectionT* boxCollection);

/** deleteBoxes function
*
* This function frees up all the memory for the box collection
*
* @param boxCollection the collection of boxes
*/
void deleteBoxes(BoxCollectionT* boxCollection);

#endif /* BINS_H_ */
