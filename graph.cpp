/*
* File: graph.cpp
* Name: Fonz Hamilton
*/
#include <iostream>
#include "graph.h"
#include "heap.h"
using namespace std;

extern VERTEX *vertice;

// print path
void printPath(int n, int source, int destination, int s, int t) {
	PATH *pointPath;
	PATH *pointNode;
	
	int u, v;

	if (vertice[t].color == 0) {
		if (destination < 1 || destination > n || t == destination) {
			printf("No %d-%d path exists.\n", s, t);
			return;
		}
		else {
			printf("No %d-%d path has been computed.\n", s, t);
			return;
		}
	}
	else if (vertice[t].color == 1) {
		printf("Path not known to be shortest: <%d", s);
		
	}
	else if (vertice[t].color == 2) {
		printf("Shortest path: <%d", s);
	}

	// push onto stack
	pointNode = new PATH;
	pointNode->vertex = t;				// sets the node to destination vertex
	pointNode->next = NULL;				// sets next to NULL
	pointPath = pointNode;				// path = node
	v = pointNode->vertex;				// v = vertex of pointNode
	
	while (vertice[v].pi) {
		u = vertice[v].pi;
		pointNode = new PATH;
		pointNode->vertex = u;
		pointNode->next = pointPath;
		pointPath = pointNode;
		v = pointNode->vertex;
	}

	pointNode = pointPath;
	pointPath = pointPath->next;
	delete pointNode;
	
	while (pointPath) {
		pointNode = pointPath;
		printf(", %d", pointNode->vertex);
		pointPath = pointPath->next;
		delete pointNode;
	}
	delete pointPath;
	printf(">\n");
	printf("The path weight is: %12.4f\n", vertice[t].dist);
}

// dijkstras shortest path algorithm
int dijkstra(int n, pNODE *adjacencyList, int s, int t, int flag) {
	pNODE node;								// struct with v, w, next
	HEAP *heap;								// heap just heaps
	ELEMENT *element;						// struct with int vertex, float key

	int u, v;								// u for current, v for next
	float w;

	int pos;
	int heapifyCount;
	
	vertice = new VERTEX[n+1];

	for (int i = 1; i <= n; i++) {
		vertice[i].color = 0;				// 0 is used for white
		vertice[i].pi = 0;					// 0 is used for nil
	}
	vertice[s].dist = 0;					// current distance from source
	vertice[s].color = 1;					// 1 is used for grey

	heap = heapInit(n);						// builds a heap with n nodes

	element = new ELEMENT;
	element->vertex = s;
	element->key = 0;

	insert(heap, element);					// adds the source node to the priority queue
	if (flag == 1) {
		printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
	}
	while (heap->size != 0) {
		element = deleteMin(heap, &flag);	// extracts the min vertex value from heap and sets it to u
		
		if (flag == 1) {
			printf("Delete vertex %d, key=%12.4f\n", element->vertex, element->key);
		}

		u = element->vertex;
		vertice[u].color = 2;				// sets the color to black
		
		delete element;
		if (u == t) {


			if (heap != NULL) {
            	for (int i = 0; i < heap->size; i++) {
                	delete heap->elements[i];
				}
			}


			delete[] heap;
			if (node != NULL) {
				delete node;
			}
			return 0;
		}
		
		node = adjacencyList[u];
		while (node != NULL) {
			v = node->v;
			w = node->w;
			if (vertice[v].color == 0) {
				vertice[v].dist = vertice[u].dist + w;
				vertice[v].pi = u;
				vertice[v].color = 1;
				element = new ELEMENT;
				element->vertex = node->v;
				element->key = vertice[v].dist;
				
				if (flag == 1) {
                    printf("Insert vertex %d, key=%12.4f\n", element->vertex, element->key);
                }
				insert(heap, element);
			}
			else if (vertice[v].dist > vertice[u].dist + w) {
				float test = vertice[v].dist;
				vertice[v].dist = vertice[u].dist + w;
				vertice[v].pi = u;
				
				
				if (flag == 1) {
					printf("Decrease key of vertex %d, from %12.4f to %12.4f\n", v, test, vertice[v].dist);
				}

				heap->elements[vertice[v].position]->key = vertice[v].dist;
				movingUp(heap, vertice[v].position);
			}
			node = node->next;
		}
		
	}
	if (heap != NULL) {
		for (int i = 0; i < heap->size; i++) {
			delete heap->elements[i];
		}
    }

	delete[] heap;
	delete node;
	return 1;
}
