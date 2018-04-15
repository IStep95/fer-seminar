#include <iostream>
#include <list>
#include <string>
#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"
#include "Distance.h"

using namespace std;

void fillDistances(Distance *distances, int arrayLength, int value)
{
	for (int i = 0; i < arrayLength; i++)
	{
		distances[i].SetDistance(value);
	}
}

Distance* shortestReachBFS(int startId, Graph *graph)
{
	int vertexesNum = graph->GetAllVertexes().size();
	Distance *distances = new Distance[vertexesNum];

	list<int> queue;
	queue.push_back(startId);
	
	fillDistances(distances, vertexesNum, -1);
	distances[startId].SetDistance(0);

	while (!queue.empty())
	{
		int vertexId = queue.front();
		Vertex vertex = graph->GetVertex(vertexId);
		queue.erase(queue.begin());
		list<Vertex>::iterator it;
		list<Vertex>neighbours = vertex.GetNeighbours();

		for (it = neighbours.begin(); it != neighbours.end(); ++it)
		{
			int neighbourId = it->GetId();
			Vertex neighbour = graph->GetVertex(neighbourId);
			int newDistance = distances[vertexId].GetDistance() + graph->GetEdgeWeight(vertex, neighbour);
			
			if (distances[neighbourId].GetDistance() == -1 || newDistance < distances[neighbourId].GetDistance())
			{
				distances[neighbourId].SetDistance(newDistance);
				distances[neighbourId].SetReturnVertex(vertex);
				queue.push_back(neighbourId);
			}
		}
	}
	return distances;
}

int main()
{
    Graph *graph = new Graph();

    graph->AddEdge(0, 1, 4);
    graph->AddEdge(0, 2, 2);
    graph->AddEdge(0, 3, 5);
    graph->AddEdge(1, 6, 2);
    graph->AddEdge(1, 2, 1);
    graph->AddEdge(2, 6, 3);
    graph->AddEdge(2, 5, 2);
    graph->AddEdge(2, 4, 4);
    graph->AddEdge(2, 3, 8);
    graph->AddEdge(3, 4, 1);
    graph->AddEdge(4, 5, 6);
    graph->AddEdge(5, 6, 10);

    graph->SetVertexData(0, "3");
    graph->SetVertexData(1, "1");
    graph->SetVertexData(2, "4");
    graph->SetVertexData(3, "6");
    graph->SetVertexData(4, "7");
    graph->SetVertexData(5, "5");
    graph->SetVertexData(6, "2");

	Distance *distances = shortestReachBFS(0, graph);
	for (int i = 0; i < graph->GetAllVertexes().size(); ++i)
	{
		cout << distances[i].GetDistance() << " ";
		cout << graph->GetVertex(i).GetData() << "\n";
	}
    return 0;
}