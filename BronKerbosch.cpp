#include "BronKerbosch.h"

using namespace std;

//template<typename Map>
void intersection(vector<int> &v1, vector<int> &v2, vector<int> &vectorIntersection){

	vectorIntersection.clear();
	map<int,int> mapInter;

	for(int v: v1){
		mapInter[v] = 1;
	}

	for(int v: v2){
		if(mapInter[v]){
			mapInter[v] += 1;
		}
		else{
			mapInter[v] = 1;
		}
	}

	for(auto item : mapInter){
		if(item.second == 2){
			vectorIntersection.push_back(item.first);
		}

	}

}

void v1PriveDeV2(vector<int> &v1, vector<int> &v2, vector<int> &vectorV1PriveDeV2){

	vectorV1PriveDeV2.clear();
	map<int, int> mapInter;

	for(int v: v1){
		mapInter[v] = 1;
	}

	for(int v: v2){
		if(mapInter[v]){
			mapInter[v] += 1;
		}
	}

	for(auto item : mapInter){
		if(item.second == 1){
			vectorV1PriveDeV2.push_back(item.first);
		}

	}

}


void BronKerbosch(vector<int> &P, vector<int> &R, vector<int> &X, vector<vector<int>> &cliques, Graph &G){

	int sizeP = P.size();

	if(P.size() + X.size() == 0){
		cliques.push_back(R);
	}

	for(int i = 0; i < sizeP; i++){
		
		vector<int> interPVoisinsV;
		vector<int> unionRetV;
		vector<int> interXVoisinsV;
		vector<int> ensembleV = {P[i]};
		vector<int> &voisinsV = *G.GetVoisins(P[i]);


		/*std::set_intersection(P.begin(), P.end(),
                          voisinsV.begin(), voisinsV.end(),
                          std::back_inserter(interPVoisinsV));*/
		intersection(P,voisinsV,interPVoisinsV);

		std::set_union(R.begin(), R.end(),
                          ensembleV.begin(), ensembleV.end(),
                          std::back_inserter(unionRetV));

		/*std::set_intersection(X.begin(), X.end(),
                          voisinsV.begin(), voisinsV.end(),
                          std::back_inserter(interXVoisinsV));*/
		intersection(X,voisinsV,interXVoisinsV);

		BronKerbosch(interPVoisinsV, unionRetV, interXVoisinsV,cliques,G);
		X.push_back(P[i]);
		P.erase(P.begin());

	}
	
}


void ordreDegenerescence(Graph *graphe, vector<int> &tabOrdreDege, int posSommetOrdreDege[]){
	//get max degre graphe
	int maxDeg = 0;
	int degSommet;
	vector<int8_t> &sommetsGraphe = *graphe->GetListeSommets();
	int tailleGraphe = sommetsGraphe.size();
	//int v : graphe.GetListeSommets()
	for(int i=0; i < tailleGraphe; i++){
		if((int)sommetsGraphe[i] == 1){
			degSommet = graphe->GetDegres(i);
			if(degSommet > maxDeg){
				maxDeg = degSommet;
			}
		}
	}

	//bin sort
	//bin sort
    vector<int> tabDegres[maxDeg+1];
    for(int i=0; i < tailleGraphe; i++){
        if((int)sommetsGraphe[i] == 1){
            degSommet = graphe->GetDegres(i);
            tabDegres[degSommet].push_back(i);
        }
    }


	int k = 0;
	int l;
	//int ordreDegenerescence[graphe.GetNbSommets()];
	while(tailleGraphe > 0){

		for(l=0; l < maxDeg+1; l++ ){
			if(tabDegres[l].size() != 0){
				break;
			}
		}

		posSommetOrdreDege[tabDegres[l][0]] = k;
		tabOrdreDege.push_back(tabDegres[l][0]);
		vector<int> &voisinsSommetASup = *graphe->GetVoisins(tabDegres[l][0]);
		int nbSommetsASup = voisinsSommetASup.size();
		int degreVoisin;
		//int v : voisinsSommetASup
		for(int i=0; i < nbSommetsASup; i++){
			degreVoisin = graphe->GetDegres(voisinsSommetASup[i]);		
			tabDegres[degreVoisin].erase(std::remove(tabDegres[degreVoisin].begin(), tabDegres[degreVoisin].end(), voisinsSommetASup[i]), tabDegres[degreVoisin].end());
			tabDegres[degreVoisin-1].push_back(voisinsSommetASup[i]);
		}
		graphe->SupprimerSommet(tabDegres[l][0]);
		graphe->RafraichirAretes();
		tabDegres[l].erase(tabDegres[l].begin());

		k = k + 1;
		tailleGraphe = graphe->GetNbSommets();

	}
}


void BronKerboschPivot(vector<int> &P, vector<int> &R, vector<int> &X,vector<vector<int>> &cliques, Graph &G){
    	
	int sizeIntersectionVoisins;

	if(P.size() + X.size() == 0){
		cliques.push_back(R);
		return;
	}

	//Choose Pivot maximise P inter voisins u dans P U X

	vector<int> unionPetX;
	std::set_union(P.begin(), P.end(),
                          X.begin(), X.end(),
                          std::back_inserter(unionPetX));

	vector<int> interPVoisinsU;
	int maxPinterVoisinsU = 0;
	int pivot = unionPetX[0];
	
	for(int u : unionPetX){

		
		vector<int> &voisinsU = *G.GetVoisins(u);

		//std::set_intersection(P.begin(), P.end(),
                  //        voisinsU.begin(), voisinsU.end(),
                    //      std::back_inserter(interPVoisinsU));
		intersection(P,voisinsU,interPVoisinsU);

		sizeIntersectionVoisins = interPVoisinsU.size();

		if(sizeIntersectionVoisins > maxPinterVoisinsU){
			maxPinterVoisinsU = interPVoisinsU.size();
			pivot = u;
		}
	}
	
	vector<int> &voisinsPivot = *G.GetVoisins(pivot);
	vector<int> PPriveVoisinsPivot;
	
	v1PriveDeV2(P,voisinsPivot,PPriveVoisinsPivot);


	
	for(int v : PPriveVoisinsPivot){
		vector<int> interPVoisinsV;
		vector<int> unionRetV;
		vector<int> interXVoisinsV;
		vector<int> ensembleV = {v};
		vector<int> &voisinsV = *G.GetVoisins(v);

		
		//std::set_intersection(P.begin(), P.end(),
                  //        voisinsV.begin(), voisinsV.end(),
                    //      std::back_inserter(interPVoisinsV));
		intersection(P,voisinsV,interPVoisinsV);

		std::set_union(R.begin(), R.end(),
                          ensembleV.begin(), ensembleV.end(),
                          std::back_inserter(unionRetV));


		//std::set_intersection(X.begin(), X.end(),
                  //        voisinsV.begin(), voisinsV.end(),
                    //      std::back_inserter(interXVoisinsV));
		intersection(X,voisinsV,interXVoisinsV);


		BronKerboschPivot(interPVoisinsV, unionRetV, interXVoisinsV,cliques,G);
		
		X.push_back(v);
		P.erase(std::remove(P.begin(), P.end(), v), P.end());
		
		
	}
	
}


void BronKerboschDegeneracy(vector<vector<int>> &cliques,Graph &G){
    
	int positionSommetOrdreDege[G.GetNbSommets()];
	vector<int> vectOrdreDegenerescence;
	Graph* copieGraphe = G.CreerCopie();
	ordreDegenerescence(copieGraphe,vectOrdreDegenerescence,positionSommetOrdreDege);
	vector<int> P;
	vector<int> R;
	vector<int> X;

	//int i = 0; i < G.GetNbSommets(); i++
	for(int v : vectOrdreDegenerescence){
	
		int posVDansOrdre = positionSommetOrdreDege[v];

		vector<int> &voisinsV = *G.GetVoisins(v);

		int nbVoisinsV = voisinsV.size();
		vector<int> ensembleV = {v};
		
		for(int i = 0; i < nbVoisinsV; i++){
			if(positionSommetOrdreDege[voisinsV[i]] > posVDansOrdre){
    				P.push_back(voisinsV[i]);
  			}
			else{
    				X.push_back(voisinsV[i]);
			}
		} 
		BronKerboschPivot(P,ensembleV,X,cliques,G);
		P.clear();
		X.clear();
		ensembleV.clear();
	
	}
	
	
}


/*int main(){


	Graph* g = new Graph(6);

	


	g->AjouterArete(0,1);
	g->AjouterArete(0,4);
	g->AjouterArete(1,2);
	g->AjouterArete(4,3);
	g->AjouterArete(1,4);
	g->AjouterArete(2,3);
	g->AjouterArete(3,5);

	//g->PrintDab();
	//cout<<"\n";
	


	vector<int> P = {0,1,2,3,4,5};
	vector<int> R;
	vector<int> X;

	//vector<vector<int>> res = ;
	vector<vector<int>> res; 
	BronKerbosch(P,R,X,res,*g);
	cout << "BronKerbosch: ";
	for(vector<int> v : res){
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << ' ';
		}
		cout << "\n";
	}
	//g->PrintDab();
	cout<<"\n";

	vector<vector<int>> res1; 
	BronKerboschPivot(P,R,X,res1,*g);
	cout << "BronKerboschPivot: ";
	for(vector<int> v : res){
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << ' ';
		}
		cout << "\n";
	}
	//g->PrintDab();
	cout<<"\n";



	vector<vector<int>> res2; 
	BronKerboschDegeneracy(res2,*g);
	cout << "BronKerboschDege: ";
	for(vector<int> v : res2){
		for (int i = 0; i < v.size(); i++) {
			cout << v[i] << " ";
		}
		cout << "\n";
		
	}






	vector<int> nums;
	nums.push_back(1);
	nums.push_back(3);	
	nums.push_back(4);
	nums.push_back(5);
	nums.push_back(9);

	//std::sort(nums.begin(), nums.end());	

	vector<int> num1;
	
	num1.push_back(2);
	num1.push_back(7);
	num1.push_back(8);
	num1.push_back(10);

	
	vector<int> vectorRes;
	//intersection(nums, num1, vectorRes);
	v1PriveDeV2(nums,num1,vectorRes);

	for(int i = 0; i < nums.size(); i){
		cout << nums[i];
		num1.push_back(nums[i]);
		cout << nums[i] << "\n";
		nums.erase(nums.begin());
		
		

	}

	//std::sort(num1.begin(), num1.end());
	cout << "ens1: ";
	for (int i = 0; i < nums.size(); i++) {
		cout << nums[i] << ' ';
	}

	cout << "\n";
	cout << "ens2: ";
	for (int i = 0; i < num1.size(); i++) {
		cout << num1[i] << ' ';
	}

	//BronKerbosch(num1,num1,nums);

	cout << "\n";
	cout << "prive: ";
	for (int i = 0; i < vectorRes.size(); i++) {
		cout << vectorRes[i] << " ";
	}


	
	
	

	return 0;
}*/
