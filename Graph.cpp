//207275215
#include <iostream>
#include "Graph.hpp"

constexpr int NONE_WEIGHTED_EDGE = 1;
constexpr int NONE_EDGE = 0;

using namespace ariel;

typedef std::vector<std::vector<int>> Matrix;

Graph::Graph() : numVertices(0), numEdges(0), isUndirected(false), isWeighted(false) {}
Graph::~Graph() = default;

void Graph::updateGraphProperty() 
{
	// Get the size of the matrix
	this->numVertices = myMatrix.size();
	// Transpose the matrix, initial with row, column size.
	Matrix transpose(this->numVertices, std::vector<int>(this->numVertices));

	bool changeFlagWeight = false;

	// Iterate over the matrix and fill the transpose matrix
	for (std::size_t vertexA = 0; vertexA < this->numVertices; ++vertexA)
	{
		for (std::size_t vertexB = 0; vertexB < this->numVertices; ++vertexB) {
			transpose[vertexB][vertexA] = myMatrix[vertexA][vertexB];

			if ( myMatrix[vertexA][vertexB] != NONE_EDGE ) {
				this->numEdges++;

				if(myMatrix[vertexA][vertexB] != NONE_WEIGHTED_EDGE && !changeFlagWeight ) {
					this->isWeighted = true;
					changeFlagWeight = true;
				}
			}
		}
	}
	this->myTransposeMatrix = transpose;
	this->isUndirected = (myMatrix == transpose);

	//If its true the the count of numEdges was not correct.
	if(this->isUndirected) {
		this->numEdges = (this->numEdges % 2 == 0) ? (this->numEdges / 2) : ((this->numEdges / 2) - 1);
	}

}

// Getter for myTransposeMatrix
const Matrix& Graph::getTransposeMatrix() const {return myTransposeMatrix;}

// Getter for myMatrix
const Matrix& Graph::getMatrix() const {return myMatrix;}

// Getter for directed graph status
bool Graph::isUndirectedGraph() const { return this->isUndirected; }

// Getter for weighted graph status
bool Graph::isWeightedGraph() const { return this->isWeighted; }

// Getter for the number of vertices
size_t Graph::getNumOfVertices() const { return this->numVertices; }

// Getter for the number of edges
size_t Graph::getNumOfEdges() const { return this->numEdges; }

// Load the graph from the input matrix
void Graph::loadGraph(const Matrix& inputMatrix)
{
	// init / clean last uploaded graph.
	this->numVertices = 0;
	this->isWeighted = false;
	this->isUndirected = false;

	if(inputMatrix.empty())
	{
		throw std::invalid_argument("Invalid graph: The graph is empty.");
	}

	if(inputMatrix.size() != inputMatrix[0].size())
	{
		throw std::invalid_argument("Invalid graph: The graph is not a square matrix.");
	}

	this->myMatrix = inputMatrix;
	updateGraphProperty();
}

// Print the graph number of vertices and edges
void Graph::printGraph() const {
  std::cout<< "Graph with " << this->numVertices << " vertices and " << this->numEdges << " edges." << std::endl;
}

