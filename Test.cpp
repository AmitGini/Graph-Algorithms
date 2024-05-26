//207275215
//amitgini0369@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

using namespace std;

TEST_CASE("Graph Initialization")
{
    ariel::Graph g;

    CHECK(g.getNumOfVertices() == 0);
    CHECK(g.getNumOfEdges() == 0);
    CHECK(g.isUndirectedGraph() == false);
    CHECK(g.isWeightedGraph() == false);
}

TEST_CASE("Test invalid graph")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 2, 0},
        {1, 0, 3, 0},
        {2, 3, 0, 4},
        {0, 0, 4, 0},
        {0, 0, 0, 5},
        {0, 0, 0, 5}};
    CHECK_THROWS(g.loadGraph(graph));
}

TEST_CASE("Graph With Neg Edges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, -3},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getNumOfVertices() == 3);
    CHECK(g.getNumOfEdges() == 4);
    CHECK(g.isUndirectedGraph() == false);
    CHECK(g.isWeightedGraph() == true);
}

TEST_CASE("Graph With Pos Edges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(g.getNumOfVertices() == 3);
    CHECK(g.getNumOfEdges() == 2);
    CHECK(g.isUndirectedGraph() == true);
    CHECK(g.isWeightedGraph() == false);
}

TEST_CASE("Load and Retrieve Graph Properties")
{
    ariel::Graph g;
    ariel::Matrix matrix = {
        {0, 1, 2},
        {1, 0, 0},
        {2, 0, 0}};

    g.loadGraph(matrix);

    CHECK(g.getNumOfVertices() == 3);
    CHECK(g.getNumOfEdges() == 2);
    CHECK(g.isWeightedGraph() == true);
    CHECK(g.isUndirectedGraph() == true);
    CHECK(g.getMatrix() == matrix);
    CHECK(g.getTransposeMatrix() == matrix); // Assuming it processes the transpose correctly
}

TEST_CASE("Check Undirected Graph Detection")
{
    ariel::Graph g;
    ariel::Matrix symmetricMatrix = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};

    g.loadGraph(symmetricMatrix);

    CHECK(g.isWeightedGraph() == false);
    CHECK(g.isUndirectedGraph() == true);
}

TEST_CASE("Check Directed Graph Detection")
{
    ariel::Graph g;
    ariel::Matrix asymmetricMatrix = {
        {0, 1, 0},
        {0, 0, 1},
        {1, 0, 0}};

    g.loadGraph(asymmetricMatrix);

    CHECK(g.isWeightedGraph() == false);
    CHECK(g.isUndirectedGraph() == false);
}


TEST_CASE("Test isContainsCycle")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);
    
    vector<vector<int>> graph1= {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph1);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}


TEST_CASE("Test shortestPath")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 4) == "0");
}

TEST_CASE("ShortestPathReturnsCorrectPathForDirectedWeightedGraph")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 3, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 2},
        {4, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");
}

TEST_CASE("ShortestPathReturnsCorrectPathForDirectGraphWithMixedWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 4},
        {0, 0, 2, 0},
        {3, 0, 0, 0},
        {0, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
}

TEST_CASE("ShortestPathReturnsCorrectPathForUndirectedGraphWithUniformWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1, 0},
        {1, 0, 0, 1},
        {1, 0, 0, 1},
        {0, 1, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->3");
}

TEST_CASE("ShortestPathReturnsCorrectPathForNonDirectGraphWithUniformWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->1->2->3");
}

TEST_CASE("ShortestPathReturnsCorrectPathForNonSymmetricGraphWithNegativeWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0, 0},
        {0, 0, -4, 2},
        {0, 0, 0, 3},
        {1, -1, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0");
}

TEST_CASE("ShortestPathReturnsCorrectPathForSymmetricGraphWithNoNegativeWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 3, 2, 0},
        {3, 0, 0, 4},
        {2, 0, 0, 1},
        {0, 4, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0->2->3");
}

TEST_CASE("Test isConnected")
{
    ariel::Graph g;
    vector<vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);

    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}


TEST_CASE("IsConnectedReturnsTrueForLargeConnectedGraph") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1, 1, 1},
        {1, 0, 1, 1, 1},
        {1, 1, 0, 1, 1},
        {1, 1, 1, 0, 1},
        {1, 1, 1, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g));
}

TEST_CASE("IsConnectedReturnsFalseForLargeNonConnectedGraph") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0, 0, 0},
        {0, 0, 1, 1, 1},
        {0, 1, 0, 1, 1},
        {0, 1, 1, 0, 1},
        {0, 1, 1, 1, 0}};
    g.loadGraph(graph);
    CHECK_FALSE(ariel::Algorithms::isConnected(g));
}

TEST_CASE("IsConnectedReturnsFalseForNonConnectedGraph") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == false);
}

TEST_CASE("IsConnectedReturnsTrueForConnectedUndirectedGraph_4x4") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("IsConnectedReturnsTrueForConnectedUndirectedGraph_5x5") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0, 1},
        {1, 0, 1, 0, 0},
        {0, 1, 0, 1, 0},
        {0, 0, 1, 0, 1},
        {1, 0, 0, 1, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("IsConnectedReturnsTrueForConnectedUndirectedGraph_6x6") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0, 0, 1},
        {1, 0, 1, 0, 0, 0},
        {0, 1, 0, 1, 0, 0},
        {0, 0, 1, 0, 1, 0},
        {0, 0, 0, 1, 0, 1},
        {1, 0, 0, 0, 1, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("IsConnectedReturnsTrueForConnectedWeightedUndirectedGraph_4x4") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0, 3},
        {2, 0, 3, 0},
        {0, 3, 0, 4},
        {3, 0, 4, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("IsConnectedReturnsTrueForConnectedWeightedUndirectedGraph_5x5") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0, 5},
        {1, 0, 2, 0, 0},
        {0, 2, 0, 3, 0},
        {0, 0, 3, 0, 4},
        {5, 0, 0, 4, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("IsConnectedReturnsTrueForSymmetricConnectedGraphWithNegativeWeights_4x4") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -1, 0, 5},
        {-1, 0, -2, 0},
        {0, -2, 0, -3},
        {5, 0, -3, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("IsConnectedReturnsTrueForConnectedDirectedGraphWithNegativeWeights_4x4") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -2, 0, 3},
        {2, 0, -3, 0},
        {0, 3, 0, -4},
        {-3, 0, 4, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("IsConnectedReturnsTrueForConnectedGraphWithNegativeWeights_6x6") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -2, 0, 3, 0, 0},
        {2, 0, -3, 0, 0, 0},
        {0, 3, 0, -4, 0, 0},
        {-3, 0, 4, 0, 5, 0},
        {0, 0, 0, 5, 0, -6},
        {0, 0, 0, 0, -6, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}

TEST_CASE("IsConnectedReturnsTrueForSymmetricConnectedUndirectedGraphWithNegativeWeights_5x5") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -1, 0, 0, 5},
        {-1, 0, -2, 0, 0},
        {0, -2, 0, -3, 0},
        {0, 0, -3, 0, -4},
        {5, 0, 0, -4, 0}
    };
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
}


TEST_CASE("IsBipartiteReturnsTrueForBipartiteGraph") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
}
TEST_CASE("Test isBipartite"){
    ariel::Graph g;
    vector<vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2); // Load the graph to the object.
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    // 5x5 matrix that reprsents a connected weighted graph.
    vector<vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3); // Load the graph to the object.
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
}

TEST_CASE("IsBipartiteReturnsTrueForSymmetricGraphWithMixedWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -1, 2, 0},
        {-1, 0, 0, 3},
        {2, 0, 0, -4},
        {0, 3, -4, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 3}, B={1, 2}");
}

TEST_CASE("IsBipartiteReturnsTrueForSymmetricGraphWithPositiveWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0, 4},
        {2, 0, 3, 0},
        {0, 3, 0, 1},
        {4, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("IsBipartiteReturnsTrueForSymmetricGraphWithNonWeightedEdges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 1},
        {1, 0, 1, 0},
        {0, 1, 0, 1},
        {1, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("IsBipartiteReturnsTrueForNonSymmetricGraphWithMixedWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -2, 0, 0},
        {2, 0, -3, 0},
        {0, 3, 0, 1},
        {0, 0, -1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("IsBipartiteReturnsTrueForNonSymmetricGraphWithPositiveWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, 0, 0},
        {0, 0, 3, 0},
        {0, 0, 0, 1},
        {4, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("IsBipartiteReturnsTrueForNonSymmetricGraphWithNonWeightedEdges")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0},
        {0, 0, 1, 0},
        {0, 0, 0, 1},
        {1, 0, 0, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1, 3}");
}

TEST_CASE("NegativeCycleReturnsCorrectCycleForGraphWithNegativeCycle") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, -3},
        {0, 1, 0}};
    g.loadGraph(graph);
    // Assuming the function returns the smallest possible negative cycle.
    CHECK(ariel::Algorithms::negativeCycle(g) == "Cycle: 2->1->2");
}

TEST_CASE("NegativeCycleReturnsFailForGraphWithoutNegativeCycle") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 3},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "0");
}

TEST_CASE("NegativeCycleReturnsCorrectCycleForSymmetricGraphWithMixedWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 2, -3, 0},
        {2, 0, 0, -4},
        {-3, 0, 0, 1},
        {0, -4, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Cycle: 0->2->3->1->0");
}

TEST_CASE("NegativeCycleReturnsCorrectCycleForSymmetricGraphWithMixedWeights_5x5")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, -2, 0, 0},
        {1, 0, 3, -4, 0},
        {-2, 3, 0, 0, 1},
        {0, -4, 0, 0, 2},
        {0, 0, 1, 2, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Cycle: 0->1->3->0");
}

TEST_CASE("NegativeCycleReturnsCorrectCycleForNonSymmetricGraphWithMixedWeights_6x6")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0, 0, 0},
        {0, 0, -3, 0, 0, 0},
        {0, 2, 0, -1, 0, 0},
        {0, 0, 0, 0, -2, 1},
        {0, 0, 0, 2, 0, -3},
        {-4, 0, 0, 0, 3, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Cycle: 2->1->2");
}
