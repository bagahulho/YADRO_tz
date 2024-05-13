yadro : main.o functions.o cases.o Table.o
	g++ -std=c++17 main.o functions.o cases.o Table.o -o yadro

main.o : main.cpp
	g++ -c main.cpp

functions.o : functions.h
	g++ -c functions.cpp

cases.o : cases.h
	g++ -c cases.cpp

Table.o : Table.h
	g++ -c Table.cpp