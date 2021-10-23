#ifndef _SARRAY_
#define _SARRAY_




#include <vector>
#include <string>
#include <iostream>

using namespace std;
//Implementation de l'algorithme de Skew pour la construction de tableau de suffixe
/*Reference:
https://gist.github.com/markormesher/59b990fba09972b4737e7ed66912e044
http://www.mi.fu-berlin.de/wiki/pub/ABI/SS13Lecture3Materials/script.pdf
https://www.cs.cmu.edu/~ckingsf/bioinfo-lectures/suffixarrays.pdf
*/
//TODO Methode de recherche dans un tableau de suffixes
//TODO La fusion des teableaux de suffixes pour une recherche dichotomique d'un seul tableau en O(n)
class TableauSuffix {
	public:
		TableauSuffix();
		~TableauSuffix();
		void ajoutVecteur(vector<int>);
		void creerTableau();
		void fusionTableau(TableauSuffix*);
		bool rechercheSuffix(vector<int>);
		void printSA();
		void test();
		vector<int> getSA();
	private:
		vector<int>* sa;
		vector<int>* listeVecteur;
		int numString;
		int caractereNull = -1;
		//FONCTION
		void constructionTableauSuffix(vector<int>,vector<int>*,int);
		int getMax(vector<int>);
		void trieComptage(vector<int>*, vector<int>*,vector<int>,int);
		void trieRadix(vector<int>*, vector<int>*,vector<int>,int,int);
		template <typename T>
		void printVector(vector<T>*);
};

#endif // !_SARRAY_