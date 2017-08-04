//Corresponding Headers
#include "customer.h"

//Standard Includes
#include <stdlib.h>

// typedef of struct type
typedef FifoQueueT* NodePtr;
NodePtr* fifoFront;

//newCustomer; creates and initializes new events to be added to the priority queue
CustomerT* newCustomer(ServerT* server) {

	CustomerT* temp = (CustomerT*) malloc(sizeof(CustomerT));

	temp->arvTime = getNextRandomIntreval(server->avgArrivals)
			+ server->totInterval;
	temp->servTime = getNextRandomIntreval(server->avgServed);
	temp->dprtTime = temp->arvTime + temp->servTime;
	temp->arriving = 1;

	server->totInterval = temp->arvTime;

	return temp;

} /* END */

//processEvent; processes arrivals and departures of event ****** under maintenance ******
void processEvent(PrioQueueT* pq, ServerT* server) {

	CustomerT* temp = pq->event[0];
	float placeHolder = 0;

	if (isArrival(temp) == true) { //if customer being processed is arriving
		if (server->numChannels == 0)
			server->totIdle += temp->arvTime - server->totInterval;
		server->totArvIntrv += temp->arvTime;
		server->totInterval = temp->arvTime;

		//processing arrival
		if (server->numChannels > 0) { //if service channels are open

			server->numChannels--; //customer pushed into open channel

			temp = pqDeQueue(pq); //remove this arrival event
			temp->arriving = 0;
			pqEnQueue(pq, temp); //add this departure event to priority queue

		} else {

			server->f++;
			temp = pqDeQueue(pq);
			temp->arriving = 0;
			fiEnQueue(temp); //add this event to FIFO queue
		}

	} else if (isArrival(temp) == false) { //else customer being processed is departing

		server->totDptIntrv += temp->dprtTime;
		server->totInterval = temp->dprtTime;

		server->numChannels++;
		temp = pqDeQueue(pq);
		placeHolder = temp->dprtTime;

		//processing departure
		if (fifoFront != NULL) { //if an event is in the FIFO queue

			server->numChannels--; //reduce number of channels

			temp = fiDeQueue();     //save the FIFO queue event, and remove it
			temp->dprtTime = placeHolder + temp->servTime; //determine the departure time of the event
			server->totWaitInFifo += temp->arvTime + placeHolder;
			temp->arriving = 0; //set event to departing

			pqEnQueue(pq, temp); //add this event departure event
		}

	}

	if (pqIsEmpty(pq) == true && !fifoFront) { //if all events processed
		printf("\nAll customers processed.\n");
	}
} /* END */
