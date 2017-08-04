/**
 * Contains all of the function logic for all of the operations
 * to be performed on the freword ADT
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#include "freqword.h"
#include <malloc.h>
#include <string.h>
#include <stdio.h>

FreqWordNode* newFreqWord(Word word, int id) {

	// Create a new freqword node and initializes all of it's fields
	FreqWordNode* node = malloc(sizeof(FreqWordNode));
	node->word = word;
	node->totDocOccurence = 0;

	int i;
	for (i = 0; i < NUM_OF_DOCUMENTS; i++)
	{
		node->id[i] = 0;
		node->weight[i] = 0;
	}

	freqaddID(node, id);

	return node;

}

void freqaddID(FreqWordNode* node, int id)
{

	// Update the amount of total document occurrences of a particular word
	if (node->id[id] == 0) {
		node->totDocOccurence++;
	}

	// Update the frequency of a particular word in a certain document
	node->id[id]++;

}

void freqworddelete(FreqWordNode* node)
{

	free(node);

}
