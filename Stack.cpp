#include "Stack.h"
#include <iostream>

void Stack::push(Node input)
{
	if (top == capacity - 1) std::cout << "Stack Overflowed" << std::endl;
	else stack[++top].set(input.getHash_val(), input.getLink_val());
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