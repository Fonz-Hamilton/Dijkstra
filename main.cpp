/**
* Name: 	Fonz Hamilton
* Course:	CSE310
* Project:	Project 3
* File:		main.cpp
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include "graph.h"
#include "util.h"
#include "heap.h"

using namespace std;

VERTEX *vertice;
int main(int argc, char *argv[]) {
	string direction = argv[2];			// stores the direction in string
	pNODE *adjacencyList;				// array of nodes for the adjacency list
	pNODE node;							// to store data for each node
	

	int n, m, graphDirection;			// variables to store the first two lines of file and direction arg
	int edgeID;							// currently just to hold the the first value in the file
	int u, v;							// u is current vertex, v is next
	float w;
	int source, destination;
	int s, d, flag;
	string input;						// input for query
	int readValue;
	int inputArg1, inputArg2, inputArg3;// this is for my util function. will take those and pass them to
										// the correct variable after parsed

	
	// if no arguments then prompt for correct format
	if (argc < 2) {
		cout << "Command Format: "<< argv[0] << " <graph_file> <direction>" << endl;
		return 1;						// exit
	}
	
	// find if directed or undirected and store into graphDirection int
	if (direction.compare("directed") == 0) {
		graphDirection = 1;
	}
	else if (direction.compare("undirected") == 0) {
		graphDirection = 2;
	}
	else {
		graphDirection = 0;
	}

	ifstream inFile(argv[1]);
	if (!inFile.good()) {
		cout << "ERROR: cannot read file" << endl;
		return 1;
	}
	
	inFile >> n;						// stores the first number into n
	inFile >> m;						// stores the second number into m

	adjacencyList = new pNODE[n + 1];
	
	// builds the adjacencyList
	for (int i = 0; i < m; i++) {
		inFile >> edgeID;
		inFile >> u;
		inFile >> v;
		inFile >> w;
		node = new NODE;
		node->v = v;
		node->w = w;
		node->next = adjacencyList[u];
		adjacencyList[u] = node;
		
		// if it is not a directed graph then add node u to vertex v
		if (graphDirection == 2) {
			node = new NODE;
			node->v = u;
			node->w = w;
			node->next = adjacencyList[v];
			adjacencyList[v] = node;
		}
		
	}

	inFile.close();						// close the file

	source = 0;
	destination = 0;
	vertice = new VERTEX[n + 1];

	while(1) {
		getline(cin, input);
		readValue = nextWord(input, &inputArg1, &inputArg2, &inputArg3);
		
		if (readValue == 0) {
			cout << "Query: stop" << endl;
			// delete all the nodes in each index	
			for (int i = 1; i < n + 1; i++) {
				node = adjacencyList[i];
				pNODE next = NULL;

				while(node != NULL) {
					next = node->next;
					delete node;
					node = next;
				}
				// set the index to null just in case
				adjacencyList[i] = NULL;
				
			}
			// delete the array
			delete[] adjacencyList;
			
			// delete the vertice array
			
			if (vertice != NULL) {
				delete[] vertice;
			}
        	return 0;
		}

		else if (readValue == 1) {
			cout << "Query: find " << inputArg1 << " " << inputArg2 << " " << inputArg3 << endl;
			
			if (inputArg1 < 1 || inputArg1 > n || inputArg3 < 0 || inputArg3 > 1) {
				cout << "Error: invalid find query" << endl;
			}

			else {
				source = inputArg1;
				destination = inputArg2;
				flag = inputArg3;
				
				if (vertice != NULL) {
					delete[] vertice;
				}
				dijkstra(n, adjacencyList, source, destination, flag);
			}
		}

		else if (readValue == 2) {
			cout << "Query: write path " << inputArg1 << " " << inputArg2 << endl;
			
			if (inputArg1 == 0) {
				cout << "Error: no path computation done" << endl;
			}
			else if (inputArg1 != source || inputArg2 == inputArg1 ||  inputArg2 > n) {
				cout << "Error: invalid source destination pair" << endl;
			}
			else {
				s = inputArg1;
				d = inputArg2;

				printPath(n, source, destination, s, d);
			}
		}

	}


	return 0;

}
