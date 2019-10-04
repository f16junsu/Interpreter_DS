#pragma once
#include "Hash.h"

class MemoryNode
{
private:
	int left;
	int right;

public:
	MemoryNode() { this->left = 0, this->right = 0; }
	int getLeft(void) { return this->left; }
	int getRight(void) { return this->right; }
	void setLeft(int val) { this->left = val; }
	void setRight(int val) { this->right = val; }
};

class MemoryTable
{
private:
	MemoryNode* memorytable;
	HashTable& hashtable;
	int free_list;
	int node_root;
	void setMemoryNode(int ind);
	std::string echo(int ind);
	void dealloc(int ind);

public:
	MemoryTable(HashTable& hashtable) : hashtable(hashtable) { memorytable = new MemoryNode[SIZE_OF_MEMORY_TABLE], free_list = 1, node_root = 1; }
	~MemoryTable() { delete[] memorytable; }
	void initmemorytable(void);
	MemoryNode& operator[](int ind) { return memorytable[ind]; }
	void setNode_root(int ind);
	int alloc(void);
	void initFree_list(void) { free_list = 1; }
	int getFree_list(void) { return free_list; }
	int getNode_root(void) { return node_root; }
	void printTable(void);
	std::string echo(void);
	void print(void);
	void dealloc(void);
};