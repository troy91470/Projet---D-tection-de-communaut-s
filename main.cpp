#include <chrono>
#include "enumerationCliquesMaximales.cpp"

int main(){

    	using std::chrono::high_resolution_clock;
    	high_resolution_clock::time_point t1;
        high_resolution_clock::time_point t2;
    	std::chrono::duration<double> temps;

	int nbCliquesMax, sizeClique, vSize;
	vector<vector<int>> res;
    	vector<int> P = {0,1,2,3,4,5};
	vector<int> R;
	vector<int> X;

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

    Graph* listeGraphes[5];
    listeGraphe[0] = g;
    listeGraphe[1] = GenererGraphRandom(10,75);
    listeGraphe[2] = GenererGraphBarabasiAlbert(10,3);
    listeGraphe[3] = GenererGraphRandom(69,25);
    listeGraphe[4] = GenererGraphBarabasiAlbert(69,5);

    for (int i=0;i<5;i++) {
        Graph gPtr = *listeGraphe[i];
        
            t1 = high_resolution_clock::now();
        BronKerbosch(P,R,X,res,*listeGraphe[i]);
            t2 = high_resolution_clock::now();
            temps = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        cout << "BronKerbosch: "<< temps.count();

        for(vector<int> v : res)
        {
            vSize = v.size();
            for (int i = 0; i < vSize; i++) {
                cout << v[i] << ' ';
            }
            cout << "\n";
        }
        //g->PrintDab();
        cout<<"\n";
        vector<vector<int>> res1; 
            t1 = high_resolution_clock::now();
        BronKerboschPivot(P,R,X,res1,*listeGraphe[i]);
            t2 = high_resolution_clock::now();
            temps = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        cout << "BronKerboschPivot: "<< temps.count();

        for(vector<int> v : res)
        {
            vSize = v.size();
            for (int i = 0; i < vSize; i++) {
                cout << v[i] << ' ';
            }
            cout << "\n";
        }
        //g->PrintDab();
        cout<<"\n";
        vector<vector<int>> res2; 
            t1 = high_resolution_clock::now();
        BronKerboschDegeneracy(res2,*listeGraphe[i]);
            t2 = high_resolution_clock::now();
            temps = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
        cout << "BronKerboschDege: "<< temps.count();

        for(vector<int> v : res2)
        {
            vSize = v.size();
            for (int i = 0; i < vSize; i++) {
                cout << v[i] << " ";
            }
            cout << "\n";
            
        }

        t1 = high_resolution_clock::now();
            res = listeCliquesEnumAlgo1(gPtr);
            t2 = high_resolution_clock::now();
            temps = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
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
            temps = std::chrono::duration_cast<std::chrono::duration<double>>(t2 - t1);
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
        cout << "\n\n";
    }

	return 0;
}