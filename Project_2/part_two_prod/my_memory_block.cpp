#include "my_memory_block.h"
using namespace my_memory_block;

// two-parameter constructor with default ind & len = 0
MyMemoryBlock::MyMemoryBlock(int ind, int len) 
   : index(ind), length(len) {}

// returns the length of the memory block
int MyMemoryBlock::get_length() {
    return length;
}

// returns the index of the memory block
int MyMemoryBlock::get_index() {
    return index;
}

// this function emulates memory allocation, where "len" is the requested memory length
int MyMemoryBlock::allocate_mem(int len) {
    if (len > length) {
        return -1;
    }

    length -= len;
    return len;

}

// emulates memory de-allocation, adding len to the length of the memory block
void MyMemoryBlock::free_mem(int len) {
    length += len;
}

