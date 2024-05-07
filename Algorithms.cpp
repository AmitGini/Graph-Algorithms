#include <iostream>
#include <string>
#include <queue>
#include <limits>
#include <set>
#include <algorithm>
#include <vector>

#include "Graph.hpp"
#include "Algorithms.hpp"



#define NON_NEG_NUM 0
#define CONNECTED_FLAG -1
#define CYCLE_FLAG -2
#define SUCCESS "1"


//Genral
#define START 0

// Bipartite
#define NO_COLOR 0
#define RED 1
#define BLUE 2
#define FAIL "0" // isBipartite / shortestPath

// isContainedCycle / BF / shortestPath / negativeCycle
#define NONE_EDGE 0
#define DEF_MAX_INT std::numeric_limits<int>::max()
#define DEF_MAX_SIZE_T std::numeric_limits<size_t>::max()


using ariel::Graph;
using std::string;
using std::vector;
using std::size_t;
using Matrix = std::vector<std::vector<int>>;

using namespace ariel;

Algorithms::Algorithms(){}

// This function is used to check if the graph is connected or not.
bool Algorithms::isConnected(const Graph &graph)
{
    return false;
}

// This function is used to find the shortest path between two vertices in the graph.
string Algorithms::shortestPath(const Graph &graph, size_t src, size_t dest){

    Matrix edges = graph.getMatrix(); // adjacency matrix
    size_t numVertices = graph.getNumOfVertices(); // number of rows or columns is the number of vertices
    vector<int> dist(numVertices, DEF_MAX_INT);
    vector<size_t> prev(numVertices, DEF_MAX_SIZE_T);

    // if the source or destination is not in the graph return -1
    if(src >= numVertices || dest >= numVertices)
    {
        return FAIL;
    }


    // Check for negative cycles
    if(algoBF(graph, dist, prev)) return FAIL;

    // Reconstruct the path from dest to src
    vector<size_t> path;
    for(size_t vertex = dest; vertex != src; vertex = prev[vertex]) {
        path.push_back(vertex);
    }
    path.push_back(src);

    // Reverse the path to get it from src to dest
    reverse(path.begin(), path.end());

    // Convert the path to string
    std::string pathStr = "Shortest Path: ";

    for(size_t vertex : path) {
        pathStr += std::to_string(vertex) + ">";
    }

    return pathStr;
}

//string Algorithms

bool Algorithms::algoBF(const Graph &graph,vector<int> &dist, vector<size_t> &prev) {

    Matrix edges = graph.getMatrix(); // adjacency matrix
    size_t numVertices = graph.getNumOfVertices(); // number of rows or columns is the number of vertices
    size_t numEdges = graph.getNumOfEdges();

    // Set the distance of the source vertex to 0
    dist[START] = 0;

    // Relax the edges |V| - 1 times
    for(size_t verticsXTo = START; verticsXTo < numVertices - 1; ++verticsXTo) {
        for(size_t vericesY = START; vericesY < numEdges; ++vericesY) {
            if(edges[verticsXTo][vericesY] != NONE_EDGE) {
                if(dist[verticsXTo] + edges[verticsXTo][vericesY] < dist[vericesY]) {
                    dist[vericesY] = dist[verticsXTo] + edges[verticsXTo][vericesY];
                }
            }
        }
    }

    // Check for negative cycles
    for(size_t verticsXTo = START; verticsXTo < numVertices - 1; ++verticsXTo) {
        for(size_t vericesY = START; vericesY < numVertices; ++vericesY) {
            if(edges[verticsXTo][vericesY] != NONE_EDGE) {
                if(dist[verticsXTo] + edges[verticsXTo][vericesY] < dist[vericesY]) {
                    return true;
                }
            }
        }
    }

    return false;
}

// this function is used to find if the graph contains a cycle or not. and return the cycle if exist
bool Algorithms::isContainsCycle(const Graph &graph){
    Matrix edges = graph.getMatrix(); // adjacency matrix
    size_t numVertices = graph.getNumOfVertices(); // number of rows or columns is the number of vertices
    vector<int> dist(numVertices, DEF_MAX_INT);
    vector<size_t> prev(numVertices, DEF_MAX_SIZE_T);

    // Since bellmanford findes negative cycle, Check for positive cycles
    for(size_t verticsXTo = START; verticsXTo < numVertices; ++verticsXTo) {
        for(size_t vericesY = START; vericesY < numVertices; ++vericesY) {
            if(edges[verticsXTo][vericesY] != NONE_EDGE) {
                edges[verticsXTo][vericesY] = -edges[verticsXTo][vericesY];
            }
        }
    }
    return algoBF(graph, dist, prev);
}


// This method coloring the vertices of the graph in two colors, and return if its 2 coloroble or not.
bool Algorithms::isBipartiteHelper(const Matrix &edges, size_t numVertices,
                                       size_t src, std::vector<int> &color) {
    color[src] = RED;

    std::queue<size_t> que;
    que.push(src);

    while(!que.empty()) {
        size_t vertex = que.front();
        que.pop();

        // If self Loop exists, then adjacency matrix
        // will have 1 in the diagonal element
        // and we have to return false in case of  adjacency matrix
        if(edges[vertex][vertex] != NONE_EDGE) return false;

        for(size_t neighbor = START; neighbor < numVertices; ++neighbor) {
            if(edges[vertex][neighbor] != NONE_EDGE) {
                if(color[neighbor] == NO_COLOR) {
                    color[neighbor] = (color[vertex] == RED) ? BLUE : RED;
                    que.push(neighbor);
                } else if(color[neighbor] == color[vertex]) {
                    return false;
                }
            }
        }
    }
    return true;
}


string Algorithms::isBipartite(const Graph &graph) {

    Matrix edges = graph.getMatrix();
    size_t numVertices = graph.getNumOfVertices();

    //  cycled graph with n vertices is 2 colorable if and only if n is even number
    if(isContainsCycle(graph) == false && numVertices % 2 != 0) return FAIL;

    // Create a vector to store the color of each vertex
    vector<int> colored(numVertices, NO_COLOR);

    // Check if the graph is bipartite and update the color of each vertex
    for (size_t vertex = START; vertex < numVertices; ++vertex) {
        if (colored[vertex] == NO_COLOR) {
            if (!isBipartiteHelper(edges, numVertices, vertex, colored)) {
                return FAIL;
            }
        }
    }

    std::vector<size_t> groupA, groupB;

    // Separate the vertices into two sets based on their colors
    for (size_t vertix = START; vertix < numVertices; ++vertix) {
        if (colored[vertix] == RED) {
            groupA.push_back(vertix);
        } else if (colored[vertix] == BLUE) {
            groupB.push_back(vertix);
        }
    }

    // Convert the sets to strings
    string strGroupAVertices = "A={";
    for (size_t vertexAt : groupA) {
        strGroupAVertices += std::to_string(vertexAt) + ", ";
    }

    // Remove the last comma and space, and add a closing brace
    strGroupAVertices = strGroupAVertices.substr(START, strGroupAVertices.length() - 2) + "}";

    string strGroupBVertices = "B={";
    for (size_t vertexAt : groupB) {
        strGroupBVertices += std::to_string(vertexAt) + ", ";
    }

    // Remove the last comma and space, and add a closing brace
    strGroupBVertices = strGroupBVertices.substr(START, strGroupBVertices.length() - 2) + "}";
    std::cout << strGroupAVertices << std::endl;
    std::cout << strGroupBVertices << std::endl;
    return "The graph is bipartite: " + strGroupAVertices + ", " + strGroupBVertices;
}

string Algorithms::reconstructCycle(size_t startVertex, size_t endVertex, const std::vector<size_t>& prev) {

    std::vector<size_t> cycle;

    // Start from the end vertex and follow predecessors to reconstruct the cycle
    for (size_t currVertex = endVertex; ; currVertex = prev[currVertex]) {
        cycle.push_back(currVertex);
        if (currVertex == startVertex && cycle.size() > 1) {
            break;  // Once we reach the start vertex again, we complete the cycle
        }
    }

    cycle.push_back(startVertex);  // Complete the cycle by adding the start vertex at the end

    // To ensure the cycle is readable from start to finish, reverse the vector
    std::reverse(cycle.begin(), cycle.end());

    // Build the string representation of the cycle
    std::string cycleStr = "Cycle: ";
    for (int v : cycle) {
        cycleStr += std::to_string(v) + "->";
    }
    cycleStr = cycleStr.substr(START, cycleStr.length() - 2);
    return cycleStr;
}

// This function is used to check if there is a negative cycle in the graph and return the proper string.
string Algorithms::negativeCycle(const Graph &graph)
{
    Matrix edges = graph.getMatrix(); // adjacency matrix
    size_t numVertices = graph.getNumOfVertices(); // number of rows or columns is the number of vertices
    size_t numEdges = graph.getNumOfEdges();
    vector<int> dist(numVertices, DEF_MAX_INT);
    vector<size_t> prev(numVertices, DEF_MAX_SIZE_T);

    if(algoBF(graph, dist, prev) == false) return FAIL;

    string pathStr = FAIL;
    // Check for negative cycles
    for(size_t verticesX = START; verticesX < numVertices - 1; ++verticesX) {
        for(size_t toVerticesY = START; toVerticesY < numVertices; ++toVerticesY) {
            if(edges[verticesX][toVerticesY] != NONE_EDGE) {
                if(dist[verticesX] + edges[verticesX][toVerticesY] < dist[toVerticesY]) {
                    pathStr = reconstructCycle(verticesX, toVerticesY, prev);
                }
            }
        }
    }
    return pathStr;
}

