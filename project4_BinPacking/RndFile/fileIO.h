/*
 * fileIO.h :: fileIO.c
 *
 *  Created on: Apr 14, 2017
 *      Author: Front
 */

/**
 * This is the header file for handling the File I/O used for Project 4; bin-packing.

 * The first number in the file is the number of boxes, the second being the size of bins,
 * the third being the number of bins.
 */

#ifndef FILEIO_H_
#define FILEIO_H_

//Standard Includes
#include <stdio.h>
#include <stdlib.h>

//Corresponding Headers
#include "rndgen.h"

/** createFile function
 *
 * This function creates a new file in which box data is placed.
 */
void createFile();

/** fillFile function
 *
 * This function fills a file with box data.
 *
 * @param: argv; a string passed for the name of the file being created.
 */
void fillFile(char *argv);

#endif /* FILEIO_H_ */
