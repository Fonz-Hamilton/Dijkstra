/*
* File: graph.h
* Name:	Fonz Hamilton
*/
typedef struct TAG_VERTEX {
	int vertex;
	int color;				// color of the vertex (0, 1, 2 | white, grey, black)
	int pi;					// predecessor of vertex (0(nil), 1, 2, ... , n)
	float dist;				// current distance from the source
	int position;			// position in the heap array
} VERTEX;

typedef VERTEX *pVERTEX;

typedef struct TAG_NODE {
	int u;					// redundant safe guard. may delete
	int v;					// the vertex in the node
	float w;				// the weight of (u,v)
	TAG_NODE *next;			// points to the next vertex in the list
} NODE;

typedef NODE *pNODE;		// an array of pointers of type NODE
							// A[i] is the adjacency list of vertex i

typedef struct TAG_PATH {
	int vertex;
	TAG_PATH *next;
} PATH;

typedef PATH *pPATH;		// an array of pointers of type PATH

// print path
void printPath(int n, int source, int destination, int s, int t);

// dijkstras shortest path algorithm
int dijkstra(int n, pNODE *adjacencyList, int s, int t, int flag);

