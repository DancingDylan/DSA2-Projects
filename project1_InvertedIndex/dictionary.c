/**
 * This file handles all of the logic for all of the operations
 * you would use in a dictionary ADT
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dictionary.h"

DictionaryT* newDictionary(int capacity)
{

	// Create the new dictionary and initialize all of it's fields
	DictionaryT* dictionary = malloc(sizeof(DictionaryT));
	dictionary->size = 0;
    dictionary->counter = 0;
	dictionary->wordList = (WordNode **) malloc (sizeof(WordNode*) * capacity);
	dictionary->capacity = capacity;

	return dictionary;

}

void setCapacity (DictionaryT* dictionary, int newCapacity)
{
	// check for invalid parameter
	if (dictionary == NULL)
		return; // unable to perform operation

	// create a new list with the new capacity
	WordNode **newList = (WordNode **) malloc (sizeof(WordNode*) * newCapacity);

	int i;
	for (i=0; i < dictionary->size; i++)
		newList[i] = dictionary->wordList[i];

	// free old vector
	free (dictionary->wordList);

	// update vector's new capacity
	dictionary->capacity = newCapacity;

	// set vector's list to new list
	dictionary->wordList = newList;
}

void dicadd(DictionaryT* dictionary, Word word, int id)
{

	// check for invalid parameter
	if (dictionary == NULL)
		return; // unable to perform operation

	// if the frequency is full add space to the frequency structure
	if (dictionary->size == dictionary->capacity)
		setCapacity (dictionary, dictionary->capacity * GROWTH_RATE);

	// if the dictionary is empty just add the first word
	if (dictionary->size == 0)
	{

		dictionary->wordList[dictionary->size] = newWord(word, id);
		dictionary->size++;

		return;

	}

	// add new node to list if it is not already in the dictionary else just update the occurrences in the particular document
	int index = dicsearch(dictionary, word);
	if (index == dictionary->size || strcmp(dictionary->wordList[index]->word, word) != 0)
	{

		int i;
		for (i = dictionary->size; i > index; i--)
			dictionary->wordList[i] = dictionary->wordList[i - 1];

		dictionary->wordList[index] = newWord(word, id);
		addID(dictionary->wordList[index], id);
		dictionary->size++;

	}
	else
		addID(dictionary->wordList[index], id);

}

int dicsearch(DictionaryT* dictionary, Word word)
{

	// Implements a binary search to find a word in the dictionary
	int upper = dictionary->size - 1;
	int lower = 0;
	int midpoint = 0;

	while(upper >= lower)
	{

		midpoint = (lower + upper) / 2;

		if (strcmp(dictionary->wordList[midpoint]->word, word) > 0)
		{
			upper = midpoint - 1;
		}
		else if (strcmp(dictionary->wordList[midpoint]->word, word) < 0)
		{
			lower = midpoint + 1;
		}
		else return midpoint;

	}


	if (strcmp(dictionary->wordList[midpoint]->word, word) < 0)
		midpoint++;

	return midpoint;

}

void dicshow(DictionaryT* dictionary) {

	// Display all of the words and the documents that contain the words in a nice format
	size_t i, j;
	for (i = 0; i < dictionary->size; i++) {
		printf("%s: ", dictionary->wordList[i]->word);
		for (j = 0; j < NUM_OF_DOCUMENTS; j++)
			if (dictionary->wordList[i]->id[j] > 0)
				printf("%2zu,  ", j + 1);

		printf("\n");
	}

}

void dicclear(DictionaryT* dictionary)
{
	size_t i;

	// traverse the list of pointers and free them
	for (i=0; i < dictionary->size; i++)
		worddelete(dictionary->wordList[i]);

	// free the dictionary's list
	free (dictionary->wordList);
}

void dicdelete(DictionaryT* dictionary)
{
	// clear the list
	dicclear (dictionary);

	// free memory of vector
	free (dictionary);

	printf("Deleted the dictionary\n");
}
