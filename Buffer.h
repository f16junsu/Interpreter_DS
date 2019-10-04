#pragma once
#include <sstream>

char tolow(char ch);
class Buffer
{
private:
	std::stringstream ss;

public:
	std::string getNextToken(void);
	void init(const std::string& input);
	std::string preprocessing(void);
	void pushBack(void);
};