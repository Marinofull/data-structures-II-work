#include "data-structure.h"

int hash1(int key, const int length)
{
    return key % length;
}

int hash2(int key, const int length)
{
    return max(floor(kay/length), 1);
}
