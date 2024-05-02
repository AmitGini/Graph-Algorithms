
#include <string>
#include "Graph.hpp"
#include "Algorithms.hpp"


using ariel::Matrix;
using ariel::Graph;

namespace ariel
{
    class Algorithms
    {
        private:
            Algorithms();

        public:
            
            static bool isConnected(const Graph &graph)
            {
                Matrix matrix = graph.getMatrix();
                for(std::size_t i = 0; i < matrix.size(); ++i)
                {
                    for(std::size_t j = 0; j < matrix.size(); ++j)
                    {
                        if(matrix[i][j] == 0)
                        {
                            return false;
                        }
                    }
                }
            }
            static std::string shortestPath(const Graph &graph, int src, int dest);
            static std::string isContainsCycle(const Graph &graph);
            static std::string isBipartite(const Graph &graph);
            static std::string negativeCycle(const Graph &graph);
    };

}