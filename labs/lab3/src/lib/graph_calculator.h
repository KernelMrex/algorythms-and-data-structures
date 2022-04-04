#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <vector>

struct GraphEdge
{
	GraphEdge(int fromVertex, int toVertex)
		: fromVertex(fromVertex)
		, toVertex(toVertex)
	{
	}
	int fromVertex;
	int toVertex;
};

std::vector<int> calculateGraphCenterOfGravity(const std::vector<GraphEdge>& graphEdges);

#endif // CALCULATOR_H
