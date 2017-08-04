/**
 * Contains all of the function logic for all of the operations
 * to be performed on the Frequency ADT
 *
 * @author Dylan Hall and Nathan Cooper
 * @date 1/22/2017
 * @info Course COP4534
 */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <math.h>
#include "frequency.h"

FrequencyT* newFrequency(int capacity) {

	// Create the new frequency and initialize all of it's fields
	FrequencyT* frequency = malloc(sizeof(FrequencyT));
	frequency->size = 0;

	frequency->freqList = (FreqWordNode **) malloc(sizeof(FreqWordNode*) * capacity);
	frequency->capacity = capacity;

	return frequency;

}

void setCapacityFreqT(FrequencyT* frequency, int newCapacity)
{

	// check for invalid parameter
	if (frequency == NULL)
		return; // unable to perform operation

	// create a new list with the new capacity
	FreqWordNode **newList = (FreqWordNode **) malloc(sizeof(FreqWordNode*) * newCapacity);

	int i;
	for (i = 0; i < frequency->size; i++)
		newList[i] = frequency->freqList[i];

	// free old vector
	free(frequency->freqList);

	// update vector's new capacity
	frequency->capacity = newCapacity;

	// set vector's list to new list
	frequency->freqList = newList;

}

void freqAdd(FrequencyT* frequency, Word word, int id) {

	// check for invalid parameter
	if (frequency == NULL)
		return; // unable to perform operation

	// if the frequency is full add space to the frequency structure
	if (frequency->size == frequency->capacity)
		setCapacityFreqT(frequency, frequency->capacity * GROWTH_RATE);

	// if the frequency is empty just add the first word
	if (frequency->size == 0) {

		frequency->freqList[frequency->size] = newFreqWord(word, id);
		frequency->size++;

		return;

	}

	// add new node to list if it is not already in the frequency else just update the occurrences in the particular document
	int index = freqSearch(frequency, word);
	if (index == frequency->size
			|| strcmp(frequency->freqList[index]->word, word) != 0) {

		int i;
		for (i = frequency->size; i > index; i--)
			frequency->freqList[i] = frequency->freqList[i - 1];

		frequency->freqList[index] = newFreqWord(word, id);

		freqaddID(frequency->freqList[index], id);
		frequency->size++;

	} else
		freqaddID(frequency->freqList[index], id);

}

void freqCalculateWeight(FrequencyT* frequency)
{

	// Calculates each of the words weights in the various documents
	int i, j;
	for (i = 0; i < NUM_OF_DOCUMENTS; i++)
	{

		double max_weight = 0;
		for (j = 0; j < frequency->size; j++)
		{

			if (frequency->freqList[j]->id[i] != 0)
			{

				double log_amount = log((double) NUM_OF_DOCUMENTS / frequency->freqList[j]->totDocOccurence);
				frequency->freqList[j]->weight[i] = frequency->freqList[j]->id[i]*log_amount;
				if (frequency->freqList[j]->weight[i] > max_weight)
					max_weight = frequency->freqList[j]->weight[i];

			} else frequency->freqList[j]->weight[i] = 0;

		}

		for (j = 0; j < frequency->size; j++)
		{

			if (frequency->freqList[j]->id[i] != 0)
			{
				frequency->freqList[j]->weight[i] = frequency->freqList[j]->weight[i] / max_weight;
			}

		}

	}

}

void docusim(FrequencyT* frequency)
{

	// Prints out the document similarity incidents matrix
	printf("\td1\td2\td3\td4\td5\td6\td7\td8\td9\td10\n");
	int i, j, k;
	for (i = 0; i < NUM_OF_DOCUMENTS; i++)
	{

		printf("d%d\t", i + 1);
		for (j = 0; j < NUM_OF_DOCUMENTS; j++)
		{

			double sim = 0;
			double numerator = 0;
			double denominator = 0;
			double denominator1 = 0;
			double denominator2 = 0;
			for (k = 0; k < frequency->size; k++)
			{

				numerator += (frequency->freqList[k]->weight[i] * frequency->freqList[k]->weight[j]);
				denominator1 += pow(frequency->freqList[k]->weight[i], 2);
				denominator2 += pow(frequency->freqList[k]->weight[j], 2);

			}

			denominator = sqrt(denominator1)*sqrt(denominator2);
			if (denominator != 0)
				sim = numerator / denominator;

			printf("%0.3f\t", sim);

		}

		printf("\n");

	}

}

int freqSearch(FrequencyT* frequency, Word word) {

	// Implements a binary search to find a word in the frequency structure
	int upper = frequency->size - 1;
	int lower = 0;
	int midpoint = 0;

	while (upper >= lower) {

		midpoint = (lower + upper) / 2;

		if (strcmp(frequency->freqList[midpoint]->word, word) > 0) {
			upper = midpoint - 1;
		} else if (strcmp(frequency->freqList[midpoint]->word, word) < 0) {
			lower = midpoint + 1;
		} else
			return midpoint;

	}

	if (strcmp(frequency->freqList[midpoint]->word, word) < 0)
		midpoint++;

	return midpoint;

}

void freqShow(FrequencyT* frequency) {

	// Display all of the words, weights, occurences, and the documents that contain the words in a nice format
	size_t i, j;
	for (i = 0; i < frequency->size; i++) {
		printf("word: %-20s\tOccurences:\tWeights\n", frequency->freqList[i]->word);
		for (j = 0; j < NUM_OF_DOCUMENTS; j++)
			if (frequency->freqList[i]->id[j] > 0)
				printf("Document: %-20zu\t%d\t\t%0.3f\n", j + 1, frequency->freqList[i]->id[j], frequency->freqList[i]->weight[j]);

		printf("\n");
	}

}

void freqClear(FrequencyT* frequency) {
	size_t i;

	// traverse the list of pointers and free them
	for (i = 0; i < frequency->size; i++)
		freqworddelete(frequency->freqList[i]);

}

void freqDelete(FrequencyT* frequency) {
	// clear the list
	freqClear(frequency);

	// free vector's list
	free(frequency->freqList);

	// free memory of vector
	free(frequency);

	printf("Deleted the frequency\n");
}
