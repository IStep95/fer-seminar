#include "Edge.h"
#include "Vertex.h"

Edge::~Edge(){}

Edge::Edge(Vertex _vertex1, Vertex _vertex2, int _weight)
{
    vertex1 = _vertex1;
    vertex2 = _vertex2;
    weight  = _weight;
}

Vertex Edge::GetVertex1()
{
	return vertex1;
}

Vertex Edge::GetVertex2()
{
	return vertex2;
}

int Edge::GetWeight()
{
	return weight;
}

bool Edge::Equals(Edge edge)
{
	if (vertex1.Equals(edge.GetVertex1()) && vertex2.Equals(edge.GetVertex2()) && weight == edge.GetWeight()) return true;
	if (vertex1.Equals(edge.GetVertex2()) && vertex2.Equals(edge.GetVertex1()) && weight == edge.GetWeight()) return true;

	return false;
}