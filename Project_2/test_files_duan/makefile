test_list.x: List.hpp List.h test_list.cpp
	g++ -Wall -pedantic -o $@ test_list.cpp

proj2.x: List.hpp List.h mem_manager.o mymemoryblock.o mymemory.o
	g++ -Wall -pedantic -o $@ mem_manager.o mymemoryblock.o mymemory.o

mymemory.o: List.hpp List.h mymemory.h mymemory.cpp
	g++ -Wall -pedantic -c -o $@ mymemory.cpp

.SUFFIXES: .x

.PHONY: clean 

clean:
	rm -f *.o *.x core.*