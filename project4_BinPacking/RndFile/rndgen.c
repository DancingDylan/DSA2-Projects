/*
 * rndgen.c :: rndgen.h
 *
 *  Created on: Apr 14, 2017
 *      Author: Dylan + Nathan
 *
 *  Project 4
 *  DSA2/COP4534
 */

//Corresponding Headers
#include "rndgen.h"

//rndBinSize; determines the size of the bins used in the simulation
int rndBinSize() {

	/** Note:
		 * I'm making sure the range is from 3 - 16.
		 * I'll assume we always have a size for bins larger than 9, and smaller than 225.
		 */
	return mkRnd(3, 16);
}

//rndNumberOfBins; determines the number of bins used in the simulation
int rndNumberOfBins() {

	/** Note:
	 * I'm making sure the range is from 1 - 10.
	 * I'll assume we always have more than 2 bins at each run.
	 */
	return mkRnd(2, 16);
} /* END */

//rndNumberOfBoxes; determines the number of boxes used in the simulation
int rndNumberOfBoxes() {

	/** Note:
	 * I'm making sure the range is from 5 - 30.
	 * I'll assume we always have more than 5 boxes at each run.
	 */
	return mkRnd(2, 31);
} /* END */

//mkRnd; generates a random number based on a range
int mkRnd(int min, int max) {

	srand(time(NULL));
	return (rand() % max + min);

} /* END */

/* END RNDGEN_C_ */
