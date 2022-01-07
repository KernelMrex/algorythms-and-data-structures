#ifndef STRINGWIDEFORMATWRITER_H
#define STRINGWIDEFORMATWRITER_H

#include <ostream>

#include "String.h"
#include "StringWriter.h"

class StringWideFormatWriter final : public StringWriter
{
public:
	explicit StringWideFormatWriter(std::ostream& out, unsigned long stringWidth)
		: StringWriter(out)
		, m_stringWidth(stringWidth)
	{
	}

	bool write(const Vector<String>& words) final
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
			if (!(m_out << words.get(i))) return false;

			if (spacesAmount > 0)
			{
				for (int j = 0; j < defaultWordSpacing; ++j)
				{
					if (!(m_out << ' ')) return false;
				}

				if (biggerSpacesAmount > 0)
				{
					if (!(m_out << ' ')) return false;
					biggerSpacesAmount--;
				}

				spacesAmount--;
			}
		}

		return (m_out << std::endl).good();
	}

private:
	unsigned long m_stringWidth;
};

#endif
