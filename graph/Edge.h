#ifndef EDGE_H
#define EDGE_H
#include "Vertex.h"
using namespace std;

class Edge
{
	private:
        Vertex vertex1;
        Vertex vertex2;
        int weight;
    public:
        Edge(Vertex,Vertex,int);
        ~Edge();
        Vertex GetVertex1();
        Vertex GetVertex2();
        int GetWeight();
        bool Equals(Edge);
};
#endif