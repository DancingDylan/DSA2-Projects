/*
 * fileIO.c :: fileIO.h
 *
 *  Created on: Apr 14, 2017
 *      Author: Dylan + Nathan
 *
 *  Project 4
 *  DSA2/COP4534
 */

/**
 * This is the source code for handling the File I/O used for Project 4; bin-packing.
 * Via project description we need to input a file name, which will contain a random
 * number of boxes with random sizes.
 *
 * The first number in the file is the number of boxes, the second being the size of bins
 */

//Corresponding Includes
#include "fileIO.h"

//Prototypes
void createFile();
void fillFile(char *argv);


/**    ############# IMPORTANT #############
 * This is currently commented out, due to two mains within a single project.
 * The professor indicated that that file must be existent for the project to run
 * and that I could create a separate program solely to generate the file.
 *
 * I'll be turning this in also, with clear indication that it isn't directly used
 * within solving the simulation.
 *
 * Note: When the user wishes to generate a different file, being inside a kernel
 * makes this process easy. But, if one is to use an IDE, the user MUST:
 * comment out the main function within the main.c file, and un-comment
 * the main function from within this file; fileIO.c, then compile and run.
 * 	   ############# IMPORTANT #############
 */

//main; this is the main function for producing a file used in the bin-packing problem
/*
int main(void) {

	printf("Producing file...\n");
	createFile();
	printf("Ending...\n");

	return 0;

}  END */

//createFile; creates the file to retain box data
void createFile() {

	// Set file name
	char* argv = "boxdata.txt";
	FILE* fin = fopen(argv, "w");

	// Check if file was created
	if (fin != NULL) {
		printf("File name: %s, created successfully.\n", argv);
		fclose(fin);
	} else {
		perror("Error creating file.");
		exit(1);
	}

	// Fill the file with box data
	fillFile(argv);

} /* END */

//fillFile; fills the file with box data
void fillFile(char *argv) {

	/**
	 * No need to check if it exists, function gets called
	 * promptly after file creation.
	 */
	FILE* fin = fopen(argv, "w");

	// Set the number of boxes
	int numBoxes = rndNumberOfBoxes();

	int x = rand() % 16 + 3;
	int y = rand() % 16 + 3;
	int size = AREA(x, y);

	fprintf(fin, "%d\n%d\n%d\n", numBoxes, size, rndNumberOfBins());

	// Print the data to the file
	int key, i;
	for (i = 0, key = 1; i < numBoxes; i++, key++) {
		int size = AREA(rand() % 11 + 1, rand() % 11 + 1);
		fprintf(fin, "%d, %d\n", key, size);
	}

	printf("File data created.\n");

} /* END */

/* FILEIO_C_ */
