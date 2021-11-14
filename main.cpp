#include <chrono>
include "enumerationCliquesMaximales.cpp"
int main(){

    using std::chrono::high_resolution_clock;
    high_resolution_clock::time_point t1;
    high_resolution_clock::time_point t2;
    duration<double> temps;

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

    g->PrintDab();
	cout<<"\n";

    vector<int> P = {0,1,2,3,4,5};
	vector<int> R;
	vector<int> X;
	//vector<vector<int>> res = ;
	vector<vector<int>> res; 
    t1 = high_resolution_clock::now();
	BronKerbosch(P,R,X,res,*g);
    t2 = high_resolution_clock::now();
    temps = duration_cast<duration<double>>(t2 - t1);
	cout << "BronKerbosch: "<< temps.count();
	for(vector<int> v : res){
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << ' ';
		}
		cout << "\n";
	}
	//g->PrintDab();
	cout<<"\n";
	vector<vector<int>> res1; 
    t1 = high_resolution_clock::now();
	BronKerboschPivot(P,R,X,res1,*g);
    t2 = high_resolution_clock::now();
    temps = duration_cast<duration<double>>(t2 - t1);
	cout << "BronKerboschPivot: "<< temps.count();
	for(vector<int> v : res){
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << ' ';
		}
		cout << "\n";
	}
	//g->PrintDab();
	cout<<"\n";
	vector<vector<int>> res2; 
    t1 = high_resolution_clock::now();
	BronKerboschDegeneracy(res2,*g);
    t2 = high_resolution_clock::now();
    temps = duration_cast<duration<double>>(t2 - t1);
	cout << "BronKerboschDege: "<< temps.count();
	for(vector<int> v : res2){
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << "\n";
		
	}

    t1 = high_resolution_clock::now();
    res = listeCliquesEnumAlgo1(gPtr);
    t2 = high_resolution_clock::now();
    temps = duration_cast<duration<double>>(t2 - t1);
    cout << "Algo 1: " << temps.count();

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

    t1 = high_resolution_clock::now();
	res = listeCliquesEnumAlgo2(gPtr);
    t2 = high_resolution_clock::now();
    temps = duration_cast<duration<double>>(t2 - t1);
    cout << "Algo 2: " << temps.count();

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

