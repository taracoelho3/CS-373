all:	p1

p1:	coelho_p1.o
	g++ -g -Wall -std=c++11 coelho_p1.o -o p1

coelho_p1.o:	coelho_p1.cpp
	g++ -c coelho_p1.cpp 

clean:
	rm *.o p1