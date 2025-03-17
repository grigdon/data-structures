in2post.x: in2post.o stack.h
	g++ -Wall -pedantic -o $@ in2post.o

in2post.o: in2post.cpp stack.h
	g++ -Wall -pedantic -c -o $@ in2post.cpp

clean:
	rm in2post.x in2post.o