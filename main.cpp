#include "enumerationCliquesMaximales.cpp"
int main(){

	int nbCliquesMax, sizeClique;
	vector<vector<int>> res;

	Graph* g = new Graph(6);
	g->AjouterArete(0,1);
	g->AjouterArete(0,4);
	g->AjouterArete(1,2);
	g->AjouterArete(4,3);
	g->AjouterArete(1,4);
	g->AjouterArete(2,3);
	g->AjouterArete(3,5);
	Graph gPtr = *g;

	res = listeCliquesEnumAlgo2(gPtr);

	nbCliquesMax = res.size();
	for (int i = 0; i < nbCliquesMax; i++)
	{
		sizeClique = res[i].size();
		for (int j = 0; j < sizeClique; j++)
		{
			cout << res[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}
