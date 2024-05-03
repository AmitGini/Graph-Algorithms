#include <iostream>
#include "Graph.hpp"

#define UN_WEIGHTED_EDGE_VALUE 1
#define NO_EDGE_VALUE 0

using namespace ariel;

typedef std::vector<std::vector<int>> Matrix;


Graph::Graph() : isUndirectedGraph(false), isWeightedGraph(false) {};



void Graph::updateGraphProperty() 
	{
		// Get the size of the matrix
		std::size_t matrixSize = myMatrix.size();
		// Transpose the matrix, initial with row, column size.
		Matrix transpose(matrixSize, std::vector<int>(matrixSize));

		// Iterate over the matrix and fill the transpose matrix
		for (std::size_t i = 0; i < matrixSize; ++i) 
		{
			for (std::size_t j = 0; j < matrixSize; ++j) 
			{
				transpose[j][i] = myMatrix[i][j];

				if ( !(this->isUndirectedGraph) 
					&& myMatrix[i][j] != NO_EDGE_VALUE 
					&& myMatrix[i][j] != UN_WEIGHTED_EDGE_VALUE ) 
				{
					this->isWeightedGraph = true;
				}
			}
		}
		this->isUndirectedGraph = (myMatrix == transpose);
	}


// Getter for myMatrix
const Matrix& Graph::getMatrix() const {return myMatrix;}

// Getter for directed graph status
bool Graph::getIsUndirectedGraph() const { return this->isUndirectedGraph; }

// Getter for weighted graph status
bool Graph::getIsWeightedGraph() const { return this->isWeightedGraph; }

// Load the graph from the input matrix
void Graph::loadGraph(const Matrix& inputMatrix)
{
	if(inputMatrix.empty())
	{
		throw std::invalid_argument("Invalid graph: The graph is empty.");
	}
	else if(inputMatrix.size() != inputMatrix[0].size())
	{

		throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
	}

	this->myMatrix = inputMatrix;
	updateGraphProperty();
}

/*
	This function iterates over each row in the matrix,
	and then over each cell in the row.
	If the cell is not zero, it increments the edge count.
	Since this is an undirected graph,
	each edge is counted twice (once for each vertex it connects),
	so we divide the total count by 2 to get the actual number of edges.
	Finally, it prints the number of vertices and edges.
*/
void Graph::printGraph() const{
	std::size_t vertices = (this->myMatrix).size();
	int edges = 0;
	for (const auto& row : myMatrix) 
	{
		for (int cell : row) 
		{
			if (cell != 0) 
			{
				edges++;
			}
		}
	}
	
	// If the graph is undirected, each edge is counted twice
	if(isUndirectedGraph) 
	{
		edges /= 2;
	}
	std::cout << "Graph with " << vertices << " vertices and " << edges << " edges." << std::endl;
}



