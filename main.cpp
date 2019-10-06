#include "Others.h"

int main(void)
{
	HashTable hashtable;
	MemoryTable memorytable(hashtable);
	Buffer buf;
	run(hashtable, memorytable, buf);

	return 0;
}