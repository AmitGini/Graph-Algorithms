//207275215
//amitgini0369@gmail.com
#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

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

TEST_CASE("NegativeCycleReturnsCorrectCycleForNonSymmetricGraphWithMixedWeights")
{
    ariel::Graph g;
    std::vector<std::vector<int>> graph = {
        {0, 1, 0, 0},
        {-2, 0, -3, 0},
        {0, 2, 0, -1},
        {0, 0, 1, 0}};
    g.loadGraph(graph);
    CHECK(ariel::Algorithms::negativeCycle(g) == "Cycle: 2->1->2");
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
