#ifndef ARGS_H
#define ARGS_H

#include <optional>
#include <string>
#include <utility>

class Args final
{
public:
	static std::optional<Args> parseFromCLI(int argc, char** argv)
	{
		if (argc != 3)
		{
			return std::nullopt;
		}

		return { (Args){ std::string(argv[1]), std::string(argv[2]) } };
	}

	[[nodiscard]] const std::string& getInputFilePath() const
	{
		return inputFilePath;
	}

	[[nodiscard]] const std::string& getOutputFilePath() const
	{
		return outputFilePath;
	}

private:
	Args(std::string&& inputFilePath, std::string&& outputFilePath)
		: inputFilePath(std::move(inputFilePath))
		, outputFilePath(outputFilePath){};

	std::string inputFilePath;
	std::string outputFilePath;
};

#endif // ARGS_H
