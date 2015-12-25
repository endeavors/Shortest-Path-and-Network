/************************************************************************
 * Name: Gurkirat Singh 
 * Description: The cpp file for Vertex class. 
 ************************************************************************/

#include "Vertex.hpp"
#include "UndirectedGraph.hpp"
#include "Vertex.hpp"

/* Function: :Vertex(const string &name)
 * Description: Constructor for the Vertex class. Set the name of the 
 *              Vertex.
 * Return value: None.
 */
Vertex::Vertex(const string &name):name(name){}

/* Function: addEdgeToMap(string vtxName, Edge edge)
 * Description: Function that attach a new edge to the map of vertex.
 * Return value: None.
 */
void Vertex::addEdgeToMap(string vtxName, Edge edge){
    edges.emplace(vtxName, edge);

} 

/* Function: vertexTotalCost()
 * Description: Function that adds up the total value of costs
 *              within the vertex's map.
 * Return value: int that represents the total costs of the 
 *               vertex.
 */
int Vertex::vertexTotalCost(){
    int ttlCost = 0;

    /* Iterate through the map */
    for (auto item : edges){
        /* For each edge, add the cost to ttlCost */
	Edge ed = item.second;
        ttlCost += ed.returnCost();
    } 
    return ttlCost;
}
