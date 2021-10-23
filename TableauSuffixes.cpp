#include "TableauSuffixes.h"


TableauSuffix::TableauSuffix()
{
	numString = 0;
	sa = new vector<int>;
	listeVecteur = new vector<int>;

}
TableauSuffix::~TableauSuffix()
{
	delete sa;
	delete listeVecteur;
}
void TableauSuffix::ajoutVecteur(vector<int> v)
{
	listeVecteur->insert(end(*listeVecteur),begin(v),end(v));
    listeVecteur->push_back(caractereNull);
    caractereNull -= 1;
}
void TableauSuffix::creerTableau() //IMPLEMENTATION SKEW
{
	int n = listeVecteur->size();
	sa->resize(listeVecteur->size());
	listeVecteur->push_back(caractereNull); // Ajout de caractere null en cas si le vecteur
	listeVecteur->push_back(caractereNull); // d'entree n'est pas un multiple de 3.
	listeVecteur->push_back(caractereNull);
	constructionTableauSuffix(*listeVecteur,sa,n);
	listeVecteur->pop_back();
	listeVecteur->pop_back();
	listeVecteur->pop_back();
}

void TableauSuffix::constructionTableauSuffix(vector<int> vecteurATrie,vector<int>* SA,int longeur)
{
	int n0 = ((longeur + 2) / 3);
	int n1 = (longeur + 1) / 3;
	int n2 = longeur / 3 ;
	int n02 = n0 + n2;
	vector<int> s12(n02 + 3);
	vector<int> SA12(n02 + 3);
	s12[n02] = s12[n02 + 1] = s12[n02 + 2] = caractereNull;
	SA12[n02] = SA12[n02 + 1] = SA12[n02 + 2] = caractereNull;
	vector<int> s0(n0);
	vector<int> SA0(n0);

	for(int i = 0, j = 0;i< longeur + (n0 - n1);i++)
	{
		if (i % 3 != 0)
			s12[j++] = i;
	}
	//std::cout << "before sort : ";
	//printVector(&SA12);
	trieRadix(&s12,&SA12,vecteurATrie,n02,2);
	trieRadix(&SA12,&s12,vecteurATrie,n02,1);
	trieRadix(&s12,&SA12,vecteurATrie,n02,0);
	int nomLex = 0, c0 = -1, c1 = -1, c2 = -1;
	//on donne un nom lexicographique unique pour chaque triplet
	//Exemple : la suite 428, on associe le nom 1
	//std::cout << "after sort : ";
	//printVector(&SA12);
	for (int i = 0; i < n02; i++)
	{
		//cout << "C0 = " << vecteurATrie[SA12[i]] << " C1 = " << vecteurATrie[SA12[i] + 1] << " C2 = " << vecteurATrie[SA12[i] + 2] << endl;
		if (vecteurATrie[SA12[i]] != c0 || vecteurATrie[SA12[i] + 1] != c1 || vecteurATrie[SA12[i] + 2] != c2)
		{
			nomLex++;
			c0 = vecteurATrie[SA12[i]]; c1 = vecteurATrie[SA12[i] + 1]; c2 = vecteurATrie[SA12[i] + 2];
		}
		SA12[i] % 3 == 1 ? s12[SA12[i] / 3] = nomLex : s12[SA12[i] / 3 + n0] = nomLex;
	}
	//cout << "SA12 ";
	//printVector(&SA12);
	//cout << endl;
	//std::cout << "Naming : ";
	//printVector(&s12);
	//Il est possible que le nom soit pas unique donc on refait l'algo sur
	//une partie plus petite du vecteur. on on réduit donc la taille de la donnee a traiter a chaque fois.
		if (nomLex < n02)//pas tous les triplets ont un nom unique.
		{
			cout << "ERREUR NOM PAS UNIQUE"<< endl;
			printVector(&SA12);
			exit(4);
			//creerTableau(s12, SA12, n02, nomLex);
			//for (int i = 0; i < n02; i++) s12[SA12[i]] = i + 1;
		}
		else
			for (int i = 0; i < n02; i++)
			{
				SA12[s12[i] - 1] = i;
			}

		for (int i=0, j=0; i < n02; i++)
			if (SA12[i] < n0)
				s0[j++] = SA12[i] * 3;

		trieRadix(&s0,&SA0,vecteurATrie,n0,0);
	//		std::cout << "SA0 : ";
	//printVector(&SA0);
	//std::cout << std::endl;
		//merge SA0 and SA12 suffixes
		auto leqPair = [](int a1,int a2, int b1, int b2)->bool{
			return a1 < b1 || a1 == b1 && a2 <= b2;
		};
		auto leqTriple = [leqPair](int a1, int a2, int a3, int b1, int b2, int b3)->bool {
			return a1 < b1 || a1 == b1 && leqPair(a2,a3,b2,b3);
		};
		#define getI() (SA12[t] < n0 ? SA12[t] * 3 + 1 : (SA12[t] - n0) * 3 + 2)
		for (int p = 0, t = n0 - n1, k = 0; k < longeur; k++)
		{
			int i = getI(); //offset of 12 suffix
			int j = SA0[p]; //offset of 0 suffix
			if (SA12[t] < n0 ? leqPair(vecteurATrie[i],s12[SA12[t]+n0],vecteurATrie[j],s12[j/3]) :
				leqTriple(vecteurATrie[i],vecteurATrie[i+1],s12[SA12[t]-n0+1], vecteurATrie[j],vecteurATrie[j+1],s12[j/3+n0]))
			{
				SA->operator[](k) = i;
				t++;
				if (t == n02)// done --- only SA0 suffixes left
					for (k++; p < n0; p++, k++) SA->operator[](k) = SA0[p];
			}
			else
			{
				SA->operator[](k) = j;
				p++;
				if (p == n0)// done --- only SA12 suffixes left
				{
					for (k++; t < n02; t++, k++)
						SA->operator[](k) = getI();
				}
			}
		}
}

int TableauSuffix::getMax(vector<int> tableau)
{
	int max = tableau[0];
	for (int i = 1; i < tableau.size(); i++)
	{
		if (tableau[i] > max)
			max = tableau[i];
	}
	return max;
}

void TableauSuffix::trieRadix(vector<int>* 	vecteurIndice, vector<int>* sortie,vector<int> entree,int longeur, int decalage)
{
		//printVector(vecteurIndice);
		int max = getMax(entree);
		int compte[max+1+(-caractereNull)] = { 0 };
		//cout << "CarNULL "<<-caractereNull<<endl;
		for (int i = 0; i < longeur; i++)
		{
			compte[entree[vecteurIndice->operator[](i) + decalage]+(-caractereNull)]++; // +1 car le symbole null est -1, on ajuste pour que ca soit 0
		}
		int somme = 0;
		for (int i = 0; i <= max +1+(-caractereNull); i++)
		{
			int val = compte[i];
			compte[i] = somme;
			somme += val;
			//cout << compte[i]<< " ";
		}
		//cout << endl;
		for (int i = 0; i < longeur; i++)
		{
			//for (int j = 0; j < max+1; j++)
			//	cout << compte[j]<< " ";
			//cout << endl;
			sortie->operator[](compte[entree[vecteurIndice->operator[](i) + decalage]+(-caractereNull)]++) = vecteurIndice->operator[](i);
			//cout << "OK " << compte[entree[vecteurIndice->operator[](i) + decalage]+1] <<endl;

		}
}
vector<int> TableauSuffix::getSA()
{
	return *sa;
}
/**
vector<vector<int>> TableauSuffix::getListeVecteur()
{
	return listeVecteur;
}
**/
//La fusion est plus complique en temps que prevue.
/*void TableauSuffix::fusionTableau(TableauSuffix* t) //Limite de 100 noeuds dans une clique
{
	listeVecteur->push_back(t->getListeVecteur()[0]);//On suppose que le tableau de suffix a ajouter contient uniquement qu'une sequence.
	indicesequence = listeVecteur->size()-1;
	vector<int> tableauT = t->getSA();
	vector<int> resultat;
	resultat.resize(sa->size()+tableauT.size());
	for (int i = 0,p = 0, j = 0; i < resultat.size(); i++)
	{
		int x = sa->operator[](p);
		int y = tableauT[j];
		while (condi)
		{
		}
		
	}
}
*/
bool TableauSuffix::rechercheSuffix(vector<int> v)
{
	int start = 0,end = sa->size()-1,mid;
	bool match = false;
	while (end >= start)
	{
		mid = (start + end) / 2;
		int x = mid,y = 0;
		vector<int> sousVecteur(listeVecteur->cbegin()+sa->operator[](mid),listeVecteur->cbegin() + sa->operator[](mid) + v.size());
		if(v == sousVecteur)
		{
			match = true;
			break;
		}
		else if (v < sousVecteur)
			end = mid - 1;
		else // v > sousVecteur
			start = mid + 1;
	}
 	return match;
}



/*


void TableauSuffix::trieComptage(vector<int>* vecteurIndice, vector<int>* sortie,vector<int> entree, int indice)
{
	const int max = 10;
	int compte[max] = { 0 };

	//Comptage des elements de 0 a 10
	for (int i = 0; i < sortie->size(); i++)
	{
		//indice = 1,10,100,..
		//exemple : entree[i] == 128 et indice == 1
		// (entree[i]/ indice) %10 == 8
		compte[(entree[i] / indice) % 10] ++;
	}
	for(int i = 1; i < max; i ++)
	{
		compte[i] += compte[i -1];
	}
	for (int i = max - 1; i > 0; i--)
	{
		compte[i] = compte[i - 1];
	}
	compte[0] = 0;

	for (int i = 0; i < sortie->size(); i++)
	{
		sortie->operator[](compte[(entree[i] / indice) % 10]) = vecteurIndice->operator[](i);
		//	cout << "indice : " << compte[(entree[i] / indice) % 10] << " valeur : " << entree[i] << endl;
		compte[(entree[i] / indice) % 10] ++;
	}
	//cout << "OK" << endl;
}
//Le trie radix est modifie pour accepter des entiers et ne trie pas directement les element d'un vecteur
//mais des indices de la position des elements du vecteur "entree"
void TableauSuffix::trieRadix(vector<int>* vectorIndice, vector<int>* sortie,vector<int> entree,int indice)
{
	if(indice == -1)
	{
		int max = getMax(entree);
		for (int indice = 1; indice < max; indice *= 10)
		{
			if(indice ==1)
				trieComptage(vectorIndice, sortie,entree, indice);
			else
				trieComptage(vectorIndice, sortie,*sortie, indice);
		}
	}
	else
	{
		trieComptage(vectorIndice, sortie,entree, indice);
	}
}

*/

template <typename T>
void TableauSuffix::printVector(vector<T>* vec )
{
	for (auto i = vec->begin(); i != vec->end(); i++)
	{
		cout << *i << ' ';
	}
	cout << "DONE" << endl;
}


void TableauSuffix::printSA()
{
	cout << "SA : ";
	printVector(sa);
	cout << endl;

}

void TableauSuffix::test()
{
	vector<int> test1 = {6,5,1,2,7,3,8,9};
	vector<int> test2 = {11,28,4,12,0};
	ajoutVecteur(test1);
	ajoutVecteur(test2);
	creerTableau();
	printVector(sa);
	cout << endl;
	cout << " Recherche {4,12,0} : " <<rechercheSuffix({4,12,0}) << endl;
}
