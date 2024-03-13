vector: main.o
	g++ -o vector main.o
main.o:
	g++ -c main.cpp
