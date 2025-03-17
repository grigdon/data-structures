proj4.x: proj4.o bet.h
	g++ -Wall -pedantic -o $@ proj4.o

proj4.o: proj4_driver.cpp bet.h
	g++ -Wall -pedantic -c -o $@ proj4_driver.cpp

clean:
	rm -f proj4.x proj4.o
