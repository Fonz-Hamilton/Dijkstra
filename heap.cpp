/*File:		heap.cpp
* Name:		Fonz Hamilton
* Dynamic memory allocation: lines: 12, 17
*/
#include <iostream>
#include <limits>
#include "heap.h"
#include "graph.h"
using namespace std;

int heapifyCount = 0;
extern VERTEX *vertice;

// function to initialize heap
HEAP *heapInit(int capacity) {
	HEAP *heap;
	heap = new HEAP;		// allocate memory for object

	heap->capacity = capacity;	// set capacity in heap struct to capacity parameter
	heap->size = 0;			// initialize size in heap struct to 0

	heap->elements = new ElementT[capacity + 1];	//allocate memory for elements pointer

	return heap;			// return address of heap object
}

// function to print heap to terminal
void heapPrint(HEAP *H) {
	if (H == NULL) {	// make sure heap isnt null
		cout << "Error: heap is NULL" << endl;
	}
	// do some printing
	else {
		cout << "capacity=" << H->capacity << ", size=";
		cout << H->size << endl;
		for (int i = 1; i <= H->size; i++) {
			if (i < H->size) {
				cout << H->elements[i]->key << ", ";
			}
			else {
				cout << H->elements[i]->key;
			}
		}
		if (H->size > 0) {
			cout << endl;
		}
	}
}

/* 
* functions to print parent, left, and right indexs
*/
int parent(int index) {
	int parentIndex = index / 2;
	return parentIndex;
}
int left(int index) {
	int leftIndex = 2 * index;
	return leftIndex;
}
int right(int index) {
	int rightIndex = (2 * index) + 1;
	return rightIndex;
}

// min heapify
void minHeapify(HEAP *H, int index) {
	heapifyCount++;
	int smallest;
	int l = left(index);
	int r = right(index);
	
	if (l <= H->size && H->elements[l]->key < H->elements[index]->key) {
		smallest = l;
	}
	else {
		smallest = index;
	}

	if (r <= H->size && H->elements[r]->key < H->elements[smallest]->key) {
		smallest = r;
	}

	if (smallest != index) {
		//ElementT temp;
		int temp;

		temp = H->elements[index]->key;
		H->elements[index]->key = H->elements[smallest]->key;
		H->elements[smallest]->key = temp;

		minHeapify(H, smallest);
	}
}

// build the heap
void buildMinHeap(HEAP *H) {
	heapifyCount = 0;
	//H->size = H->capacity;

	for (int i = ((H->size) / 2); i > 0; i--) {
		minHeapify(H, i);
	}
}

// heap extract min
int heapExtractMin(HEAP *H) {
	int min;
	heapifyCount = 0;
	min = H->elements[1]->vertex;
	
	H->elements[1]->vertex = H->elements[H->size]->vertex;
	H->size = H->size - 1;
	minHeapify(H, 1);
	
	return min;
}



// heap decrease key
void heapDecreaseKey(HEAP *H, int index, float key) {
	int v;

	if (key > H->elements[index]->key) {
		cout << "Error: new key is bigger than current key" << endl;
	}
	else {
		H->elements[index]->key = key;
		while ((index > 1) && (H->elements[parent(index)]->key > H->elements[index]->key)) {
			int temp;

			temp = H->elements[index]->key;
			v = H->elements[index]->vertex;
			
			// this should swap all the values of the child with the parents
			H->elements[index]->key = H->elements[parent(index)]->key;
			H->elements[index]->vertex = H->elements[parent(index)]->vertex;
			vertice[H->elements[index]->vertex].position = parent(index);
			
			// this should swap the parent with the child
			H->elements[parent(index)]->key = temp;
			H->elements[parent(index)]->vertex = v;
			vertice[H->elements[parent(index)]->vertex].position = index;

			index = parent(index);
		}
		
	}

}

// min heap insert
void minHeapInsert(HEAP *H, float key, int v) {
	float imax = std::numeric_limits<float>::max();
	H->size = H->size + 1;
	ElementT element = new ELEMENT;
	element->key = imax;
	element->vertex = v;

	H->elements[H->size] = element;
	vertice[H->elements[H->size]->vertex].position = H->size;

	heapDecreaseKey(H, H->size, key);
	

}

// new insert cause the other might have been bad
void insert(HEAP *H, ElementT vert) {
	
	if (H->size >= H->capacity) {
		cout << "Problem in insert" << endl;
	}
	H->size++;
	H->elements[H->size] = vert;
	vertice[H->elements[H->size]->vertex].position = H->size;
	movingUp(H, H->size);
}

// moving up
void movingUp(HEAP *H, int pos) {
    int parent = pos/2;
    ElementT temp;

    if (pos > 1 && H->elements[pos]->key < H->elements[parent]->key) {
        temp = H->elements[pos];
        H->elements[pos] = H->elements[parent];
        H->elements[parent] = temp;
        vertice[H->elements[pos]->vertex].position = pos;
        vertice[H->elements[parent]->vertex].position = parent;
        movingUp(H, parent);
    }
}

// moving down
void movingDown(HEAP *H, int index, int *flag) {
	heapifyCount++;
    int smallest;
    int l = left(index);
    int r = right(index);
    if (l <= H->size && H->elements[l]->key < H->elements[index]->key) {
        smallest = l;
    }
    else {
        smallest = index;
    }

    if (r <= H->size && H->elements[r]->key < H->elements[smallest]->key) {
        smallest = r;
    }

    if (smallest != index) {
        
        ElementT temp;

        temp = H->elements[index];
		H->elements[index] = H->elements[smallest];
		H->elements[smallest] = temp;
		
		vertice[H->elements[index]->vertex].position = index;
        vertice[H->elements[smallest]->vertex].position = smallest;


		//vertice[H->elements[index]->vertex].position = smallest;
		//vertice[H->elements[smallest]->vertex].position = index;
        movingDown(H, smallest, flag);
	
    }
}

// method to delete minimum value from heap. return element
ElementT deleteMin(HEAP *H, int *flag) {

	ElementT min;
	ElementT last;

	if (H->size <= 0) {
		cout << "Error in deleteMin: heap empty" << endl;
		return NULL;
	}

	min = H->elements[1];
	last = H->elements[H->size--];
	H->elements[1] = last;
	vertice[H->elements[1]->vertex].position = 1;
	movingDown(H, 1, flag);
	vertice[min->vertex].position = 0;
	return min;
}

// print heapify calls
void printHeapifyCalls() {
	cout << "Number of Heapify calls: " << heapifyCount << endl;
	heapifyCount = 0;
}

