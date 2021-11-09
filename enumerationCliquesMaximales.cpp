#include "BronKerbosch.cpp"
#include "TableauSuffixes.h"

bool verifClique(Graph graph,vector<int> K,int ordreDegenerescence[],int sommetSousGraphe,int sommetEtude);

vector<vector<int>> listeCliquesEnumAlgo1(Graph graph)
{
	int i;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum, maxClique;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(graph, vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	sortDegenerativeList(posSommetOrdreDegenerescence);
	TableauSuffix T = TableauSuffix();

	while(graph.GetNbSommets() > 0)
	{
		maxClique = BronKerboschDegeneracy(graph);
		for(i=0;i<maxClique.size();i++)
		{
			if(T.rechercheSuffix(maxClique[i]))
				//Reject K
			else
			{
				T.ajoutVecteur(maxClique[i]);
				T.creerTableau();
				listeCliquesEnum.push_back(maxClique[i]);
			}
		}
		graph = trouveSousGraph(graph);
	}
	return listeCliquesEnum;
}


vector<vector<int>> listeCliquesEnumAlgo2(Graph graph)
{
	int i, j, z;
	bool aAjouter = true;
	int posSommetOrdreDegenerescence[graph.GetNbSommets()];
	vector<vector<int>> listeCliquesEnum, maxCliques;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(graph, vectOrdreDegenerescence, posSommetOrdreDegenerescence);
	sortDegenerativeList(posSommetOrdreDegenerescence);

	for(i=0;i<graph.GetNbSommets();i++)
	{
		Graph Gi = sousgraphe(posSommetOrdreDegenerescence[i]);
		maxCliques = BronKerboschDegeneracy(Gi);
		for(j=0;j<maxCliques.size();j++)
		{
			//TODO TRIER MAXCLIQUE[J]
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
				listeCliquesEnum.push_back(maxClique[i]);
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
			voisinsDeVoisins = graph->GetVoisins(i);// IF neighbors of X adjacent to all vertex of K
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


int main(){

	return 0;
}




