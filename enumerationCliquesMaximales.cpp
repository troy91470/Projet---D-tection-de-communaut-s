#include "enumerationCliquesMaximales.h"


vector<vector<int>> listeCliquesEnumAlgo1(Graph &graph)
{
	int i,j,nbClique;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum,maxClique;
	vector<vector<int>> &maxCliqueRef=maxClique;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(graph.CreerCopie(), vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	graph.triVecteurSelonOrdreDege(posSommetOrdreDegenerescence);
	TableauSuffix T = TableauSuffix();

	for(i=0;i<graph.GetNbSommets();i++) //on parcourt les sommets du graphe
	{
		//on initialise les cliques max pour le sommet
		maxClique = {};

		//on trouve le sous-graphe du sommet
		Graph* sousgraphe = graph.TrouveSousGraphe(posSommetOrdreDegenerescence,  vectOrdreDegenerescence[i]); 
		Graph &sousGraphePtr = *sousgraphe;

		BronKerboschDegeneracy(maxCliqueRef,sousGraphePtr);

		nbClique= maxClique.size();
		for(j=0;j<nbClique;j++) //on parcourt la liste de cliques
		{
			//si le tableau suffixe connait deja la clique, on n'accepte pas la clique
			if(T.rechercheSuffix(maxClique[j])) 
			{
				//RIEN
			}
			//sinon on accepte la clique, cad qu'on l'ajoute au tableau suffixe et a l'enumeration de cliques
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
	Graph* copiegraph = graph.CreerCopie();
	int i, j, z, nbMaxCliques, sizeClique;
	bool aAjouter = true;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum,maxCliques;
	vector<vector<int>> &maxCliquesRef=maxCliques;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(copiegraph->CreerCopie(), vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	copiegraph->triVecteurSelonOrdreDege(posSommetOrdreDegenerescence);

	for(i=0;i<copiegraph->GetNbSommets();i++) //on parcourt les sommets du graphe
	{
		//on initialise les cliques max pour le sommet
		maxCliques={};

		//on trouve le sous-graphe du sommet
		Graph* Gi = copiegraph->TrouveSousGraphe(posSommetOrdreDegenerescence, vectOrdreDegenerescence[i]);
		Graph &GiPtr = *Gi;

		BronKerboschDegeneracy(maxCliquesRef,GiPtr);

		nbMaxCliques = maxCliques.size();
		for(j=0;j<nbMaxCliques;j++) //on parcourt la liste de cliques
		{
			sizeClique = maxCliques[j].size();
			if(sizeClique > 1) //si la clique a plus d'un element
			{
				for(z=0;z<sizeClique;z++) //on parcourt la clique
				{
					//si la clique est acceptable on ne change pas le flag aAjouter
					if(verifClique(copiegraph,maxCliques[j],posSommetOrdreDegenerescence,posSommetOrdreDegenerescence[i],z))
					{
						//RIEN
					}
					//sinon met le flag aAjouter a false et on quitte la boucle
					else
					{
						aAjouter = false;
						break;
					}
				}
 				//pour ajouter la clique max
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
			voisinsDeVoisins = graph->GetVoisins(i);
			int length = voisinsDeVoisins->size();
			vector<int> copieVoisins = {};

			for (int l = 0; l < length; l++)
			{
				int x = voisinsDeVoisins->operator[](i); //version non-deferencee de voisinsDeVoisins[i]
				copieVoisins.push_back(x);
			}

			copieVoisins = trierVecteurSelonOrdre(copieVoisins,ordreDegenerescence,graph->GetNbSommets());
			set_intersection(copieVoisins.begin(),copieVoisins.end(),K.begin(),K.end(),back_inserter(intersection));

			if (intersection.size() == K.size()) //si l'intersection est K
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

        vector<int> gauche(v.begin(),v.begin()+mid); //on divise le vecteur pour prendre sa partie gauche
        vector<int> droite(v.begin()+mid,v.begin()+v.size()); //on divise le vecteur pour prendre sa partie droite

        gauche = trierVecteurSelonOrdre(gauche,ordre,taille); //on appelle la fonction sur la partie gauche du vecteur
        droite = trierVecteurSelonOrdre(droite,ordre,taille); //on appelle la fonction sur la partie droite du vecteur

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



