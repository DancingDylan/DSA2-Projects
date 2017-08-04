/*
 * main.c
 *
 *  Created on: Apr 15, 2017
 *      Author: Dylan + Nathan
 *
 *  Project 4
 *  DSA2/COP4534
 */

/**
 * This is the main function of Project 4 - bin-packing.
 *
 * This will call corresponding functions from the headers
 * included to solve a randomly generated set for the bin-packing problem.
 *
 * Once simulation results are determined, they will be pushed into a file named : "simresults.txt,"
 * note, system output will notify user with the files name and when it is finalized.
 *
 * Also, a Report file has been created in the same directory as the rest of the program, used to
 * Illustrate and explain  the project and the method used to retain information and solve the bin-packing problem.
 *
 * Also, the method I created in generating a random file is within the folder: "RndFile," which has its own
 * headers, classes and makefile.
 *
 */

/**
 * File containing box data: boxdata.txt
 * Report file name: Report.txt
 * Simulation results: simresults.txt
 */

//Corresponding Headers
#include "packing.h"

//Define global output file name
char* argv2 = "simresults.txt";

int main(int argc, char **argv) {

	// Open the file and check for existence and readability
	FILE* fin = fopen(argv[1], "r");
	if (fin != NULL) {
		printf("File name: %s, opened successfully.\n", argv[1]);
	} else {
		perror("Error");
		exit(1);
	}

	// Bin variables
	int numBins = 0, binSize = 0;

	// Box variables
	int numBoxes = 0, boxKey = 0, boxSize = 0;

	fscanf(fin, "%d\n%d\n%d", &numBoxes, &binSize, &numBins);

	// Initialize the box and bin collections
	BoxCollectionT* boxCollection = initBoxCollection(numBoxes);
	BinCollectionT* binCollection = initBins(numBins, binSize);

	// Logic check
	printf("\nUser logic check:\n");
	printf("Number of Boxes: %d\n", boxCollection->numBoxes);
	printf("Number of Bins: %d\n", binCollection->numBins);
	printf("Size of Bins: %d\n\n", binCollection->binSize);

	// Scan through the file for the box data
	int i;
	for (i = 0; fscanf(fin, "%d, %d", &boxKey, &boxSize) != EOF; i++) {
		boxCollection->box[i] = initBox(boxKey, boxSize);
	}

	// Close the input file
	fclose(fin);

	// Create the output file and open it
	printf("Creating output file: simresults.txt.\n## This file will hold the simulation results. ##\n\n");
	FILE* fout = fopen("simresults.txt", "w");

	fprintf(fout, "This file holds the simulation results for both the Off/Online approaches to solving the bin-packing problem.\n");
	fprintf(fout, "\n\n-Unordered-\nBox Collection:\n");
	for (i = 0; i < boxCollection->numBoxes; i++) {
		fprintf(fout, "Key: %-4d   Size: %2d\n", boxCollection->box[i]->boxKey,
				boxCollection->box[i]->boxSize);
	}

	fprintf(fout, "\n\n___________________________________________________________________________________________________________________________\n");
	fprintf(fout, "\nSimulation results for Online First Fit approach:\n\n");
	firstFit(binCollection, boxCollection, fout);

	fprintf(fout, "\n\n___________________________________________________________________________________________________________________________\n");
	fprintf(fout, "\nSimulation results for Online Best Fit approach:\n\n");
	bestFit(binCollection, boxCollection, fout);

	fprintf(fout, "\n\n___________________________________________________________________________________________________________________________\n");
	fprintf(fout, "\nSimulation results for Online Next Fit approach:\n\n");
	nextFit(binCollection, boxCollection, fout);

	printf("Online bin-packing results finalized.\n");
	sortCollectionDescending(boxCollection);

	fprintf(fout, "\n\n-Descending Order-\nBox Collection:\n");
	for (i = 0; i < boxCollection->numBoxes; i++) {
		fprintf(fout, "Key: %-4d   Size: %2d\n", boxCollection->box[i]->boxKey,
						boxCollection->box[i]->boxSize);
	}

	fprintf(fout, "\n\n\n\n___________________________________________________________________________________________________________________________\n");
	fprintf(fout, "\nSimulation results for Offline First Fit approach:\n\n");
	firstFit(binCollection, boxCollection, fout);

	fprintf(fout, "\n\n___________________________________________________________________________________________________________________________\n");
	fprintf(fout, "\nSimulation results for Offline Best Fit approach:\n\n");
	bestFit(binCollection, boxCollection, fout);

	fprintf(fout, "\n\n___________________________________________________________________________________________________________________________\n");
	fprintf(fout, "\nSimulation results for Offline Next Fit approach:\n\n");
	nextFit(binCollection, boxCollection, fout);
	
	deleteBoxes(boxCollection);
	free(binCollection->bin[0]);
	free(binCollection->bin);
	free(binCollection);
	// Close the output file
	fclose(fout);

	printf("Offline bin-packing results finalized.\n\nEnding...");
	return 0;
} /* END */


