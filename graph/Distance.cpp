#include "Distance.h"

Distance::Distance()  {}
Distance::~Distance() {}

int Distance::GetDistance()
{
	return distance;
}

Vertex Distance::GetReturnVertex()
{
	return returnVertex;
}

void Distance::SetDistance(int _distance)
{
	distance = _distance;
}

void Distance::SetReturnVertex(Vertex _returnVertex)
{
	returnVertex = _returnVertex;
}
