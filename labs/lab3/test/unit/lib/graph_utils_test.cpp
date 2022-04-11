#include "../../../../../lib/catch.hpp"
#include "../../../src/lib/WeightedGraph.h"
#include "../../../src/lib/graph_utils.h"

TEST_CASE("Graph utils test", "[graph_utils]")
{
	SECTION("Get distances to vertecies in sigle way graph")
	{
		// Graph
		//
		//  2 - 1
		//      |
		//	6 - 3 - 4 - 5
		//      |
		//  7 - 8

		WeightedGraph<int, int> graph;
		graph.AddEdge(1, 2, 1);
		graph.AddEdge(2, 1, 1);

		graph.AddEdge(1, 3, 1);
		graph.AddEdge(3, 1, 1);

		graph.AddEdge(3, 6, 1);
		graph.AddEdge(6, 3, 1);

		graph.AddEdge(3, 8, 1);
		graph.AddEdge(8, 3, 1);

		graph.AddEdge(3, 4, 1);
		graph.AddEdge(4, 3, 1);

		graph.AddEdge(8, 7, 1);
		graph.AddEdge(7, 8, 1);

		graph.AddEdge(4, 5, 1);
		graph.AddEdge(5, 4, 1);

		auto result = getDistancesToVertecies<int, int>(graph, 2);
		REQUIRE(result == std::unordered_map<int, int>{
					{2, 0},
					{1, 1},
					{3, 2},
					{6, 3},
					{8, 3},
					{4, 3},
					{7, 4},
					{5, 4},
				});
	}

	SECTION("Get distances to vertecies in cycled graph")
	{
		// Graph
		//
		//  2 - 1
		//  |   |
		//	6 - 3 - 4 - 5
		//      |
		//  7 - 8

		WeightedGraph<int, int> graph;
		graph.AddEdge(1, 2, 1);
		graph.AddEdge(2, 1, 1);

		graph.AddEdge(2, 6, 1);
		graph.AddEdge(6, 2, 1);

		graph.AddEdge(1, 3, 1);
		graph.AddEdge(3, 1, 1);

		graph.AddEdge(3, 6, 1);
		graph.AddEdge(6, 3, 1);

		graph.AddEdge(3, 8, 1);
		graph.AddEdge(8, 3, 1);

		graph.AddEdge(3, 4, 1);
		graph.AddEdge(4, 3, 1);

		graph.AddEdge(8, 7, 1);
		graph.AddEdge(7, 8, 1);

		graph.AddEdge(4, 5, 1);
		graph.AddEdge(5, 4, 1);

		auto result = getDistancesToVertecies(graph, 2);
		REQUIRE(result == std::unordered_map<int, int>{
					{2, 0},
					{1, 1},
					{3, 2},
					{6, 1},
					{8, 3},
					{4, 3},
					{7, 4},
					{5, 4},
				});
	}

	SECTION("Find graph center of gravity")
	{
		// Graph
		//
		//  2 - 1
		//      |
		//	6 - 3 - 4 - 5
		//      |
		//  7 - 8

		WeightedGraph<int, int> graph;

		graph.AddEdge(1, 2, 1);
		graph.AddEdge(2, 1, 1);

		graph.AddEdge(1, 3, 1);
		graph.AddEdge(3, 1, 1);

		graph.AddEdge(3, 6, 1);
		graph.AddEdge(6, 3, 1);

		graph.AddEdge(3, 8, 1);
		graph.AddEdge(8, 3, 1);

		graph.AddEdge(3, 4, 1);
		graph.AddEdge(4, 3, 1);

		graph.AddEdge(8, 7, 1);
		graph.AddEdge(7, 8, 1);

		graph.AddEdge(4, 5, 1);
		graph.AddEdge(5, 4, 1);

		REQUIRE(calculateGraphCenterOfGravity(graph) == std::unordered_set<int>{3});
	}
}