#include "my_memory.h"
#include "my_memory_block.h"
using namespace my_memory;
using namespace my_memory_block;

void print_menu();

int main(void) {

	int numBlocks, blockSize;
	char input;
	bool shouldContinue = true;

	std::cout << "Memory Configuration:\n";
	std::cout << "Number of memory blocks (integer):\n";
		std::cin >> numBlocks;
	std::cout << "Memory block size (integer): ";
		std::cin >> blockSize;


	// Creates MyMemory doubly linked list of "numBlocks" number of blocks, where each block is "blockSize" large
	MyMemory myMem(numBlocks, blockSize);

	// Creates the user-interactable menu
	while(shouldContinue) {

		print_menu();
		std::cin >> input;

		switch(input) {

			case 'd':  {
				std::cout << "choice: d\n";
				myMem.dump();
				break;
			}
			case 'r': {
				std::cout << "choice: r\n";
				int reqMemSize;
				std::cout << "Requested memory size (integer):";
				std::cin >> reqMemSize; 			
				myMem.req_mem(reqMemSize);
				break;
			}
			case 'l': {
				std::cout << "choice: l\n";
				int relMemIndex, relMemLength;
				std::cout << "Release memory index (integer):";	
				std::cin >> relMemIndex;
				std::cout << "Release memory length (integer):";
				std::cin >> relMemLength;			
				myMem.release_mem(relMemIndex, relMemLength);
				break;
			}
			case 'm': {
				std::cout << "choice: m\n";
				myMem.merge_mem();
			        break;
			}
			case 'x': {
				std::cout << "choice: x\n";
				shouldContinue = false;
				break;
			}
			default: {
				std::cout << "Invalid entry. Try again.\n";
				break;
			}
		}
	}
	
	return(0);
}

void print_menu() {
	std::cout << std::string(20, '=') << std::endl;
	std::cout << "d: memory dump" << std::endl;
	std::cout << "r: request memory" << std::endl;
	std::cout << "l: release memory" << std::endl;
	std::cout << "m: merge memory" << std::endl;
	std::cout << "x: quit program" << std::endl;
	std::cout << "Your choice: ";	
}
