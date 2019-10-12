#include "Run.h"

namespace materials
{
	HashTable hashtable;
	MemoryTable memorytable(hashtable);
	Buffer buf;
}

void run(Buffer& buf, HashTable& hashtable, MemoryTable& memorytable)
{
	memorytable.initmemorytable();

	while (true)
	{
		std::cout << "> ";
		std::string input;
		std::getline(std::cin, input);
		buf.init(input);
		memorytable.setNode_root(read(buf, hashtable, memorytable));
		int result;
		try { result = memorytable.eval(); memorytable.printEval(result); }
		catch (std::exception & e) { std::cout << e.what() << std::endl; }
		materials::hashtable.printTable();
	}
}

void run(void)
{
	run(materials::buf, materials::hashtable, materials::memorytable);
	return;
}