output: test_list.o
	g++ -o test_list.x test_list.o

test_list.o: test_list.cpp List.h List.hpp
	g++ -std=c++11 -c test_list.cpp

clean:
	rm *.o test_list.x
