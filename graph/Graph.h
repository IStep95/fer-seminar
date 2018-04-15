#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <map>
#include <string>
#include "Edge.h"
#include "Vertex.h"
using namespace std;

class Graph
{    
  	private:
  		
    	
    public:
    	std::list<Edge> AllEdges;
    	std::map<long, Vertex> AllVertexes;
    	Graph();
    	~Graph();
    	void AddVertex(long,string);
    	void AddVertex(Vertex);
    	Vertex GetVertex(long);
    	void AddEdge(long,long,int);

    	list<Edge> GetAllEdges();
        list<Vertex> GetAllVertexes();
};

#endif