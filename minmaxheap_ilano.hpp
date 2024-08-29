/*
Author: Gabriel Ilano
Date: 4/19/24
Description: Contains vertex struct and modified MinHeap structure specifically implemented for storing vertices
*/

#ifndef MINMAXHEAP_ILANO_HPP
#define MINMAXHEAP_ILANO_HPP
#include <concepts>
#include <stdexcept>
#include <algorithm>

struct vertex {
    int index;
    float weight;
};

class MinHeap {
private:
    vertex* array;
    int count;
    int capacity;

public:
    MinHeap() { //constructor
        array = new vertex[999]; //default capacity of 999
        count = 0;
        capacity = 999;
    }

    MinHeap(int size) { //constructor with set size
        array = new vertex[size];
        count = 0;
        capacity = size;
    }

    ~MinHeap() { //destructor
        delete[] array;
    }

    void enqueue(int index, float weight) { //adds item and re sorts heap
        if (count == capacity) { //throws exception if array is full
            throw std::out_of_range("Heap is Full");
        }

        array[count] = {index, weight}; //place item at the end of array
        count++; //increment to account for new item
        buildMinHeap(array, count); //reorganize heap
    }

    void dequeue() { //removes smallest item (root) of heap
        if (isEmpty()) { //throws exception if heap is empty
            throw std::out_of_range("Heap is Empty");
        }

        array[0] = array[count - 1]; //first item is set to last item
        count--; //decrement count
        buildMinHeap(array, count); //reorganize heap
    }

    vertex peek() { //returns smallest item (root) of heap
        return array[0];
    }

    int getSize() { //returns count of items in heap
        return count;
    }

    int getCapacity() { //returns max capacity of heap
        return capacity;
    }

    bool isEmpty() { //returns true if heap is empty
        if (count == 0) {
            return true;
        }
        return false;
    }

    void minHeapify(vertex* array, int count, int i) { //checks and performs swaps to ensure sub tree maintains heap property
        int smallest = i; //root
        int left = 2*i + 1; //left child
        int right = 2*i + 2; //right child
  
        if (left < count && array[left].weight < array[smallest].weight) //root becomes left if left child exists and is smaller
            smallest = left;

        if (right < count && array[right].weight < array[smallest].weight) //root becomes right if right child exists and is smaller
            smallest = right;

        if (smallest != i) { //if smallest is not root, swaps smallest with root
            std::swap(array[i], array[smallest]);
            minHeapify(array, count, smallest); //continues heapifying subtree until heap property is restored
        }
    }

    void buildMinHeap(vertex* array, int count) { //converts unsorted array into heap by applying minheapify from bottom to top
        int index = (count / 2) - 1; //finds last non leaf node

        for (int i = index; i >= 0; i--) { //apply minheapify from all nodes starting from last non leaf
            minHeapify(array, count, i);
        }
    }
};
#endif