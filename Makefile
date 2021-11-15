main.o: main.cpp Graph.cpp BronKerbosch.cpp TableauSuffixes.cpp enumerationCliquesMaximales.cpp
	g++ -g main.cpp Graph.cpp BronKerbosch.cpp TableauSuffixes.cpp enumerationCliquesMaximales.cpp -o projetCommunautes -Wall
