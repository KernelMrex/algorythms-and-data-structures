#include <iostream>
#include <vector>
#include "lib/graph_calculator.h"

constexpr int MAX_GRAPH_SIZE = 10000;

int main()
{
	std::vector<GraphEdge> graphEdges;

	int amountVertexes;
	std::cin >> amountVertexes;

	int fromVertex, toVertex;
	for (int i = 0; i < (amountVertexes - 1) && std::cin; i++)
	{
		std::cin >> fromVertex >> toVertex;
		graphEdges.emplace_back(fromVertex - 1, toVertex - 1);
	}

	if (!std::cin.eof() && std::cin.fail())
	{
		std::cout << "Error while reading input values" << std::endl;
		return EXIT_FAILURE;
	}

	auto centersOfGravity = calculateGraphCenterOfGravity(graphEdges);
	std::cout << centersOfGravity.size() << std::endl;
	for (auto centerOfGravity : centersOfGravity)
	{
		std::cout << centerOfGravity + 1 << ' ';
	}
	std::cout << std::endl;
}
