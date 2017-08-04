/**
 * This file contains the structure for the frequency ADT
 * as well as all of the function signatures for all the
 * frequency operations
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#ifndef FREQUENCY_H_
#define FREQUENCY_H_

#include "freqword.h"

// ---------------------------
// Definition of a Frequency
// ---------------------------
typedef struct FrequencyT {

	FreqWordNode** freqList;	// The list of word structures

	float** weight;

	int size;	// The number of elements in the frequency
	int capacity;	// The maximum size allotted to the frequency
	int counter;

} FrequencyT;

#define GROWTH_RATE 2	// The factor that the capacity of the frequency grows by

// ----------------------
// Interface to the Frequency ADT
// ----------------------

/**
 * Creates a new frequency with an initial capacity
 *
 * @param capacity the initial capacity of the frequency
 *
 * @return frequency the newly created frequency
 */
FrequencyT* newFrequency(int capacity);

/**
 * Creates a new frequency of size newCapacity and copies all of the elements
 * from the old frequency to the new one and reassigns the frequency pointer
 * to the newly allocated frequency with the new capacity
 *
 * @param frequency the old frequency which has reached its capacity
 * @param newCapacity the new maximum amount of elements the new frequency can have
 */
void setCapacityFreqT(FrequencyT* frequency, int newCapacity);

/**
 * Inserts the new word with the id of the document containing the word
 * to the existing frequency while maintaining the sorted order
 *
 * @param frequency the frequency which will have the word and id added to it
 * @param word the new word to be inserted into the frequency
 * @param id the id which corresponds to the document which contains the word
 */
void freqAdd(FrequencyT* frequency, Word word, int id);

/**
 * Calculates each of the weights for each of the words for all of the documents and stores
 * them in the frequency ADT
 *
 * @param frequency the frequency containing all of the words to be calculated
 */
void freqCalculateWeight(FrequencyT* frequency);

/**
 * Displays the incidents matrix of the various documents
 *
 * @param frequency the frequency structure which contains all of the words and their weights
 */
void docusim(FrequencyT* frequency);

/**
 * Searches through the sorted frequency for a specific word
 * using a binary search. Returns either the index of the word
 * in the frequency if the frequency exists or the insertion
 * point for the word if it does not
 *
 * @param frequency the sorted frequency to be searched
 * @param word the word to be searched for in the sorted frequency
 */
int freqSearch(FrequencyT* frequency, Word word);

/**
 * Displays each of the words in the frequency along with their corresponding documents in which they appear
 *
 * @param frequency the frequency to be displayed
 */
void freqShow(FrequencyT* frequency);

/**
 * Removes from memory the list of words
 *
 * @param frequency the frequency to free the list of words from
 */
void freqClear(FrequencyT* frequency);

/**
 * Removes from memory the frequency
 *
 * @param frequency the frequency to be freed from memory
 */
void freqDelete(FrequencyT* frequency);

#endif /* FREQUENCY_H_ */
