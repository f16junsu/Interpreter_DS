#include "Hash.h"

int HashTable::hashfunc(const std::string& input)
{
	int ascii_sum = 0;
	for (char ch : input)
		ascii_sum += ch;
	int ind = ascii_sum % 1000;
	while (hashtable[ind].getSymbol() != std::string())
	{
		if (hashtable[ind].getSymbol() == input) break;
		else ++ind;
		if (ind == SIZE_OF_HASH_TABLE) ind = 1;
	}

	return -ind;
}

void HashTable::hashinsert(const std::string & input)
{
	int ind = -hashfunc(input);
	if (hashtable[ind].getSymbol() != std::string()) return;
	else hashtable[-hashfunc(input)].setSymbol(input);
}

void HashTable::printTable(void)
{
	std::cout << "Hash Table : \n| Hash Value |   Symbol   |   Link  |\n";
	for (int i = 0; i < 37; ++i) printf("-"); std::cout << std::endl;
	std::string temp;
	for (int i = 0; i < SIZE_OF_HASH_TABLE; ++i)
	{
		if ((temp = hashtable[i].getSymbol()) != std::string())
			std::cout << "|" << std::setw(11) << (-i) << " |" << std::setw(11) << temp << " |     NIL |" << std::endl;
	}
	std::cout << std::endl;
}
