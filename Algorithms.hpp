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
      static bool isBipartiteHelper(const Graph &graph, size_t numVertices,  std::vector<size_t> &color, size_t src);
      static bool algoBF(const Graph &graph, std::vector<int> &dist, std::vector<size_t> &prev);
      static bool BFS(const Graph &graph, std::vector<int> &dist, size_t src, std::vector<size_t> &prev, size_t dest);
      static bool algoDFS(const Graph &graph, std::vector<int> &dist, std::vector<size_t> &prev);
      static bool algoDFSVisit(const Graph &graph, size_t vertex, std::vector<size_t> &color, size_t currTime, std::vector<size_t> &discTime, std::vector<size_t> &finishTime, std::vector<size_t> &prev);
      static bool isConnectedHelper(const Matrix& edges);
      static string reconstructCycle(size_t startVertex, const std::vector<size_t>& prev, size_t endVertex);


    public:
      static bool isConnected(const Graph &graph);
      static bool isContainsCycle(const Graph &graph);
      static string shortestPath(const Graph &graph, size_t src, size_t dest);
      static string isBipartite(const Graph &graph);
      static string negativeCycle(const Graph &graph);


  };
}

#endif