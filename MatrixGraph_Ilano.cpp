/*
Author: Gabriel Ilano
Date: 4/19/24
Description: Definitions for the Matrix Graph Class with Dijkstra Algorithm functionality
*/

#include "Queue_Ilano.hpp"
#include "minmaxheap_ilano.hpp"
#include "MatrixGraph_Ilano.h"
#include <iostream>
#include <iomanip>
using namespace std;

MatrixGraph::MatrixGraph(int vertices, bool directed) { //constructor
    array = new float*[vertices]; //creates first array
    for (int i = 0; i < vertices; i++) { //creates array for each index
        array[i] = new float[vertices]();
    }
    this->directed = directed;
    this->vertices = vertices;
    edges = 0; //initialize edges to 0
}

MatrixGraph::~MatrixGraph() { //destructor
    for (int i = 0; i < vertices; i++) { //deletes array at each index
        delete[] array[i];
    }
    delete[] array; //cleans array
    array = nullptr;
}


void MatrixGraph::addEdge(int start, int end, float weight) { //adds corresponding values to array to represent edge
    if (array[start-1][end-1] == 0.0) { //increments edge count if edge is new
        edges++;
    }

    array[start-1][end-1] = weight; //set value at given vertices

    if (!directed) { //add mirroring edge for undirected graphs
        array[end-1][start-1] = weight;
    }
}

void MatrixGraph::removeEdge(int start, int end) { //removes edge by reassigning value to 0
    array[start-1][end-1] = 0.0; //reassign edge to 0

    if (!directed) {
        array[end-1][start-1] = 0.0; //reassign mirroring edge to 0
    }
    edges--; //decrement count of edges
}

bool MatrixGraph::adjacent(int start, int end) { //returns true if value is found between two vertices
    if (array[start-1][end-1] != 0.0 || array[end-1][start-1] != 0.0) { //if value is found return true
        return true;
    }
    return false; //defaults to false
}

float MatrixGraph::getEdgeWeight(int start, int end) { //returns value at given vertices
    return array[start-1][end-1];
}

int MatrixGraph::getVertices() { //getter for vertices
    return vertices;
}

int MatrixGraph::getEdges() { //getter for edges
    return edges;
}

void MatrixGraph::setEdgeWeight(int start, int end, float weight) { //reassigns value at given vertices
    array[start-1][end-1] = weight; //reassign weight at given vertices

    if (!directed) { 
        array[end-1][start-1] = weight; //reassign weight at mirroring vertices if undirected
    }
}

string MatrixGraph::toString() { //returns string representation of graph
    ostringstream stream;

    for (int i = 1; i <= vertices; i++) {
        stream << "[" << setw(2) << i << "]:"; //leading title for each vertex

        for (int j = 1; j <= vertices; j++) { //for entire array within index
            if (array[i-1][j-1] != 0.0) {
                stream << "-->[" << setw(2) << i << "," << setw(2) << j //appends to for each edge
                       << "::" << setw(6) << fixed << setprecision(2) << array[i-1][j-1] << "]";
            }
        }

        stream << endl; //create new line for next vertex
    }
    return stream.str(); //return string of stream
}

void MatrixGraph::printRaw() { //prints 2d array directly
    cout << "Adjacency Matrix:\n\n";

    for (int i = 0; i < vertices; i++) { //for each vertex
        for (int j = 0; j < vertices; j++) { //for each index within each vertex
            cout << fixed << setprecision(2) << setw(7) << array[i][j]; //prints float value
        }
        cout << endl; //new line for next row
    }
}

bool MatrixGraph::pathExists(int start, int end) { //returns a boolean that represents if a path exists between two vertices

    start--; //modify values for 0 based indexing
    end--;

    bool* visited = new bool[vertices](); //initialize all values to false
    Queue<int> queue;

    queue.enqueue(start); //queue start vertex
    visited[start] = true; //mark start as visited

    while (!queue.isEmpty()) { //until no more edges are found
        int curr = queue.front(); //saves first item in queue
        queue.dequeue(); //removes first item

        for (int i = 0; i < vertices; i++) { //loops through sub array of current vertex
            if (array[curr][i] != 0.0 && !visited[i]) { //if edge is found and vertex is not visited
                if (i == end) { //returns true if end edge match is found
                    delete[] visited; //clean array
                    return true; 
                }
                queue.enqueue(i); //enqueue edges found connected from current item
                visited[i] = true; //mark vertex as visited
            }
        }
    }

    delete[] visited; //clean array
    return false; //defaults to false if path is not found
}

vector<int> MatrixGraph::getBFSPath(int start, int end) { //returns vector of path between two vertices

    start--; //modify values for 0 based indexing
    end--;

    bool* visited = new bool[vertices](); //initialize all values to false
    int* parent = new int[vertices]; //create array of parents to recontruct path

    for(int i = 0; i < vertices; i++) { //initialize all values in parent array to -1
        parent[i] = -1;
    }

    Queue<int> queue;
    queue.enqueue(start); //queue start vertex
    visited[start] = true; //mark start as visited
    bool pathFound = false; //path is not found by default

    while (!queue.isEmpty() && !pathFound) { //while queue is not empty and path is not found
        int curr = queue.front(); //save vertex at front of queue
        queue.dequeue(); //dequeue first item

        for (int i = 0; i < vertices; i++) { //loops through sub array of vertex
            if (array[curr][i] != 0.0 && !visited[i]) { //if edge is found and not visited yet
                parent[i] = curr; //mark current in parent array
                if (i == end) { //if end vertex is found
                    pathFound = true; //mark path as found
                    break; //end of loop
                }
                queue.enqueue(i); //queue edges found
                visited[i] = true; //mark vertexes as visited
            }
        }
    }

    vector<int> path; //instantiate vector for return

    if (pathFound) { //if path is found
        int curr = end; //starts at end of path
        while (curr != -1) { //loop until no parents are left
            path.insert(path.begin(), curr + 1); // insert parent incrementing by 1 for one based indexing
            curr = parent[curr]; //move to parent of current index
        }
    }

    delete[] visited; //clean arrays
    delete[] parent;

    return path; //return path vector
}

vector<int> MatrixGraph::getDijkstraPath(int start, int end) {
    if (start == end) { //return empty array if same start and end
        return vector<int>();
    }

    start--; //decrement for 0 based indexing
    end--;

    float* distance = new float[vertices]; //store distances from start to each vertex
    int* parent = new int[vertices]; //store parent vertices
    bool* visited = new bool[vertices](); //initialize all values to false
    bool pathFound = false; //defaults to false since path not found yet
   
    for(int i = 0; i < vertices; i++) { //initialize single source
        distance[i] = 999999; //v.d = inf
        parent[i] = -1; //v.pi = NIL
    }
    distance[start] = 0.0; //s.d = 0 since same starting node

    MinHeap priorityQueue;

    priorityQueue.enqueue(start, 0.0);

    while(!priorityQueue.isEmpty()) { //while vertexes still in heap
        int u = priorityQueue.peek().index; //looks at first item in heap
        priorityQueue.dequeue();
        if(visited[u]) continue; //continues only if not visited previously

        if (u == end) { //path is found if ending vertex is met
            pathFound = true;
        }

        visited[u] = true; //mark vertex as visited
        
        for (int i = 0; i < vertices; i++) { //for all edges adjacent to vertex
            if (array[u][i] != 0.0 && distance[i] > distance[u] + array[u][i]) { //relax
                distance[i] = distance[u] + array[u][i]; //reassign distance if shorter path
                parent[i] = u; //reassign parent
                priorityQueue.enqueue(i, distance[i]); //enqueue 
            }
        }
    }

    vector<int> path; //instantiate vector for return

    if (pathFound) { //if path is found
        int curr = end; //starts at end of path
        while (curr != -1) { //loop until no parents are left
            path.insert(path.begin(), curr + 1); // insert parent incrementing by 1 for one based indexing
            curr = parent[curr]; //move to parent of current index
        }
    }

    delete[] distance; //clean arrays
    delete[] parent;
    delete[] visited;

    return path;
}

vector<vector<int>> MatrixGraph::getDijkstraAll(int vertex) {
    vector<vector<int>> paths(vertices, vector<int>());
    for (int i = 0; i < vertices; i++) {
        paths[i] = getDijkstraPath(vertex, i + 1);
    }
    return paths;
}