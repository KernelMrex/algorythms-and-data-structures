#ifndef STRING_H
#define STRING_H

#include <cstring>
#include <iostream>
#include <new>
#include <ostream>

class String final
{
public:
	String()
		: m_string(new char[String::DEFAULT_CAPACITY])
		, m_size(0)
		, m_capacity(String::DEFAULT_CAPACITY)
	{
	}

	explicit String(const char* strPtr, std::size_t size)
		: m_capacity(size)
		, m_size(size)
		, m_string(new char[size])
	{
		std::memcpy(m_string, strPtr, size);
	}

	explicit String(const char* strPtr)
		: m_capacity(std::strlen(strPtr))
		, m_size(std::strlen(strPtr))
	{
		m_string = new char[m_size];
		std::memcpy(m_string, strPtr, m_size);
	}

	String(const String& s)
		: m_size(s.m_size)
		, m_capacity(s.m_capacity)
		, m_string(new char[s.m_capacity])
	{
		std::memcpy(m_string, s.m_string, s.m_size);
	}

	String(String&& s) noexcept
		: m_size(s.m_size)
		, m_capacity(s.m_capacity)
	{
		m_string = s.m_string;
		s.m_string = nullptr;
		s.m_size = 0;
		s.m_capacity = 0;
	}

	~String()
	{
		delete[](m_string);
	}

	bool addChar(char ch) noexcept
	{
		if (this->m_size == this->m_capacity && !this->expandCapacity())
		{
			return false;
		}
		this->m_string[this->m_size] = ch;
		this->m_size++;
		return true;
	}

	bool clear() noexcept
	{
		delete[](m_string);

		try
		{
			this->m_string = new char[String::DEFAULT_CAPACITY];
		}
		catch (std::bad_alloc& ex)
		{
			return false;
		}

		this->m_capacity = String::DEFAULT_CAPACITY;
		this->m_size = 0;
		return true;
	}

	[[nodiscard]] std::size_t getSize() const noexcept
	{
		return m_size;
	}

	String& operator=(const String& other)
	{
		// Guard self assignment
		if (this == &other)
			return *this;

		// Guard different capacity
		if (m_capacity != other.m_capacity)
		{
			delete[] m_string;
			m_string = new char[other.m_capacity];
		}

		m_size = other.m_size;
		m_capacity = other.m_capacity;
		std::copy(other.m_string, other.m_string + other.m_capacity, m_string);

		return *this;
	}

	String& operator=(String&& other) noexcept
	{
		m_size = other.m_size;
		m_capacity = other.m_capacity;
		m_string = other.m_string;

		other.m_string = nullptr;
		other.m_size = 0;
		other.m_capacity = 0;

		return *this;
	}

	friend std::ostream& operator<<(std::ostream& os, const String& str)
	{
		char *buf = new char[str.m_size];
		std::memcpy(buf, str.m_string, str.m_size);
		buf[str.m_size] = 0;

		os << buf;

		delete[] buf;

		return os;
	}

private:
	static const std::size_t DEFAULT_CAPACITY = 16;
	char* m_string;
	std::size_t m_size;
	std::size_t m_capacity;

	bool expandCapacity() noexcept
	{
		char* oldString = this->m_string;

		std::size_t newCapacity = (this->m_capacity == 0) ? 1 : this->m_capacity * 2;

		try
		{
			this->m_string = new char[newCapacity];
		}
		catch (std::bad_alloc& ex)
		{
			return false;
		}

		std::memcpy(this->m_string, oldString, this->m_size);

		delete[](oldString);

		return true;
	}
};

#endif
