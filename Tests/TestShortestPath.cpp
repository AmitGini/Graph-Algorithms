//207275215
//amitgini0369@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

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

TEST_CASE("ShortestPathReturnsCorrectPathForUndirectedGraphWithNegativeWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, -1, -3, 0},
        {-1, 0, -2, -3},
        {-3, -2, 0, -1},
        {0, -3, -1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::shortestPath(g, 0, 3) == "0");
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
