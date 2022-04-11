#ifndef GRAPH_UTILS_H
#define GRAPH_UTILS_H

#include <unordered_map>
#include <queue>
#include "WeightedGraph.h"

template <class VertexIndexType, class EdgeWeightType>
std::unordered_map<VertexIndexType, EdgeWeightType> getDistancesToVertecies(const WeightedGraph<VertexIndexType, EdgeWeightType>& graph, VertexIndexType fromVertex)
{
	std::queue<VertexIndexType> queue;
	std::unordered_map<VertexIndexType, EdgeWeightType> verteciesDistance;

	queue.push(fromVertex);
	verteciesDistance.insert(std::pair<VertexIndexType, EdgeWeightType>(fromVertex, 0));

	while (!queue.empty())
	{
		auto currentVertex = queue.front();
		queue.pop();
		auto currentWeight = verteciesDistance.find(currentVertex)->second;
		for (auto relatedVertex : graph.GetRelatedVertecies(currentVertex))
		{
			auto savedDistance = verteciesDistance.find(relatedVertex);
			if (savedDistance == verteciesDistance.end())
			{
				verteciesDistance.insert(std::pair<VertexIndexType, EdgeWeightType>(
					relatedVertex, currentWeight + graph.GetEdge(currentVertex, relatedVertex).getWeight()
				));
				queue.push(relatedVertex);
			}
			else
			{
				auto edgeToRelatedVertexFromCurrent = graph.GetEdge(currentVertex, relatedVertex);

				if (currentWeight + edgeToRelatedVertexFromCurrent.getWeight() < savedDistance->second)
				{
					verteciesDistance.insert(std::pair<VertexIndexType, EdgeWeightType>(
						relatedVertex, currentWeight + graph.GetEdge(currentVertex, relatedVertex).getWeight()
					));

					for (auto vertexToUpdate : graph.GetRelatedVertecies(relatedVertex))
					{
						auto vertexToUpdateDistance = verteciesDistance.find(vertexToUpdate);
						if (vertexToUpdateDistance != verteciesDistance.end() && vertexToUpdateDistance->second <= graph.GetEdge(relatedVertex, vertexToUpdate).getWeight())
						{
							queue.push(vertexToUpdate);
						}
					}
				}
			}
		}
	}

	return verteciesDistance;
}

template <class VertexIndexType, class EdgeWeightType>
EdgeWeightType calculateGraphVertexEccentricity(const WeightedGraph<VertexIndexType, EdgeWeightType>& graph, VertexIndexType fromVertex)
{
	auto distances = getDistancesToVertecies<VertexIndexType, EdgeWeightType>(graph, fromVertex);
	return std::max_element(distances.begin(), distances.end(), [](std::pair<VertexIndexType, EdgeWeightType> a, std::pair<VertexIndexType, EdgeWeightType> b) -> bool {
		return a.second < b.second;
	})->second;
}

template <class VertexIndexType, class EdgeWeightType>
std::unordered_set<VertexIndexType> calculateGraphCenterOfGravity(const WeightedGraph<VertexIndexType, EdgeWeightType>& graph)
{
	auto vertecies = graph.GetVertecies();
	std::unordered_map<VertexIndexType, EdgeWeightType> verteciesEccentricity;
	for (auto vertex : vertecies)
	{
		auto eccentricity = calculateGraphVertexEccentricity(graph, vertex);
		verteciesEccentricity.insert(std::pair<VertexIndexType, EdgeWeightType>(vertex, eccentricity));
	}

	EdgeWeightType minEccentricity = verteciesEccentricity.begin()->second;
	std::unordered_set<VertexIndexType> centerOfGravity{verteciesEccentricity.begin()->first};
	for (auto vertexEccentricity : verteciesEccentricity)
	{
		if (minEccentricity > vertexEccentricity.second)
		{
			centerOfGravity.clear();
			centerOfGravity.insert(vertexEccentricity.first);
			minEccentricity = vertexEccentricity.second;
		}
		else if (minEccentricity == vertexEccentricity.second)
		{
			centerOfGravity.insert(vertexEccentricity.first);
		}
	}

	return centerOfGravity;
}

#endif // GRAPH_UTILS_H
