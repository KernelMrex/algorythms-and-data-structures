#ifndef STACK_H
#define STACK_H

#include <memory>
#include <stack>

template <class T>
class Stack final
{
private:
	class StackNode
	{
	private:
		T m_value;
		std::shared_ptr<StackNode> m_next;

	public:
		explicit StackNode(T value)
			: m_value(value)
			, m_next(nullptr)
		{
		}

		~StackNode() = default;

		[[nodiscard]]
		T getValue() const
		{
			return m_value;
		}

		std::shared_ptr<StackNode> getNext() const
		{
			return m_next;
		}

		void setNext(std::shared_ptr<StackNode> next)
		{
			m_next = next;
		}
	};

public:
	Stack()
		: m_tail(nullptr){};

	~Stack() = default;

	[[nodiscard]]
	T pop()
	{
		if (m_tail == nullptr)
		{
			throw std::runtime_error("stack is empty");
		}

		auto extractedNode = m_tail;
		if (m_tail->getNext() != nullptr)
		{
			m_tail = m_tail->getNext();
		}
		else
		{
			m_tail == nullptr;
		}

		auto extractedValue = extractedNode->getValue();

		return extractedValue;
	}

	void push(T value)
	{
		if (m_tail == nullptr)
		{
			m_tail = std::make_shared<StackNode>(value);
			return;
		}
		m_tail->setNext(std::make_shared<StackNode>(value));
	}

	[[nodiscard]]
	bool isEmpty() const
	{
		return m_tail == nullptr;
	}

private:
	std::shared_ptr<StackNode> m_tail;
};

#endif // STACK_H
