#ifndef ALGORITHMS_HPP
#define ALGORITHMS_HPP

#include "Graph.hpp"

namespace ariel{
  
  class Algorithms{
    
    private:
      Algorithms();

    public:
      static bool isConnected(const Graph &graph);
      static std::string shortestPath(const Graph &graph, int src, int dest);
      static std::string isContainsCycle(const Graph &graph);
      static std::string isBipartite(const Graph &graph);
      static std::string negativeCycle(const Graph &graph);
      

  };
}

#endif