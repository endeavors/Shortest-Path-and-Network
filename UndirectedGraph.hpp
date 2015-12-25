/*************************************************************************
 * Name: Gurkirat Singh
 * Description: Header file for undirected graph that has double edges
 *              and pointers to vertices, which are allocated on the heap.
 *              It builds the MST using Prim's algorithm.
 ************************************************************************/

#ifndef UNDIRECTEDGRAPH_HPP
#define UNDIRECTEDGRAPH_HPP

#include <string>
#include <unordered_map>

#include "Vertex.hpp"

/**
 * Implements an undirected graph. Any edge in the graph
 * represents a bidirectional connection between two vertices.
 * 
 * Implements methods for producing a minimum spanning tree of the
 * graph, as well as calculating the total length of the shortest
 * paths between each pair of vertices.
 */
class UndirectedGraph {
  public:
    /*Constructs an empty UndirectedGraph with no vertices and no edges. */
    UndirectedGraph();

    /* Destructs an UndirectedGraph. */
    ~UndirectedGraph();

    /* Check if vertex alredy exists in the graph */
    Vertex* checkVertex(string vertexName);
    
    /* Add vertex to the map */
    void add(Vertex * vertex);

    /* buildMST() calls buildGraph to create new vertices and edges. This
    function takes cares of mapping all edges and vertices and initializing
    and allocating memory for them */
    void buildGraph(string vertex1, string vertex2, int cost, int length);

    /* Build the MST separately from the original graph, so that it has its
    own vertices and edges allocated */
    UndirectedGraph buildMST();
    
    /* Calculate the total cost of the entire graph */
    int totalCost();
  
    /* Running Dijstra's Algorithm */
    unsigned int getShortestPath();
    
    /* Return all the vertices in the graph */
    unordered_map<string, Vertex*> getVertexMap();
  private:
    /*Comparison functor for use with Dijkstra's algorithm. Allows Vertices
      to be added to a priority queue more than once, with different weights.
     */
    class DijkstraVertexComparator {
      public:
        bool operator()(const std::pair<Vertex*, unsigned int> &left,
                const std::pair<Vertex*, unsigned int> &right);
    };
    
    /* Map of vertex name to Vertex */
    std::unordered_map<std::string, Vertex*> vertices;
};

#endif
