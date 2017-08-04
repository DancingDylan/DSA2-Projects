/*
 * route.c
 *
 *  Created on: Mar 16, 2017
 *      Author: Nathan + Dylan
 *
 *  This is the source code for the correspoding header file: route.h
 */

#include "route.h"
#include "citygraph.h"

//initRoute; initialize a collection (dictionary) of routes
RouteCollectionT* initRoute(int capacity) {

	RouteCollectionT* collection = malloc(sizeof(RouteCollectionT));
	collection->routes = (RouteT**) malloc(sizeof(RouteT*) * capacity);
	collection->capacity = capacity;
	collection->size = 0;

	return collection;

} /* END */

//addRoute; adds a route to the collection
void addRoute(GraphT* graph, RouteCollectionT* collection, RouteT* newRoute) {

	newRoute->cost = traverseGraph(graph, newRoute->route);
	if (collection->size == collection->capacity)
	{
		printf("\nNo room\n");
		return;
	}

	if (collection->size == 0) {

		collection->routes[collection->size] = newRoute;
		collection->size++;

		return;

	}

	int index = routesSearch(collection, newRoute);

	int i;
	for (i = collection->size; i > index; i--)
		collection->routes[i] = collection->routes[i - 1];

	collection->routes[index] = newRoute;
	collection->size++;

} /* END */

//splice; function splices two routes together to create two offspring
void splice(GraphT* graph, RouteCollectionT* collection, int current) {

	//check if the next route being passed is null, aswell as the next route to it.
	if(collection->routes[current]->route == NULL || collection->routes[current+1]->route == NULL)
		return;

	//All the routes will be of same length based on the project
	int num_cities = strlen(collection->routes[0]->route);

	//Create some temp variables as to not mess with too many pointers
	char* currRoute = malloc(sizeof(collection->routes[current]->route) + 1);
	strcpy(currRoute, collection->routes[current]->route);
	currRoute[strlen(currRoute)] = '\0';

	char* nextRoute = malloc(sizeof(collection->routes[current + 1]->route) + 1);
	strcpy(nextRoute, collection->routes[current + 1]->route);
	nextRoute[strlen(nextRoute)] = '\0';

	//For loop, splice the first routes half with the second routes half.
	size_t i, j = 0;
	for (i = num_cities / 2; i < num_cities; i++, j++) {
		char tmp = currRoute[i];
		currRoute[i] = nextRoute[j];
		nextRoute[j] = tmp;
	}

	// Remove weaker routes
	free(collection->routes[collection->size - 1]->route);
	free(collection->routes[--collection->size]);
	free(collection->routes[collection->size - 1]->route);
	free(collection->routes[--collection->size]);

	// Fix the newly spliced routes
	fixRoute(currRoute);
	fixRoute(nextRoute);

	//Create the new route node to be added to our collection
	RouteT* newRoute1 = (RouteT*) malloc(sizeof(RouteT));
	newRoute1->route = malloc(strlen(currRoute) + 1);
	newRoute1->cost = 0;
	strcpy(newRoute1->route, currRoute);

	//Add the route to the collection
	addRoute(graph, collection, newRoute1);

	//Create the new route node to be added to our collection
	RouteT* newRoute2 = (RouteT*) malloc(sizeof(RouteT));
	newRoute2->route = malloc(strlen(nextRoute) + 1);
	newRoute2->cost = 0;
	strcpy(newRoute2->route, nextRoute);
	//Add the route to the collection
	addRoute(graph, collection, newRoute2);

	free(currRoute);
	free(nextRoute);

} /* END */

//fixRoute; function fixes a route, i.e. if a route has duplicate cities within it after mutation
void fixRoute(char* route)
{

	// Create a histogram of all of the repeated letters and the ones that are missing
	int* histogram = malloc(sizeof(int*) * strlen(route));

	// Creating a clone of the route to manipulate
	char* temp;
	temp = (char*) malloc(strlen(route) + 1);
	strcpy(temp, route);
	temp[strlen(route)] = '\0';

	int i;
	for (i = 0; i < strlen(route); i++)
		histogram[i] = 0;

	int j;
	for (j = 0; j < strlen(temp); j++)
		histogram[temp[j] - 'A']++;

	int k, l, m;
	for (k = 0; k < strlen(temp); k++) // Run through all of the histogram items
		if (histogram[k] == 0) // Check for letters that are missing using the histogram
			for (l = 0; l < strlen(temp); l++) // Run through the histogram again but now looking for ones that are repeated
				if(histogram[l] > 1) // Check for letters that are repeated using the histogram
				{
					/* Once you have the letter that is missing and the letter that is repeated
					 * Run through the temp route
					 */
					for (m = 0; m < strlen(temp); m++)
						if (l + 'A' == temp[m]) // Find where in the temp route there is the repeated letter
						{
							temp[m] = (char) (k + 'A'); // Swap out the repeated letter for the missing one

							// Update the histogram
							histogram[l]--;
							histogram[k]++;
							break;

						}
					break;
				}

	// Copy the new fixed route into the original route variable
	strncpy(route, temp, strlen(route));
	free(histogram);
	// Clean up the old temp
	free(temp);

} /* END */

//mutate; function mutates a single randomly chosen route, with random city swaps within it
void mutate(GraphT* graph, RouteCollectionT* collection, char* oldRoute)
{

	int random = rand() % 4 + 1;
	char* tmp = malloc(strlen(oldRoute) + 1);
	strcpy(tmp, oldRoute);

	int i;

	for (i = 0; i < random; i++)
	{

		swap(tmp, rand() % strlen(oldRoute), rand() % strlen(oldRoute));

	}

	RouteT* newRoute = malloc(sizeof(RouteT));
	newRoute->route = malloc(strlen(oldRoute) + 1);
	newRoute->route[strlen(oldRoute)] = '\0';
	newRoute->cost = 0;
	strcpy(newRoute->route, tmp);

	free(collection->routes[collection->size - 1]->route);
	free(collection->routes[collection->size - 1]);
	collection->size--;
	addRoute(graph, collection, newRoute);

	free(tmp);

} /* END */

//routeSearch; function searches the collection for a specific route
int routesSearch(RouteCollectionT* collection, RouteT* route) {

	// Implements a binary search to find a word in the dictionary
	int upper = collection->size - 1;
	int lower = 0;
	int midpoint = 0;

	while (upper >= lower) {

		midpoint = (lower + upper) / 2;

		if (collection->routes[midpoint]->cost > route->cost) {
			upper = midpoint - 1;
		} else if (collection->routes[midpoint]->cost < route->cost) {
			lower = midpoint + 1;
		} else
			return midpoint;

	}

	if (collection->routes[midpoint]->cost < route->cost)
		midpoint++;

	return midpoint;

} /* END */

//routeDisplay; displays the route collection
void routeDisplay(RouteCollectionT* collection)
{

	int i;
	for (i = 0; i < collection->size; i++)
		printf("Cost: %d Route: %s\n", collection->routes[i]->cost, collection->routes[i]->route);

} /* END */

//routesClear; clears the data from the route collection
void routesClear(RouteCollectionT* collection)
{

	int i;
	for (i = 0; i < collection->size; i++)
	{

		free(collection->routes[i]->route);
		free(collection->routes[i]);

	}

} /* END */

//routesDelete; frees the allocated memory for the route collection
void routesDelete(RouteCollectionT* collection)
{

	routesClear(collection);
	free(collection->routes);
	free(collection);

} /* END */


//swap; swaps two cities
void swap(char* cities, int firstIndex, int secondIndex) {

	char tmp = cities[firstIndex];
	cities[firstIndex] = cities[secondIndex];
	cities[secondIndex] = tmp;

} /* END */

