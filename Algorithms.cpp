#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include <set>
#include <algorithm>
#include <vector>

#include "Graph.hpp"
#include "Algorithms.hpp"

#define DEF_MAX_INT std::numeric_limits<int>::max()
#define DEF_MAX_SIZE_T std::numeric_limits<size_t>::max()
#define TRUE 1
#define FALSE 0
#define NON_NEG_NUM 0
#define CONNECTED_FLAG -1
#define CYCLE_FLAG -2
#define SUCCESS "1"
#define FOUND_NOTHING "0"
#define FAIL "-1"



using ariel::Graph;
using std::string;
using std::vector;
using std::size_t;
using Matrix = std::vector<std::vector<int>>;

using namespace ariel;

Algorithms::Algorithms(){}

// This function is used to check if the graph is connected or not, and find shortest path to unweighted graphs.
string Algorithms::bfs(const Graph &graph, int start, int end) {
    Matrix myMatrix = graph.getMatrix(); // adjacency matrix
    size_t numVertices = myMatrix.size(); // number of rows or columns is the number of vertices
    size_t src, dest;
    string pathStr = "";
    bool connectedFlag = (start == CONNECTED_FLAG && end == CONNECTED_FLAG);
    bool cycleFlag = (start == CYCLE_FLAG && end == CYCLE_FLAG);
    bool shortPathFlag = (start >= 0 && end >= 0);  // Assuming NON_NEG_NUM is 0

    if (shortPathFlag) 
    {
        src = static_cast<size_t>(start);  // Casting to size_t after confirming start is non-negative
        dest = static_cast<size_t>(end);
    } 
    else if(connectedFlag || cycleFlag)
    {
        src = 0;
        dest = numVertices - 1;
    }
    else 
    {
        throw std::invalid_argument("Invalid input: The input is invalid.");
    }

    vector<bool> visited(numVertices, false);
    vector<size_t> parent(numVertices, DEF_MAX_SIZE_T);
    std::queue<size_t> queue;

    visited[src] = true;
    queue.push(src);

    while (!queue.empty()) 
    {
        size_t vertex = queue.front();  // Ensure vertex is size_t to match the type used in indexing
        queue.pop();

        if (vertex == dest && shortPathFlag) 
            break;

        for (size_t neighbor = 0; neighbor < numVertices; ++neighbor) 
        {
            if (myMatrix[vertex][neighbor] != 0 && !visited[neighbor]) 
            {
                visited[neighbor] = true;
                parent[neighbor] = vertex;
                queue.push(neighbor);
            } 

            if (myMatrix[vertex][neighbor] && neighbor != parent[vertex] && cycleFlag)
            {
                vector<int> cycle;
                for (size_t i = vertex; i != DEF_MAX_SIZE_T; i = parent[i]) 
                {
                    cycle.push_back(static_cast<int>(i));  // Cast to int if necessary for your system's logic
                }

                cycle.push_back(static_cast<int>(vertex));
                if (cycle.size() < 2) continue;

                pathStr += "The cycle is: ";
                for (size_t i = cycle.size() - 1; i != 0; i--)
                {
                    pathStr += std::to_string(cycle[i]) + "->";
                }
                
                pathStr = pathStr.substr(0, pathStr.length() - 2);
                std::cout << pathStr << std::endl;
                return pathStr;
            }
        }
    }



    // if we are checking if the graph is connected
    if(connectedFlag){
        for(size_t visit : visited) // Check if all vertices are being visited
        {
            if(!visit)
            {
                return FAIL; // There is a vertex that is not being visited so the graph is not connected
            }
        }
        return SUCCESS;
    }else{

        if(!visited[dest]){
            return FAIL;
        }

        std::vector<size_t> path;
        for(size_t at = dest; at != DEF_MAX_SIZE_T; at = parent[at]){
            path.push_back(at);
        }

        std::reverse(path.begin(), path.end());
        for (size_t i = 0; i < path.size(); ++i) {
            pathStr += std::to_string(path[i]);
            if (i < path.size() - 1)
            {
                pathStr += "->";
            }
        }
    }

    return pathStr.empty() ? FAIL : pathStr;
}



// Method to detect negative cycles using Bellman-Ford algorithm
string Algorithms::negCycleBF(const Graph &graph, int start, int end) 
{
    Matrix matrix = graph.getMatrix(); // adjacency matrix
    size_t numVertices = matrix.size(); // number of rows or columns is the number of vertices
    size_t src, dest;
    string strPath = "";
    size_t cycleFlag = (start == CYCLE_FLAG && end == CYCLE_FLAG );
    
    if(cycleFlag)
    {
        src = 0;
        dest = numVertices - 1;
    }
    else
    {
        src = static_cast<size_t>(start);
        dest = static_cast<size_t>(end);
    }

    vector<int> distance(numVertices, DEF_MAX_INT);
    vector<size_t> predecessor(numVertices, DEF_MAX_SIZE_T);
    distance[0] = 0;

    // Relax all edges |V| - 1 times
    for (size_t i = 0; i < numVertices - 1; ++i) 
    {
        for (size_t u = 0; u < numVertices; ++u) 
        {
            for (size_t v = 0; v < numVertices; ++v) 
            {
                if (matrix[u][v] != NON_NEG_NUM && distance[u] != DEF_MAX_INT && 
                    distance[u] + matrix[u][v] < distance[v]) 
                    
                {
                    distance[v] = distance[u] + matrix[u][v];
                    predecessor[v] = u;
                }
            }
        }
    }
    
    // If we are checking for negative cycle in the graph and not shortest path of weighted graph
    
    // Check for negative weight cycle one more time Relax all edges total |V| times.
    for (size_t verXTo = 0; verXTo < numVertices; ++verXTo) 
    {
        for (size_t verY = 0; verY < numVertices; ++verY) 
        {
            if (matrix[verXTo][verY] != NON_NEG_NUM && distance[verXTo] != DEF_MAX_INT &&
                distance[verXTo] + matrix[verXTo][verY] < distance[verY]) 
            {
                // Negative cycle detected. Reconstruct the cycle.
                if(!cycleFlag) return FAIL;
                vector<size_t> cycle;
                size_t cycleVertex = verY;

                do 
                {
                    cycle.push_back(cycleVertex);
                    cycleVertex = predecessor[cycleVertex];
                }
                while (cycleVertex != static_cast<int>(verY) && cycle.size() <= numVertices);
                
                cycle.push_back(verY);  // Close the cycle

                // Convert the cycle to a string
                size_t cycleSize = cycle.size();
                for (size_t i = --cycleSize ; i >= 0; --i) 
                {
                    strPath += std::to_string(cycle[i]) + "->";
                }
            }
        }
    }   
    
    if(cycleFlag)
    {
        for (size_t v = 0; v < numVertices; ++v) 
        {

            if (distance[v] != DEF_MAX_INT) 
            {
                vector<size_t> path;  // There is a path from the source to v
                for (size_t u = v; u != DEF_MAX_SIZE_T; u = predecessor[u]) 
                {
                    path.push_back(u);
                }

                std::reverse(path.begin(), path.end());  // Reverse the path to get it from source to v
                for (int u : path) // Convert the path to a string
                {
                    strPath += std::to_string(u) + "->";
                }
            }
        }
    }

    return strPath.empty() ? FAIL : strPath;
}


// This function is used to check if the graph is connected or not.
bool Algorithms::isConnected(const Graph &graph)
{
    Matrix myMatrix = graph.getMatrix(); // adjacency matrix

    size_t numVertices = myMatrix.size(); // number of rows or columns is the number of vertices

    if(numVertices < 2)
    {
        return TRUE;
    }

    // BFS
    int isGraphConnected = bfs(graph, CONNECTED_FLAG , CONNECTED_FLAG).compare(FAIL);
    
    return isGraphConnected; 
}

// This function is used to find the shortest path between two vertices in the graph.
string Algorithms::shortestPath(const Graph &graph, size_t src, size_t dest){
    if(src >= graph.getMatrix().size() || dest >= graph.getMatrix().size())
    {
        return FAIL;
    }
    
    std::string pathStr;
    
    if( !(graph.getIsWeightedGraph()) ) // if its not weighted graph run BFS
    {
        int source = static_cast<int>(src);
        int destination = static_cast<int>(dest);
        pathStr = bfs(graph, source, destination);
        return pathStr;
    }

    // if its weighted graph run Bellman-Ford algorithm to find shortest path
    // if there is a negative cycle it return -1, else it return the path.
    pathStr = negCycleBF(graph, src, dest);
    return pathStr;
}

// this function is used to find if the graph contains a cycle or not. and return the cycle if exist            
bool Algorithms::isContainsCycle(const Graph &graph){
        
        string strCycle = bfs(graph, CYCLE_FLAG, CYCLE_FLAG);
        bool containCycle = false;
        
        if(strCycle.compare(FAIL) != 0)
        {
            containCycle = true;
            //strCycle = FOUND_NOTHING; //Tests want bool demo wants string need to be checked.
        }
        
        return containCycle;
        
    }
    
string Algorithms::isBipartite(const Graph &graph)
{
    Matrix myMatrix = graph.getMatrix();
    size_t numVertices = myMatrix.size();
    std::vector<size_t> colors(numVertices, DEF_MAX_SIZE_T);
    std::vector<size_t> A, B;  // Add vectors to store the vertices of each set
    std::queue<size_t> queue;
    for (size_t start = 0; start < numVertices; ++start) {
        if (colors[start] == DEF_MAX_SIZE_T) {
            colors[start] = 0;
            queue.push(start);

            while (!queue.empty()) {
                size_t u = queue.front();
                queue.pop();

                for (size_t v = 0; v < numVertices; ++v) {
                    if (myMatrix[u][v] && colors[v] == DEF_MAX_SIZE_T) {
                        colors[v] = 1 - colors[u];
                        queue.push(v);
                    } else if (myMatrix[u][v] && colors[v] == colors[u]) {
                        return FOUND_NOTHING;
                    }
                }
            }
        }
    }

    // Separate the vertices into two sets based on their colors
    for (size_t i = 0; i < numVertices; ++i) {
        if (colors[i] == 0) {
            A.push_back(i);
        } else if (colors[i] == 1) {
            B.push_back(i);
        }
    }

    // Convert the sets to strings
    string A_str = "A={";
    for (size_t i : A) {
        A_str += std::to_string(i) + ", ";
    }
    A_str = A_str.substr(0, A_str.length() - 2) + "}";  // Remove the last comma and space, and add a closing brace

    string B_str = "B={";
    for (size_t i : B) {
        B_str += std::to_string(i) + ", ";
    }
    B_str = B_str.substr(0, B_str.length() - 2) + "}";  // Remove the last comma and space, and add a closing brace

    return "The graph is bipartite: " + A_str + ", " + B_str;
}

// This function is used to check if there is a negative cycle in the graph and return the proper string.
string Algorithms::negativeCycle(const Graph &graph)
{
    string strNegCycle = negCycleBF(graph, CYCLE_FLAG, CYCLE_FLAG);
    
    if(strNegCycle.compare(FAIL) == 0)
    {
        return "There is no negative cycle in the graph.";
    }
    
    else
    {
        return strNegCycle;
    }
}

