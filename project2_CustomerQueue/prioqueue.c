/*
 * prioqueue.c
 *
 *  Created on: Feb 13, 2017
 *      Author: gbdan
 *
 *  priqueue.c: source code for the event queue. A priority queue with a min heap property
 *  used to sort and manage highest priority events being processed. Containts functions
 *  used to create and utilize a priorioty queue.
 */

//Corresponding Headers
#include "prioqueue.h"

#include <stdio.h>

//pqCreate; initializes pq priority queue
PrioQueueT* pqCreate(int capacity) {

	PrioQueueT* temp = (PrioQueueT*) malloc(sizeof(PrioQueueT));
	temp->event = (CustomerT**) malloc(sizeof(CustomerT) * capacity); //Is of type PrioQueueT with an element of type CustomerT** which holds the events

	temp->capacity = capacity;
	temp->size = 0;

	return temp;
}

//pqSetCapacity; updates the capacity of the priority queue when more memory is needed
void pqSetCapacity(PrioQueueT* pq) {

	// check for invalid parameter
	if (pq == NULL)
		return; // unable to perform operation

	pq->capacity *= 2;

	// create pq new list with the new capacity
	CustomerT** newList = malloc(sizeof(CustomerT*) * pq->capacity);

	int i;
	for (i = 0; i < pq->size; i++)
		newList[i] = pq->event[i];

	// free old vector
	free(pq->event);

	// set vector's list to new list
	pq->event = newList;
}

//pqEnQueue; Enqueues pq node into the priority queue
void pqEnQueue(PrioQueueT* pq, CustomerT* newCustomer) {

	if (pq->size == pq->capacity) {
		pqSetCapacity(pq);
	}

	if (isArrival(newCustomer) == true) {
		newCustomer->priority = newCustomer->arvTime;
	} else {
		newCustomer->priority = newCustomer->dprtTime;
	}

	pq->event[pq->size] = newCustomer;

	pq->size++;

	percolateUp(pq);

}

//pqDeQueue; Dequeues pq node from the priority queue #first node
CustomerT* pqDeQueue(PrioQueueT* pq) {

	CustomerT* item;

	if (pqIsEmpty(pq) == true) {
		printf("Queue Underflow\n");
		exit(1);
	}

	item = pq->event[0];

	swap(pq, 0, pq->size - 1);

	pq->size--;

	percolateDown(pq, 0);

	return item;
} /* END */

//percolateUp; shifts a node upward through the priority queue to invoke a heap property
void percolateUp(PrioQueueT* pq) {

	int index = pq->size - 1;
	int parent = (index - 1) / 2;

	while (index > 0 && pq->event[parent]->priority > pq->event[index]->priority) {
			swap(pq, parent, index);
			index = parent;
			parent = (index - 1) / 2;
	}
}

//percolateDown; shifts a node downward through the priority to invoke a heap property
void percolateDown(PrioQueueT* pq, int i) {

	// Root denotes the top of the subtree at the current level you are at which is based on i
	// swapIndex is which event below you should swap with
	int root, swapIndex;
	root = i;

	// Find the left child of the current level root node you are at
	int leftChild = (2 * i) + 1;

	// Checks to see if you are at the end of the heap
	if (leftChild > pq->size - 1)
		return; // heap established

	swapIndex = root;

	// check left leftChild
	if (pq->event[root]->priority > pq->event[leftChild]->priority)
		swapIndex = leftChild;

	// check right child if existing
	if ((leftChild + 1 <= pq->size - 1)
			&& (pq->event[swapIndex]->priority
					> pq->event[leftChild + 1]->priority))
		swapIndex = leftChild + 1;

	// swap if index was changed
	if (swapIndex != root) {
		swap(pq, root, swapIndex);
		percolateDown(pq, swapIndex);
	}

}

//swap; swaps two nodes in the priority queue
void swap(PrioQueueT* pq, int parent, int index) {

	CustomerT* tmp = pq->event[parent];
	pq->event[parent] = pq->event[index];
	pq->event[index] = tmp;

}

//pqIsEmpty; checks to see if the priority queue is empty
bool pqIsEmpty(PrioQueueT* pq) {

	if (pq->size == 0)
		return true;
	else
		return false;

}

//pqShow; displays the information of the priority queue
void pqShow(PrioQueueT* pq) {

	size_t i;
	for (i = 0; i < pq->size; i++)
		printf(
				"Index %zu     Prio: %f   Arrv: %f    Departe: %f    yes/no: %d\n",
				i, pq->event[i]->priority, pq->event[i]->arvTime,
				pq->event[i]->dprtTime, pq->event[i]->arriving);

}

void pqClear(PrioQueueT* pq) {

	size_t i;
	for (i = 0; i < pq->size; i++)
		free(pq->event[i]);

}

//pqDelete; frees the memory for the priority queue
void pqDelete(PrioQueueT* pq) {

	// free the event' list
	pqClear(pq);
	free(pq->event);

	// free memory of vector
	free(pq);

	printf("\nDeleted the priority queue\n");
}

//isArrival; function returns a true if the customer is arriving or false if the customer is departing
bool isArrival(CustomerT* event) {

	if (event->arriving == true)
		return true;

	return false;

} /* END */
