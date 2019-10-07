#pragma once
#include <stdexcept>

class Node
{
private:
	int hash_val;
	int link_val;

public:
	Node() : hash_val(0), link_val(0) {}
	Node(int h, int l) : hash_val(h), link_val(l) {}
	int getHash_val(void) { return hash_val; }
	int getLink_val(void) { return link_val; }
	void set(int h, int l) { hash_val = h, link_val = l; }
};

class Stack
{
private:
	Node* stack;
	int capacity;
	int top;

public:
	Stack(const int& cap) : capacity(cap), top(-1) { stack = new Node[capacity]; }
	~Stack() { delete[] stack; }
	bool isEmpty(void) { return top == -1; }
	int getTop(void) const { return top; }
	void push(Node input);
	Node pop(void);
};