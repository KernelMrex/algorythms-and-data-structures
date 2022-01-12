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
		if (argc != 4)
		{
			return std::nullopt;
		}

		unsigned long stringSize;

		try
		{
			stringSize = std::stoi(argv[3]);
		}
		catch (const std::invalid_argument& e)
		{
			return std::nullopt;
		}
		catch (const std::overflow_error& e)
		{
			return std::nullopt;
		}

		return { (Args){
			std::string(argv[1]),
			std::string(argv[2]),
			stringSize } };
	}

	[[nodiscard]] const std::string& getInputFilePath() const
	{
		return m_inputFilePath;
	}

	[[nodiscard]] const std::string& getOutputFilePath() const
	{
		return m_outputFilePath;
	}

	[[nodiscard]] unsigned long getStringSize() const
	{
		return m_stringSize;
	}

private:
	Args(std::string&& inputFilePath, std::string&& outputFilePath, unsigned long stringSize)
		: m_inputFilePath(std::move(inputFilePath))
		, m_outputFilePath(outputFilePath)
		, m_stringSize(stringSize){};

	std::string m_inputFilePath;
	std::string m_outputFilePath;
	unsigned long m_stringSize;
};

#endif // ARGS_H
