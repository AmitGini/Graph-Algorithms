//207275215
#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <vector>

namespace ariel {
	typedef std::vector<std::vector<int>> Matrix;

	class Graph {
		private:
		Matrix myMatrix;
		Matrix myTransposeMatrix;
		std::size_t numVertices;
		std::size_t numEdges;
		bool isUndirected;
		bool isWeighted;

		void updateGraphProperty();

		public:
		Graph();
		~Graph();

		void loadGraph(const Matrix& matrix);
		void printGraph() const;

		// Getter methods
		const Matrix& getMatrix() const;
		const Matrix& getTransposeMatrix() const;
		bool isUndirectedGraph() const;
		bool isWeightedGraph() const;
		std::size_t getNumOfVertices() const;
		std::size_t getNumOfEdges() const;

	};
}

#endif
