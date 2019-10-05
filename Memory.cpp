#include "Memory.h"
#include <string>
#include <sstream>
using namespace symbols;

bool isFloat(const std::string& input)
{
	int i = 0;
	if (isdigit(input[i]) || input[i] == '-')
	{
		int cnt = 0;
		for (i = 1; input[i] != '\0'; ++i)
		{
			if (input[i] == '.')
			{
				++cnt;
				if (cnt - 1) return false;
			}
			else if (!isdigit(input[i])) return false;
		}
	}
	else return false;
	return true;
}

template<typename T>
std::string tostr(const T& input)
{
	std::stringstream ss;
	ss << input;
	return ss.str();
}

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

int MemoryTable::eval(void)
{
	return eval(node_root);
}

float* MemoryTable::cal_float(int root)
{
	float* arr = new float[2];
	int root_right = memorytable[root].getRight();
	arr[0] = stof(hashtable[-eval(memorytable[root_right].getLeft())].getSymbol());
	arr[1] = stof(hashtable[-eval(memorytable[memorytable[root_right].getRight()].getLeft())].getSymbol());
	return arr;
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

int MemoryTable::eval(int root)
{
	if (root <= 0)
		return hashtable[-root].getValue_index();
	int tok_ind = memorytable[root].getLeft();
	if (tok_ind == PLUS)
	{
		float* two = cal_float(root);
		std::string sresult = tostr<float>(two[0] + two[1]);
		delete[] two;
		hashtable.hashinsert(sresult);
		return hashtable.hashfunc(sresult);
	}
	else if (tok_ind == MINUS)
	{
		float* two = cal_float(root);
		std::string sresult = tostr<float>(two[0] - two[1]);
		delete[] two;
		hashtable.hashinsert(sresult);
		return hashtable.hashfunc(sresult);
	}
	else if (tok_ind == TIMES)
	{
		float* two = cal_float(root);
		std::string sresult = tostr<float>(two[0] * two[1]);
		delete[] two;
		hashtable.hashinsert(sresult);
		return hashtable.hashfunc(sresult);
	}
	else if (tok_ind == isNUMBER)
	{
		int result_ind = eval(memorytable[memorytable[root].getRight()].getLeft());
		if (result_ind > 0) return FALSE;
		else
		{
			std::string temp = hashtable[-result_ind].getSymbol();
			if (isFloat(temp)) return TRUE;
			else return FALSE;
		}
	}
	else if (tok_ind == isSYMBOL)
	{
		int result_ind = eval(memorytable[memorytable[root].getRight()].getLeft());
		if (result_ind > 0) return FALSE;
		else
		{
			std::string temp = hashtable[-result_ind].getSymbol();
			if (isFloat(temp)) return FALSE;
			else return TRUE;
		}
	}
	else if (tok_ind == isNULL)
	{
		if (eval(memorytable[root].getRight()) == NIL)
			return TRUE;
		return FALSE;
	}
	else if (tok_ind == CONS)
	{

	}
	else if (tok_ind == COND)
	{

	}
	else if (tok_ind == CAR)
	{
		return memorytable[eval(memorytable[memorytable[root].getRight()].getLeft())].getLeft();
	}
	else if (tok_ind == CDR)	
	{
		return memorytable[eval(memorytable[memorytable[root].getRight()].getLeft())].getRight();
	}
	else if (tok_ind == DEFINE)
	{
		int rr_ind = memorytable[memorytable[root].getRight()].getRight();
		if (memorytable[rr_ind].getLeft() < 0);
		else if (memorytable[memorytable[rr_ind].getLeft()].getLeft() == LAMBDA)
		{
			hashtable[-memorytable[memorytable[root].getRight()].getLeft()].setValue_index(
				memorytable[rr_ind].getLeft()
			);
			std::cout << "lambda case" << std::endl;
			return 0;
		}
		hashtable[-memorytable[memorytable[root].getRight()].getLeft()].setValue_index(
			eval(memorytable[rr_ind].getLeft())
		);
		std::cout << "var case" << std::endl;
		return 0;
	}
	else if (tok_ind == QUOTE)
		return memorytable[memorytable[root].getRight()].getLeft();
}

void MemoryTable::printEval(int result_ind)
{
	if (result_ind > 0);
	else std::cout << hashtable[-result_ind].getSymbol() << std::endl;
}