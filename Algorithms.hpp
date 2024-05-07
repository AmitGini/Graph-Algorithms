#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include <string>
#include "Graph.hpp"

using ariel::Graph;
using std::string;

namespace ariel{

  class Algorithms{
    
    private:
      Algorithms();
      //static string bfs(const Graph &graph, int start, int end);
      //static string negCycleBF(const Graph &graph, int start, int end);
      static bool isBipartiteHelper(const Matrix &edges, size_t numVertices, size_t src, std::vector<int> &color);
      static bool algoBF(const Graph &graph, std::vector<int> &dist, std::vector<size_t> &prev);
      static string reconstructCycle(size_t startVertex, size_t endVertex, const std::vector<size_t>& prev);


    public:
      static bool isConnected(const Graph &graph);
      static bool isContainsCycle(const Graph &graph);
      static string shortestPath(const Graph &graph, size_t src, size_t dest);
      static string isBipartite(const Graph &graph);
      static string negativeCycle(const Graph &graph);


  };
}

#endif