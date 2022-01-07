#ifndef STRINGWRITER_H
#define STRINGWRITER_H

#include "String.h"
#include "Vector.h"

class StringWriter
{
public:
	explicit StringWriter(std::ostream& out)
		: m_out(out)
	{
	}

	virtual bool write(const Vector<String>& words)
	{
		bool isFirstWord = true;
		for (int i = 0; i < words.getSize(); ++i)
		{
			if (!isFirstWord)
			{
				if (!(m_out << ' '))
					return false;
			}
			else
			{
				isFirstWord = false;
			}

			if (!(m_out << words.get(i)))
				return false;
		}

		return true;
	}

protected:
	std::ostream& m_out;
};

#endif
