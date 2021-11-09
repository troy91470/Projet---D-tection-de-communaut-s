#include "BronKerbosch.cpp"
#include "TableauSuffixes.h"


vector<vector<int>> listeCliquesEnumAlgo1(Graph graph)
{
	int i;
	int posSommetOrdreDegenerescence[graph->GetNbSommets()];
	vector<vector<int>> listeCliquesEnum, maxClique;
	vector<int> vectOrdreDegenerescence;

	ordreDegenerescence(graph, vectOrdreDegenerescence, posSommetOrdreDegenerescence)
	sortDegenerativeList(posSommetOrdreDegenerescence);
	TableauSuffix T = TableauSuffix();

	while(graph->GetNbSommets() > 0)
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
	int i, j;
	vector<vector<int>> listeCliquesEnum, maxClique;

	while(graph->GetNbSommets() > 0)
	{
		maxClique = BronKerboschDegeneracy(graph);
		for(i=0;i<maxClique.size();i++)
		{
			for(j=0;j<maxClique[i].size();j++)
			{
				if
					//Reject K
				else
					listeCliquesEnum.push_back(maxClique[i]);
			}
		}
	}

	return listeCliquesEnum;
}


int main(){
	

	return 0;
}




