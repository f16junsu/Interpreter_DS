#pragma once
#include "Buffer.h"
#include "Memory.h"

bool isPredefined(int check);

template<typename T>
inline std::string tostr(const T& input)
{
	std::stringstream ss;
	ss << input;
	return ss.str();
}

bool isFloat(const std::string& input);

int read(Buffer& buf, HashTable& hashtable, MemoryTable& memorytable);