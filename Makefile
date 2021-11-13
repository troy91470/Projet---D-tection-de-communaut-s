main.o: main.cpp Graph.cpp BronKerbosch.cpp TableauSuffixes.cpp
	g++ main.cpp Graph.cpp BronKerbosch.cpp TableauSuffixes.cpp -o projetCommunautes -Wall
