#include "Memory.h"
#include "Others.h"
#include <string>
#include <sstream>
using namespace symbols;

template<typename T>
std::string tostr(const T& input)
{
	std::stringstream ss;
	ss << input;
	return ss.str();
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
	if (node_root == 0) return "()";
	return "(" + echo(node_root);
}

void MemoryTable::print(void)
{
	if (node_root < 0) std::cout << hashtable[-node_root].getSymbol() << std::endl;
	else std::cout << echo() << std::endl;
}

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
		if (result_ind >= 0) return FALSE;
		else
		{
			std::string temp = hashtable[-result_ind].getSymbol();
			if (isFloat(temp)) return FALSE;
			else return TRUE;
		}
	}
	else if (tok_ind == isNULL)
	{
		if (eval(memorytable[root].getRight()) == NIL) return TRUE;
		return FALSE;
	}
	else if (tok_ind == CONS)
	{
		int newmemory = alloc();
		memorytable[newmemory].setLeft(eval(memorytable[memorytable[root].getRight()].getLeft()));
		memorytable[newmemory].setRight(eval(
			memorytable[memorytable[memorytable[root].getRight()].getRight()].getLeft()
		));
		return newmemory;
	}
	else if (tok_ind == COND)
	{
		int cond_root = root;
		while (memorytable[memorytable[cond_root].getRight()].getRight()) // (cond ((number? 3) (* 2 2)) (else (* 5 5)))
		{
			cond_root = memorytable[cond_root].getRight();
			if (eval(memorytable[memorytable[cond_root].getLeft()].getLeft()) == TRUE)
				return eval(memorytable[memorytable[memorytable[cond_root].getLeft()].getRight()].getLeft());
		}
		try
		{
			if (memorytable[memorytable[memorytable[cond_root].getRight()].getLeft()].getLeft() != ELSE)
				throw std::runtime_error("else expected : enter again");
		}
		catch (std::exception & e) { std::cout << e.what() << std::endl; }
		return eval(memorytable[memorytable[memorytable[memorytable[cond_root].getRight()].getLeft()].getRight()].getLeft());
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
			return 0;
		}
		hashtable[-memorytable[memorytable[root].getRight()].getLeft()].setValue_index(
			eval(memorytable[rr_ind].getLeft())
		);
		return 0;
	}
	else if (tok_ind == QUOTE)
	{
		return memorytable[memorytable[root].getRight()].getLeft();
	}
	else
	{
		int lamb = eval(tok_ind); // 4
		int iter_paras, iter_factors;
		int cnt = 0;
		if ((iter_paras = memorytable[memorytable[lamb].getRight()].getLeft())) // iter_paras = 6
		{
			iter_factors = memorytable[root].getRight();
			do
			{
				stack.push(Node(memorytable[iter_paras].getLeft(),
					hashtable[-memorytable[iter_paras].getLeft()].getValue_index()));
				hashtable[-memorytable[iter_paras].getLeft()].setValue_index(eval(memorytable[iter_factors].getLeft()));
				iter_paras = memorytable[iter_paras].getRight();
				iter_factors = memorytable[iter_factors].getRight();
				++cnt;
			} while (iter_factors);
		}
		int result = eval(memorytable[memorytable[memorytable[lamb].getRight()].getRight()].getLeft());
		while (cnt)
		{
			Node temp = stack.pop();
			hashtable[-temp.getHash_val()].setValue_index(temp.getLink_val());
			--cnt;
		}
		return result;
	}
}

void MemoryTable::printEval(int result_ind)
{
	if (result_ind > 0) std::cout << "'(" + echo(result_ind) << std::endl;
	else if (result_ind == 0) std::cout << "NIL" << std::endl;
	else 
	{
		std::string temp = hashtable[-result_ind].getSymbol();
		if (isFloat(temp)) std::cout << temp << std::endl;
		else if (result_ind == TRUE || result_ind == FALSE) std::cout << temp << std::endl;
		else std::cout << "'" + temp << std::endl;
	}
}