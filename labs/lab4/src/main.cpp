#include <iostream>
#include <vector>
#include <memory>
#include "lib/WeightedGraph.h"

std::unique_ptr<std::vector<int>> ProccessNode(int currVertex, std::vector<int> route, const WeightedGraph<int, int>& graph, int startVertex)
{
	route.push_back(currVertex);
	for (auto relatedVertex : graph.GetRelatedVertecies(currVertex))
	{
		if (std::find(route.begin() + 1, route.end(), relatedVertex) != route.end())
		{
			continue;
		}

		if (relatedVertex == startVertex)
		{
			return std::make_unique<std::vector<int>>(route);
		}
		else
		{
			return ProccessNode(relatedVertex, route, graph, startVertex);
		}
	}
	return nullptr;
}

void OptimizeGraph(WeightedGraph<int, int>& graph, const std::vector<int>& loopVertecies)
{
	std::cout << "=== Begin optimization iteration ===" << std::endl;

	std::cout << "Loop optimiaztion: ";
	for (auto node : loopVertecies)
	{
		std::cout << node << " ";
	}
	std::cout << std::endl;

	auto edgeToOptimize = graph.GetEdge(loopVertecies[0], loopVertecies[1]);
	std::cout << "Remove edge (" << edgeToOptimize.getFromVertex() << ", " << edgeToOptimize.getToVertex() << ", " << edgeToOptimize.getWeight() << ")" << std::endl;
	graph.RemoveEdge(loopVertecies[0], loopVertecies[1]);

	int vertexWeight = edgeToOptimize.getWeight();
	for (int i = 1; i < loopVertecies.size() - 1; i++)
	{
		auto curEdge = graph.GetEdge(loopVertecies[i], loopVertecies[i + 1]);
		std::cout <<
			"Reduce edge weight "
			<< "(" << curEdge.getFromVertex() << ", " << curEdge.getToVertex() << ")"
			<< " from " << curEdge.getWeight() << " to " << curEdge.getWeight() - vertexWeight
			<< (curEdge.getWeight() - vertexWeight == 0 ? " and delete edge " : "")
			<< std::endl;

		if (curEdge.getWeight() - vertexWeight == 0)
		{
			graph.RemoveEdge(loopVertecies[i], loopVertecies[i + 1]);
		}
		else
		{
			graph.UpdateEdge(loopVertecies[i], loopVertecies[i + 1], curEdge.getWeight() - vertexWeight);
		}
	}

	std::cout << "=== Optimization iteration complete ===" << std::endl;
}

int main()
{
	WeightedGraph<int, int> graph;

	int amountOfEdges;
	std::cin >> amountOfEdges;

	int fromVertex, toVertex, weight;
	for (int i = 0; i < amountOfEdges; i++)
	{
		std::cin >> fromVertex >> toVertex >> weight;
		graph.AddEdge(fromVertex, toVertex, weight);
	}

	for (int i = 0; i < amountOfEdges - 1; i++)
	{
		auto minEdge = graph.FindMinEdge();
		std::vector<int> route;

		auto startVertex = minEdge.getFromVertex();
		auto currVertex = minEdge.getToVertex();
		route.push_back(startVertex);

		auto loop = ProccessNode(currVertex, route, graph, startVertex);
		if (loop != nullptr)
		{
			loop->push_back(startVertex);
			OptimizeGraph(graph, *loop);
		}
		else
		{
			graph.RemoveEdge(minEdge.getFromVertex(), minEdge.getToVertex());
		}
	}

	return EXIT_SUCCESS;
}
