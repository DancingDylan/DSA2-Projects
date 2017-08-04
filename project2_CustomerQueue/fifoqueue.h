/*
 * fifoqueue.h
 *
 *  Created on: Feb 13, 2017
 *      Author: gbdan
 *
 *      Header file for the First in First out queue, using a Linked List
 */


#ifndef FIFOQUEUE_H_
#define FIFOQUEUE_H_


//Corresponding Headers
#include "customer.h"

//Standard Includes
#include "stdlib.h"

//Forward declaration of CalcT
struct CustomerADT;
typedef struct CustomerADT CustomerT;

/** FifoQueueADT structure
 *
 *  Structure to hold the customers that aren't being serviced
 *
 *  *next: used to create a linked list
 *   data: just holds an id for a customer. likely an index
 */
typedef struct FifoQueueADT { //first in first out.

	struct FifoQueueADT* next;
	CustomerT* event;

} FifoQueueT;

/** fiEnQueue function
 *
 * Function takes in a positive integer as data, and adds a node, with
 * the relative data and puts it into a FIFO Queue
 *
 * @params: unsigned int x; just a positive data element to be held within a given node
 */
void fiEnQueue(CustomerT* newCustomer);

/** fiDeQueue function
 *
 * Function dequeues, or removes the data and frees the node
 * at the prioFront of the Linked List (FIFO Queue)
 *
 * returns deQueued value
 */
CustomerT* fiDeQueue();

/** peek function
 *
 * Function returns the value at the fifoFront of the Queue.
 *
 * returns -1 if the Queue is empty, i.e. fifoFront == NULL
 * else
 * returns the nodes data at the fifoFront of the queue
 *
 */
CustomerT* peek();

/** display function
 *
 * Function displays the queue
 *
 */
void display();

/** freeFifo function
 *
 * Function dequeues each node until empty.
 * Then frees the allocated memory for fifoFront and rear global vars
 *
 */
void freeFifo();

#endif /* FIFOQUEUE_H_ */
