#include "Hash.h"
#include "Others.h"

int HashTable::hashfunc(const std::string& input)
{
	for (int i = 1; i < -NUMBER_OF_SYMBOLS; ++i)
		if (hashtable[i].getSymbol() == input) return -i;
	int ascii_sum = 0;
	for (char ch : input)
		ascii_sum += ch * ch;
	int ind = ascii_sum % SIZE_OF_HASH_TABLE;
	while (hashtable[ind].getSymbol() != std::string())
	{
		if (hashtable[ind].getSymbol() == input) break;
		else ++ind;
		if (ind == SIZE_OF_HASH_TABLE) ind = -NUMBER_OF_SYMBOLS;
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
			if (hashtable[i].getValue_index() == UNDEFINED) std::cout << " | UNDEFINED |" << std::endl;
			else std::cout << " |" << std::setw(10) << hashtable[i].getValue_index() << " |" << std::endl;
		}
	}
	std::cout << std::endl;
}

void HashTable::tableinit(void)
{
	hashtable[-NIL].setNode("NIL", NIL);
	hashtable[-LEFT_PAREN].setNode("(", LEFT_PAREN);
	hashtable[-RIGHT_PAREN].setNode(")", RIGHT_PAREN);
	hashtable[-TRUE].setNode("#t", TRUE);
	hashtable[-FALSE].setNode("#f", FALSE);
	hashtable[-PLUS].setNode("+", PLUS);
	hashtable[-MINUS].setNode("-", MINUS);
	hashtable[-TIMES].setNode("*", TIMES);
	hashtable[-isNUMBER].setNode("number?", isNUMBER);
	hashtable[-isSYMBOL].setNode("symbol?", isSYMBOL);
	hashtable[-isNULL].setNode("null?", isNULL);
	hashtable[-CONS].setNode("cons", CONS);
	hashtable[-COND].setNode("cond", COND);
	hashtable[-ELSE].setNode("else", ELSE);
	hashtable[-CAR].setNode("car", CAR);
	hashtable[-CDR].setNode("cdr", CDR);
	hashtable[-DEFINE].setNode("define", DEFINE);
	hashtable[-QUOTE].setNode("quote", QUOTE);
	hashtable[-LAMBDA].setNode("lambda", LAMBDA);
}