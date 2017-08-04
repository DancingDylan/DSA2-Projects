/*
 * server.h
 *
 *  Created on: Feb 13, 2017
 *      Author: gbdan
 */

#ifndef SERVER_H_
#define SERVER_H_

//Standard Includes
#include <stdlib.h>
#include <stdio.h>

//Forward declaration of CalcT
struct CalculationADT;
typedef struct CalculationADT CalcT;

/** ServerADT structure
 *
 * Structure to hold the user input, i.e. initial simulation stats
 * Will be used to perform several calculates based on the below values
 *
 * int numArrivals    ; //total number of clients to simulate
 * float avgArrivals  ; //average number of arrivals at a time
 * float avgServed    ; //average number served at a time
 * size_t numChannels ; //how many people can be served at a time
 * size_t k           ; //number of customers
 * float totArvIntrv  ; //total arrival interval of simulation
 * float totDptIntrv  ; //total arrival interval of simulation
 * float totInterval  ; //total runtime interval of simulation
 * float totWaitInFifo; //total wait for events in FIFO queue
 */
typedef struct ServerADT { //initial server tests
	int numArrivals;
	float avgArrivals;
	float avgServed;
	size_t numChannels;
	size_t k;
	int f;

	float totArvIntrv;
	float totDptIntrv;
	float totIdle;
	float totInterval;;
	float totWaitInFifo;
} ServerT;

/** getServerInfo function
 *
 * Function takes in a struct var of type ServerT*; holds user input
 * Then just prompts for user input for initial simulation stats
 */
void getServerInfo(ServerT* server);

/** getServerCalculations function
 *
 * Function takes in a struct var of type ServerT*; holds user input
 * and also takes in 7 pointers from main.c       ; used to hold calculations
 *
 * #might be removed later and just added to main, thought it was alot cleaner this way
 */
void getServerCalculations(ServerT* server, CalcT* calcs);


#endif /* SERVER_H_ */
