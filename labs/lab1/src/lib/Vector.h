#ifndef VECTOR_H
#define VECTOR_H

template <class T>
class Vector final
{
public:
	Vector()
		: m_capacity(Vector::DEFAULT_CAPACITY)
		, m_size(0)
		, m_items(new T[Vector::DEFAULT_CAPACITY])
	{
	}

	explicit Vector(std::size_t capacity)
		: m_capacity(capacity)
		, m_size(0)
		, m_items(new T[capacity])
	{
	}

	Vector(const Vector& v)
		: m_capacity(v.m_capacity)
		, m_size(v.m_size)
		, m_items(new T[v.m_capacity])
	{
		for (int i = 0; i < v.m_size; ++i)
		{
			m_items[i] = v.m_items[i];
		}
	}

	Vector(Vector&& v) noexcept
		: m_capacity(v.m_capacity)
		, m_size(v.m_size)
		, m_items(v.m_items)
	{
		v.m_capacity = 0;
		v.m_size = 0;
		v.m_items = nullptr;
	}


	~Vector()
	{
		delete[] m_items;
	}

	void push(const T& item)
	{
		if (m_size >= m_capacity)
		{
			this->reAlloc();
		}

		m_items[m_size] = item;
		m_size++;
	}

	void push(T&& item)
	{
		if (m_size >= m_capacity)
		{
			this->reAlloc();
		}

		m_items[m_size] = std::move(item);
		m_size++;
	}

	[[nodiscard]] T get(std::size_t i) const
	{
		if (i >= m_size)
		{
			throw std::overflow_error("array overflow");
		}

		return m_items[i];
	}

	[[nodiscard]] Vector<T> popSlice(std::size_t from, std::size_t amount)
	{
		if (m_size < from + amount)
		{
			throw std::overflow_error("Invalid indexes when slicing array");
		}

		Vector<T> slice(amount);

		for (std::size_t i = from, j = 0; i < from + amount; ++i, ++j)
		{
			slice.m_items[j] = std::move(m_items[i]);
			slice.m_size++;
		}

		for (std::size_t i = from + amount, j = from; i < m_size; ++i, ++j)
		{
			slice.m_items[j] = std::move(m_items[i]);
		}

		m_size = m_size - amount;

		return std::move(slice);
	}

	[[nodiscard]] std::size_t getSize() const noexcept
	{
		return m_size;
	}

private:
	static const std::size_t DEFAULT_CAPACITY = 2;
	std::size_t m_size;
	std::size_t m_capacity;
	T* m_items;

	bool reAlloc()
	{
		std::size_t newCapacity = m_capacity * 2;
		T* newItems;

		try
		{
			newItems = new T[newCapacity];
		}
		catch (std::bad_alloc& ex)
		{
			return false;
		}

		for (int i = 0; i < m_size; ++i)
		{
			newItems[i] = std::move(m_items[i]);
		}

		delete[] m_items;
		m_items = newItems;
		m_capacity = newCapacity;

		return true;
	}
};

#endif
