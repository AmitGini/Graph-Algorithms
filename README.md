### 207275215
### amitgini0369@gmail.com
# Graph-Algorithms
Algorithms implementations on Graph represented by adjacency matrix.

**Info-**
- The Code representing graph using adjacency matrix with integers values.
- The graph can be direct or undirected.
- The graph can be weighted or unweighted, and with integers values.

## Definitions:
**NOTE!** When talking about i and j, means 0 <= i,j <= n (n is the length of columns that is equal to the length of rows).
- `Adjacency Matrix` - The matrix must be with equal size of rows and columns, with Integer values.
- `Directed Graph` - There is value (i,j) in the adjacency matrix that is NOT equal to (j,i). **(Check NOTE!)**
- `Undirected Graph` - The adjacency matrix is equal to its transport [meaning for every i,j in adjacency matrix (i,j) = (j,i)]. **(Check NOTE!)**
- `Weight Graph` - There is value (i,j) in the adjacency matrix that not equals to 0 or 1. **(Check NOTE!)**
- `Unweighted Graph` - For every (i,j) in the adjacency matrix, all the values equals to 0 or 1. **(Check Note!)**

## Type Definition Variable:
- `typedef vector<vector<int>> Matrix` - Defining new variable represented by 2 vectors of ints - (2D array).

## Graph:
Class that represented graph, using adjacency matrix with integers values.
### Graph:Constructors:
- `Graph()` - Default Constructor
- `~Graph()` - Destructor
### Graph:Fields(private):
- `Matrix` = `vector<vector<int>>` - Double array of integers
- `Matrix myTransposeMatrix` - The transpose of the matrix, updated after loading the matrix.
- `size_t numVertices` - The number of vertices in the graph, updated after loading the matrix.
- `size_t numEdges` - The number of edges in the graph, updated after loading the matrix.
- `bool isUndirected` - True - Undirected Graph, False - Directed, default value false, after loading matrix updated if needed.
- `bool isWeighted` - True - Weighted Graph, False - Unweighted Graph, default value false, after loading matrix updated if needed.

### Graph Methods:
**Set Methods(private):**
- `updateGraphProperty()` - Update the graph properties(transpose, isWeighted, isUndirected) after loading the matrix.
**Set Methods(public):**
- `void loadGraph(const Matrix matrixArg)` - load matrix to the graph, and calling updateGraphProperty() to update the graph properties.
- `void printGraph() const` - Print the graph will print on the output screen the number of edges and vertices in the graph.
**Getters Methods(public):**
- `const Matrix& getMatrix() const` - Return the matrix 
- `const Matrix& getTransposeMatrix() const` - Return the transpose matrix
- `bool isUndirectedGraph() const` - Return if its undirected graph
- `bool isWeightedGraph() const` - Return if its weighted graph
- `size_t getNumVertices() const` - Return the number of vertices in the graph
- `size_t getNumEdges() const` - Return the number of edges in the graph

## Algorithms:
### Fields
`None`
### Algorithms Methods:
- `static bool isConnected(const Graph &graph)` - Return 1 = True if the graph is connected else, 0 = False
- `static isContainsCycle(const Graph &graph)` - Return 1 = True if the graph contains cycle else, 0 = False
- `static string shortestPath(const Graph &graph, size_t src, size_t dest)` - Return the minimum weight or shortest path, if not weights graph it will return the shortest path between 2 vertices, if there is no path "0" == FAIL.
- `static string isBipartite(const Graph &graph)` - Return "0" if there is no bipartite else return string of the groups A and B.
- `static string negativeCycle(const Graph &graph)` - Return string of the negative cycle if there is one else return "0" == FAIL.

### Helper Methods:
- `static string BFS(const Graph &graph, vector<int> &dist, size_t src, vector<int> &prev, size_t dest)` - updating dist and prev vectors to reconstruct the shortest path of the graph from the source vertex.
- `static string DFS(const Graph &graph, vector<int> &dist, vector<int> &prev)` - Return if the graph is connected.
- `static string DFSVisit(const Graph &graph, size_t vertex, vector<size_t> &color, size_t currTime, vector<size_t> &discTime, vector<size_t> &finishTime, vector<int> &prev )` - DFSVisit method for DFS method.
- `static int BF(const Graph &graph, size_t src, size_t dest)` - updating dist and prev vectors to reconstruct the shortest path of the graph from the source vertex, and also check if there is negative cycle, also return index that part of the negative cycle to reconstruct it.
- `static isBipartiteHelper(const Graph &graph, vector<size_t> &color, size_t src)` - Helper method for isBipartite method.
