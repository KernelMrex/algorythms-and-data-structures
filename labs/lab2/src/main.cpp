#include <iostream>
#include <optional>
#include "lib/State.h"
#include "lib/Stack.h"
#include "lib/KeyWord.h"

std::optional<KeyWord> mapStringToKeyWord(const std::string& string);

int main()
{
	char ch;
	std::string buff;
	State state = State::READING;
	bool isLoop = true;

	Stack<KeyWord> stack;

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
			else if (ch == ';' || ch == ' ' || ch == '\n')
			{
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
					stack.push(keyword.value());
				}
				buff.clear();
			}
			state = State::READING;
			break;
		case State::FINAL:
			isLoop = false;
			break;
		}
	}
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