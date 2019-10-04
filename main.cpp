#include <iostream>
#include <string>
#include <sstream>
#include <iomanip>
#include "Others.h"

int main(void)
{
	HashTable hashtable;
	MemoryTable memorytable(hashtable);
	Buffer buf;
	run(hashtable, memorytable, buf);
	return 0;
}