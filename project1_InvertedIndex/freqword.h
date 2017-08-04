/**
 * This file contains the structure for the word ADT
 * as well as all of the function signatures for all the
 * freqword operations
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#ifndef FREQWORD_H_
#define FREQWORD_H_

typedef char* Word;

#define NUM_OF_DOCUMENTS 10 // the number of documents being used

// Definition of what a freqword is
typedef struct FreqWordNode
{

	Word word; // the word that represents this freqword node
	int id[NUM_OF_DOCUMENTS]; // the various documents the word may appear in
	double weight[NUM_OF_DOCUMENTS]; // the weight of this word in each of the documents
	int totDocOccurence; // the total number of documents this word occurs in

} FreqWordNode;

/**
 * Creates a new freqword node
 *
 * @param word the word to represent this freqword not
 * @param id the id that the word appeared in
 */
FreqWordNode* newFreqWord(Word word, int id);

/**
 * Increment the occurrences of a word in a particular document
 *
 * @param node the freqword node to be updated
 * @param id the id of the document to be increment the occurrences of a word
 */
void freqaddID(FreqWordNode* node, int id);

/**
 * Deletes the given freqword node
 *
 * @param node the freqword node to be deleted
 */
void freqworddelete(FreqWordNode* node);

#endif /* FREQWORD_H_ */
