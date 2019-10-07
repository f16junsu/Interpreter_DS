#include "Hash.h"
#include "Others.h"
#include "Symbols.h"

using namespace symbols;

int HashTable::hashfunc(const std::string& input)
{
	int ascii_sum = 0;
	for (char ch : input)
		ascii_sum += ch;
	int ind = ascii_sum % SIZE_OF_HASH_TABLE;
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
	hashtable[ind].setSymbol(input);
	if (isFloat(input)) hashtable[ind].setValue_index(-ind);
}

void HashTable::printTable(void)
{
	std::cout << "Hash Table : \n| Hash Value |   Symbol   |   Link  |\n";
	for (int i = 0; i < 37; ++i) printf("-"); std::cout << std::endl;
	std::string temp;
	for (int i = 0; i < SIZE_OF_HASH_TABLE; ++i)
	{
		if ((temp = hashtable[i].getSymbol()) != std::string())
		{
			std::cout << "|" << std::setw(11) << (-i) << " |" << std::setw(11) << temp;
			if (hashtable[i].getValue_index() == INT_MAX) std::cout << " | UNDEFINED |" << std::endl;
			else std::cout << " |" << std::setw(10) << hashtable[i].getValue_index() << " |" << std::endl;
		}
	}
	std::cout << std::endl;
}

void HashTable::tableinit(void)
{
	for (int i = 1; i < SIZE_OF_HASH_TABLE; ++i)
		hashtable[i].setValue_index(INT_MAX);
	hashinsert("("); hashtable[-LEFT_PAREN].setValue_index(LEFT_PAREN);
	hashinsert(")"); hashtable[-RIGHT_PAREN].setValue_index(RIGHT_PAREN);
	hashinsert("define"); hashtable[-DEFINE].setValue_index(DEFINE);
	hashinsert("quote"); hashtable[-QUOTE].setValue_index(QUOTE);
	hashinsert("+"); hashtable[-PLUS].setValue_index(PLUS);
	hashinsert("-"); hashtable[-MINUS].setValue_index(MINUS);
	hashinsert("*"); hashtable[-TIMES].setValue_index(TIMES);
	hashinsert("number?"); hashtable[-isNUMBER].setValue_index(isNUMBER);
	hashinsert("symbol?"); hashtable[-isSYMBOL].setValue_index(isSYMBOL);
	hashinsert("null?"); hashtable[-isNULL].setValue_index(isNULL);
	hashinsert("cons"); hashtable[-CONS].setValue_index(CONS);
	hashinsert("cond"); hashtable[-COND].setValue_index(COND);
	hashinsert("car"); hashtable[-CAR].setValue_index(CAR);
	hashinsert("cdr"); hashtable[-CDR].setValue_index(CDR);
	hashinsert("#t"); hashtable[-TRUE].setValue_index(TRUE);
	hashinsert("#f"); hashtable[-FALSE].setValue_index(FALSE);
	hashinsert("lambda"); hashtable[-LAMBDA].setValue_index(LAMBDA);
	hashinsert("else"); hashtable[-ELSE].setValue_index(ELSE);
	hashtable[0].setSymbol("NIL");
	hashtable[0].setValue_index(0);
}