/*
 * citygraph.c
 *
 *  Created on: Mar 6, 2017
 *      Author: natha
 */

//Time Handling
struct timespec starttime, endtime;

#include "citygraph.h"

//readFile; function opens up a passed text file with city data, and retrieves, stores and processes the data
void readFile(GraphT* graph, char* argv, int numCities) {

	//file pointer
	FILE* fin = fopen(argv, "r");

	//variables used to read from file
	char from, to; //one holds the FROM cities and the other holds to TO cities
	int cost; //int to hold the cost of travel between two cities

	//scans the text file and retrieves the data, and passes them into the graph to create appropriate linkage
	while (fscanf(fin, " %c,%c,%d", &from, &to, &cost) != EOF) {
		if ((from - 'A') >= numCities || (to - 'A') >= numCities) {
			continue;
		} else {
			addEdge(graph->cities[from - 'A'], graph->cities[to - 'A'], cost);
		}
	}
	fclose(fin);
} /* END */

//initGraph; initialize the graph
GraphT* initGraph(int capacity) {

// Create the new graph with a given capacity and initialize it's fields
	GraphT* graph = (GraphT*) malloc(sizeof(GraphT));
	graph->cities = (CityNodeT**) malloc(sizeof(GraphT*) * capacity);
	graph->capacity = capacity;
	graph->min_cost = 1000;
	graph->size = 0;

	return graph;

} /* END */

//addCity; adds a city to the graph
void addCity(GraphT* graph, char cityName) {

// Create the new city node and initialize all it's fields
	CityNodeT* newCity = (CityNodeT*) malloc(sizeof(CityNodeT));
	newCity->list = (EdgeT**) malloc(sizeof(EdgeT) * (graph->capacity - 1));
	newCity->size = 0;
	newCity->name = cityName;
	newCity->visited = 0;

// Add the city to the graph's city list
	graph->cities[graph->size] = newCity;

// Increment the size of the graph
	graph->size++;

} /* END */

//traverseGraph; traverse through the graph and determine the route costs
int traverseGraph(GraphT* graph, char* route) {

	// Setting the min cost to something outrages
	char* completeRoute = (char*) malloc(strlen(route) + 2);
	char last = route[0];
	strcpy(completeRoute, route);
	completeRoute[strlen(route)] = last;
	completeRoute[strlen(route) + 1] = '\0';

	size_t i;
	for (i = 0; i < graph->size; i++) { // Looping through each city and using it as a starting city to find best route

		if (graph->cities[i]->name == completeRoute[0]) {

			// Go through all possible routes starting at the current starting city
			int cost = traverseRoute(graph, graph->cities[i], completeRoute, 0,
					0);

			// Check to see the totalCost of the current route is less than what the graph currently has
			if (graph->min_cost > cost) {
				if (graph->min_cost != 1000)
					free(graph->bestRoute);
				graph->min_cost = cost; // Update the newest lowest cost
				graph->bestRoute = malloc(strlen(completeRoute) + 1);
				graph->bestRoute[strlen(completeRoute)] = '\0';
				strcpy(graph->bestRoute, completeRoute);
			}

			free(completeRoute);
			return cost;

		}
	}

	free(completeRoute);

	return 0;
} /* END */

//traverseRoute; traverses a specific route and determines its total cost
int traverseRoute(GraphT* graph, CityNodeT* currentCity, char* route,
		int traveled, int totalCost) {

	if (currentCity->size < traveled) {

		return totalCost;

	} else {
		traveled++;

		size_t i;
		for (i = 0; i < currentCity->size; i++) {

			if (currentCity->list[i]->to->name == route[traveled]) {

				totalCost += currentCity->list[i]->weight;
				totalCost = traverseRoute(graph, currentCity->list[i]->to,
						route, traveled, totalCost);
				break;
			}
		}
	}

	return totalCost;
} /* END */

//addEdge; adds an edge to the grapgh between two city nodes
void addEdge(CityNodeT* from, CityNodeT* to, int weight) {

// Initialize the edge from the beginning city to the ending city and initialize it's fields
	EdgeT* newEdgeFrom = malloc(sizeof(EdgeT));
	newEdgeFrom->from = from;
	newEdgeFrom->to = to;
	newEdgeFrom->weight = weight;

// Give this new connection to the from city
	from->list[from->size] = newEdgeFrom;

// Increment the amount of connections this city has
	from->size++;

// Initialize the edge from the ending city to the beginning city and initialize it's fields
	EdgeT* newEdgeTo = malloc(sizeof(EdgeT));
	newEdgeTo->from = to;
	newEdgeTo->to = from;
	newEdgeTo->weight = weight;

// Give this new connection to the to city
	to->list[to->size] = newEdgeTo;

// Increment the amount of connections this city has
	to->size++;

} /* END */

//clearGraph; clears the data from within the graph
void clearGraph(GraphT* graph) {

	int i, j;
	for (i = 0; i < graph->size; i++) {
		for (j = 0; j < graph->cities[i]->size; j++)
			free(graph->cities[i]->list[j]);
		free(graph->cities[i]->list);
		free(graph->cities[i]);

	}

} /* END */

//deleteGraph; frees the allocated memory for the graph
void deleteGraph(GraphT* graph) {

	clearGraph(graph);
	free(graph->cities);
	free(graph->bestRoute);
	free(graph);

} /* END */
