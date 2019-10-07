#include "Stack.h"
#include <iostream>

void Stack::push(Node input)
{
	try { if (top == capacity - 1) throw std::runtime_error("Stack Overflowed"); }
	catch (std::exception & e) { std::cout << e.what() << std::endl; }
	
	stack[++top].set(input.getHash_val(), input.getLink_val());
}

Node Stack::pop(void)
{
	if (isEmpty())
	{
		std::cout << "Stack is Empty" << std::endl;
		return Node();
	}
	return stack[top--];
}