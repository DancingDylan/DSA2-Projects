/*
 * tspGenetic.c
 *
 *  Created on: Mar 14, 2017
 *      Author: Dylan + Nathan
 *
 *  This is the main program function that will run the corresponding source codes
 *  that will attempt to use a genetic mutation alogrithm to compute the least cost route 
 *  between an initial number of cities.
 */

//Corresponding Headers
#include "citygraph.h"
#include "route.h"

//Prototypes
void generateRoutes(GraphT* graph, RouteCollectionT* collection, char* cities,
		int numTours, int level);

//Defining a base optimal route.
#define MOSTOPTIMAL 4;

//tspGenetic; a genetic algorithm approach to solve the traveling salesman problem
int main(int argc, char **argv) {

	//Check to assure correct parameters
	if (argc != 6) {
		printf(
				"Error: invalid number of arguments.\nUsage: ./tspGenetic ./file.txt <numCities> <numGen> <numTours> <percent>\n\n");
		return 0;
	}

	//declare file pointer and attempt to open file passed as command argument
	FILE* fin = fopen(argv[1], "r");
	if (fin) { //if file is opened, close and continue. #quick check to make sure arguments are correct on command line
		printf(
				"File %s opened, with following parameters:\nNumber of Cities: %d\nNumber of Tours: %d\n\n",
				argv[1], atoi(argv[2]), atoi(argv[4]));
		fclose(fin);
	} else {   //else the file doesn't exist, exit.
		perror("Error");
		exit(1);
	}

	srand(time(NULL));

	// Variables based on user input
	int numCities = atoi(argv[2]); //number of cities
	int numGenerations = atoi(argv[3]); //number of generations
	int numTours = atoi(argv[4]); //number of tours
	double percentage = (double) atoi(argv[5]) / 100; //percentage
	int mostOptimal = 3;
	int optimal = mostOptimal * numCities;

	char cities[numCities];

	GraphT* graph = initGraph(numCities);
	RouteCollectionT* collection = initRoute(numTours);

	// Loop to determine the Cities node names and adding them to the grapgh
	size_t i = 0;
	size_t j = 0;
	size_t k = 0;
	size_t counter = 0;
	for (i = 0; i < numCities; i++) {
		cities[i] = i + 'A';
		addCity(graph, cities[i]);
	}

	cities[i] = '\0';

	// Read through the file and determine specific edge costs
	readFile(graph, argv[1], numCities);

	// Start the clock timer
	clock_t start = clock(), diff;
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;

	// Connect the edges and determine the costs of each route
	generateRoutes(graph, collection, cities, numTours, 0);

	// Beginning loop for the genetic algorithm
	while (counter != numGenerations && collection->routes[j]->cost != optimal) { // while( getPercentDiff( routeOne, routeTwo, percentage ) )

		//used for random swaps between routes and mutation process
		int rndchk = rand() % 2; //between 0 - 1, 0 will splice, 1 will mutate routes.

		if (rndchk == 0) {
			for (i = 0; i < numTours * percentage; i += 2) {
				splice(graph, collection, i);
			}
		} else {

			for (i = 0; i < numCities * percentage; i++) {

				char* rndRoute = collection->routes[rand() % numTours]->route; // the random route chosen
				mutate(graph, collection, rndRoute);

			}
		}

		/* quick check to make sure no double routes, we were occasionally getting duplicate routes,
		 * we can probably devise a better check for this though.
		 */
		for (k = 0; k < numTours - 1; k++) {
			if (strcmp(collection->routes[k]->route,
					collection->routes[k + 1]->route) == 0) {
				mutate(graph, collection, collection->routes[k]->route);
			}
		}

        //This will cycle through the routes while the while loop processes, to check if a "most-optimal" route has been determined.
		if (j == collection->size - 1 && j > 0)
			j--;
		else if (j == 0 && j < collection->size - 1)
			j++;

		counter++;
	}

	printf("\nMost efficient route: %s with the cost of: %d\n",
			collection->routes[0]->route, graph->min_cost);
	printf("Time taken %d seconds %d milliseconds", msec / 1000, msec % 1000);

	// Free allocated memory
	routesDelete(collection);
	deleteGraph(graph);
	return 0;

} /* END */

//generateRoutes; generate the permutations based on the initial number of cities
void generateRoutes(GraphT* graph, RouteCollectionT* collection, char* cities,
		int numTours, int level) {

	int i, j, random;
	for (i = 0; i < numTours; i++) {

		char* tmp = malloc(strlen(cities) + 1);
		strcpy(tmp, cities);

		for (j = 0; j < strlen(tmp); j++) {
			random = rand() % strlen(tmp);

			swap(tmp, random, strlen(tmp) - 1);
		}

        // Creating the new route node
		printf("Routes: %s\n", tmp);
		RouteT* newRoute = malloc(sizeof(RouteT));
		newRoute->route = malloc(strlen(tmp) + 1);
		newRoute->cost = i;
		strcpy(newRoute->route, tmp);

        // Adding the new node to the route collection
		addRoute(graph, collection, newRoute);

		free(tmp);

	}

	printf("\n");
} /* END */
