#include <iostream>
#include <set>
#include "lib/WeightedGraph.h"
#include "lib/graph_utils.h"

constexpr int MAX_GRAPH_SIZE = 10000;

int main()
{
	WeightedGraph<int, int> graph;

	int amountVertexes;
	std::cin >> amountVertexes;

	int fromVertex, toVertex;
	for (int i = 0; i < (amountVertexes - 1) && std::cin; i++)
	{
		std::cin >> fromVertex >> toVertex;
		graph.AddEdge(fromVertex, toVertex, 1);
		graph.AddEdge(toVertex, fromVertex, 1);
	}

	if (!std::cin.eof() && std::cin.fail())
	{
		std::cout << "Error while reading input values" << std::endl;
		return EXIT_FAILURE;
	}

	auto centersOfGravity = calculateGraphCenterOfGravity(graph);
	std::cout << centersOfGravity.size() << std::endl;
	auto res = std::set(centersOfGravity.begin(), centersOfGravity.end());
	for (auto centerOfGravity : res)
	{
		std::cout << centerOfGravity << ' ';
	}
	return EXIT_SUCCESS;
}
