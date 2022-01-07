#include <fstream>
#include <iostream>
#include <optional>

#include "lib/Args.h"
#include "lib/Vector.h"
#include "lib/StringWideFormatWriter.h"
#include "lib/WordCallbackReader.h"

int main(int argc, char** argv)
{
	auto args = Args::parseFromCLI(argc, argv);
	if (!args.has_value())
	{
		std::cout << "Invalid args count. Usage lab1.out <input file> <output file>" << std::endl;
		return 1;
	}

	std::ifstream inputFileStream;
	inputFileStream.open(args->getInputFilePath());
	if (!inputFileStream.good())
	{
		std::cerr << "Error while opening file " << args->getInputFilePath() << std::endl;
		return 1;
	}

	std::ofstream outputFileStream;
	outputFileStream.open(args->getOutputFilePath());
	if (!outputFileStream.good())
	{
		std::cerr << "Error while opening file " << args->getOutputFilePath() << std::endl;
		return 1;
	}

	unsigned long maxStringSize = 40;

	WordCallbackReader wordCallbackReader(inputFileStream >> std::noskipws);
	Vector<String> words;
	StringWideFormatWriter wideFormatWriter(outputFileStream, maxStringSize);
	unsigned long charsAmount = 0;

	bool ioOk = wordCallbackReader.readAllWithCallback([&words, &wideFormatWriter, &charsAmount, maxStringSize](const String& word) {
		charsAmount += word.getSize() + 1;
		if (charsAmount - 1 > maxStringSize)
		{
			bool writeOk = wideFormatWriter.write(words.popSlice(0, words.getSize()));
			if (!writeOk)
				return false;
			charsAmount = word.getSize() + 1;
		}
		words.push(word);
		return true;
	});
	if (ioOk)
	{
		StringWriter writer(outputFileStream);
		ioOk = writer.write(words);
	}

	if (!ioOk)
	{
		std::cerr << "Error while performing reading or writing to files: "
				  << args->getInputFilePath() << ' ' << args->getOutputFilePath()
				  << std::endl;
		return 1;
	}

	std::cout << "Successfully formatted! " << std::endl;
	return 0;
}