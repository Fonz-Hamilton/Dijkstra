/*File: heap.h
* Name: Fonz Hamilton
*/

// struct for ELEMENT
typedef struct TAG_ELEMENT {
	int vertex;				// points to vertex V[vertex]
	float key;
}ELEMENT;

// Pointer of ELEMENTS
typedef ELEMENT *ElementT;

typedef struct TAG_HEAP {
	int capacity;			// max size of the heap
	int size;				// current size of the heap
	ElementT *elements;		// array of pointers to elements
}HEAP;

// intitialize heap
HEAP *heapInit(int capacity);

// print the heap to terminal
void heapPrint(HEAP *H);
/*
* functions to print the parent, left, and right index of the tree
*/
int parent(int index);
int left(int index);
int right(int index);

// min heapify
void minHeapify(HEAP *H, int index);

// build the heap
void buildMinHeap(HEAP *H);

// heap extract min
int heapExtractMin(HEAP *H);

// heap decrease key
void heapDecreaseKey(HEAP *H, int index, float key);

// min heap insert
void minHeapInsert(HEAP *H, float key, int v);

// moving up function
void movingUp(HEAP *H, int pos);

// moving down
void movingDown(HEAP *H, int pos, int *flag);

// insert function
void insert(HEAP *H, ElementT vert);

// method to delete minimum value from heap. return element
ElementT deleteMin(HEAP *H, int *flag);

// print heapify calls
void printHeapifyCalls();
