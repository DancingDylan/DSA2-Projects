/*
 * customer.h
 *
 *  Created on: Feb 14, 2017
 *      Author: natha
 */

#ifndef CUSTOMER_H_
#define CUSTOMER_H_

//Defining boolean
typedef int bool;
enum { false, true };

//Corresponding Headers
#include "server.h"
#include "prioqueue.h"
#include "fifoqueue.h"
#include "calculations.h"

//Standard Includes
#include <stdio.h>

//Forward declaration of PrioQueueT
struct PrioQueueADT;
typedef struct PrioQueueADT PrioQueueT;

/** CustomerT structure
 *
 *  Structure to hold the customer information
 *
 * double arvTime: event time of arrival
 * double servTime: the time a event service takes
 * double dprtTime: event time of departure; arricalTime + servTime
 */
typedef struct CustomerADT {

	double arvTime;
	double servTime;
	double dprtTime;
	double priority;

	unsigned short arriving;

} CustomerT;

/** newCustomer function
 *
 * Function creates and allocates memory for a new customer to be processed
 * and added go the priority queue
 *
 * @params:
 * CustomerT* event: struct var event of type CustomerT*, the new event
 * ServerT* server: struct var server of type ServerT*, holds the init server stats
 */
CustomerT* newCustomer(ServerT* server);

/** processEvent function
 *
 * Function processes arrivals and departures of event in the simulation
 *
 * @params:
 * ServerT* server; struct var server of type ServerT*, holds the server stats
 * PrioQueueT* pq; struct var pq of type PrioQueueT*, holds the priority queue with the events
 * CustomerT* customer; struct var customer of type CustomerT*, holds individual customer data
 * bool debug: used to test the output to help for debugging
 */
void processEvent(PrioQueueT* pq, ServerT* server);

#endif /* CUSTOMER_H_ */
