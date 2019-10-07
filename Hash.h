#pragma once
#include "Symbols.h"
#include <iostream>
#include <iomanip>

#define SIZE_OF_MEMORY_TABLE 1000
#define SIZE_OF_HASH_TABLE 997
class HashNode
{
private:
	std::string symbol;
	int value_index;

public:
	HashNode() { this->symbol = std::string(), this->value_index = 0; }
	std::string getSymbol(void) { return this->symbol; }
	int getValue_index(void) { return this->value_index; }
	void setSymbol(std::string val) { this->symbol = val; }
	void setValue_index(int val) { this->value_index = val; }
};

class HashTable
{
private:
	HashNode* hashtable;

public:
	HashTable() { hashtable = new HashNode[SIZE_OF_HASH_TABLE]; tableinit(); }
	~HashTable() { delete[] hashtable; }
	int hashfunc(const std::string& input);
	void hashinsert(const std::string& input);
	void tableinit(void);
	HashNode& operator[](int ind) { return hashtable[ind]; }
	void printTable(void);
};