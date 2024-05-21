#define CATCH_CONFIG_MAIN
#include "Algorithms.hpp"
#include "Graph.hpp"
#include "doctest.h"


TEST_CASE("IsConnectedReturnsTrueForConnectedGraph") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph ={
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isConnected(g) == true);
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

TEST_CASE("ShortestPathReturnsCorrectPath") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0->1->2");
}

TEST_CASE("ShortestPathReturnsFailForNoPath") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 0, 0},
        {0, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 2) == "0");
}

TEST_CASE("IsContainsCycleReturnsTrueForGraphWithCycle") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);

    std::vector<std::vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isContainsCycle(g) == true);
}

TEST_CASE("IsContainsCycleReturnsFalseForGraphWithoutCycle") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isContainsCycle(g) == false);


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

TEST_CASE("IsBipartiteReturnsFalseForNonBipartiteGraph") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 1},
        {1, 0, 1},
        {1, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    std::vector<std::vector<int>> graph2 = {
        {0, 1, 1, 0, 0},
        {1, 0, 1, 0, 0},
        {1, 1, 0, 1, 0},
        {0, 0, 1, 0, 0},
        {0, 0, 0, 0, 0}};
    g.loadGraph(graph2);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");

    std::vector<std::vector<int>> graph3 = {
        {0, 1, 2, 0, 0},
        {1, 0, 3, 0, 0},
        {2, 3, 0, 4, 0},
        {0, 0, 4, 0, 5},
        {0, 0, 0, 5, 0}};
    g.loadGraph(graph3);
    CHECK(ariel::Algorithms::isBipartite(g) == "0");
}

TEST_CASE("NegativeCycleReturnsCorrectCycleForGraphWithNegativeCycle") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, -3},
        {0, 1, 0}};
    g.loadGraph(graph);
    // Assuming the function returns the smallest possible negative cycle.
    CHECK(ariel::Algorithms::negativeCycle(g) == "Cycle: 1->2->1");
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