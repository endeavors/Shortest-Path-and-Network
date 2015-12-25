/************************************************************************
 * Name: Gurkirat Singh
 * Description: This class represents an undirected graph where a double
 *              edge is created between two vertices. It implements the
 *              Dikjstra algorithm to find the shortest path in the 
 *              original graph and also creates a minimum spanning tree
 *              that allocates memory from its own vertices. Prim's
 *              algorithm is used to create the MST.
 ***********************************************************************/

#include <limits>
#include <queue>
#include "UndirectedGraph.hpp"
#include "Edge.hpp"
#include "Vertex.hpp"

/* Function: UndirectedGraph
 * Desciption: The constructor of graph class that doesn't do anything
 * Return value: None.
 */
UndirectedGraph::UndirectedGraph(void){
}

/* Function: checkVertex()
 * Description: Checks if the vertex is already in the graph
 * Return value: pointer to the vertex if the vertex already exists
 *               or nullptr
 */
Vertex* UndirectedGraph::checkVertex(string vertexName){
    
    //see if the key has a value or nullptr
    Vertex * rtnVertex = vertices[vertexName];
    return rtnVertex;
}

/* Function: add
 * Description: Add a new vertex pointer to the graph map that contains
 *              all the vertices
 * Return value: None
 */
void UndirectedGraph::add(Vertex* start){
    
    //map vertex name to its vertex pointer
    vertices[start->name] = start;
}

/* Function: getVertexMap
 * Description: Returns the entire unordered map since vertices variable
 *              is private and we want to make least information public
 *              as possible
 * Return value: unordered map
 */ 
unordered_map<string, Vertex*> UndirectedGraph::getVertexMap(){
    return vertices;
}

/* Function: totalCost()
 * Description: Calculate the total cost of the graph by going through
 *              each vertex and adding its cost
 * Return: The total cost of the graph (int)
 */
int UndirectedGraph::totalCost(){
    
    int ttlCost = 0;

    /* Go through each vertex and add its total cost to the variable*/
    for(auto item : vertices){
        ttlCost += item.second->vertexTotalCost(); 
    }

    //Divide by 2 since we have double edges between two vertices
    ttlCost = ttlCost/2;

    return ttlCost;
    
}

/* Function: buildGraph()
 * Description: Build the graph by first checking if the vertex is in the graph
 *              and allocating space on the heap. All edges are kept on the stack
 *              and double edges are used since we have an undirected graph. This
 *              function takes care of mapping all vertices and edges.
 * Return: None
 */
void UndirectedGraph::buildGraph(string vertex1, string vertex2,\
    int cost, int length){
    
    Vertex *start;
    Vertex *end;

    //check if vertex is already in the graph
    Vertex *returnedVtx = checkVertex(vertex1);

    //vertex is in the graph, so just return the pointer to it
    if(returnedVtx != nullptr) start = returnedVtx;
    else{

        //create a new vertex and add it to the graph
        start = new Vertex(vertex1);
        add(start);
    }
    
    //check if the second vertex is in the graph
    returnedVtx = checkVertex(vertex2);
    if (returnedVtx != nullptr) end = returnedVtx;
    else{

        //add vertex to the graph
        end = new Vertex(vertex2);
        add(end);
    }

    //create double edges since it's an undirected graph
    Edge startToEnd(start, end, cost, length);
    Edge endToStart(end, start, cost, length);

    //map the edges to their corresponding vertex names
    start->addEdgeToMap(vertex2,startToEnd);
    end->addEdgeToMap(vertex1, endToStart);

}

/* Function: buildMST
 * Description: Build the MST by creating a new graph with its own set of vertices.
 *              Prim's algorithm is used where you keep going through a vertex's 
 *              edges until all vertices are visited.
 * Return: MST graph we created
 */
UndirectedGraph UndirectedGraph::buildMST(){
    
    UndirectedGraph MSTGraph;
    priority_queue<Edge> queue;
    //copy the map of the original graph to the MST graph
    unordered_map<string, Vertex*> inGraphMap = vertices;

    //set all vertices' visited to false 
    for (auto vertex: inGraphMap){
        vertex.second->visited = false;
    }
   
    Vertex *startVtx = inGraphMap.begin()->second;

    //push all adjacent vertices to the queue
    for (auto edge: startVtx->edges){
        queue.push(edge.second);
    }
    startVtx->visited = true;
   
    while(!queue.empty()){
        //get the top element in the priority queue
        Edge edge = queue.top();
        queue.pop();

        if (edge.to->visited) continue;
        else edge.to->visited = true;
        
        //add vertices and edges to the new MST graph
        MSTGraph.buildGraph(edge.from->name, edge.to->name, edge.cost,
            edge.length);

        //add all the possible edges of the current vertex to the queue
        for (auto neighborEdge : edge.to->edges){
            queue.push(neighborEdge.second);
        }
             
    }
    
    return MSTGraph;
}

/* Function: getShortestPath()
 * Description: Get the shortest path for each vertex in the graph. This
 *              function implements the Dikjstra algorithm and is called
 *              by both the original graph and the MST graph 
 * Return: The total cost in finding the shortest path in the graph
 */
unsigned int UndirectedGraph::getShortestPath(){

    unsigned int ttlCost = 0;
    unsigned int graphSize = vertices.size();

    //create a custom priority queue so that can compare two pairs
    priority_queue<pair<Vertex*,unsigned int>, vector<pair<Vertex*,\
        unsigned int>>,DijkstraVertexComparator> queue;

    for (auto item: vertices){

        //reset distance and done flag for each vertex in the graph
        for (auto i: vertices){
            Vertex *tempVtx = i.second;
            tempVtx->distance = numeric_limits<int>::max();
            tempVtx->done = false;
        }
       
        //the starting vertex distance is always set to 0
        Vertex * startVtx = item.second;
        startVtx->distance = 0;
        unsigned int vtxCost = 0;
        unsigned int vtxCounter = 0;
   
        //create a new pair with the vertex pointer that it is pointing to
        //and its score and push it to the queue
        pair<Vertex*,unsigned int> vertexPair = make_pair(startVtx,0);
        queue.push(vertexPair);
        
        while (!queue.empty()){
            pair<Vertex*,unsigned int> topPair = queue.top();
            queue.pop();

            Vertex *topVtx = topPair.first;

            if (topVtx->done == true) continue;
            else topVtx->done = true; //we found the shortest path to topPair
            
            //increment counter to show that we visited a node
            //keeps track of if all nodes were successfully reached or not
            vtxCounter++;

            vtxCost = vtxCost + topPair.second;

            /* For each of the edges that haven't been visited, add their totalcost
               and update them to their corresponding vertices*/

            for(auto edgeItem: topPair.first->edges){
                if (edgeItem.second.to->done == false){
                    unsigned int edgeCost = topPair.second + edgeItem.second.length;
                    
                    //only update if the calculated cost is less than the one already
                    //there
                    if (edgeCost < edgeItem.second.to->distance){
                        
                        //push the updated vertex pair and score to the queue
                        edgeItem.second.to->distance = edgeCost;
                        pair<Vertex*,unsigned int> newPair = make_pair\
                            (edgeItem.second.to, edgeCost);
                        queue.push(newPair);
                    }
                }
            }  
        } 
        
        ttlCost += vtxCost;
        
        //if the graph is not connected, break out and return infinity
        if (vtxCounter != graphSize){
            ttlCost = numeric_limits<int>::max();
            break;
        }
    } 
   
    return ttlCost;

}

/* Function: ~UndirectedGraph()
 * Description: The Destructor for the undirected graph. Deallocates all memory 
 *              for the vertices
 * Return: None
 */
UndirectedGraph::~UndirectedGraph(){
    
    //Go through the vertices map and delete each vertex one by one
    for(auto vertex: vertices){
        delete vertex.second;
    }
}

/* Function: operator()
 * Description: Overloading to compare two pairs in the queue. We want the pair
 *              with the lower score to have a higher priority
 * Return: True if A is less than B
 */
bool UndirectedGraph::DijkstraVertexComparator::operator()\
    (const std::pair<Vertex*, unsigned int> &left, const std::pair<Vertex*,\
     unsigned int> &right){
    return left.second > right.second; 
}
