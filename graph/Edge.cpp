#include "Edge.h"
#include "Vertex.h"

Edge::Edge(Vertex _vertex1, Vertex _vertex2, int _weight)
{
    vertex1 = _vertex1;
    vertex2 = _vertex2;
    weight  = _weight;

    // vertex1.AddNeighbourVertex(vertex2);
    // vertex2.AddNeighbourVertex(vertex1);
}

Vertex Edge::GetVertex1()
{
	return vertex1;
}
Vertex Edge::GetVertex2()
{
	return vertex2;
}