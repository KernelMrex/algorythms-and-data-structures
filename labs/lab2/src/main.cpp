#include <iostream>
#include <optional>
#include "lib/State.h"
#include "lib/KeyWord.h"
#include "lib/PascalSyntaxAnalyzer.h"

std::optional<KeyWord> mapStringToKeyWord(const std::string& string);

int main()
{
	char ch;
	std::string buff;
	State state = State::READING;
	bool isLoop = true;
	PascalSyntaxAnalyzer analyzer;
	int lineCounter = 1;
	while (isLoop)
	{
		switch (state)
		{
		case State::READING:
			if (!std::cin)
			{
				state = State::FINAL;
				break;
			}
			std::cin >> std::noskipws >> ch;
			if (std::isalpha(ch))
			{
				state = State::WORD;
				break;
			}
			else if (ch == ';' || ch == ' ' || ch == '.')
			{
				state = State::SEPARATOR;
				break;
			}
			else if (ch == '\n')
			{
				lineCounter++;
				state = State::SEPARATOR;
				break;
			}
			break;
		case State::WORD:
			buff.push_back(ch);
			state = State::READING;
			break;
		case State::SEPARATOR:
			if (!buff.empty())
			{
				auto keyword = mapStringToKeyWord(buff);
				if (keyword.has_value())
				{
					analyzer.addWord(keyword.value());
				}
				buff.clear();
			}

			if (ch == ';')
			{
				analyzer.addSeparator(PascalSeparator::SEMICOLON);
			}
			else if (ch == '.')
			{
				analyzer.addSeparator(PascalSeparator::DOT);
			}

			if (analyzer.isError())
			{
				std::cout << "Error in syntax! Line: " << lineCounter << std::endl;
				return EXIT_FAILURE;
			}

			state = State::READING;
			break;
		case State::FINAL:
			isLoop = false;
			break;
		}
	}

	if (!analyzer.isEnded())
	{
		std::cout << "Unexpected end of file! " << std::endl;
		return EXIT_FAILURE;
	}

	std::cout << "Syntax check successful" << std::endl;
	return EXIT_SUCCESS;
}

std::optional<KeyWord> mapStringToKeyWord(const std::string& string)
{
	if (string == "REPEAT")
	{
		return KeyWord::REPEAT;
	}
	else if (string == "UNTIL")
	{
		return KeyWord::UNTIL;
	}
	else if (string == "IF")
	{
		return KeyWord::IF;
	}
	else if (string == "THEN")
	{
		return KeyWord::THEN;
	}
	else if (string == "ELSE")
	{
		return KeyWord::ELSE;
	}
	else if (string == "BEGIN")
	{
		return KeyWord::BEGIN;
	}
	else if (string == "END")
	{
		return KeyWord::END;
	}
	else if (string == "RECORD")
	{
		return KeyWord::RECORD;
	}
	return std::nullopt;
}