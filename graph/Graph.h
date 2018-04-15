#ifndef GRAPH_H
#define GRAPH_H
#include <list>
#include <map>
#include <string>
#include <iostream>
#include "Edge.h"
#include "Vertex.h"
using namespace std;

class Graph
{    
  	private:
  		std::list<Edge> AllEdges;
        std::map<long, Vertex> AllVertexes;
    public:
    	Graph();
    	~Graph();
    	void AddVertex(long,string);
    	void AddVertex(Vertex);
    	Vertex GetVertex(long);
    	void AddEdge(long,long,int);
        int GetEdgeWeight(Vertex,Vertex);
        void SetVertexData(long,string);
        bool ContainsVertex(map<long, Vertex>, long);
        bool ContainsVertex(map<long, Vertex>, Vertex);
        bool ContainsEdge(list<Edge>, Edge);
    	list<Edge> GetAllEdges();
        list<Vertex> GetAllVertexes();

};
#endif