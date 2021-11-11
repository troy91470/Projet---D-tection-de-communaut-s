#include "BronKerbosch.h"
#include "TableauSuffixes.h"

bool verifClique(Graph* graph,vector<int> K,int ordreDegenerescence[],int sommetSousGraphe,int sommetEtude);
vector<int> trierVecteurSelonOrdre(vector<int> v,int* ordre,int taille);


vector<vector<int>> listeCliquesEnumAlgo1(Graph &graph)
{
	int i,j;
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

		for(j=0;j<maxClique.size();j++)
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
	int i, j, z;
	bool aAjouter = true;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum,maxCliques;
	vector<vector<int>> &maxCliqueRef=maxCliques;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(graph.CreerCopie(), vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	graph.sortDegenerativeList(posSommetOrdreDegenerescence);

	for(i=0;i<graph.GetNbSommets();i++)
	{
		Graph* Gi = graph.TrouveSousGraphe(posSommetOrdreDegenerescence, vectOrdreDegenerescence[i]);
		Graph &GiPtr = *Gi;
		maxCliques={};
		BronKerboschDegeneracy(maxCliqueRef,GiPtr);
		cout << "CLIQUESNB : "<<maxCliques.size() << endl;
		for(j=0;j<maxCliques.size();j++)
		{
			cout << "CLIQUE : ";
			for (int k = 0; k < maxCliques[j].size(); k++)
				{
					cout << maxCliques[j][k];
				}
				cout << endl;
			for(z=0;z<maxCliques[j].size();z++)
			{
				if(verifClique(&graph,maxCliques[j],posSommetOrdreDegenerescence,posSommetOrdreDegenerescence[i],z))
				{
					aAjouter = false;
					break;
				}
				else
				{
					//RIEN
				}
			}
			if(aAjouter)
			{
				listeCliquesEnum.push_back(maxCliques[i]);
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
	vector<int>* voisinsDeSommetEtude = graph->GetVoisins(sommetEtude);
	vector<int>* voisinsDeVoisins;
	vector<int> intersection;

	for (int i = 0; i < voisinsDeSommetEtude->size(); i++)
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



