#include "graph_calculator.h"
#include "SquareMatrix.h"

constexpr int MAX_GRAPH_SIZE = 10000;
constexpr int EMPTY_EDGE = -1;
constexpr int MAX_INT = std::numeric_limits<int>::max();
constexpr int DETACHED_VERTEX_ECCENTRICITY = -2;

int calculateEccentricityForGraphVertex(const SquareMatrix<int>& matrix, int vertex);

std::vector<int> getDistancesToVertecies(const SquareMatrix<int>& matrix, int fromVertex);

std::vector<int> calculateGraphCenterOfGravity(const std::vector<GraphEdge>& graphEdges)
{
	SquareMatrix<int> matrix(MAX_GRAPH_SIZE, EMPTY_EDGE);
	for (const GraphEdge& graphEdge : graphEdges)
	{
		matrix.SetValue(graphEdge.fromVertex, graphEdge.toVertex, 1);
		matrix.SetValue(graphEdge.toVertex, graphEdge.fromVertex, 1);
	}

	std::vector<int> verticiesEccentricities(matrix.GetSize());
	for (int i = 0; i < matrix.GetSize(); i++)
	{
		bool isDetachedVertex = true;
		for (int j = 0; j < matrix.GetSize(); j++)
		{
			if (matrix.GetValue(i, j) != EMPTY_EDGE)
			{
				isDetachedVertex = false;
				break;
			}
		}

		verticiesEccentricities[i] = !isDetachedVertex
			? calculateEccentricityForGraphVertex(matrix, i)
			: DETACHED_VERTEX_ECCENTRICITY;
	}

	std::vector<int> graphCenterOfGravity;
	int min = MAX_INT;
	for (int i = 0; i < matrix.GetSize(); i++)
	{
		if (verticiesEccentricities[i] == DETACHED_VERTEX_ECCENTRICITY)
		{
			continue;
		}

		if (verticiesEccentricities[i] < min)
		{
			min = verticiesEccentricities[i];
			graphCenterOfGravity.clear();
			graphCenterOfGravity.push_back(i);
		}
		else if (verticiesEccentricities[i] == min)
		{
			min = verticiesEccentricities[i];
			graphCenterOfGravity.push_back(i);
		}
	}

	return graphCenterOfGravity;
}

int calculateEccentricityForGraphVertex(const SquareMatrix<int>& matrix, int vertex)
{
	auto distances = getDistancesToVertecies(matrix, vertex);
	return *std::max_element(
		distances.begin(),
		distances.end(),
		[=](int a, int b) -> bool {
			if (a == MAX_INT) return true;
			if (b == MAX_INT) return false;
			return a < b;
		}
 	);
}

std::vector<int> getDistancesToVertecies(const SquareMatrix<int>& matrix, int fromVertex)
{
	std::vector<int> weights(matrix.GetSize(), std::numeric_limits<int>::max());
	weights[fromVertex] = 0;
	std::vector<bool> visited(matrix.GetSize(), false);

	int minIndex, minWeight;
	do
	{
		minIndex = MAX_INT;
		minWeight = MAX_INT;

		for (int i = 0; i < weights.size(); i++)
		{
			if (!visited[i] && weights[i] < minWeight)
			{
				minIndex = i;
				minWeight = weights[i];
			}
		}

		if (minIndex != MAX_INT)
		{
			for (int j = 0; j < matrix.GetSize(); j++)
			{
				if (
					matrix.GetValue(minIndex, j) != EMPTY_EDGE
					&& !visited[j]
					&& weights[j] > minWeight + matrix.GetValue(minIndex, j)
				){
					weights[j] = minWeight + matrix.GetValue(minIndex, j);
				}
			}

			visited[minIndex] = true;
		}
	}
	while (minIndex != MAX_INT);

	return weights;
}





