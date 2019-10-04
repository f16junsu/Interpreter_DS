#pragma once
#include "Buffer.h"
#include "Memory.h"

int read(Buffer& buf, HashTable& hashtable, MemoryTable& memorytable);
void run(HashTable& hashtable, MemoryTable& memorytable, Buffer& buf);