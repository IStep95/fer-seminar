#include "Vertex.h"
#include <iostream>
#include <string>
using namespace std;

Vertex::Vertex(){}
Vertex::~Vertex(){}

Vertex::Vertex(long _id)
{
	id = _id;
}

Vertex::Vertex(long _id, string _data)
{
    id = _id;
    data = _data;
}

long Vertex::GetId()
{
	return id;
}

string Vertex::GetData()
{
	return data;
}

void Vertex::AddNeighbourVertex(Vertex *vertex)
{
	std::list<Vertex>::iterator it;
	for (it = neighbours.begin(); it != neighbours.end(); ++it)
	{
    	if (it->GetId() == vertex->GetId()) return;
    }
    neighbours.push_back(*vertex);
}

list<Vertex> Vertex::GetNeighbours()
{
	return neighbours;
}