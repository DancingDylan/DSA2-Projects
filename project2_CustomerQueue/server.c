/*
 * server.c
 *
 *  Created on: Feb 13, 2017
 *      Author: gbdan
 *
 *  server.c: source code that is mostly used to simplify main.c, to allow
 *  ease of access and usage. Pushing most user input prompts into single functions
 *  in which to reduce clutter.
 */
/*
 * server.c
 *
 *  Created on: Feb 13, 2017
 *      Author: gbdan
 */

//Corresponding Headers
#include "server.h"
#include "calculations.h"

//getServerInfo; prompts for user input to store initial simulation stats
void getServerInfo(ServerT* server) {

	printf("Enter the number of arrivals: ");
	fflush(stdout); //eclipse doesn't register the printf's before the scanf's, had to flush standard output
	scanf("%d", &server->numArrivals);

	printf("Enter the average arrivals: ");
	fflush(stdout);
	scanf("%f", &server->avgArrivals);

	printf("Enter the average served: ");
	fflush(stdout);
	scanf("%f", &server->avgServed);

	printf("Enter the number of channels used: ");
	fflush(stdout);
	scanf("%zu", &server->numChannels);

	server->totArvIntrv = 0;
	server->totDptIntrv = 0;
	server->totIdle = 0;
	server->totInterval = 0;
	server->totWaitInFifo = 0;
	server->k = 0;
	server->f = 0;
} /* END */

//getServerCalculations; body function to store other function calls, specifically server stat calculations
void getServerCalculations(ServerT* server, CalcT* calcs) {
	

	printf("\t\tAnalytical Model\t\tSimulated Model\n");

	calcs->f = getNextRandomIntreval(server->avgArrivals);
	double percentIdleAnalytic = percentIdleTimeAnalytical(server->numChannels, server->avgArrivals, server->avgServed);
	double percentIdleSimulated = server->totIdle / server->totInterval;
	printf("Percent Idle:\t\t%8.2lf\t\t\t%7.2lf\n", percentIdleAnalytic, percentIdleSimulated);
	
	double avgNumAnalytic = avgNumInSystem(percentIdleAnalytic, server->numChannels, server->avgArrivals, server->avgServed);

	printf("Average Customers:\t%8.2lf\n", avgNumAnalytic);
	//calcs->avgInSystem = avgNumInSystem(server, calcs->percentIdle);
	
	double avgTimeInSystemAnalytic = avgTimeInSystem(avgNumAnalytic, server->avgArrivals);
	double avgTimeInSystemSimulated = (server->totDptIntrv - server->totArvIntrv) / server->k;
	printf("Average Time:\t\t%8.2lf\t\t\t%7.2lf\n", avgTimeInSystemAnalytic, avgTimeInSystemSimulated);

	//calcs->avgSystemTime = avgTimeInSystem(server, calcs->avgInSystem);
	
	double avgNumInQAnalytic = avgCustomerInQueue(avgNumAnalytic, server->avgArrivals, server->avgServed);
	//double avgNumInQSimulated = avgCustomerInQueue(avgNumSimulated, server->avgArrivals, server->avgServed);

	printf("Averege In Q:\t\t%8.2lf\n", avgNumInQAnalytic);

	//calcs->avgCustInQueue = avgCustomerInQueue(server, calcs->avgInSystem);
	
	double avgTimeInQAnalytic = avgWaitInQueue(avgNumInQAnalytic, server->avgArrivals);
	//double avgTimeInQSimulated = avgWaitInQueue(avgNumInQSimulated, server->avgArrivals);
	
	printf("Average Wait in Q:\t%8.2lf\t\t\t%7.2lf\n", avgTimeInQAnalytic, server->totWaitInFifo / server->k);

	//calcs->avgWait = avgWaitInQueue(server, calcs->avgInSystem);
	
	calcs->utilFactor = calcUtilFactor(server);
	double rhoSimulated = (server->totDptIntrv - server->totArvIntrv) / (server->numChannels * server->totInterval);
	printf("\nUtility Factor:\t\t%8.2f\t\t\t%7.2f\n", calcs->utilFactor, rhoSimulated);
	
} /* END */
