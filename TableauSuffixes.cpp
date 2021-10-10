#include "TableauSuffixes.h"

TableauSuffix::TableauSuffix()
{
	numString = 0;
	sa = new std::vector<int>;
	texte = "";
}

void TableauSuffix::creerTableau()
{
	
	for (int i = 0; i < texte.size(); i++)
	{
		sa->push_back(i);
	}
}



void TableauSuffix::ajouterString(std::string entree)
{
	texte += entree;
}


int TableauSuffix::getMax(std::vector<int> tableau)
{
	int max = tableau[0];
	for (int i = 1; i < tableau.size(); i++)
	{
		if (tableau[i] > max)
			max = tableau[i];
	}
	return max;
}

void TableauSuffix::trieComptage(std::vector<int> entree, std::vector<int>* sortie, int indice)
{
	const int max = 10;
	int compte[max] = { 0 };

	//Comptage des elements de 0 à 10
	for (int i = 0; i < sortie->size(); i++)
	{
		//indice = 1,10,100,..
		//exemple : entree[i] == 128 et indice == 1
		// (entree[i]/ indice) %10 == 8
		compte[(entree[i] / indice) % 10] ++;
	}
	for (int i = 1; i < max; i++)
	{
		compte[i] += compte[i - 1];
	}
	for (int i = max - 1; i > 0; i--)
	{
		compte[i] = compte[i - 1];
	}
	compte[0] = 0;
	for (int i = 0; i < sortie->size(); i++)
	{
		sortie->operator[](compte[(entree[i] / indice) % 10]) = entree[i];
		std::cout << "indice : " << compte[(entree[i] / indice) % 10] << " valeur : " << entree[i] << std::endl;
		compte[(entree[i] / indice) % 10] ++;
	}
	std::cout << "OK" << std::endl;
}
void TableauSuffix::trieRadix(std::vector<int> entree, std::vector<int>* sortie)
{
	int max = getMax(entree);
	for (int indice = 1; indice < max; indice *= 10)
	{
		if(indice ==1)
			trieComptage(entree, sortie, indice);
		else
			trieComptage(*sortie, sortie, indice);

	}
}

template <typename T>
void TableauSuffix::printVector(std::vector<T>* vec )
{
	for (auto i = vec->begin(); i != vec->end(); i++)
	{
		std::cout << *i << ' ';
	}
	std::cout << "DONE" << std::endl;
}


void TableauSuffix::printSA()
{
	std::cout << "SA : ";
	printVector(sa);
	std::cout << std::endl;

}

void TableauSuffix::test()
{
	std::vector<int> test = { 128, 75, 9, 32, 52 };
	std::vector<int>* sortie = new std::vector<int>(test.size());
	trieRadix(test, sortie);
	printVector(sortie);
	std::cout << std::endl;
}
