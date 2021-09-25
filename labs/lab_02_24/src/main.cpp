#include <fstream>
#include <iostream>
#include <optional>

#include "WordCallbackReader/WordCallbackReader.h"

struct Args {
	std::string inputFilePath;
	std::string outputFilePath;
};

std::optional<Args> parseArgs(int argc, char** argv);

int main(int argc, char** argv)
{
	auto args = parseArgs(argc, argv);
	if (!args.has_value())
	{
		std::cout << "Invalid args count. Usage lab_02_24.out <input file> <output file>" << std::endl;
		return 1;
	}

	std::cout
		<< "Input file:  " << args->inputFilePath << std::endl
		<< "Output file: " << args->outputFilePath << std::endl;
}

std::optional<Args> parseArgs(int argc, char** argv)
{
	if (argc != 3)
	{
		return std::nullopt;
	}

	return {(Args) { argv[1], argv[2] }};
}
