#ifndef WORDCALLBACKFILEREADER_H
#define WORDCALLBACKFILEREADER_H

#include "String.h"
#include <functional>
#include <iostream>

class WordCallbackReader final
{
public:
	explicit WordCallbackReader(std::istream& inputStream)
		: in(inputStream){};

	bool readAllWithCallback(const std::function<void(const String& word)>& callback)
	{
		String word;
		ReadState state = ReadState::STATE_WAIT_FOR_WORD;
		char ch;
		while (in >> ch)
		{
			switch (state)
			{
			case ReadState::STATE_WAIT_FOR_WORD:
				if (std::isalpha(ch))
				{
					state = ReadState::STATE_READ_WORD;
					if (!word.addChar(ch)) return false;
				}
				break;
			case ReadState::STATE_READ_WORD:
				if (std::isalpha(ch) || ch == '.' || ch == ',' || ch == '?' || ch == '!')
				{
					if (!word.addChar(ch)) return false;
				}

				if (ch == ' ' || ch == '\n')
				{
					callback(word);
					word.clear();
					state = ReadState::STATE_WAIT_FOR_WORD;
				}

				if (ch == '-')
				{
					state = ReadState::WORD_SPLIT;
				}
				break;
			case ReadState::WORD_SPLIT:
				if (ch == '\n')
				{
					state = ReadState::STATE_READ_WORD;
					break;
				}

				if (std::isalpha(ch))
				{
					state = ReadState::STATE_READ_WORD;
					if (!word.addChar(ch)) return false;
					break;
				}

				callback(word);
				word.clear();
				state = ReadState::STATE_WAIT_FOR_WORD;
				if (!word.addChar(ch)) return false;
				break;
			}
		}

		if (!in.eof() && !in.good())
		{
			return false;
		}

		callback(word);

		return true;
	};

private:
	std::istream& in;

	enum class ReadState
	{
		STATE_WAIT_FOR_WORD,
		STATE_READ_WORD,
		WORD_SPLIT
	};
};

#endif
