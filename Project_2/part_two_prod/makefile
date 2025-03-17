# Default target will now build both test_list.x and proj2.x
all: test_list.x proj2.x

# Rule to build test_list.x
test_list.x: List.hpp List.h test_list.o
	g++ -Wall -pedantic -o $@ test_list.o

# Rule to compile test_list.o
test_list.o: test_list.cpp List.hpp List.h
	g++ -Wall -pedantic -c -o $@ test_list.cpp

# Rule to build proj2.x
proj2.x: List.hpp List.h mem_manager.o mymemoryblock.o mymemory.o
	g++ -Wall -pedantic -o $@ mem_manager.o mymemoryblock.o mymemory.o

# Rule to compile mem_manager.o
mem_manager.o: List.hpp List.h mem_manager.cpp
	g++ -Wall -pedantic -c -o $@ mem_manager.cpp

# Rule to compile mymemoryblock.o
mymemoryblock.o: List.hpp List.h my_memory_block.h my_memory_block.cpp
	g++ -Wall -pedantic -c -o $@ my_memory_block.cpp

# Rule to compile mymemory.o
mymemory.o: List.hpp List.h my_memory.h my_memory.cpp
	g++ -Wall -pedantic -c -o $@ my_memory.cpp

# Clean up compiled files
.SUFFIXES: .x

.PHONY: clean all

clean:
	rm -f *.o *.x core.*