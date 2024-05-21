#include "doctest.h"
#include "Algorithms.hpp"
#include "Graph.hpp"

// todo: add print tests

TEST_CASE("Graph Initialization")
{
    ariel::Graph g;

    CHECK(g.getNumOfVertices() == 0);
    CHECK(g.getNumOfEdges() == 0);
    CHECK(g.isUndirectedGraph() == false);
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

    CHECK(g.isUndirectedGraph() == false);
}

// todo: check this test

// TEST_CASE("LoadGraphWithIrregularMatrix")
// {
//     ariel::Graph g;
//     ariel::Matrix irregularMatrix = {
//         {0, 1, 2},
//         {1, 0}}; // Irregular matrix, second row is shorter

//     SUBCASE("Exception for non-uniform matrix sizes")
//     {
//         CHECK_THROWS_AS(g.loadGraph(irregularMatrix), std::invalid_argument);
//     }

//     SUBCASE("No change in graph properties after exception")
//     {
//         try
//         {
//             g.loadGraph(irregularMatrix);
//         }
//         catch (const std::invalid_argument &)
//         {
//             irregularMatrix = {
//                 {1, 1},
//                 {1, 1}};
//         }
//         // Check that no properties were altered
//         CHECK(g.getNumOfVertices() == 2);
//         CHECK(g.getNumOfEdges() == 3);
//         CHECK(g.isWeightedGraph() == false);
//         CHECK(g.isUndirectedGraph() == false);
//     }
// }