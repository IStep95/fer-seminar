#include "Graph.h"
#include "Vertex.h"
#include <string>
#include <iostream>
#include <stdexcept>

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
	if (AllVertexes.count(id)) return;
	AllVertexes.insert(std::pair<long, Vertex>(id, *vertex));
}

bool Graph::ContainsVertex(std::map<long, Vertex> map, Vertex vertex)
{
	for(std::map<long,Vertex>::iterator it = AllVertexes.begin(); it != AllVertexes.end(); ++it) 
	{
		if (it->second.Equals(vertex)) return true;
	}
	return false;
}

bool Graph::ContainsVertex(std::map<long, Vertex> map, long id)
{
	Vertex vertex = Vertex(id);
	return ContainsVertex(map, vertex);
}

Vertex Graph::GetVertex(long id)
{
	if (!ContainsVertex(AllVertexes, id)) throw invalid_argument("No such element.");
	return AllVertexes.find(id)->second;
}

bool Graph::ContainsEdge(std::list<Edge> list, Edge edge)
{
	std::list<Edge>::iterator it;
	for (it = list.begin(); it != list.end(); ++it)
	{
		if (it->Equals(edge)) return true;
	}
	return false;
}

void Graph::SetVertexData(long id, string data)
{
	std::map<long, Vertex>::iterator it = AllVertexes.find(id);
	if (it != AllVertexes.end()) it->second.SetData(data);
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

	Edge *edge = new Edge(*vertex1, *vertex2, weight);
	edgeExist = ContainsEdge(GetAllEdges(), *edge);
	if (edgeExist) return;

	vertex1->AddNeighbourVertex(vertex2);
	vertex2->AddNeighbourVertex(vertex1);

	if (!vertex1Exist) AddVertex(*vertex1);
	if (!vertex2Exist) AddVertex(*vertex2);

	AllEdges.push_back(*edge);
}

int Graph::GetEdgeWeight(Vertex v1, Vertex v2)
{
	std::list<Edge>::iterator it;
	for (it = AllEdges.begin(); it != AllEdges.end(); ++it)
	{
		if (it->GetVertex1().GetId() == v1.GetId() && it->GetVertex2().GetId() == v2.GetId()) return it->GetWeight();

		if (it->GetVertex1().GetId() == v2.GetId() && it->GetVertex2().GetId() == v1.GetId()) return it->GetWeight();
	}

	// Edge not found in graph.
	return -1;
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
