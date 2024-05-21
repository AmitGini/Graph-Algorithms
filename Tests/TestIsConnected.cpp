#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"


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