#ifndef WIDESTRINGFORMATTERWRITER_H
#define WIDESTRINGFORMATTERWRITER_H

#include "String.h"
#include <ostream>

class WideStringFormatter final
{
public:
	explicit WideStringFormatter(std::ostream& out, unsigned long stringWidth)
		: m_out(out)
		, m_stringWidth(stringWidth)
	{
	}

	void write(const Vector<String>& words)
	{
		unsigned long wordsAmount = words.getSize();
		unsigned long spacesAmount = wordsAmount - 1;
		unsigned long charsAmount = 0;

		for (unsigned long i = 0; i < wordsAmount; ++i)
		{
            charsAmount += words.get(i).getSize();
		}

		spacesAmount = spacesAmount == 0 ? 1 : spacesAmount;

		auto freeSpace = m_stringWidth - charsAmount;
		auto defaultWordSpacing = freeSpace / spacesAmount;
		auto biggerSpacesAmount = freeSpace % spacesAmount;

		for (unsigned long i = 0; i < wordsAmount; ++i)
		{
			m_out << words.get(i);

			if (spacesAmount > 0)
			{
				for (int j = 0; j < defaultWordSpacing; ++j)
				{
					m_out << ' ';
				}

				if (biggerSpacesAmount >= 0)
				{
					m_out << ' ';
					biggerSpacesAmount--;
				}

				spacesAmount--;
			}
		}

		m_out << std::endl;
	}

private:
	std::ostream& m_out;
	unsigned long m_stringWidth;
};

#endif
