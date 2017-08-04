/**
 * Contains all the structures representing the documents and
 * the stop word list and their function signatures
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#ifndef _DOCUMENT_H
#define _DOCUMENT_H

//Library includes
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <dirent.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>
#include <ctype.h>

#include "dictionary.h"
#include "frequency.h"

// the various characters to split the text by
#define DELIMITER "            À½¹£.,:;'\"”“’‘+-_(){}[]<>*&^%$#@!?~/|\\=\a\b\f\v\'\?\t\r\n1234567890\0 "
#define STOPWORDFILE "StopWords.txt"               //hardcoded file name
#define WORDLENGTH  50
#define MAXDOCS 10	// the number of documents to be used

/** Document ADT
 * -will be used as an array of structures
 *
 * @ FILE *fp: file pointer for each file. i.e. so you can hold open several files at a time
 *
 * @ char *text: memory is allocated to allow text to hold the text documents
 * @      *name: memory is allocated to allow name to hold the name of the text document
 *
 * @ long int size: used to save the TOTAL size of each document
 */

// ---------------------------
// Definition of a Document
// ---------------------------
typedef struct DOCUMENTADT {
	char* text; //retains the documents text
	char* name; //retains the name of the document
} DocumentT;

/** Stop Word ADT
 * - will be a structure that retains the stopword list and its size.
 *
 *  @char** text will be the list.
 *     - "An array of arrays of characters." = Array of strings.
 *
 *  @ unsigned short size; small variable to hold the integer value of the size
 *     - Number of words in the list.
 *
 */

// ---------------------------
// Definition of a StopwordList
// ---------------------------
typedef struct STOPWORDADT {
	char** text; //retains the words in the StopWord.txt file
	unsigned short size; //retains the size of the StopWord.txt file
} StopWordListT;

/**
 * Function saves an entire document of text into a single string of memory.
 *   i.e. finds total size of a document in bytes, then allocates memory equal to
 *        the number of bytes to a text, that the document gets loaded into
 *
 * @param document the document array to be read in
 * @param dictionary the dictionary which will contain each of the words from the documents
 * @param frequency the frequency which will contain each of the words from the documents
 * @param stopList the stopword list which will filter out some of the words from the documents
 */
void toString(DocumentT** document, DictionaryT* dictionary,
		FrequencyT* frequency, StopWordListT* stopList);

/**
 * Function tokenizes a string, or splits it based on a set of delimiters
 *
 * @param document the document array to be read in
 * @param dictionary the dictionary which will contain each of the words from the documents
 * @param frequency the frequency which will contain each of the words from the documents
 * @param stopList the stopword list which will filter out some of the words from the documents
 */
void tokenize(DocumentT** document, DictionaryT* dictionary, FrequencyT* frequency,
		StopWordListT* stopList);

/** -checkWord function-
 * @ params: Document document, DictionaryT dictionary, unsigned short filecount, size_t i
 *
 *
 * Function checks to see if any word being tokenized is in the stopword list text file
 *  then if it is, skips over it and contiunes the checks and then sends them to the
 *  dictionary if they are not within the stop word list
 *
 */

/**
 * Function checks to see if any word being tokenized is in the stopword list text file
 *  then if it is, skips over it and contiunes the checks and then sends them to the
 *  dictionary if they are not within the stop word list
 *
 *  @param tok the word which has been tokenized from a document
 *  @param stopList the list of stop words to compare the given word tok to
 *  @return result whether or not the word is in the list or not. Returns 0 if it contains the word or 1 otherwise
 */
int checkWord(char* tok, StopWordListT* stopList);

/**
 * Function opens a hardcoded file name that contains stop words
 * then reads them into a double char pointer to be manipulated into an array
 *
 * @param newList the list of stop words container
 */
void getStopWords(StopWordListT* newList);

/**
 * Function takes in a struc type pointer, see above param
 * Then locates the file and retrieves the list
 *
 * @param newList the new stopword list to be created
 */
void createStopList(StopWordListT* newList);


/** -showUsage function-
 *
 * Function just displays the arguments in order to input at command line
 *  run the program when -h or -help is a command line argument
 *
 */
void showUsage(void);

/**
 * Function frees and clears the document structure created,
 *  per each document processes.
 *
 *  @param document the array of documents to be deleted
 */
void docdelete(DocumentT** document);

/** -freeList function-
 *
 *
 * Function frees the stop word list, stopList; of type StopWordListT
 *
 */

/**
 * Prints out the incidence matrix compare the different documents to each other
 *
 * @param frequency the frequency structure which contains all of the words and their weights for each document
 */
void sim(FrequencyT* frequency);

/**
 * Function frees the stop word list, stopList; of type StopWordListT
 *
 * @param stopList the list of stop words to be deleted
 */
void freeList(StopWordListT* stopList);

#endif //_DOCUMENT_H
