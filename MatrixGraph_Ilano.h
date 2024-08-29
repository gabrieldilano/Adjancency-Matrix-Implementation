/*
Author: Gabriel Ilano
Date: 4/19/24
Description: Declarations for the Matrix Graph Class with Dijkstra declarations
*/

#ifndef MATRIXGRAPH_ILANO_H
#define MATRIXGRAPH_ILANO_H
#include <vector>
#include <string>
#include <stdexcept>
using namespace std;

class MatrixGraph {
private: //variable declarations
    float** array;
    int vertices;
    int edges;
    bool directed;

public: //method declarations
    MatrixGraph(int vertices, bool directed);
    ~MatrixGraph();
    void addEdge(int start, int end, float weight);
    void removeEdge(int start, int end);
    bool adjacent(int start, int end);
    float getEdgeWeight(int start, int end);
    int getVertices();
    int getEdges();
    void setEdgeWeight(int start, int end, float weight);
    string toString();
    void printRaw();
    bool pathExists(int start, int end);
    vector<int> getBFSPath(int start, int end);
    vector<int> getDijkstraPath(int start, int end);
    vector<vector<int>> getDijkstraAll(int vertex);
};
#endif