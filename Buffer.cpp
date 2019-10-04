#include "Others.h"

std::string Buffer::getNextToken(void)
{
	std::string tok;
	ss >> tok;
	for (auto iter = tok.begin(); iter != tok.end(); ++iter)
		* iter = tolow(*iter);
	return tok;
}

void Buffer::init(const std::string & input)
{
	ss.str(std::string());
	ss.clear();
	std::string temp = input;
	int i = 0;
	while (temp[i] != NULL)
	{
		if (temp[i] == '(')
			temp = temp.insert(i + 1, " "), ++i;
		else if (temp[i] == ')')
			temp = temp.insert(i + 1, " "), temp = temp.insert(i, " "), i += 2;
		++i;
	}
	this->ss.str(temp);
}

void Buffer::pushBack()
{
	auto pos = ss.tellg();
	ss.str(ss.str().insert(ss.tellg(), "("));
	ss.seekg(pos);
}