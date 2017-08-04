/*
 * prioqueue.h
 *
 *  Created on: Feb 13, 2017
 *      Author: gbdan
 */

#ifndef PRIOQUEUE_H_
#define PRIOQUEUE_H_

//Corresponding Headers
#include "customer.h"

//Forward declaration of CalcT
struct CustomerADT;
typedef struct CustomerADT CustomerT;

/** PrioQueueADT structure
 *
 *  Structure to hold the priority queues information
 *
 * @params:
 * unsigned short capacity: total capacity of the priority queue
 * unsigned short size: total number of nodes in the priority queue
 */
typedef struct PrioQueueADT {

	CustomerT** event; // Might be better to abstract all the data into a customer ADT like what he has in the pseudo code

	unsigned short capacity;
	unsigned short size;

} PrioQueueT; //typedef of PrioQueueADT, promotes ease of use when declaring new variables

/** pqCreate function
 *
 * Function takes in a capacity that will initialize and create the init priority
 * queue used to hold arrival and departure events
 *
 * @params:
 * int capacity: the initial capacity of the prio queue
 */
PrioQueueT* pqCreate(int capacity);

/* pqSetCapacity function
 *
 * Function takes in a PrioQueueT* type struct variable that is the priority queue used in the simulation
 * Then, it creates with a new priority queue with double the original size and then returns that new priority queue
 *
 * @params:
 * PrioQueueT* pq: struct var pq of type PrioQueueT*, priority queue in which the capacity is being doubled
 *
 * @returns: new priority queue with the updated capacity.
 */
PrioQueueT* pqSetCapcity(PrioQueueT* pq);

/* pqEnQueue function
 *
 * Function takes in a new customer event and the priority queue,
 * then adds the new event to the queue and heapifies the queue giving
 * it a min heap property
 *
 * @params:
 * PrioQueueT* pq:  struct var pq of type PrioQueueT*, priority queue that is being added to
 * CustomerT* event: struct var event of type CustomerT*, the new event being added to the priority queue
 */
void pqEnQueue(PrioQueueT* pq, CustomerT* event);

/* pqDeQueue function
 *
 * Function takes in a PrioQueueT* type structure variable pq that is the priority queue
 * Then it removes the very first node in the queue, which will have the highest priority
 * or the lowest priority time
 *
 * @params:
 * PrioQueueT* pq:  struct var pq of type PrioQueueT*, priority queue that is being removed from
 *
 * @returns: the customers event
 */
CustomerT* pqDeQueue(PrioQueueT* pq);

/* percolateUp function
 *
 * Function maintains the heap property of the data structure by moving up higher
 * priority events that are just added until their rightful place
 *
 * @params:
 * PrioQueueT* pq: the priority queue to be modified to maintain its heap property
 */
void percolateUp(PrioQueueT* pq);

/* percolateDown function
 *
 * Function maintains heap property after a removal by moving down lower priority events
 * to their rightful place
 *
 * @params:
 * PrioQueueT* pq: the priority queue to be modified to maintain its heap property
 * int i: the place in the heap to be shifted down
 */
void percolateDown(PrioQueueT* pq, int i);

/* percolate function
 *
 * Function percolates a node through the priority queue used to retain min heap property
 * Then it locates and returns the greatest in value node.
 *
 * @params:
 * PrioQueueT* pq: struct var pq of type PrioQueueT*, priority queue percolating through
 * int n: the actual size of the priority queue #pq->size
 * int i: the swap index used when retaining min heap property
 *
 * @returns: the largest valued node
 */
int percolate(PrioQueueT* pq, int n, int i);

/* heapify function
 *
 * Function takes in a PrioQueueT* type struct variable that is the priority queue used to heapify
 * or create the min heap property.
 *
 * @params:
 * PrioQueueT* pq: priority queue being heapified
 * int n: the total size of the priority queue #pq->size
 * int i: the actual swap index used when swapping nodes
 */
void heapify(PrioQueueT* pq, int n, int i);

/* heapSort function
 *
 * Function takes in a priority queue and sorts it using heap sort
 * and retaining a min heap property.
 *
 * @params:
 * PrioQueueT* pq: priority queue being sorted and prioritized with min heap property
 */
void heapSort(PrioQueueT* pq);

/* swap function
 *
 * Function swaps two nodes with one another.
 *
 * @params:
 * PrioQueueT* pq: the priority queue in which nodes are being swapped
 * int parent: the parent index being swapped
 * int index: the child inde being swapped
 */
void swap(PrioQueueT*, int parent, int swapIndex);

/* pqIsEmpty function
 *
 * Function takes in a priority queue to check if it is empty.
 *
 * @params:
 * PrioQueueT* pq: priority queue to check if empty
 *
 * @returns: true if empty or false if not empty
 */
bool pqIsEmpty(PrioQueueT* pq);

/* pqShow function
 *
 * Function displays the priority queue.
 *
 * @params:
 * PrioQueueT* pq: struct var pq of type PrioQueueT*, the priority queue being displayed
 */
void pqShow(PrioQueueT* pq);

/*pqClear function
 *
 * Function frees all of the entries of events in the event priority queue from memory
 *
 * @params:
 * PrioQueueT* pq: The priority queue containing the event queue events to be freed
 */
void pqClear(PrioQueueT* pq);

/* pqDelete function
 *
 * Function frees and clears all the priority queue nodes.
 *
 * @params:
 * PrioQueueT* pq: the priority queue being freed
 */
void pqDelete(PrioQueueT* pq);

/* isArrival function
 *
 * Function takes in an event and check whether it is an arrival
 * or a departure.
 *
 * @params:
 * CustomerT* event: event checked whether it is an arrival or a departure
 *
 * @returns: true if an arrival or false if a departure
 */
bool isArrival(CustomerT* event);

#endif /* PRIOQUEUE_H_ */
