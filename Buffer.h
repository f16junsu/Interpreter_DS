#pragma once
#include <sstream>

class Buffer
{
private:
	std::stringstream ss;

public:
	std::string getNextToken(void);
	void init(const std::string& input);
	void pushBack();
};