#pragma once
#include "Hash.h"
#include "Stack.h"

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
	Stack stack;
	int free_list;
	int node_root;
	std::string echo(int ind); // function called in 'string echo(void)' 
	void dealloc(int ind); // function called in 'void dealloc(void)'
	int eval(int root); // function called in 'int eval(void)'
	float* cal_float(int root); // function called in 'int eval(int root)'
public:
	MemoryTable(HashTable& hashtable) : hashtable(hashtable), stack(Stack(20))
	{ memorytable = new MemoryNode[SIZE_OF_MEMORY_TABLE], free_list = 1, node_root = 0; }
	~MemoryTable() { delete[] memorytable; }
	void initmemorytable(void);
	MemoryNode& operator[](int ind) { return memorytable[ind]; }
	void setNode_root(int ind) { node_root = ind; }
	int alloc(void);
	int getFree_list(void) { return free_list; }
	int getNode_root(void) { return node_root; }
	void printTable(void);
	std::string echo(void);
	void print(void); // function which prints the echoed string
	void dealloc(void);
	int eval(void) { return eval(node_root); }
	void printEval(int result_ind);
};