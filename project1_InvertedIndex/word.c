/**
 * Contains all of the function logic for all of the operations
 * to be performed on the word ADT
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#include "word.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

WordNode* newWord(Word word, int id) {

	// Create a new word node and initializes all of it's fields
	WordNode* node = malloc(sizeof(WordNode));
	node->word = word;

	int i;
	for (i = 0; i < NUM_OF_DOCUMENTS; i++)
		node->id[i] = 0;

	addID(node, id);

	return node;

}

void addID(WordNode* node, int id) {

	// Update the particular document id that the word occurred in
	if (node->id[id] == 0) {
		node->id[id]++;
	}

}

void worddelete(WordNode* node)
{

	free(node);

}
