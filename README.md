# Graph-Algorithms
Algorithms implementations on Graph represented by adjacency matrix.

Info-
The Code representing graph using adjacency matrix with integers values.
The graph can be direct or undirected.
The graph can be weighted or unweighted, and with integers values.

Definitions:
NOTE! When talking about i and j, means 0 <= i,j <= n (n is the length of columns that is equal to the length of rows).
Adjacency Matrix - The matrix must be with equal size of rows and columns, with Integer values.
Directed Graph - There is value (i,j) in the adjacency matrix that is NOT equal to (j,i). (Check NOTE!)
Undirected Graph - The adjacency matrix is equal to its transport [meaning for every i,j in adjacency matrix (i,j) = (j,i)]. (Check NOTE!)
Weight Graph - There is value (i,j) in the adjacency matrix that not equals to 0 or 1. (Check NOTE!)
Unweighted Graph - For every (i,j) in the adjacency matrix, all the values equals to 0 or 1. (Check Note!)
Moreover using algorithms we can check more details on the graph and its characteristics.


Graph Methods-
loadGraph - To the graph we can load matrix only in the same row and column size.
printGraph - Print the graph will print on the output screen the number of edges and vertices in the graph.

Algorithms Methods-
isConnected(graph) - I think the name say it all.
shortestPath(graph,start,end) - return the minimum weight path, if not weights graph it will return the shortest path between 2 vertices, if there is one, else 1.
isContainsCycle(graph) - Also the name say it all, else 0.
isBipartite(graph) - return bipartite graph if it can, else 0
negativeCycle(graph) - if there is a negative cycle in the graph



