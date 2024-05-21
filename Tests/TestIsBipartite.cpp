#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

TEST_CASE("IsBipartiteReturnsTrueForBipartiteGraph") {
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0},
        {1, 0, 1},
        {0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::isBipartite(g) == "The graph is bipartite: A={0, 2}, B={1}");
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
