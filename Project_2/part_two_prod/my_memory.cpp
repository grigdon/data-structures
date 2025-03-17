#include "my_memory.h"
#include "my_memory_block.h"

using namespace my_memory;
using namespace my_memory_block;
using namespace cop4530;

// two parameter constructor with default values num, len = 0
MyMemory::MyMemory(int ind, int len)
    : max_index(ind - 1), block_size(len) {
        for(int i = 0; i < ind; ++i) {
            mlist.push_back(MyMemoryBlock(i, len));
        }
}

// resizes mlist according to the two parameters ind and len
void MyMemory::resize(int ind, int len) {

    // clears the MyMemory object
    mlist.clear();

    //mimics the function of the two parameter constructor above
    max_index = ind - 1;
    block_size = len;
    for(int i = 0; i < ind; ++i) {
        mlist.push_back(MyMemoryBlock(i, len));
    }
}

// requests memory from the list of size length
int MyMemory::req_mem(int len) {
    for(auto it = mlist.begin(); it != mlist.end(); ++it) {
        if(it ->get_length() >= len) {

            it->allocate_mem(len);
            if(it->get_length() == 0) {
                mlist.erase(it);
            }
            
            return it->get_length();
        }
    }

    return -1;
}

// frees memory from the the list of size length at the specified index
bool MyMemory::release_mem(int ind, int len) {

    if(ind > 0 && ind < max_index && len > 0 && len < block_size) {

        // case where the desired index exists in the list
        for (auto it = mlist.begin(); it != mlist.end(); ++it) {
            if (it->get_index() == ind) {
                it->free_mem(len);
                return true;
            }
        }
        // case where the desired index does not exist in the list
        MyMemoryBlock newBlock(ind, len);
        for (auto it = mlist.begin(); it != mlist.end(); ++it) {
            if (it->get_index() > ind) {
                mlist.insert(it, newBlock);
                return true;
            }
        }
        mlist.push_back(newBlock);
        return true;
    }

    return false;
}

// merge neighboring memory blocks
void MyMemory::merge_mem() {

    // look for blocks to merge in the list
    for (auto itMain = mlist.begin(); itMain != mlist.end();) {
        auto itMainNext = itMain;
        itMainNext++;

        // keep merging until the block size maximum is reached
        while (itMainNext != mlist.end() && itMain->get_length() + itMainNext->get_length() <= block_size) {

            itMain->free_mem(itMainNext->get_length());
            itMainNext = mlist.erase(itMainNext);
        }

        itMain = itMainNext;
    }
}

// dump (print) the contents of mlist
void MyMemory::dump() {
     std::cout << "Number of blocks: " << mlist.size() << "\n";
     for(auto itr = mlist.begin(); itr != mlist.end(); ++itr) {
         std::cout << "Block(index =  " << itr->get_index() << "): " << itr->get_length() << "\n";
    }
}

// destructor from list implementation
MyMemory::~MyMemory() {
    mlist.clear();  
}