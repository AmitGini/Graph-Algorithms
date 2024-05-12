//207275215
#include <string>
#include <queue>
#include <limits>
#include <algorithm>
#include <vector>

#include "Graph.hpp"
#include "Algorithms.hpp"

//Genral
constexpr auto START = 0;

// Bipartite
constexpr size_t NO_COLOR = 0;
constexpr size_t RED = 1;
constexpr size_t BLUE = 2;
constexpr const char* FAIL = "0"; // isBipartite / shortestPath

//BFS
constexpr size_t WHITE = 0;
constexpr size_t GRAY = 1;
constexpr size_t BLACK = 2;

// isContainedCycle / BF / shortestPath / negativeCycle
constexpr size_t NONE_EDGE = 0;
constexpr int UNDEFINED = -1;
constexpr int VISITED = 1;

constexpr int  NO_CYCLE = -1;
constexpr int DEF_MAX_INT = std::numeric_limits<int>::max();
constexpr size_t DEF_MAX_SIZE_T = std::numeric_limits<size_t>::max();

using ariel::Graph;
using std::string;
using std::vector;
using std::size_t;
using Matrix = std::vector<std::vector<int>>;

using namespace ariel;

Algorithms::Algorithms()= default;

bool Algorithms::isConnectedHelper(const Matrix& edges) {

    size_t numVertices = edges.size();
    std::vector<bool> visited(numVertices, false);
    std::queue<size_t> queue;

    queue.push(START);
    visited[START] = true;
    size_t visitedCount = 1;

    while (!queue.empty()) {
        size_t currentVertex = queue.front();
        queue.pop();

        for (size_t vertex = START; vertex < numVertices; vertex++) {
            if (edges[currentVertex][vertex] != NONE_EDGE && !visited[vertex]) {
                queue.push(vertex);
                visited[vertex] = true;
                visitedCount++;
            }
        }
    }

    return visitedCount == numVertices;
}

// Function to check if a graph is strongly connected
bool Algorithms::isConnected(const Graph &graph)
{
    const Matrix& matrix = graph.getMatrix(); // adjacency matrix
    if (!isConnectedHelper(matrix)) {
        return false;
    }
    const Matrix& transposeMatrix = graph.getTransposeMatrix();

    return isConnectedHelper(transposeMatrix);
}

//
bool Algorithms::BFS(const Graph &graph, vector<int> &dist, size_t src, vector<int> &prev, size_t dest){
    // initialize the color, distance, and previous vectors of the source vertex
    vector<size_t> color(graph.getNumOfVertices(), WHITE);
    color[src] = GRAY;
    dist[src] = 0;
    prev[src] = -1;
    std::queue<size_t> que;
    que.push(src);

    while(!que.empty()) {
        size_t vertex = que.front();
        que.pop();

            for(size_t neighbor = START; neighbor < graph.getNumOfVertices(); ++neighbor) {
                if(graph.getMatrix()[vertex][neighbor] != NONE_EDGE) {
                    if(color[neighbor] == WHITE) {
                        color[neighbor] = GRAY;
                        dist[neighbor] = dist[vertex] + 1;
                        prev[neighbor] = static_cast<int>(vertex);
                        que.push(neighbor);
                    }
                }
            }
            color[vertex] = BLACK;
    }

    return color[dest] == BLACK;
}

//
bool Algorithms::DFSVisit(const Graph &graph, size_t vertex,
                                   vector<size_t> &color, size_t currTime,
                                   vector<size_t> &discTime,
                                   vector<size_t> &finishTime,
                                   vector<int> &prev) {
    color[vertex] = GRAY;
    discTime[vertex] = ++currTime;
    Matrix edges = graph.getMatrix();
    for(size_t neighbor = START; neighbor < graph.getNumOfVertices(); ++neighbor) {
        if( edges[vertex][neighbor] != NONE_EDGE) {
            if(graph.isUndirectedGraph() && neighbor == prev[vertex]) {
                continue;
            }
            if(color[neighbor] == GRAY) {
                return true;
            }
            if(color[neighbor] == WHITE) {
                prev[neighbor] = static_cast<int>(vertex);
                DFSVisit(graph, neighbor, color, currTime, discTime, finishTime, prev);
            }
        }
    }
    color[vertex] = BLACK;
    finishTime[vertex] = ++currTime;
    return false;
}

//
bool Algorithms::DFS(const Graph &graph, vector<int> &prev) {

    vector<size_t> color(graph.getNumOfVertices(), WHITE);
    vector<size_t> discTime(graph.getNumOfVertices(), DEF_MAX_SIZE_T);
    vector<size_t> finishTime(graph.getNumOfVertices(), DEF_MAX_SIZE_T);
    size_t numVertices = graph.getNumOfVertices();
    size_t currTime = 0;

    for(size_t vertex = START; vertex < numVertices; ++vertex) {
        if(color[vertex] == WHITE) {
            if(DFSVisit(graph, vertex, color,currTime, discTime, finishTime, prev)) {
                return true;
            }
        }
    }
    return false;
}

//
int Algorithms::BF(const Graph &graph, vector<int> &dist, vector<int> &prev) {
    Matrix edges = graph.getMatrix();
    size_t numVertices = graph.getNumOfVertices(); // number of rows or columns is the number of vertices

    dist.assign(numVertices, DEF_MAX_INT);
    prev.assign(numVertices, UNDEFINED);  // Use -1 to indicate no predecessor

    dist[START] = 0;
    vector<int> visited(numVertices, UNDEFINED);
    int partOfCycle = NO_CYCLE;

    // Relax the edges |V| - 1 times
    for(size_t relax = 0; relax < numVertices - 1; ++relax) {
        for(size_t vertixA = START; vertixA < numVertices; ++vertixA) {

            for(size_t toVertixB = START; toVertixB < numVertices; ++toVertixB) {

                if(edges[vertixA][toVertixB] != NONE_EDGE) {

                    if(dist[vertixA] + edges[vertixA][toVertixB] < dist[toVertixB]) {

                        dist[toVertixB] = dist[vertixA] + edges[vertixA][toVertixB];
                        prev[toVertixB] = static_cast<int>(vertixA);

                    }
                }
            }
        }
    }

    // Check for negative cycles
    for(size_t vertixA = START; vertixA < numVertices; ++vertixA) {
        for(size_t vertixB = START; vertixB < numVertices; ++vertixB) {
            if(edges[vertixA][vertixB] != NONE_EDGE) {
                if(dist[vertixA] + edges[vertixA][vertixB] < dist[vertixB]) {
                    partOfCycle = static_cast<int>(vertixB);
                }
            }
        }
    }
    return partOfCycle;
}

// This function is used to find the shortest path between two vertices in the graph.
string Algorithms::shortestPath(const Graph &graph, size_t src, size_t dest){

    size_t numVertices = graph.getNumOfVertices(); // number of rows or columns is the number of vertices
    vector<int> dist(numVertices, DEF_MAX_INT);
    vector<int> prev(numVertices, -1);

    // if the source or destination is not in the graph return -1
    if(src >= numVertices || dest >= numVertices)
    {
        return FAIL;
    }

    if(!graph.isWeightedGraph()) {
        bool result = BFS(graph, dist, src, prev, dest);
        if(!result) {
            return FAIL;
        }
    }

    else {
        int result = BF(graph, dist, prev);
        if( result > NO_CYCLE) {
            return FAIL;
        }
    }

    // Reconstruct the path from dest to src
    vector<size_t> path;
    vector<bool> visited(numVertices, false);
    size_t indexVertex = dest;
    size_t countNumInsertion = 0;

    while(src != indexVertex) {
        path.push_back(indexVertex);
        countNumInsertion++;
        visited[indexVertex] = true;

        if(prev[indexVertex] == -1) {
            break;
        }
        indexVertex = static_cast<size_t>(prev[indexVertex]);
    }
    if(!visited[src]) {
        path.push_back(src);
        visited[src] = true;
    }
    // Reverse the path to get it from src to dest
    reverse(path.begin(), path.end());

    // Convert the path to string
    std::string pathStr;

    for(size_t vertex : path) {
        pathStr += std::to_string(vertex) + "->";
    }
    pathStr = pathStr.substr(START, pathStr.length() - 2);
    return pathStr;
}

// this function is used to find if the graph contains a cycle or not. and return the cycle if exist
bool Algorithms::isContainsCycle(const Graph &graph){
    Matrix edges = graph.getMatrix(); // adjacency matrix
    size_t numVertices = graph.getNumOfVertices(); // number of rows or columns is the number of vertices
    vector<int> prev(numVertices, -1);

    if(graph.isWeightedGraph()) {
        Graph tempGraph;
        tempGraph.loadGraph(edges);
        // Since bellmanford findes negative cycle, Check for positive cycles
        for(size_t verticsXTo = START; verticsXTo < numVertices; ++verticsXTo) {
            for(size_t vericesY = START; vericesY < numVertices; ++vericesY) {
                if(edges[verticsXTo][vericesY] != NONE_EDGE) {
                    edges[verticsXTo][vericesY] = -edges[verticsXTo][vericesY];
                }
            }
        }
        vector<int> dist(numVertices, DEF_MAX_INT);
        return BF(tempGraph, dist, prev) == NO_CYCLE; // contain a cycle if true
    }

    return DFS(graph,prev);
}

// This method coloring the vertices of the graph in two colors, and return if its 2 coloroble or not.
bool Algorithms::isBipartiteHelper(const Graph &graph,
                                        std::vector<size_t> &color, size_t src) {
    Matrix edges = graph.getMatrix(); // adjacency matrix
    color[src] = RED;
    std::queue<size_t> que;
    que.push(src);

    while(!que.empty()) {
        size_t vertex = que.front();
        que.pop();

        // If self Loop exists, then adjacency matrix
        // will have 1 in the diagonal element
        // and we have to return false in case of  adjacency matrix
        if(edges[vertex][vertex] != NONE_EDGE) {
            return false;
        }

        for(size_t neighbor = START; neighbor < graph.getNumOfVertices(); ++neighbor) {
            if(edges[vertex][neighbor] != NONE_EDGE) {
                if(color[neighbor] == NO_COLOR) {
                    color[neighbor] = color[vertex] == RED ? BLUE : RED;
                    que.push(neighbor);
                }
                else if(color[neighbor] == color[vertex]) {
                    return false;
                }
            }
        }
    }
    return true;
}

//
string Algorithms::isBipartite(const Graph &graph) {

    size_t numVertices = graph.getNumOfVertices();

    // Create a vector to store the color of each vertex
    vector<size_t> colored(numVertices, NO_COLOR);

    // Check if the graph is bipartite and update the color of each vertex
    for (size_t vertex = START; vertex < numVertices; ++vertex) {
        if (colored[vertex] == NO_COLOR) {

            if (!isBipartiteHelper(graph, colored, vertex)) {
                return FAIL;
            }
        }
    }

    std::vector<size_t> groupA;
    std::vector<size_t> groupB;

    // Separate the vertices into two sets based on their colors
    for (size_t vertex = START; vertex < numVertices; vertex++) {
        if (colored[vertex] == RED) {
            groupA.push_back(vertex);
        } else if (colored[vertex] == BLUE) {
            groupB.push_back(vertex);
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
    return "The graph is bipartite: " + strGroupAVertices + ", " + strGroupBVertices;
}

//
string Algorithms::reconstructCycle(size_t endVertex, const vector<int>& prev) {

    size_t numVertices = prev.size();
    size_t countCycleEdges = 0;
    int prevVertex = prev[endVertex];

    vector<bool> visited(numVertices, false);
    vector<size_t> cycle;
    cycle.push_back(endVertex);
    countCycleEdges++;
    visited[endVertex] = true;

    while(prevVertex >= 0){

        size_t tempPrevVertex = static_cast<size_t>(prevVertex);
        if(visited[tempPrevVertex]) {
            break;
        }

        cycle.push_back(tempPrevVertex);
        countCycleEdges++;
        visited[tempPrevVertex] = true;

        if(countCycleEdges >= numVertices) {
            break;
        }

        prevVertex = prev[tempPrevVertex];
    }
    cycle.push_back(endVertex);

    // reverse(cycle.begin(), cycle.end());

    string cycleStr = "Cycle: ";
    for (size_t overVertices = 0; overVertices < cycle.size(); overVertices++) {
        cycleStr += std::to_string(cycle[overVertices]);
        if (overVertices < cycle.size() - 1) {
            cycleStr += "->";
        }
    }

    return cycleStr;
}

// This function is used to check if there is a negative cycle in the graph and return the proper string.
string Algorithms::negativeCycle(const Graph &graph)
{
    size_t numVertices = graph.getNumOfVertices(); // number of rows or columns is the number of vertices
    vector<int> dist(numVertices, DEF_MAX_INT);
    vector<int> prev(numVertices, -1);

    int srcCycle = BF(graph, dist, prev); //return index in the cycle

    string pathStr = FAIL; //default value

    if(srcCycle == NO_CYCLE) {
        return FAIL;
    }

    pathStr = reconstructCycle(static_cast<size_t>(srcCycle), prev);

    return pathStr;
}


