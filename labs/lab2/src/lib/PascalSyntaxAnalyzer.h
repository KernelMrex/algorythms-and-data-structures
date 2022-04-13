#ifndef PASCALSYNTAXANALYZER_H
#define PASCALSYNTAXANALYZER_H

#include "KeyWord.h"
#include "Stack.h"
#include "PascalSeparator.h"

class PascalSyntaxAnalyzer
{
public:
	PascalSyntaxAnalyzer()
		: m_stack(Stack<KeyWord>())
		, m_isError(false)
		, m_isEndingSeparatorMet(false)
	{}

	void addWord(KeyWord keyWord)
	{
		if (m_isEndingSeparatorMet)
		{
			m_isError = true;
			return;
		}

		if (m_stack.isEmpty())
		{
			if ((keyWord == KeyWord::RECORD || keyWord == KeyWord::BEGIN))
			{
				m_stack.push(keyWord);
				return;
			}
			m_isError = true;
			return;
		}

		auto prev = m_stack.viewTop();

		switch (keyWord)
		{
		case KeyWord::BEGIN:
		case KeyWord::REPEAT:
		case KeyWord::IF:
			if (prev == KeyWord::IF || prev == KeyWord::RECORD)
			{
				m_isError = true;
				return;
			}
			m_stack.push(keyWord);
			break;
		case KeyWord::THEN:
			if (prev != KeyWord::IF)
			{
				m_isError = true;
				return;
			}
			m_stack.pop();
			m_stack.push(KeyWord::IF_THEN);
			break;
		case KeyWord::ELSE:
			if (prev != KeyWord::IF_THEN)
			{
				m_isError = true;
				return;
			}
			m_stack.pop();
			break;
		case KeyWord::END:
			if (prev == KeyWord::IF_THEN)
			{
				while (prev == KeyWord::IF_THEN)
				{
					prev = m_stack.pop();
				}
				m_stack.push(prev);
			}

			if (prev != KeyWord::BEGIN && prev != KeyWord::RECORD)
			{
				m_isError = true;
				return;
			}
			m_stack.pop();
			break;
		case KeyWord::UNTIL:
			if (prev != KeyWord::REPEAT)
			{
				m_isError = true;
				return;
			}
			m_stack.pop();
			break;
		case KeyWord::RECORD:
			if (prev != KeyWord::RECORD)
			{
				m_isError = true;
				return;
			}
			m_stack.push(KeyWord::RECORD);
			break;
		}
	}

	void addSeparator(PascalSeparator separator)
	{
		if (separator == PascalSeparator::DOT)
		{
			m_isEndingSeparatorMet = true;
		}

		if (m_stack.isEmpty())
		{
			return;
		}

		auto prev = m_stack.viewTop();
		switch (separator)
		{
		case PascalSeparator::SEMICOLON:
			if (prev == KeyWord::IF_THEN || prev == KeyWord::ELSE)
			{
				while (prev == KeyWord::IF_THEN || prev == KeyWord::ELSE)
				{
					prev = m_stack.pop();
				}
				m_stack.push(prev);
			}
			break;
		case PascalSeparator::DOT:
			m_isEndingSeparatorMet = true;
			break;
		}
	}

	[[nodiscard]]
	bool isEnded()
	{
		return m_stack.isEmpty();
	}

	[[nodiscard]]
	bool isError() const
	{
		return m_isError;
	}

private:
	Stack<KeyWord> m_stack;
	bool m_isError;
	bool m_isEndingSeparatorMet;
};

#endif // PASCALSYNTAXANALYZER_H
