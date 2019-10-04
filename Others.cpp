#include "Others.h"

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
	memorytable.initmemorytable(), hashtable.hashinsert("("), hashtable.hashinsert(")");
	hashtable[0].setSymbol("NIL");

	while (true)
	{
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		buf.init(input);
		std::string temp = buf.preprocessing();
		std::cout << temp << std::endl;
		//memorytable.setNode_root(read(buf, hashtable, memorytable));
		//std::cout << "] " << "Free list's root = " << memorytable.getFree_list() << std::endl;
		//std::cout << "  " << "List's root = " << memorytable.getNode_root() << std::endl;
		//memorytable.printTable();
		//std::cout << std::endl;
		//hashtable.printTable();
		//memorytable.print();
		//memorytable.dealloc();
	}
}
