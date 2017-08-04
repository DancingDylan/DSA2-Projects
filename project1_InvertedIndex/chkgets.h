/**
 * Contains functions protoypes
 * for chkgets.c
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#ifndef _CHKGETS_H
#define _CHKGETS_H

#include "frequency.h"

/**
 * Reads in the documents from a given directory
 *
 * @param dictionary the dictionary ADT which will be used to form the inverted index
 * @param frequency the frequency ADT which will be used to form the frequency index
 * @param dirName the name of the directory which contains all of the documents to be read in
 * @param debug the debug flag which if 0 will display the inverted index to the user
 */
void readDocs(DictionaryT* dictionary, FrequencyT* frequency,
		const char* dirName, int debug);

/**
 * Retrieves the number of lines in a file
 *
 * @param chkName the name of the file to be checked
 */
unsigned short lineCount(const char *chkName);

/**
 * Retrieves the directory then returns the number of folders in it
 *
 * @param chkName the name of the file to be checked
 */
unsigned short fileListing(const char* chkName);

/**
 * Checks if passed parameter is a directory.
 *
 * @param dir the name of the directory to be checked
 * @return result the result of checking if what was passed in is a directory. Returns 1 if it is a directory, else returns -1.
 */
int isDirectory(const char *dir);

/**
 * Checks if passed parameter is a file.
 *
 * @param file the name of the file to be checked
 * @return result the result of checking if what was passed in is a file. Returns 1 if it is a file, else returns -1.
 */
int isFile(const char *file);

#endif
