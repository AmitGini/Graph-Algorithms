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
Class that represnted graph, using adjacency matrix with intergers values.
### Graph:Fields:
- `Matrix` = `vector<vector<int>>` - Double array of integers
- `bool isUndirectedGraph` - True - Undirected Graph, False - Directedas, default value false, after loading matrix updated if needed.
- `bool isWeightedGraph` - True - Weighted Graph, False - Unweighted Graph, default value false, after loading matrix updated if needed.
### Graph Methods:
**Getters Methods:**
- `const Matrix& getMatrix() const` - Return the matrix 
- `bool getIsUndirectedGraph() const` - Return if its undirected graph
- `bool getIsWeightedGraph() const` - Return if its weighted graph

**Other Methods:**
- `void loadGraph(const Matrix matrixArg)` - To the graph we can load matrix only in the same row and column size.
- `void printGraph() const` - Print the graph will print on the output screen the number of edges and vertices in the graph.


## Algorithms:
### Fields
`None`
### Algorithms Methods:
- `static bool isConnected(const Graph &graph)` - Return 1 = True if the graph is connected else, 0 = False
- `static std::string shortestPath(const Graph &graph, int src, int dest)` - Return the minimum weight path, if not weights graph it will return the shortest path between 2 vertices, if there is no path -1.
- `static std::string isContainsCycle(const Graph &graph)` - If the graph contains Cycle it will return the Cycle else, 0.
- `static std::string isBipartite(const Graph &graph)` - If the graph can be Bipartite it will return the Bipartite Graphs else return 0.
- `static std::string negativeCycle(const Graph &graph)` - If the graph contain negative cycle it will return that cycle else return > "There is not negative cycle".