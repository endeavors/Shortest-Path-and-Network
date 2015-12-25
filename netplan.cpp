/************************************************************************
 * Name: Gurkirat Singh 
 * Description: The main method for netplan. 
 ************************************************************************/

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>
#include <thread>
#include "Vertex.hpp"
#include "Edge.hpp"
#include "UndirectedGraph.hpp"

/**
 * Entry point into the netplan program.
 *
 * Usage:
 *   ./netplan infile
 *
 */

using namespace std;

/* Function: main()
 * Description: The main method of netplan. Prints out 6 lines of
 *              ints to represent 6 different values of the graph.
 * Return value: int.
 */
int main (int argc, char *argv[]){
    
    /* Check to see if the input argument is valid */
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " infile" << endl;
        return EXIT_FAILURE;
    }
    
    std::ifstream in(argv[1]);
    if (!in) {
        cerr << "Unable to open file for reading." << endl;
        return EXIT_FAILURE;
    }

    UndirectedGraph graph;    
    string vertex1;
    string vertex2;
    int cost;
    int length;
    unsigned int totalCost = 0;
    unsigned int shortestPath = 0;
    unsigned int ttlCostMST = 0;
    unsigned int shortestPathMST = 0;
    
    /* Begin to read from the file */
    while(  in.good () ){
        /* Assign values for buildGraph() function */
        in >> vertex1;
        in >> vertex2;
        in >> cost;
        in >> length;         

        if (!in.good()) break;
        /* Call the buildGraph() to populate the graph */
        graph.buildGraph(vertex1, vertex2, cost, length);

    }
    
    in.close();
    
    /* Calculate the printout int. */
    /* If the map is not empty... */
    if (graph.getVertexMap().size() != 0){
        /* Increment the value of totalCost by calling totalCost() on
 	 * each vertecies. */
        totalCost = graph.totalCost();
	/* Increment the value of shortestPath by calling getShortestPath() on
 	 * the graph. */
        shortestPath = graph.getShortestPath();
     
	/* Check to make sure the graph is connected */
        if (shortestPath == numeric_limits<int>::max()){
            cerr << "Graph is not connected." << endl;
            return EXIT_FAILURE;
        }
        
        /* Build MST */
        UndirectedGraph mstGraph = graph.buildMST(); 
        
        /* Repeat the same calculation for the MST */
        ttlCostMST = mstGraph.totalCost();
        shortestPathMST = mstGraph.getShortestPath();
    }

    /* Printing out the ints */
    cout << totalCost << endl;
    cout << ttlCostMST << endl;
    cout << totalCost - ttlCostMST << endl;
    cout << shortestPath << endl;
    cout << shortestPathMST << endl;
    cout << shortestPathMST - shortestPath << endl;
    

    return EXIT_SUCCESS;
}
