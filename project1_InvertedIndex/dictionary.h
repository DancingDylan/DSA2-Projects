/**
 * This file contains the structure for the dictionary ADT
 * as well as all of the function signatures for all the
 * dictionary operations
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#ifndef DICTIONARY_H_
#define DICTIONARY_H_

#include "word.h"

// ---------------------------
// Definition of a Dictionary
// ---------------------------
typedef struct DictionaryT {

	WordNode** wordList;	// The list of word structures
	int size;	// The number of elements in the dictionary
	int capacity;	// The maximum size allotted to the dictionary
	int counter;

} DictionaryT;

#define GROWTH_RATE 2	// The factor that the capacity of the dictionary grows by

// ----------------------
// Interface to the Dictionary ADT
// ----------------------

/**
 * Creates a new dictionary with an initial capacity
 *
 * @param capacity the initial capacity of the dictionary
 *
 * @return dictionary the newly created dictionary
 */
DictionaryT* newDictionary(int capacity);

/**
 * Creates a new dictionary of size newCapacity and copies all of the elements
 * from the old dictionary to the new one and reassigns the dictionary pointer
 * to the newly allocated dictionary with the new capacity
 *
 * @param dictionary the old dictionary which has reached its capacity
 * @param newCapacity the new maximum amount of elements the new dictionary can have
 */
void setCapacity(DictionaryT* dictionary, int newCapacity);

/**
 * Inserts the new word with the id of the document containing the word
 * to the existing dictionary while maintaining the sorted order
 *
 * @param dictionary the dictionary which will have the word and id added to it
 * @param word the new word to be inserted into the dictionary
 * @param id the id which corresponds to the document which contains the word
 */
void dicadd(DictionaryT* dictionary, Word word, int id);

/**
 * Searches through the sorted dictionary for a specific word
 * using a binary search. Returns either the index of the word
 * in the dictionary if the word in the dictionary exists or the insertion
 * point for the word if it does not
 *
 * @param dictionary the sorted dictionary to be searched
 * @param word the word to be searched for in the sorted dictionary
 */
int dicsearch(DictionaryT* dictionary, Word word);

/**
 * Displays each of the words in the dictionary along with their corresponding documents in which they appear
 *
 * @param dictionary the dictionary to be displayed
 */
void dicshow(DictionaryT* dictionary);

/**
 * Removes from memory the list of words
 *
 * @param dictionary the dictionary to free the list of words from
 */
void dicclear(DictionaryT* dictionary);

/**
 * Removes from memory the dictionary
 *
 * @param dictionary the dictionary to be freed from memory
 */
void dicdelete(DictionaryT* dictionary);

#endif /* DICTIONARY_H_ */
