#include <iostream>
#include <optional>
#include <fstream>

#include "lib/Args.h"
#include "lib/Vector.h"
#include "lib/WordCallbackReader.h"
#include "lib/WideStringFormatterWriter.h"

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

	WideStringFormatter wideStringFormatter(outputFileStream, maxStringSize);
	Vector<String> words;

	WordCallbackReader wordCallbackReader(inputFileStream >> std::noskipws);
	unsigned long charsAmount = 0;

	// TODO: annotated errors on input/output
	bool readOk = wordCallbackReader.readAllWithCallback([&words, &wideStringFormatter, &charsAmount, maxStringSize](const String& word) {
		charsAmount += word.getSize() + 1;
		if (charsAmount - 1 > maxStringSize)
		{
			wideStringFormatter.write(words.popSlice(0, words.getSize()));
			charsAmount = word.getSize() + 1;
		}
		words.push(word);
	});
	if (!readOk)
	{
		std::cerr << "Error while reading file " << args->getInputFilePath() << std::endl;
		return 1;
	}

	bool isFirstWord = true;
	for (int i = 0; i < words.getSize(); ++i)
	{
		if (!isFirstWord)
		{
			outputFileStream << ' ';
		}
		else
		{
			isFirstWord = false;
		}

		outputFileStream << words.get(i);
	}

	std::cout << "Successfully formatted! " << std::endl;
}