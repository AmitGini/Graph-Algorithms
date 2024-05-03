#include <iostream>
#include <string>
#include <queue>
#include <climits>
#include <set>
#include <algorithm>

#include "Graph.hpp"
#include "Algorithms.hpp"



using ariel::Graph;
using std::string;
using std::vector;
using std::size_t;

#define FOUND_NOTHING "0"
#define FAIL "-1"
#define DEF_VALUE -1
#define CONNECTED_FLAG -1
#define CYCLE_FLAG -2

using namespace ariel;

Algorithms::Algorithms(){}

// This function is used to check if the graph is connected or not, and find shortest path to unweighted graphs.
string Algorithms::bfs(const Graph &graph, int start, int end) {
    Matrix myMatrix = graph.getMatrix(); // adjacency matrix
    size_t numVertices = myMatrix.size(); // number of rows or columns is the number of vertices
    int src, dest;
    string pathStr = "";
    bool connectedFlag = (start == CONNECTED_FLAG && end == CONNECTED_FLAG);
    bool cycleFlag = (start == CYCLE_FLAG && end == CYCLE_FLAG);
    bool shortPathFlag = !(shortPathFlag || cycleFlag);

    if(shortPathFlag)
    {
        src = start;
        dest = end;
    }
    else
    {
        src = 0;
        dest = numVertices - 1;
    }
    
    vector<bool> visited(numVertices, false);
    vector<int> parent(numVertices, DEF_VALUE);
    std::queue<int> queue;

    visited[src] = true;
    queue.push(src);

    while(!queue.empty())
    {
        int vertex = queue.front();
        queue.pop();

        // if we found the destination vertex and we dont want to check if graph is connected
        if(vertex == dest && shortPathFlag) 
            break;

        for(size_t neighbor = 0; neighbor < numVertices; ++neighbor) // iterate over all neighbers vertices
        { 
            if(myMatrix[vertex][neighbor] != 0 && !visited[neighbor]) // if there is an edge between vertex and i
            { 
                visited[neighbor] = true;
                parent[neighbor] = vertex;
                queue.push(neighbor);
            }

            // if Cycle flag is true, check if there is a cycle in the graph
            else if (myMatrix[vertex][neighbor] && 
                    neighbor != parent[vertex] && cycleFlag) 
            {
                // Cycle detected. Reconstruct the cycle.
                vector<int> cycle;
                
                for (size_t i = vertex; i != DEF_VALUE; i = parent[i]) 
                {
                    cycle.push_back(i);
                }
                cycle.push_back(vertex);  // Close the cycle
                if(cycle.size() < 2) continue; // if the cycle is less than 2 vertices, continue to the next neighbor
                
                pathStr += "The cycle is: ";
                // Convert the cycle to a string
                for (size_t i = cycle.size() - 1; i >= 0; --i) 
                {
                    pathStr += std::to_string(cycle[i]) + "->";
                }

                pathStr = pathStr.substr(0, pathStr.length() - 2);  // Remove the last arrow
                pathStr += " ";
            }
        }
    }

    if(cycleFlag) return pathStr;

    // if we are checking if the graph is connected
    if(connectedFlag){
        for(bool visit : visited) // Check if all vertices are being visited
        {
            if(!visit)
            {
                return FAIL; // There is a vertex that is not being visited so the graph is not connected
            }
        }

    }

    if(!visited[dest]){
        return FAIL;
    }

    std::vector<int> path;
    for(size_t at = dest; at != DEF_VALUE; at = parent[at]){
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

    return pathStr.empty() ? FAIL : pathStr;
}



// Method to detect negative cycles using Bellman-Ford algorithm
string Algorithms::negCycleBF(const Graph &graph, int start, int end) 
            {
                Matrix matrix = graph.getMatrix(); // adjacency matrix
                size_t numVertices = matrix.size(); // number of rows or columns is the number of vertices
                int src, dest;
                string strPath = "";
                bool searchShortestPath = (start != CONNECTED_FLAG && end != CONNECTED_FLAG );
                
                if(searchShortestPath)
                    {
                        src = start;
                        dest = end;
                    }
                else
                    {
                        src = 0;
                        dest = numVertices - 1;
                    }

                vector<int> distance(numVertices, INT_MAX);
                vector<int> predecessor(numVertices, DEF_VALUE);
                distance[0] = 0;

                // Relax all edges |V| - 1 times
                for (size_t i = 0; i < numVertices - 1; ++i) 
                {
                    for (size_t u = 0; u < numVertices; ++u) 
                    {
                        for (size_t v = 0; v < numVertices; ++v) 
                        {
                            if (matrix[u][v] != INT_MAX && distance[u] != INT_MAX && 
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
                for (size_t u = 0; u < numVertices; ++u) 
                {
                    for (size_t v = 0; v < numVertices; ++v) 
                    {
                        if (matrix[u][v] != INT_MAX && distance[u] != INT_MAX &&
                            distance[u] + matrix[u][v] < distance[v]) 
                        {
                            // Negative cycle detected. Reconstruct the cycle.
                            if(searchShortestPath) return FAIL;
                            vector<int> cycle;
                            int cycleVertex = v;

                            do 
                            {
                                cycle.push_back(cycleVertex);
                                cycleVertex = predecessor[cycleVertex];
                            } 
                            while (cycleVertex != v);
                            
                            cycle.push_back(v);  // Close the cycle

                            // Convert the cycle to a string
                            for (size_t i = cycle.size() - 1; i >= 0; --i) 
                            {
                                strPath += std::to_string(cycle[i]) + "->";
                            }
                        }
                    }
                }   
                
                if(searchShortestPath)
                {
                    for (size_t v = 0; v < numVertices; ++v) 
                    {
                        #include <algorithm>

                        if (distance[v] != INT_MAX) 
                        {
                            vector<int> path;  // There is a path from the source to v
                            for (size_t u = v; u != DEF_VALUE; u = predecessor[u]) 
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
            
// This function is used to check if the graph contains a cycle or not.
bool Algorithms::isCycleUtil(int v, std::vector<bool>& visited, 
                        std::vector<bool>& recursionStack, const Matrix& myMatrix) 
            {
                visited[v] = true;
                recursionStack[v] = true;

                for (size_t u = 0; u < myMatrix.size(); ++u) {
                    if (myMatrix[v][u]) {
                        if (!visited[u] && isCycleUtil(u, visited, recursionStack, myMatrix)) {
                            return true;
                        } else if (recursionStack[u]) {
                            return true;
                        }
                    }
                }

                recursionStack[v] = false;
                return false;
            }

// This function is used to check if the graph is connected or not.
bool Algorithms::isConnected(const Graph &graph)
            {
                Matrix myMatrix = graph.getMatrix(); // adjacency matrix

                if(myMatrix.empty())
                {
                    return true;
                }

                size_t numVertices = myMatrix.size(); // number of rows or columns is the number of vertices
                
                if(numVertices == 0 || numVertices == 1)
                {
                    return true;
                }

                // BFS
                bool isGraphConnected = bfs(graph, CONNECTED_FLAG , CONNECTED_FLAG).compare(FAIL);
                return isGraphConnected; 
                }

// This function is used to find the shortest path between two vertices in the graph.
string Algorithms::shortestPath(const Graph &graph, int src, int dest){
                if(src < 0 || dest < 0 || src >= graph.getMatrix().size() || dest >= graph.getMatrix().size())
                {
                    return FAIL;
                }
                
                std::string pathStr;
                
                if( !(graph.getIsWeightedGraph()) ) // if its not weighted graph run BFS
                {
                    pathStr = bfs(graph, src, dest);
                    return pathStr;
                }

                // if its weighted graph run Bellman-Ford algorithm to find shortest path
                // if there is a negative cycle it return -1, else it return the path.
                return negCycleBF(graph, src, dest); 
            }

// this function is used to find if the graph contains a cycle or not. and return the cycle if exist            
string Algorithms::isContainsCycle(const Graph &graph){
                string strCycle = bfs(graph, CYCLE_FLAG, CYCLE_FLAG);
                if(strCycle.compare(FAIL) == 0)
                {
                    strCycle = FOUND_NOTHING;
                }
                
                return strCycle;
                
            }
            
string Algorithms::isBipartite(const Graph &graph)
            {
                Matrix myMatrix = graph.getMatrix();
                size_t numVertices = myMatrix.size();
                std::vector<int> colors(numVertices, DEF_VALUE);
                std::vector<int> A, B;  // Add vectors to store the vertices of each set
                std::queue<int> queue;
                for (size_t start = 0; start < numVertices; ++start) {
                    if (colors[start] == DEF_VALUE) {
                        colors[start] = 0;
                        queue.push(start);

                        while (!queue.empty()) {
                            int u = queue.front();
                            queue.pop();

                            for (size_t v = 0; v < numVertices; ++v) {
                                if (myMatrix[u][v] && colors[v] == DEF_VALUE) {
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
                for (int i : A) {
                    A_str += std::to_string(i) + ", ";
                }
                A_str = A_str.substr(0, A_str.length() - 2) + "}";  // Remove the last comma and space, and add a closing brace

                string B_str = "B={";
                for (int i : B) {
                    B_str += std::to_string(i) + ", ";
                }
                B_str = B_str.substr(0, B_str.length() - 2) + "}";  // Remove the last comma and space, and add a closing brace

                return "The graph is bipartite: " + A_str + ", " + B_str + ".";
            }
            
// This function is used to check if there is a negative cycle in the graph and return the proper string.
string Algorithms::negativeCycle(const Graph &graph){

                string strNegCycle = negCycleBF(graph, CONNECTED_FLAG, CONNECTED_FLAG);
                
                if(strNegCycle.compare(FAIL) == 0)
                {
                    return "There is no negative cycle in the graph.";
                }
                
                else
                {
                    return strNegCycle;
                }
            }
    
