#include "Graph.h"
#include <string>
#include "Vertex.h"
#include <iostream>
using namespace std;
Graph::Graph() {}

void Graph::AddVertex(Vertex vertex)
{
	if (AllVertexes.count(vertex.GetId())) return;
	AllVertexes.insert(std::pair<long, Vertex>(vertex.GetId(), vertex));
}

void Graph::AddVertex(long id, string data)
{
	Vertex *vertex = new Vertex(id, data);
	if (AllVertexes.count(id)) 
	{	
		return;
	}
	AllVertexes.insert(std::pair<long, Vertex>(id, *vertex));
}

Vertex Graph::GetVertex(long id)
{
	return AllVertexes.find(id)->second;
}

void Graph::AddEdge(long id1, long id2, int weight)
{
	Vertex *vertex1 = new Vertex();
	Vertex *vertex2 = new Vertex();
	bool edgeExist = false;
	bool vertex1Exist = false;
	bool vertex2Exist = false;

	if (AllVertexes.count(id1))
	{
		vertex1Exist = true;
		delete(vertex1);
		vertex1 = &AllVertexes.find(id1)->second;
	}
	else 
	{
		delete(vertex1);
		vertex1 = new Vertex(id1);	
	}

	if (AllVertexes.count(id2))
	{
		vertex2Exist = true;
		delete(vertex2);
		vertex2 = &AllVertexes.find(id2)->second;
	}
	else 
	{
		delete(vertex2);
		vertex2 = new Vertex(id2);
	}

	edgeExist = vertex1Exist && vertex2Exist;
	if (edgeExist) return;

	vertex1->AddNeighbourVertex(vertex2);
	vertex2->AddNeighbourVertex(vertex1);
	if (!vertex1Exist) AddVertex(*vertex1);
	if (!vertex2Exist) AddVertex(*vertex2);

	Edge *edge = new Edge(*vertex1, *vertex2, weight);
	AllEdges.push_back(*edge);
}

list<Edge> Graph::GetAllEdges()
{
	return AllEdges;
}

list<Vertex> Graph::GetAllVertexes()
{
	list<Vertex> *list = new ::list<Vertex>();
	for(map<long,Vertex>::iterator it = AllVertexes.begin(); it != AllVertexes.end(); ++it) 
	{
		list->push_back(it->second);
	}
	return *list;
}
