#ifndef MATRIX_H
#define MATRIX_H

#include <vector>
#include <stdexcept>

template <class T>
class SquareMatrix
{
public:
	SquareMatrix(int size, T initializeValue)
		: m_size(size)
	{
		m_buf = std::vector<T>(size * size, initializeValue);
	}

	T GetValue(int i, int j) const
	{
		if (i >= m_size || j >= m_size)
		{
			throw std::invalid_argument("Invalid matrix access indecies");
		}

		return m_buf[i * m_size + j];
	}

	void SetValue(int i, int j, T value)
	{
		if (i >= m_size || j >= m_size)
		{
			throw std::invalid_argument("Invalid matrix access indecies");
		}

		m_buf[i * m_size + j] = value;
	}

	[[nodiscard]]
	int GetSize() const
	{
		return m_size;
	}

private:
	int m_size;
	std::vector<T> m_buf;
};

#endif // MATRIX_H
