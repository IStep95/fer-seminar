#include <iostream>
#include <list>
#include <string>
#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;


int main()
{
    Graph *graph = new Graph();
    graph->AddVertex(0);
    Vertex v = graph->GetVertex(0);
	graph->AddEdge(0, 1, 2);
	graph->AddEdge(0, 2, 2);

	//cout << "Graf velicina vrhova " << graph->AllVertexes.size() << "\n";
	//cout << "Graf velicina bridova " << graph ->AllEdges.size() << "\n";

	std::list<Edge>::iterator it;
	for (it = graph->AllEdges.begin(); it != graph->AllEdges.end(); ++it)
	{
	    //std::cout << it->GetVertex1().GetId() << " " << it->GetVertex1().GetData() << "\n";
	    //std::cout << it->GetVertex2().GetId() << " " << it->GetVertex2().GetData() << "\n";
	}

		
	std::list<Vertex> l = graph->GetAllVertexes();

	//cout << "Velicina liste vrhova:" << l.size() << "\n";
	std::list<Vertex> l2;
	std::list<Vertex>::iterator it2;
	std::list<Vertex>::iterator it3;
	for (it2 = l.begin(); it2 != l.end(); ++it2)
	{
		cout << "Vertex: " << it2->GetId() << "\n";
		cout << "Number of neighbours: " << it2->GetNeighbours().size() << "\n";
		l2 = it2 ->GetNeighbours();
		for (it3 = l2.begin(); it3 != l2.end(); ++it3)
		{
			//cout << "iteration\n";
			cout << it3->GetId() << " ";
		}
		cout << "\n";
	}


    return 0;
}