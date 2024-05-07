#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel {
	typedef std::vector<std::vector<int>> Matrix;

	class Graph {
		private:
		Matrix myMatrix;
		std::size_t numVertices;
		std::size_t numEdges;
		bool isUndirectedGraph;
		bool isWeightedGraph;

		void updateGraphProperty();

		public:
		Graph();

		// Getter methods
		const Matrix& getMatrix() const;
		bool getIsUndirectedGraph() const;
		bool getIsWeightedGraph() const;
		std::size_t getNumOfVertices() const;
		std::size_t getNumOfEdges() const;

		void loadGraph(const Matrix& matrix);
		void printGraph() const;
	};
}

#endif
