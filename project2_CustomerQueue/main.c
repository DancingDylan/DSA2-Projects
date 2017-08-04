/*
 * main.c
 *
 *  Created on: Feb 13, 2017
 *      Author: dylan, nathan
 *
 *  main.c: source code for the tester code for the simulation. This code runs
 *  the entire simulation and puts the code together.
 *
 *  This code is based off of Queue Theory written in C.
 *  This projects a systems activated and usage based on number of events
 *  within a time interval. It creates a theoretical model based off initial
 *  server stats and then processes customer events for the requests amount.
 *  Then produces a simulation model of the calculations that the user can
 *  compare with the theoretical model to check for accuracy.
 */

//Corresponding Headers
#include "calculations.h"
#include "fifoqueue.h"
#include "server.h"
#include "customer.h"
#include "prioqueue.h"

//Standard Includes
#include <string.h>

//main; runs the simulation
int main(int argc, char **argv) {

	ServerT* server = (ServerT*) malloc(sizeof(ServerT)); //ServerT* variable that holds init server stats
	CalcT* calcs = (CalcT*) malloc(sizeof(CalcT)); //CalcT* variable that holds theoretical calculations

	getServerInfo(server); //init server stats

	PrioQueueT* pq = pqCreate(server->numArrivals); //PrioQueueT* variable used to hold the priority queue
	CustomerT** event = (CustomerT**) malloc(sizeof(CustomerT) * server->numArrivals); //event used to hold arrivals

	size_t j;
	srand(time(NULL));

	for (j = 0; j < server->avgArrivals; j++) {
		event[server->k] = newCustomer(server);
		pqEnQueue(pq, event[server->k]);
		server->k++;
	}

	while (pq->size != 0) { //while event queue isn't empty
		processEvent(pq, server); //process next event

		if (server->k < server->numArrivals && pq->size <= server->numChannels + 1) {
			for (j = 0; j < server->avgArrivals; j++) {

				if(server->k == server->numArrivals)
					break;

				event[server->k] = newCustomer(server);
				pqEnQueue(pq, event[server->k]);
				server->k++;
			}
		}
	}

	getServerCalculations(server, calcs);

	//Frees and clears malloc'd memory
	pqDelete(pq);
	for (j = 0; j < server->k; j++)
		free(event[j]);
	free(event);
	free(server);
	free(calcs);
	freeFifo();

	return 0;
} /* END */
