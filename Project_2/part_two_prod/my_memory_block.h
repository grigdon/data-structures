#ifndef MY_MEMORY_BLOCK_H
#define MY_MEMORY_BLOCK_H

namespace my_memory_block {
    class MyMemoryBlock {
        private:
            int index; // index of the memory block
            int length; // length of the memory block
        public:
            MyMemoryBlock(int ind = 0, int len = 0); // will initialize the member variables index and length, using ind and len, respectively
            int get_length(); // returns the current length of the memory block
            int get_index(); // returns the index of the memory block
            int allocate_mem(int len); // this function emulates memory allocation, where "len" is the requested memory length
            void free_mem(int len); //  emulates memory de-allocation, adding len to the length of the memory block
    };   
}

#endif
