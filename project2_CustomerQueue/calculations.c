/*
 * calculations.c
 *
 *  Created on: Feb 13, 2017
 *      Author: dylan, nathan
 *
 *  calculations.c: source code that holds the simulation and analytical calculations
 *  for the simulations, used to compare accuracy
 */

//Corresponding Header
#include "calculations.h"

//getNextRandomIntreval; calculates a new random interval; either arrival or departure
float getNextRandomIntreval(float avg) {

	float f = ((float) rand() / (float) (RAND_MAX)) * 1.0; //generating a random float on the interval 0 -> 1
	float intrevalTime = -1 * (1.0 / avg) * log(f); //calculating interval time

	return intrevalTime; //returning interval time
} /* END */

//factorial; calculates the factorial of the integer passed as param
unsigned int factorial(unsigned int f) {
	if (f == 0)
		return 1;
	return (f * factorial(f - 1));
} /* END */

//percentIdeTime; calculates the average idle time of the system
double percentIdleTimeAnalytical(int numChannels, double lambda, double mu)
{

	double percentIdle = 0;
	double summation = 0;
	double temp1 = 0;
	double temp2 = 0;	

	size_t i;
	for (i = 0; i < numChannels; i++)
		summation += (1 / factorial(i))*pow((lambda / mu), i);

	temp1 = (1 / factorial(numChannels))*pow(lambda / mu, numChannels);
	temp2 = (numChannels * mu) / ((numChannels * mu) - lambda);

	percentIdle = 1 / (summation + (temp1) * (temp2));

	return percentIdle;

} /* END */

//avgNumInSystem; calculates the average number of clients in the system
double avgNumInSystem(double percentIdleTime, int numChannels, double lambda, double mu)
{

	double avgNum = 0;
	double temp1 = 0;
	double temp2 = 0;
	double temp3 = 0;

	temp1 = lambda / mu;
	temp2 = (lambda * mu) * pow(temp1, numChannels);
	temp3 = temp2 / (factorial(numChannels - 1) * pow((numChannels * mu -lambda), 2));

	avgNum = (temp3 * percentIdleTime) + temp1;

	return avgNum;

} /* END */

//avgTimeInSystem; calculates the average time a customer is in the system
double avgTimeInSystem(double avgNumInSystem, double lambda)
{

	double avgTime = avgNumInSystem / lambda;

	return avgTime;

} /* END */

//avgCustomerInQueue; calculates the average number of customers in queue
double avgCustomerInQueue(double avgNum, double lambda, double mu)
{

	double avgNumInQ = avgNum - (lambda / mu);

	return avgNumInQ;

} /* END */

//avgWaitInQueue; calculates the average wait within the queue
double avgWaitInQueue(double avgNumInQ, double lambda)
{

	double avgWaitInQ = avgNumInQ / lambda;

	return avgWaitInQ;

} /* END */

//calcUtilFactor; calculates the utility factor of the system
float calcUtilFactor(ServerT* server) {

	float utilFactor, lambda, mu, m;

	lambda = server->avgArrivals;
	mu = server->avgServed;
	m = server->numChannels;

	utilFactor = lambda / (m * mu);
	//printf("\nUtility fator: %f\n", utilFactor);
	return utilFactor;
} /* END */
