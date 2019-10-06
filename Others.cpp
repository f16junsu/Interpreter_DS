#include "Others.h"

bool isFloat(const std::string& input)
{
	int i = 0;
	if (isdigit(input[i]) || input[i] == '-')
	{
		int cnt = 0;
		for (i = 1; input[i] != '\0'; ++i)
		{
			if (input[i] == '.')
			{
				++cnt;
				if (cnt - 1) return false;
			}
			else if (!isdigit(input[i])) return false;
		}
	}
	else return false;
	return true;
}

int read(Buffer & buf, HashTable & hashtable, MemoryTable & memorytable)
{
	int root = 0;
	int temp = 0;
	bool first = true;
	std::string tok = buf.getNextToken();

	if (tok == "(")
	{
		while ((tok = buf.getNextToken()) != ")")
		{
			if (first)
				temp = root = memorytable.alloc(), first = false;
			else
			{
				memorytable[temp].setRight(memorytable.alloc());
				temp = memorytable[temp].getRight();
			}

			if (tok == "(")
				buf.pushBack(), memorytable[temp].setLeft(read(buf, hashtable, memorytable));
			else
			{
				hashtable.hashinsert(tok);
				memorytable[temp].setLeft(hashtable.hashfunc(tok));
			}
			memorytable[temp].setRight(0);
		}
		return root;
	}
	else if (tok == std::string())
		return root;
	hashtable.hashinsert(tok);
	return hashtable.hashfunc(tok);
}

void run(HashTable & hashtable, MemoryTable & memorytable, Buffer & buf)
{
	memorytable.initmemorytable();

	while (true)
	{
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		buf.init(input);
		memorytable.setNode_root(read(buf, hashtable, memorytable));
		//std::cout << "] " << "Free list's root = " << memorytable.getFree_list() << std::endl;
		//std::cout << "  " << "List's root = " << memorytable.getNode_root() << std::endl;
		//memorytable.print();
		int result = memorytable.eval();
		memorytable.printTable();
		std::cout << std::endl;
		hashtable.printTable();
		memorytable.printEval(result);
		//memorytable.dealloc();
	}
}
