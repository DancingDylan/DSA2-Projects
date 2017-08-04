/*
 * rndgen.h :: rndgen.c
 *
 *  Created on: Apr 14, 2017
 *      Author: Dylan + Nathan
 *
 *  Project 4
 *  DSA2/COP4534
 */

/**
 * This is the header file for the random number generation
 * involved in Project 4; bin-packing.
 *
 * Corresponding file: rndgen.c
 */

#ifndef RNDGEN_H_
#define RNDGEN_H_

//Standard Includes
#include <time.h>
#include <stdlib.h>

//Defines
#define AREA(x, y) ((x) * (y));

/** rndBinSize function
 *
 * This function generates a random sized used for the bins.
 *
 * #returns the size of the bins.
 */
int rndBinSize();

/** rndNumberOfBins function
 *
 * This function generates a random number of bins.
 *
 * #returns the number of bins.
 */
int rndNumberOfBins();

/** rndNumberOfBoxes function
 *
 * This function generates a random total of boxes.
 *
 * #returns the number of boxes.
 */
int rndNumberOfBoxes();

/** mkRnd function
 *
 * This function generates a random int based on the min and max
 * passed as parameters.
 *
 * @param: min; the lowest range
 * @param: max; the largest range
 *
 * #returns the generated number
 */
int mkRnd(int min, int max);

#endif /* RNDGEN_H_ */
