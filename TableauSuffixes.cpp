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
/*
 On ajoute un vecteur a la fin de la liste de vecteur.
 On separe chaque vecteur d'un caractere null qui a un ordre lexicographique plus faible que tout autre caractere.
 Exemple : 63418(-1)99123(-2)
*/
void TableauSuffix::ajoutVecteur(vector<int> v)
{
	listeVecteur->insert(end(*listeVecteur),begin(v),end(v));
    listeVecteur->push_back(caractereNull);
    caractereNull -= 1;
}
void TableauSuffix::creerTableau()
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
	//On trie les triplets
	trieRadix(&s12,&SA12,vecteurATrie,n02,2);
	trieRadix(&SA12,&s12,vecteurATrie,n02,1);
	trieRadix(&s12,&SA12,vecteurATrie,n02,0);

	//nomage lexicographique des triplets
	int nomLex = 0, c0 = -1, c1 = -1, c2 = -1;
	for (int i = 0; i < n02; i++)
	{
		if (vecteurATrie[SA12[i]] != c0 || vecteurATrie[SA12[i] + 1] != c1 || vecteurATrie[SA12[i] + 2] != c2)
		{
			nomLex++; //Le triplet ne correspond pas au triplet precedent, on lui donne un nom unique.
			c0 = vecteurATrie[SA12[i]]; c1 = vecteurATrie[SA12[i] + 1]; c2 = vecteurATrie[SA12[i] + 2];
		}
		SA12[i] % 3 == 1 ? s12[SA12[i] / 3] = nomLex : s12[SA12[i] / 3 + n0] = nomLex;
	}

	/*Il est possible que le nom soit pas unique donc on refait l'algo sur une partie plus petite du vecteur. 
	  on réduit donc la taille de la donnee a traiter a chaque fois.
	  Cependant dans le cas des de la sauvegarde de clique maximale, il n'est pas possible d'avoir des doublons dans le vecteur
	  car chaque sommet apparait forcement qu'une fois dans le vecteur.
	  Donc ce cas n'est pas possible.
	*/
		if (nomLex < n02)//pas tous les triplets ont un nom unique.
		{
			//Si on arrive ici on n'a pas le choix de stopper le programme car le cas n'est pas traite.
			cout << "ERREUR NOM PAS UNIQUE"<< endl;
			printVector(&SA12);
			exit(4);
		}
		else // Tous les triplets de SA12 sont unique.
			for (int i = 0; i < n02; i++)
			{
				SA12[s12[i] - 1] = i;
			}
		// A partir de SA12 on peut determiner les valeurs pour S0.
		for (int i=0, j=0; i < n02; i++)
			if (SA12[i] < n0)
				s0[j++] = SA12[i] * 3;
		// On trie selon le premier caractere des triplets.
		trieRadix(&s0,&SA0,vecteurATrie,n0,0);
		//Fusion des suffixes de SA0 et SA12
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
/*
 Le trie radix fonctionne en appelent de maniere successive du trie comptage sur chaque puissance de 10 d'un nombre.(si on trie des nombre en base 10)
 Cette implementation prend en entree la puissance d'on ont veut trier.
 Cependant on trie pas directement un tableau mais un vecteur d'indice organise en triplets qui represente le debut de chaque suffixes.
 Donc on compare les cases du tableau selon un decalage car trois case du tableau reprente un triplet a trier.
 Exemple : 623 459 817 avec decalage = 1
	on va trier les triplets selon 2,5,1.
*/
void TableauSuffix::trieRadix(vector<int>* 	vecteurIndice, vector<int>* sortie,vector<int> entree,int longeur, int decalage)
{
		int max = getMax(entree);
		int compte[max+1+(-caractereNull)] = { 0 };
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
		}
		for (int i = 0; i < longeur; i++)
			sortie->operator[](compte[entree[vecteurIndice->operator[](i) + decalage]+(-caractereNull)]++) = vecteurIndice->operator[](i);
}
/*
	Pour parcourir le tableau de suffixes il suffit de faire une recherche dichotomique
	car les indices des suffixes sont triés dans l'ordre lexicographique.
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

template <typename T>
void TableauSuffix::printVector(vector<T>* vec )
{
	for (auto i = vec->begin(); i != vec->end(); i++)
	{
		cout << *i << ' ';
	}
	cout << endl;
}


void TableauSuffix::printSA()
{
	cout << "SA : ";
	printVector(sa);
	cout << endl;

}
/*
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
*/
