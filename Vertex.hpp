/************************************************************************
 * Name: Gurkirat Singh
 * Description: The header file for Vertex. 
 ************************************************************************/

#ifndef VERTEX_HPP
#define VERTEX_HPP

#include <iostream>
#include <limits>
#include <string>
#include <unordered_map>

#include "Edge.hpp"

using namespace std;
/**
 * Represents a Vertex in a graph.
 *
 * Vertices are connected to other Vertices via Edges. Each Vertex
 * maintains a collection of all Edges that originate from it.
 */
class Vertex {
  // Graph needs access to Edge map for Dijkstra/Prim algorithms.
  friend class UndirectedGraph;

  public:
    /*
     * The vertex number of the previous node
     */
    int prev;

    /*
     * Distance of this Vertex from initial Vertex.
     * Used by Dijkstra's algorithm.
     */
    unsigned int distance;
    
    /*
     * Initialize the Vertex with the given name.
     */
    Vertex(const std::string &name);

    /*
     * Function that attach an edge to the map.
     */
    void addEdgeToMap(string vtxName, Edge edge);

    /*
     * Function that returns the total edge copst of the vertex.
     */
    int vertexTotalCost(); 

    /* Map of adjacent Vertex name to Edge describing the adjacency */
    std::unordered_map<std::string, Edge> edges;

  private:

    /*
     * Name of this Vertex.
     */
    std::string name;

    /*
     * To check if we are done visited the vertex
     */
    bool done;
    
    /*
     * Whether this node has been visited.
     * Used by Prim's algorithm.
     */
    bool visited;

};

#endif
