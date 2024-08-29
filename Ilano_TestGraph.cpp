/*
Author: Gabriel Ilano
Date: 4/19/24
Description: Contains main function and logic for Matrix Graph implementation with Dijkstra functionality
*/

#include "MatrixGraph_Ilano.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

void printMenu() { //prints menu of choices and operations
    cout << "Welcome to the Graph tester!\n"
         << "1) Print the graph\n"
         << "2) Find a BFS path\n"
         << "3) Find a Single Dijkstra Path\n"
         << "4) Find all Dijkstra Paths from a start\n"
         << "5) Start a file\n"
         << "6) Add a BFS path to the file\n"
         << "7) Add single Dijkstra Path to file\n"
         << "8) Add all Dijkstra Paths from a start\n"
         << "0) Quit\n";
}

string findPath(MatrixGraph& graph) { //returns string based on path between given vertices
    int start;
    int end;
    stringstream result;

    cin >> start >> end; //get user input of vertices

    if (!graph.pathExists(start, end)) { //prints error message if no path is found between given vertices
        result << "No BFS path from " << start << " to " << end << "." << endl;
    } else {
        result << "BFS path from " << start << " to " << end << " is:" << endl;
        vector<int> path = graph.getBFSPath(start, end); //generate vector of path between vertices

        result << "[" << setw(2) << path[0] << ":" << setw(6) << fixed << setprecision(2) << 0.00 << "]"; //append the first vertex (always has value of 0.0)

        float weight = 0.0;

        for (int i = 1; i < static_cast<int>(path.size()); i++) { //append remaining vertices to string (static cast is to convert unsigned long int to int)
            weight += graph.getEdgeWeight(path[i-1], path[i]); //add edge weight to total weight
            result << "==>[" << setw(2) << path[i] << ":" << setw(6) << fixed << setprecision(2) << weight << "]"; //append vertex to stream

        }
        result << endl;
    }
    string string = result.str(); //convert stream to string
    return string;
}

void startFile(MatrixGraph& graph, string filename, bool weighted) { //writes to file 
    ofstream outputFile(filename); //open output file stream

    outputFile << graph.getVertices() << " " << graph.getEdges() << endl; //places vertex and edge count at header

    if (weighted) { //weighted graph formatting
        for (int i = 1; i <= graph.getVertices(); i++) {
            for (int j = 1; j <= graph.getVertices(); j++) {
                if (graph.getEdgeWeight(i,j) != 0.0) {
                    outputFile << i << " " << j << " " << fixed << setprecision(6) << graph.getEdgeWeight(i, j) << endl; //creates line for each edge
                }
            }
        }
    } else { //unweighted graph formatting
        for (int i = 1; i <= graph.getVertices(); i++) {
            for (int j = 1; j <= graph.getVertices(); j++) {
                if (graph.getEdgeWeight(i,j) != 0.0) {
                    outputFile << i << " " << j << endl; //creates line for each edge
                }
            }
        }
    outputFile.close(); //close file
    }
}

string dijkstraSingle(MatrixGraph& graph) { //returns dijkstra path between two given vertices within a string
    int start;
    int end;
    stringstream result;

    cin >> start >> end; //get user input of vertices

    vector<int> path = graph.getDijkstraPath(start, end); //generate vector of path between vertices

    if (path.empty()) { //prints error message if no path is found between given vertices
        result << "No DIJKSTRA path from " << start << " to " << end << "." << endl;
    } else {
        result << "DIJKSTRA path from " << start << " to " << end << " is:" << endl;

        result << "[" << setw(2) << path[0] << ":" << setw(6) << fixed << setprecision(2) << 0.00 << "]"; //append the first vertex (always has value of 0.0)

        float weight = 0.0;

        for (int i = 1; i < static_cast<int>(path.size()); i++) { //append remaining vertices to string (static cast is to convert unsigned long int to int)
            weight += graph.getEdgeWeight(path[i-1], path[i]); //add edge weight to total weight
            result << "==>[" << setw(2) << path[i] << ":" << setw(6) << fixed << setprecision(2) << weight << "]"; //append vertex to stream

        }
        result << endl;
    }
    string string = result.str(); //convert stream to string
    return string;
}

string dijkstraAll(MatrixGraph& graph) { //returns dijkstra paths to all vertices of a given vertex within a string
    int vertex;
    stringstream result;

    cin >> vertex; //collect user input of vertex

    vector<vector<int>> paths = graph.getDijkstraAll(vertex); //generate vector of vectors to all vertices

    for (int i = 1; i <= graph.getVertices(); i++) { //for each vertex
        if (i == vertex) { //prints distinguishing message if matching the input vertex
            result << "DIJKSTRA Paths start at Vertex " << vertex << endl;
        } else { //for every other vertex
            result << "Path to " << i << ": ";
                if (paths[i-1].empty()) { //prints error message if no path is found between given vertices
                    result << "No DIJKSTRA path from " << vertex << " to " << i << endl;
                } else {
                    result << "[" << setw(2) << paths[i-1][0] << ":" << setw(6) << fixed << setprecision(2) << 0.00 << "]"; //append the first vertex (always has value of 0.0)

                    float weight = 0.0; //initialize weight of path to 0

                    for (int j = 1; j < static_cast<int>(paths[i-1].size()); j++) { //append remaining vertices to string (static cast is to convert unsigned long int to int)
                        weight += graph.getEdgeWeight(paths[i-1][j-1], paths[i-1][j]); //add edge weight to total weight
                        result << "==>[" << setw(2) << paths[i-1][j] << ":" << setw(6) << fixed << setprecision(2) << weight << "]"; //append vertex to stream

                    }
                    result << endl;
                }
        }
    }
    string string = result.str(); //convert stream to string
    return string;
}


int main(int argc, char* argv[]) {

    string arg1 = argv[1]; //
    string filePath = argv[2]; //collect file path name
    bool weighted = true; //weighted by default
    bool directed = true; //directed by default
    
    if (arg1 == "-u") { //sets weighted boolean based on first argument
        weighted = false;
    }

    if (argc == 4) { //sets directed to true if [-ud] argument is present
        directed = false;
    }

    ifstream file(filePath); //create input file stream
    string line;
    getline(file, line); //gets line at file
    stringstream stream (line); //opens stream at line

    int vertices;
    int edges;

    stream >> vertices >> edges; //collects vertex and edge count from file

    MatrixGraph graph = MatrixGraph(vertices, directed); //constructor for graph

    int start; //instance variables for collecting data from file
    int end;
    float weight;

    if (weighted) { //if weighted
        for (int i = 0; i < edges; i++) {
            file >> start >> end >> weight; //collects start end and weight
            graph.addEdge(start, end, weight); //creates edge
        }

    } else { //if unweighted
        for (int i = 0; i < edges; i++) {
            file >> start >> end; //collects start and end
            graph.addEdge(start, end, 1); //creates edge
        }
    }
    file.close(); //closes file

    int choice;
    string filename;

    do {
        printMenu();
        cin >> choice;

        switch (choice) {
            case 1:
                cout << graph.toString(); //prints graph
                break;
            case 2:
                cout << findPath(graph); //prints path between given vertices
                break;
            case 3:
                cout << dijkstraSingle(graph); //prints single Dijkstra path between two vertices
                break;
            case 4:
                cout << dijkstraAll(graph); //prints Dijkstra path to all vertices with a given vertex
                break;
            case 5:
                cin >> filename; //collects file name
                startFile(graph, filename, weighted); //creates new file
                break;
            case 6:
                if (filename.empty()) { //sends error message if no file is created
                    cout << "No file has been created yet." << endl;
                } else {
                    ofstream outputFile(filename, ios::app); //opens file
                    outputFile << findPath(graph); //appends path to file
                    outputFile.close(); //close file
                }
                break;
            case 7:
                if (filename.empty()) { //sends error message if no file is created
                    cout << "No file has been created yet." << endl;
                } else {
                    ofstream outputFile(filename, ios::app); //opens file
                    outputFile << dijkstraSingle(graph); //appends path to file
                    outputFile.close(); //close file
                }
                break;
            case 8:
                if (filename.empty()) { //sends error message if no file is created
                    cout << "No file has been created yet." << endl;
                } else {
                    ofstream outputFile(filename, ios::app); //opens file
                    outputFile << dijkstraAll(graph); //appends all paths to file
                    outputFile.close(); //close file
                }
                break;
            case 9999:
                graph.printRaw(); //prints raw 2d array of graph
                break;
            default:
                if (choice != 0) cout << "Invalid option. Please try again.\n"; //error message if option not listed
                break;
        }
    } while (choice != 0); //loops ends when user inputs 0 to quit
    return 0;
}
