/**
 * citygraph.h
 *
 *  Created on: Mar 6, 2017
 *      Author: dylan, nathan
 *      Project3a: Brute Force
 *
 *  main.c: source code for the traveling sales man simulation implemented using a Graph structure in C.
 *
 *  Program computes a brute force model of the traveling sales man simulation.
 *  It simulates and compares different permutations of a route, to determine
 *  the most cost effective route to take.
 */

//Standard Includes
#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//CityNodeADT; child struct for individual city nodes
typedef struct CityNodeADT {

	struct Edge** list;
	int size;
	int visited;
	char name;

} CityNodeT; /* END */

typedef struct Edge {

	CityNodeT* from;
	CityNodeT* to;
	int weight;

} EdgeT; /* END */

//CityGraphADT; parent structure to hold all of the individual city nodes
typedef struct CityGraphADT {

	int size;
	int capacity;
	int min_cost;
	char* bestRoute;
	CityNodeT** cities; //node placeholder for head of list; #init city

} GraphT; /* END */

/** readFile function
 *
 * Function takes in a text file to read from and then saves and processes the data from it
 *
 * @params:
 * ListT* graph: the city graph
 * char* argv: command line argument passed as text file
 * int numCities: command line argument passed as number of cities to permute
 */
void readFile(GraphT* graph, char* argv, int numCities);

/**
 * Creates and returns a graph with a given capacity
 *
 * @param capacity the amount of cities the graph will hold
 * @return graph the newly created graph with the given capacity
 */
GraphT* initGraph(int capacity);

/**
 * Add a new city to the graph of cities
 *
 * @param cityName the name of the new city
 */
void addCity(GraphT* graph, char cityName);

/**
 * Returns the city structure based on the city name
 *
 * @param citName the name of the city to be found
 * @return city the structure that represents the city in the graph
 */
CityNodeT* findCity(char cityName);

int traverseGraph(GraphT* graph, char* route);

int traverseRoute(GraphT* graph, CityNodeT* currentCity, char* route,
		int traveled, int totalCost);

/**
 * Connects two cities together undirected.
 *
 * @param from the beginning city
 * @param to the ending city
 * @param weight the cost to travel from the beginning city to the ending city or vice versa
 */
void addEdge(CityNodeT* from, CityNodeT* to, int weight);

/**
 * Frees the allocated memory for the graph
 *
 * @param GraphT* graph; the graph retaining the allocated memory
 */
void deleteGraph(GraphT* graph);
