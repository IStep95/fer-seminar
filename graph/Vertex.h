#ifndef VERTEX_H
#define VERTEX_H
#include <iostream>
#include <list>
#include <string>
using namespace std;

class Vertex
{
    private:
        long id;
        string data;
    public:
        Vertex();
        ~Vertex();
        Vertex(long);
        Vertex(long, string);
        list<Vertex> neighbours;

        long GetId();
        string GetData();
        list<Vertex> GetNeighbours();
        void SetData(string data);
        void AddNeighbourVertex(Vertex*);
        bool Equals(Vertex);
};
#endif