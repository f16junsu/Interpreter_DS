#pragma once
#include "Buffer.h"
#include "Memory.h"

char tolow(char ch);
int read(Buffer& buf, HashTable& hashtable, MemoryTable& memorytable);
void run(HashTable& hashtable, MemoryTable& memorytable, Buffer& buf);