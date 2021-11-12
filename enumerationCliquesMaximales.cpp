#include "BronKerbosch.h"
#include "TableauSuffixes.h"
#include "enumerationCliquesMaximales.h"

vector<vector<int>> listeCliquesEnumAlgo1(Graph &graph)
{
	int i,j,cliqueSize;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum,maxClique;

	vector<vector<int>> &maxCliqueRef=maxClique;
	vector<int> vectOrdreDegenerescence;
	ordreDegenerescence(graph.CreerCopie(), vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	graph.sortDegenerativeList(posSommetOrdreDegenerescence);
	TableauSuffix T = TableauSuffix();

	for(i=0;i<graph.GetNbSommets();i++)
	{
		maxClique = {};
		cout << i<<endl;
		Graph* sousgraphe = graph.TrouveSousGraphe(posSommetOrdreDegenerescence,  vectOrdreDegenerescence[i]);
		Graph &sousGraphePtr = *sousgraphe;

		BronKerboschDegeneracy(maxCliqueRef,sousGraphePtr);

		cliqueSize = maxClique.size();
		for(j=0;j<cliqueSize;j++)
		{
			if(T.rechercheSuffix(maxClique[j]))
			{
				//RIEN
			}
			else
			{
				T.ajoutVecteur(maxClique[j]);
				T.creerTableau();
				listeCliquesEnum.push_back(maxClique[j]);
			}
		}
	}
	return listeCliquesEnum;
}


vector<vector<int>> listeCliquesEnumAlgo2(Graph &graph)
{
	int i, j, z, nbMaxCliques, sizeClique;
	bool aAjouter = true;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum,maxCliques;
	vector<vector<int>> &maxCliqueRef=maxCliques;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(graph.CreerCopie(), vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	graph.sortDegenerativeList(posSommetOrdreDegenerescence);
	for (int k = 0; k < graph.GetNbSommets(); k++)
	{
		cout << posSommetOrdreDegenerescence[k]<< " ";
	}
	cout << endl;
	for(i=0;i<graph.GetNbSommets();i++)
	{
		Graph* Gi = graph.TrouveSousGraphe(posSommetOrdreDegenerescence, vectOrdreDegenerescence[i]);
		Graph &GiPtr = *Gi;
		maxCliques={};
		BronKerboschDegeneracy(maxCliqueRef,GiPtr);
		cout << "CLIQUESNB : "<<maxCliques.size() << endl;

		nbMaxCliques = maxCliques.size();
		for(j=0;j<nbMaxCliques;j++)
		{
			cout << "CLIQUE : ";
			sizeClique = maxCliques[j].size();
			for (int k = 0; k < sizeClique; k++)
				{
					cout << maxCliques[j][k];
				}
				cout << endl;

			for(z=0;z<sizeClique;z++)
			{
				if(verifClique(&graph,maxCliques[j],posSommetOrdreDegenerescence,posSommetOrdreDegenerescence[i],z))
				{
					//RIEN
				}
				else
				{
					aAjouter = false;
					break;
				}
			}

			if(aAjouter)
			{
				listeCliquesEnum.push_back(maxCliques[j]);
			}
			else
			{
				//RIEN
			}
		}
	}
	return listeCliquesEnum;
}


bool verifClique(Graph* graph,vector<int> K,int ordreDegenerescence[],int sommetSousGraphe,int sommetEtude)
{
	int sizeVoisinsDeSommetEtude;
	vector<int>* voisinsDeSommetEtude = graph->GetVoisins(sommetEtude);
	vector<int>* voisinsDeVoisins;
	vector<int> intersection;

	sizeVoisinsDeSommetEtude = voisinsDeSommetEtude->size();
	for(int i = 0; i < sizeVoisinsDeSommetEtude; i++)
	{
		if(ordreDegenerescence[i] < ordreDegenerescence[sommetSousGraphe])
		{
			//Suppose que K et voisinsDeVoisins sont triees de la même maniere.
			K = trierVecteurSelonOrdre(K,ordreDegenerescence,graph->GetNbSommets());
			voisinsDeVoisins = graph->GetVoisins(i);// IF neighbors of X adjacent to all vertex of K
			*voisinsDeVoisins = trierVecteurSelonOrdre(*voisinsDeVoisins,ordreDegenerescence,graph->GetNbSommets());
			set_intersection(voisinsDeVoisins->begin(),voisinsDeVoisins->end(),K.begin(),K.end(),back_inserter(intersection));
			if (intersection.size() == K.size()) // if intersection == K
			{
				return false;
			}
		}
		else
		{
			continue;
		}
	}
	return true;
}


vector<int> trierVecteurSelonOrdre(vector<int> v,int* ordre,int taille) //Implementation du trie fusion
{
	if (v.size()>1) {
        int mid = v.size()/2;

        vector<int> gauche(v.begin(),v.begin()+mid);
        vector<int> droite(v.begin()+mid,v.begin()+v.size());

        gauche = trierVecteurSelonOrdre(gauche,ordre,taille);
        droite = trierVecteurSelonOrdre(droite,ordre,taille);

        unsigned i = 0;
        unsigned j = 0;
        unsigned k = 0;
        while (i < gauche.size() && j < droite.size()) {
            if (ordre[gauche[i]] < ordre[droite[j]]) {
                v[k]=gauche[i];
                i++;
            } else {
                v[k] = droite[j];
                j++;
            }
            k++;
        }

        while (i<gauche.size()) {
            v[k] = gauche[i];
            i++;
            k++;
        }

        while (j<droite.size()) {
            v[k]=droite[j];
            j++;
            k++;
        }

    }
    return v;
}

/**
int main(){

	return 0;
}
*/



