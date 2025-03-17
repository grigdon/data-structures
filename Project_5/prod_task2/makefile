output: proj5.o
	g++ -o proj5.x proj5.o

proj5.o: proj5.cpp passserver.h passserver.cpp
	g++ -Wall -c proj5.cpp -lcrypt

clean:
	rm -f *.o proj5.x
