#include "lib/String.h"
#include "lib/Vector.h"

int main()
{
	Vector<String> intVector;

	String s1("one");

	String s2("two");

	String s3("three");

	intVector.push(s1);

	intVector.push(s2);

	intVector.push(s3);

	auto v = intVector.popSlice(1, 2);

	for (int i = 0; i < 2; ++i)
	{
		std::cout << v.get(i) << std::endl;
	}

	std::cout << "end" << std::endl;

	std::cout << "Test test test" << std::endl;

	return 0;
}