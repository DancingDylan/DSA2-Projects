/*
 * fifoqueue.c
 *
 *  Created on: Feb 13, 2017
 *      Author: gbdan
 *
 *  fifoqueue.c: source code for the first in first out queue. Used to simulate
 *  a wait line in the system.
 *
 *  Implemented with a basic linked list structure
 */

//Corresponding Header
#include "fifoqueue.h"

//Standard Includes
#include "stdio.h"
#include "stdlib.h"

// typedef of struct type
typedef FifoQueueT* NodePtr;

//two global pointers to hold fifoFront and rear
NodePtr fifoFront = NULL, rear = NULL;

//fiEnQueue; adds a node to the queue
void fiEnQueue(CustomerT* newCustomer) {

	NodePtr fq = (FifoQueueT*) malloc(sizeof(FifoQueueT));
	if(!fq) {
		printf("Failed to allocate memory.\n");
		return;
	}

	fq->event = newCustomer;
	fq->next = NULL;

	if (fifoFront == NULL && rear == NULL) {
		fifoFront = rear = fq;
		return;
	} else {
	rear->next = fq;
	rear = fq;
	rear->next = NULL;
	}

} /* END */

//fiDeQueue; removes a node from the queue
CustomerT* fiDeQueue() {

	if (fifoFront == NULL) {
		return NULL;
	}

	CustomerT* item = fifoFront->event;

	if (fifoFront == rear) {
		fifoFront = rear = NULL;
	} else {
		fifoFront = fifoFront->next;
	}

	return item;

} /* END */

//peek; checks the data in fifoFront
CustomerT* peek() {

	if (!fifoFront) {
		return NULL;
	}
	return fifoFront->event;
} /* END */

//display; prints the queue
void display() {

	NodePtr fq = fifoFront;

	while (fq != NULL) {
		printf("Priority: %f  Arrivng: %f   Departing: %f   ye/no:    %hu\n",
				fq->event->priority, fq->event->arvTime, fq->event->dprtTime,
				fq->event->arriving);
		fq = fq->next;
	}
	printf("\n");
} /* END */

//freeFifo; frees the nodes until the queue is empty.
void freeFifo() {

	while (fifoFront) {
		fiDeQueue();
	}

	free(fifoFront);
	free(rear);

	if (!fifoFront && !rear) {
		printf("Queue has been freed\n");
	}
} /* END */
