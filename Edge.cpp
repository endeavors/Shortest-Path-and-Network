/************************************************************************
 * Name: Gurkirat Singh
 * Description: The cpp file for Edge. 
 ************************************************************************/

#include "Edge.hpp"

/* Function: Edge(Vertex *f, Vertex *t, unsigned int c, unsigned int l)
 * Description: Constructor for the Edge class.
 * Return value: None.
 */
Edge::Edge(Vertex *f, Vertex *t, unsigned int c, unsigned int l){
    from = f;
    to = t;
    cost = c;
    length = l;
}

/* Function: returnCost()
 * Description: Function that returns the cost of the edge.
 * Return value: Unsigned int to represent the cost of the edge.
 */
unsigned int Edge::returnCost(){
    return cost;
}

/* Function: operator< (const Edge & right)
 * Description: Override operator used for comparing the cost of edge.
 * Return value: None.
 */
bool Edge::operator< (const Edge & right) const{
    return cost > right.cost;
}
