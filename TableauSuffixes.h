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

class TableauSuffix {
	public:
		TableauSuffix();
		void creerTableau(vector<int>);
		void fusionTableau();
		void printSA();
		void test();
	private:
		vector<int>* sa;
		static vector<vector<int>>* listeVecteur;
		int numString;
		const int caractereNull = -1;
		//FONCTION
		void constructionTableauSuffix(vector<int>,vector<int>*,int);
		int getMax(vector<int>);
		void trieComptage(vector<int>*, vector<int>*,vector<int>,int);
		void trieRadix(vector<int>*, vector<int>*,vector<int>,int,int);
		template <typename T>
		void printVector(vector<T>*);
};

#endif // !_SARRAY_