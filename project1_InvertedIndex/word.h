/**
 * This file contains the structure for the word ADT
 * as well as all of the function signatures for all the
 * word operations
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#ifndef WORD_H_
#define WORD_H_

typedef char* Word;

#define NUM_OF_DOCUMENTS 10 // the number of documents being used

// Definition of what a freqword is
typedef struct WordNode
{

	Word word; // the word which represents the word node
	int id[NUM_OF_DOCUMENTS]; // the various documents the word may appear in

}WordNode;

/**
 * Creates a new word node
 *
 * @param word the word to represent this word not
 * @param id the id that the word appeared in
 */
WordNode* newWord(Word word, int id);

/**
 * Increment the occurrences of a word in a particular document
 *
 * @param node the word node to be updated
 * @param id the id of the document to be increment the occurrences of a word
 */
void addID(WordNode* node, int id);

/**
 * Deletes the given word node
 *
 * @param node the word node to be deleted
 */
void worddelete(WordNode* node);

#endif /* WORD_H_ */
