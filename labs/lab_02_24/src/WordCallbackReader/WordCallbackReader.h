#ifndef WORDCALLBACKFILEREADER_H
#define WORDCALLBACKFILEREADER_H

#include <iostream>

class WordCallbackReader
{
public:
	WordCallbackReader(const std::istream& istream);

private:
	const std::istream& m_istream;
};

#endif
