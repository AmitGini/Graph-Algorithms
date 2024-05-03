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
      static string bfs(const Graph &graph, int start, int end);
      static string negCycleBF(const Graph &graph, int start, int end);

    public:
      static bool isConnected(const Graph &graph);
      static bool isContainsCycle(const Graph &graph);
      static string shortestPath(const Graph &graph, size_t src, size_t dest);
      static string isBipartite(const Graph &graph);
      static string negativeCycle(const Graph &graph);
      

  };
}

#endif