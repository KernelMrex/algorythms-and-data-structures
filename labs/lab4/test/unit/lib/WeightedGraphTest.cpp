#include "../../../../../lib/catch.hpp"
#include "../../../src/lib/WeightedGraph.h"

TEST_CASE("Weighted graph", "[weighted_graph]")
{
	WeightedGraph<int, int> graph;
	graph.AddEdge(1, 1, 1);
	graph.AddEdge(1, 2, 2);
	graph.AddEdge(1, 3, 3);

	SECTION("Weighted graph get distance edge")
	{
		REQUIRE(graph.GetDistanceBetweenRelatedVertecies(1, 1) == 1);
		REQUIRE(graph.GetDistanceBetweenRelatedVertecies(1, 2) == 2);
		REQUIRE(graph.GetDistanceBetweenRelatedVertecies(2, 1) == std::nullopt);
		REQUIRE(graph.GetDistanceBetweenRelatedVertecies(1, 3) == 3);
		REQUIRE(graph.GetDistanceBetweenRelatedVertecies(3, 1) == std::nullopt);
	}

	SECTION("Weighted graph get related vertecies")
	{
		auto relatedVertecies = graph.GetRelatedVertecies(1);
		REQUIRE(relatedVertecies == std::unordered_set<int>{1, 2, 3});
	}
}