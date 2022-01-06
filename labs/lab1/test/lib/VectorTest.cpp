/**
 * Self written vector unit tests
 */

#ifndef VECTOR_H_TEST
#define VECTOR_H_TEST

#define CATCH_CONFIG_MAIN
#include "../../../../lib/catch.hpp"
#include "../../src/lib/Vector.h"
#include "../../src/lib/String.h"

TEST_CASE("vector can push and get elements", "[vector_push_get]")
{
	Vector<int> intVector;

	intVector.push(1);
	intVector.push(2);
	intVector.push(3);

	REQUIRE(intVector.get(0) == 1);
	REQUIRE(intVector.get(1) == 2);
	REQUIRE(intVector.get(2) == 3);
}

TEST_CASE("vector can pop and push complex elements", "[vector_complex_push_pop]")
{
	Vector<String> stringVector;

	String s1("one");
	String s2("two");
	String s3("three");

	stringVector.push(s1);
	stringVector.push(s2);
	stringVector.push(s3);

	stringVector.get(0);
}

#endif