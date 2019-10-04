#include "Memory.h"

void MemoryTable::setNode_root(int ind)
{
	node_root = ind;
}

void MemoryTable::setMemoryNode(int ind)
{
	memorytable[ind].setLeft(0);
	memorytable[ind].setRight(free_list);
	free_list = ind;
}

std::string MemoryTable::echo(int ind)
{
	int l, r;
	if ((l = memorytable[ind].getLeft()) < 0)
	{
		if ((r = memorytable[ind].getRight()) > 0)
			return hashtable[-l].getSymbol() + " " + echo(r);
		else return hashtable[-l].getSymbol() + ")";
	}
	else if (l == 0)
	{
		if ((r = memorytable[ind].getRight()))
			return "() " + echo(r);
		else return "())";
	}
	else
	{
		if ((r = memorytable[ind].getRight()) > 0)
			return "(" + echo(l) + " " + echo(r);
		return "(" + echo(l) + ")";
	}
}

std::string MemoryTable::echo(void)
{
	if (node_root == 0)
		return "()";
	return "(" + echo(node_root);
}

void MemoryTable::print(void)
{
	if (node_root < 0)
		std::cout << hashtable[-node_root].getSymbol() << std::endl;
	else
		std::cout << echo() << std::endl;
}

/*
void MemoryTable::dealloc(int ind)
{
	int l, r;
	if (r = memorytable[ind].getRight())
	{
		if ((l = memorytable[ind].getLeft()) < 0)
			dealloc(r), setMemoryNode(ind);
		else
		{
			if (l == 0) return;
			dealloc(r);
			dealloc(l);
			setMemoryNode(ind);
		}
	}
	else
	{
		if ((l = memorytable[ind].getLeft()) < 0)
			setMemoryNode(ind);
		else
		{
			if (l == 0) return;
			dealloc(l), setMemoryNode(ind);
		}
	}
}
*/

void MemoryTable::dealloc(int ind)
{
	int l, r;
	if (ind == 0) return;
	if (r = memorytable[ind].getRight()) dealloc(r);
	else memorytable[ind].setRight(free_list);
	if ((l = memorytable[ind].getLeft()) <= 0) memorytable[ind].setLeft(0);
	else dealloc(l), memorytable[ind].setLeft(0), memorytable[ind].setRight(free_list);
	free_list = ind;
}

void MemoryTable::dealloc(void)
{
	if (node_root < 0)
	{
		node_root = 0;
		return;
	}
	dealloc(node_root);
	node_root = 0;
}

void MemoryTable::initmemorytable(void)
{
	int len = SIZE_OF_MEMORY_TABLE;
	for (int i = 1; i < len - 1; ++i)
		memorytable[i].setRight(i + 1), memorytable[i].setLeft(0);
	memorytable[len - 1].setLeft(0);
	return;
}

int MemoryTable::alloc(void)
{
	int temp = this->free_list;
	this->free_list = memorytable[temp].getRight();
	return temp;
}


void MemoryTable::printTable(void)
{
	std::cout << "Memory Table : \n|   i  |   Left   |  Right  | \n";
	for (int i = 0; i < 29; ++i) std::cout << '-'; std::cout << std::endl;
	for (int i = 1; i < SIZE_OF_MEMORY_TABLE; ++i)
	{
		int val = memorytable[i].getRight();
		std::cout << "|" << std::setw(5) << i << " |" << std::setw(9) << memorytable[i].getLeft();
		if (val)
			std::cout << " |" << std::setw(8) << val << " |\n";
		else
			std::cout << " |" << std::setw(8) << "NIL" << " |\n";
	}
}