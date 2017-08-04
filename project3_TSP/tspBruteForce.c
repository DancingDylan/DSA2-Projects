/*
 * tspBruteForce.c
 *
 *  Created on: Mar 6, 2017
 *      Author: nathan, dylan
 *
 *  tspBruteForce.c: source code for the Brute Force approach to solve the
 *  traveling salesman problem.
 */

//Corresponding Headers
#include "citygraph.h"

//Prototypes
void generateRoutesBF(GraphT* graph, char* cities, int n, int k);
void swapBF(char* cities, int firstIndex, int secondIndex);

//tspBruteForce; brute force approach to solve traveling sales man problem
int main(int argc, char **argv) {

	if(argc != 3) {
		printf("Error: invalid number of arguments.\nUsage: ./tspBruteForce ./file.txt <numCities>\n\n");
		return 0;
	}

	//declare file pointer and attempt to open file passed as command argument
	FILE* fin = fopen(argv[1], "r");
	if (fin) { //if file is opened, close and continue. #quick check to make sure arguments are correct on command line
		printf("File %s opened, with a total number of cities set to %d.\n\n", argv[1], atoi(argv[2]));
		fclose(fin);
	} else {   //else the file doesn't exist, exit.
		perror("Error");
		exit(1);
	}

	int argN = atoi(argv[2]);
	char cities[argN];

	GraphT* graph = initGraph(argN);

	size_t i;
	for (i = 0; i < argN; i++) {
		cities[i] = i + 'A';
		addCity(graph, cities[i]);
	}

	cities[i] = '\0';

	readFile(graph, argv[1], argN);

	traverseGraph(graph, cities);

	clock_t start = clock(), diff;
	generateRoutesBF(graph, cities, argN, 0);
	diff = clock() - start;
	int msec = diff * 1000 / CLOCKS_PER_SEC;

	printf("Best cost: %d Route: %s\n", graph->min_cost, graph->bestRoute);
	printf("Time taken %d seconds %d milliseconds", msec / 1000, msec % 1000);

	return 0;

} /* END */

//generateRoutes; generates the routes taken by permuting the number of cities
void generateRoutesBF(GraphT* graph, char* cities, int n, int k) {

	if (n == k) {
		traverseGraph(graph, cities);
		return;
	}

	size_t i;
	for (i = k; i < n; i++) {

		swapBF(cities, k, i);
		generateRoutesBF(graph, cities, n, k + 1);
		swapBF(cities, k, i);
	}
} /* END */

//swap; swaps two cities
void swapBF(char* cities, int firstIndex, int secondIndex) {

	char tmp = cities[firstIndex];
	cities[firstIndex] = cities[secondIndex];
	cities[secondIndex] = tmp;

} /* END */
