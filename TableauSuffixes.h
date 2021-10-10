#ifndef _SARRAY_
#define _SARRAY_




#include <vector>
#include <string>
#include <iostream>
//Implementation de l'algorithme de Skew pour la construction de tableau de suffixe
//Reference: https://gist.github.com/markormesher/59b990fba09972b4737e7ed66912e044


class TableauSuffix {
	public:
		TableauSuffix();
		void creerTableau();
		void ajouterString(std::string);
		void printSA();
		void test();
	private:
		std::vector<int>* sa;
		std::string texte;
		int numString;
		int getMax(std::vector<int>);
		void trieComptage(std::vector<int>, std::vector<int>*,int);
		void trieRadix(std::vector<int>, std::vector<int>*);
		template <typename T>
		void printVector(std::vector<T>*);
		

		

};

#endif // !_SARRAY_