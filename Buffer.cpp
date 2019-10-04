#include "Buffer.h"

char tolow(char ch)
{
	if (ch >= 'A' && ch <= 'Z')
		return ch - ('Z' - 'z');
	return ch;
}

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
		if (temp[i] == '('|| temp[i] == '\'') temp = temp.insert(size_t(i) + size_t(1), " "), ++i;
		else if (temp[i] == ')') temp = temp.insert(size_t(i) + size_t(1), " "), temp = temp.insert(i, " "), i += 2;
		++i;
	}
	ss.str(temp);
	ss.str(preprocessing());
	ss.clear();
}

void Buffer::pushBack()
{
	auto pos = ss.tellg();
	ss.str(ss.str().insert(ss.tellg(), "("));
	ss.seekg(pos);
}

std::string Buffer::preprocessing(void)
{
	std::string newcommand = std::string();
	std::string tok;
	while ((tok = getNextToken()) != std::string())
	{
		if (tok == "define") // (define (square x) (* x x))
		{
			newcommand = newcommand + "define ";
			tok = getNextToken();
			if (tok == "(")
			{
				tok = getNextToken();
				newcommand = newcommand + tok + " ( lambda ( " + preprocessing() + ") ";
			}
			else newcommand = newcommand + tok + " ";
		}
		else if (tok == "'") // '(a b c) -> (quote (a b c))
		{
			newcommand = newcommand + "( quote ";
			int num_of_lft_paren = 0;
			do {
				tok = getNextToken();
				newcommand = newcommand + tok + " ";
				if (tok == "(") ++num_of_lft_paren;
				else if (tok == ")") --num_of_lft_paren;
			} while (num_of_lft_paren);
			newcommand = newcommand + ") ";
		}
		else newcommand = newcommand + tok + " ";
	}
	return newcommand;
}