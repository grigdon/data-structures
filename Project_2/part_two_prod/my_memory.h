#ifndef MY_MEMORY_H
#define MY_MEMORY_H

#include "List.h"
#include "my_memory_block.h"

namespace my_memory {

	class MyMemory {
	private:
		cop4530::List<my_memory_block::MyMemoryBlock> mlist; // doubly linked list of type MyMemoryBlock
		int max_index; // maximum index of the list
		int block_size; // block size of each memory block
	public:
		MyMemory(int num = 0, int len = 0); // two parameter constructor 
		void resize(int num = 100, int len = 100); // resizes mlist according to the two parameters
		int req_mem(int len); // requests memory from the list of size length
		bool release_mem(int ind, int len); // frees memory from the the list of size length at the specified index
		void merge_mem(); // merges corresponding memory blocks 
		void dump(); //prints mlist
		~MyMemory(); // destructor 
	};
}

#endif
