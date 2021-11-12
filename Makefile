main.o: main.cpp Graph.cpp Graph.h BronKerbosch.cpp BronKerbosch.h TableauSuffixes.cpp TableauSuffixes.h
	g++ main.cpp Graph.cpp Graph.h BronKerbosch.cpp BronKerbosch.h TableauSuffixes.cpp TableauSuffixes.h -o projetDegenerescence -Wall
