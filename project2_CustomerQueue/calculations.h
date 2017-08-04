/*
 * calculations.h
 *
 *  Created on: Feb 13, 2017
 *      Author: gbdan
 */

#ifndef CALCULATIONS_H_
#define CALCULATIONS_H_

//Corresponding Header
#include "server.h"

//Standard Includes
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

struct CalculationADT{

	float avgInSystem;
	float percentIdle;
	float f;
	float avgSystemTime;
	float avgCustInQueue;
	float avgWait;
	float utilFactor;
};


/** -getNextRandomIntreval function-
 *
 *  Function takes in a float as an average,
 *  then compute a random float on the interval 0 -> 1,
 *  when is then used to compute a random interval time
 *  based on the input average and the randomly generated float.
 *
 *  @params:
 *  float avg, variable input from user
 *
 *  @returns: a calculated interval time, either departure or arrival
 */
float getNextRandomIntreval(float avg);

/** -factorial function-
 *
 * Function takes in a number to compute the factorial for.
 *
 * @params: unsigned long f, value to take in and compute the factorial for
 *
 * returns the final computed factorial for f
 */
unsigned int factorial(unsigned int f);

/** percentIdleTime function-
 *
 * Function takes in a structure that holds the values for user input
 * Then computes the percent idle time, i.e. percent of time
 * that no one is in the system.
 *
 * @params: ServerT* server: struct var of type ServerT*; holds user input
 *
 * returns calculated percent the system is idle
 */
//float percentIdleTime(ServerT*);
double percentIdleTimeAnalytical(int, double, double);
/** avgNumInSystem function-
 *
 * Function takes in previously calculated percent idle time, and a server of type ServerT*
 * Then calculates the average number of clients that might be within the system,
 * based off the initial user input
 *
 * @params:ServerT* server: structure to contain the user input
 *         float percentIdleTime: previously calculated to give the percent in which
 *         the system may be idle.
 *
 * returns calculated average number of customers in the system
 */
//float avgNumInSystem(ServerT*, float percentIdleTime);
double avgNumInSystem(double, int, double, double);
/** avgTimeInSystem function
 *
 * Function takes in a server of type ServerT*, and a float calculated previously
 * Then computes the average time a customer might spend in the system
 *
 * @params: ServerT* server, struct variable of type ServerT*; holds the user input
 * 			float avgInSystem: previously calculated value for average time in system
 *
 * returns calculated average time a customer is in the system
 */
//float avgTimeInSystem(ServerT*, float avgInSystem);
double avgTimeInSystem(double, double);
/** avgCustomerInQueue function
 *
 * Function takes in a struct var of type ServerT*, and previously calculated float avgInSystem
 * Then beings to calculate the average number of customers in queue
 *
 * @params: ServerT* server: struct var server of type ServerT*, contains user input
 * 			float avgInSystem: previously calcualted value for average number of customers in system
 *
 * returns the calculated average of customers in queue
 */
//float avgCustomerInQueue(ServerT*, float avgInSystem);
double avgCustomerInQueue(double, double, double);
/** avgWaitInQueue function
 *
 * Function takes in a struct var of type ServerT* and a float avgInSystem.
 * Then goes onto calculate the average wait for a customer within the system
 *
 * @params: ServerT* server: struct var server of type ServerT*; holds the user input
 * 			float avgInSystem: previously calculated average number of customers in the system
 *
 * returns calculated average wait within the system
 */
//float avgWaitInQueue(ServerT*, float avgInSystem);
double avgWaitInQueue(double, double);
/** calcUtilFactor function
 *
 * Function takes in a struct var of type ServerT*.
 * Then calculates the total utility factor of the system.
 *
 * I think it is the total usage of the system while in use.
 *
 * returns calculated utility factor
 */
float calcUtilFactor(ServerT*);

#endif /* CALCULATIONS_H_ */
