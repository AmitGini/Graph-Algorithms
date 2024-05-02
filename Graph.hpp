#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel {
	
	typedef std::vector<std::vector<int>> Matrix;

	class Graph {

		private:
			Matrix myMatrix; // Add the 'using' statement for the std::vector class
			bool isUndirectedGraph;
			bool isWeightedGraph;

			void updateGraphProperty();

		public:
			Graph();

			// Getter methods
			const Matrix& getMatrix() const { return myMatrix; }
			bool getIsUndirectedGraph() const { return isUndirectedGraph; }
			bool getIsWeightedGraph() const { return isWeightedGraph; }

			void loadGraph(const std::vector<std::vector<int>>& matrix);
			void printGraph() const;
	};
}

#endif
