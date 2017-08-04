/*
 * route.h
 *
 *  Created on: Mar 16, 2017
 *      Author: Nathan + Dylan
 *
 * The header file for the correspoding source code: route.c,
 * this file holds the prototypes for the corresponding functions
 */

#ifndef ROUTE_H_
#define ROUTE_H_

//Standard Includes
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

//Forward declaration
typedef struct CityGraphADT GraphT;

// ADT Structure for the Collection Nodes
typedef struct RouteT
{

	char* route;
	int cost;

} RouteT;

// ADT Structure for the collection itself
typedef struct RouteCollectionT
{

	RouteT** routes;
	int capacity;
	int size;

} RouteCollectionT;

/** initRoute function
 * 
 * Takes in an initial capacity to initialize the Route Collection
 *
 */
RouteCollectionT* initRoute(int capacity);


/** addRoute function
 * 
 * Takes in an initialized graph, the route collection, and the new route to be added
 *
 * @param: graph; the graph used to hold the edges and costs per city
 * @param: collection; a type of dictionary to retain the city nodes and their costs for manipulation
 * @param: newRoute; the new route being added
 */
void addRoute(GraphT* graph, RouteCollectionT* collection, RouteT* newRoute);

/** splice function
 *
 * Takes in an initialized graph, the collection of cities, and the current index (city index)
 *
 * This function takes in a single integer as an index, and handles the next index along with it.
 * Requiring there be always two more cities to splice, will return if else, odd cases handled by
 * basic mutation.
 *
 * @param: graph; the graph used to hold the edges and costs per city
 * @param: collection; a type of dictionary to retain the city nodes and their costs for manipulation
 * @param: current; the current city index being spliced
 */
void splice(GraphT* graph, RouteCollectionT* collection, int current);

/** fixRoute function
 *
 * This function takes in a "broken" route, one in which a city appears more than once within the 
 * established route.
 *
 * @param: route; the route needing to be fixed, duplicate cities within the route after splicing
 */
void fixRoute(char* route);

/** mutate function
 *
 * This function takes in an initialized graph, the collection of city nodes and a new route to 
 * be mutated.
 *
 * @param: graph; the graph used to hold the edges and costs per city
 * @param: collection; a type of dictionary to retain the city nodes and their costs for manipulation
 * @param: oldRoute; the route that is being mutated
 */
void mutate(GraphT* graph, RouteCollectionT* collection, char* oldRoute);

/** routesSearch function
 *
 * This function takes in the collection of city nodes to be searched through and the specific route 
 *
 * @param: collection; the collection of city nodes which is being cleared
 * @param: route; the specific route being searched for
 */
int routesSearch(RouteCollectionT* collection, RouteT* route);

/** routeDisplay function
 *
 * This function takes in the collection of city nodes to be displayed
 *
 * @param: collection; the collection of city nodes which is being displayed
 */
void routeDisplay(RouteCollectionT* collection);

/** routesClear function
 *
 * This function takes in the collection of city nodes to be clear the data from
 *
 * @param: collection; the collection of city nodes which is being cleared
 */
void routeClear(RouteCollectionT* collection);

/** routesDelete function
 *
 * This function takes in the collection of city nodes to be freed
 *
 * @param: collection; the collection of city nodes which is being freed
 */
void routesDelete(RouteCollectionT* collection);

/** swap function
 *
 * This function swaps cities within a route
 *
 * @param: cities; the basic city array that holds the names of all the cities used
 * @param: firstIndex; the first index, or the first city being swapped
 * @param: secondIndex; the second index, or the second city being swapped
 */
void swap(char* cities, int firstIndex, int secondIndex);

#endif /* ROUTE_H_ */
