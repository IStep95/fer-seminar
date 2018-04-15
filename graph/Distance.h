#ifndef DISTANCE_H
#define DISTANCE_H
#include "Vertex.h"

class Distance
{
	private:
		int distance;
		Vertex returnVertex;
	public:
		Distance();
		~Distance();
		int GetDistance();
		Vertex GetReturnVertex();
		void SetDistance(int);
		void SetReturnVertex(Vertex);
};
#endif