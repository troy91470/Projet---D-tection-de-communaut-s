#include "BronKerbosch.h"

using namespace std;

/*
Fonction qui effectue l'intersection entre deux  ensembles (2 vecteurs) en remplissant un troisième vecteur 
Prend en entrée les deux vecteurs pour lesquels on veut réaliser une intersection ainsi qu'un troisième dans lequel se trouveront les sommets résultant de l'intersection
La fonction parcourt le premier ensemble en ajoutant dans un dictionnaire le numéro du sommet en clé et son nombre d'occurrence en valeur.
Elle parcourt ensuite le second ensemble et vérifie si le sommet existe dans le dictionnaire, si c'est le cas on incrémente sa valeur (nombre d'occurrence trouvées au total).
Pour terminer, on rempli le vecteur résultat avec les sommets du dictionnaire qui ont été rencontrés deux fois nous donnant ainsi l'intersection des deux ensembles.
*/
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
	}

	for(auto item : mapInter){
		if(item.second == 2){
			vectorIntersection.push_back(item.first);
		}

	}

}


/*
Fonction permettant d'obtenir un vecteur résultant d'un ensemble de sommets privé d'un autre.
Prend en entrée deux vecteurs, le premier v1 auquel on souhaite retiré les sommets présents dans v2. 
On rempli le troisième vecteur contenant les sommets se trouvant uniquement dans v1.
La fonction parcourt le premier ensemble en remplissant un dictionnaire par des clés représentant les sommets et les valeurs représentant le nombre d'occurrences trouvées dans cet ensemble.
Elle parcourt le second ensemble en regardant si le sommet existe déjà dans le dictionnaire et le cas échéant incrémente le nombre d'occurrence lui correspondant.
On finit par remplir le vecteur résultant par les sommets de v1 n'ayant été rencontré qu'une seule fois durant le parcours.
*/
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

/*
Algorithme de Bron-Kerbosch basique
Prend en entrée P ensemble des sommets qui vont être ajoutés à la clique, R l'ensemble des sommets formant une clique, et X l'ensemble des sommets exclus de la clique.
On fournit également en paramètres la structure qui va comporter l'ensemble des cliques maximales trouvées (vecteur de vecteur) ainsi que le graphe dans lequel on cherche ces cliques.
On parcourt l'ensemble des sommets de P puis appelons récursivement cette fonction afin de trouver les cliques maximales à partir des sommets parcourus
La fonction remplie la structure de résultat "cliques" pour chaque clique maximale trouvée (lorsque P et X sont vides on ne peut plus rien faire).
*/
void BronKerbosch(vector<int> &P, vector<int> &R, vector<int> &X, vector<vector<int>> &cliques, Graph &G){

	int sizeP = P.size();

	if(P.size() + X.size() == 0){
		cliques.push_back(R);
		return;
	}

	for(int i = 0; i < sizeP; i++){
		
		vector<int> interPVoisinsV;
		vector<int> unionRetV;
		vector<int> interXVoisinsV;
		vector<int> ensembleV = {P[i]};
		vector<int> &voisinsV = *G.GetVoisins(P[i]);


		intersection(P,voisinsV,interPVoisinsV);

		std::set_union(R.begin(), R.end(),
                          ensembleV.begin(), ensembleV.end(),
                          std::back_inserter(unionRetV));

		intersection(X,voisinsV,interXVoisinsV);

		BronKerbosch(interPVoisinsV, unionRetV, interXVoisinsV,cliques,G);
		X.push_back(P[i]);
		P.erase(P.begin());

	}
	
}

/*
Fonction permettant d'obtenir l'ordre de dégénérescence d'un graphe.
Prend en entrée le graphe ainsi que les deux structure dans lesquelles nous allons construire l'ordre de dégénérescence.
On cherche d'abord le degré maximum du graphe. Grace à cela, on construit un tableau de vecteur qui comporte tous les degrés entre 0 et le degré maximum trouvé précedemment.
dans chaque case du tableau (degrés) on a un vecteur qui comporte les sommets qui ont ce degré.
Puis, tant que le graphe possède encore un sommet on boucle:
On parcourt le tableau des degrés et dès que l'on rencontre dans une case un vecteur non vide alors on supprime le premier sommet du vecteur, on actualise les sommets voisins dans le tableau des degrés.
On ajoute le sommet supprimé au vecteur qui aura les sommets dans l'ordre de dégénérescence (tabOrdreDege) et remplissons la place du sommet supprimé dans le tableau posSommetOrdreDege (dont l'indice représente le numéro du sommet).
On supprime également le sommet dans le graphe.
*/
void ordreDegenerescence(Graph *graphe, vector<int> &tabOrdreDege, int posSommetOrdreDege[]){

	int maxDeg = 0;
	int degSommet;
	vector<int8_t> &sommetsGraphe = *graphe->GetListeSommets();
	int tailleGraphe = sommetsGraphe.size();

	for(int i=0; i < tailleGraphe; i++){
		if((int)sommetsGraphe[i] == 1){
			degSommet = graphe->GetDegres(i);
			if(degSommet > maxDeg){
				maxDeg = degSommet;
			}
		}
	}

	vector<int> tabDegres[maxDeg+1];
	for(int i=0; i < tailleGraphe; i++){
		if((int)sommetsGraphe[i] == 1){
			degSommet = graphe->GetDegres(i);
			tabDegres[degSommet].push_back(i);
		}
	}


	int k = 0;
	int l;

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


/*
Cette Fonction reprend le principe de l'algorithme de Bron-Kerbosch basique avec les mêmes entrées et le même objectif.
Cependant les ensembles analysés par l'algorithme seront différents.
Tout d'abord on cherche un sommet pivot dans P union X afin de maximiser l'intersection entre P et les voisins du supposé pivot 
(pour chaque sommet on retient la taille de l'intersection la plus haute ainsi que le sommet avec laquelle ont l'a atteint..
Puis on parcours l'ensembleP privé des voisins du pivot au lieu de simplement parcourir P.
Les appels récursifs se font ensuite de la même façon avec les mêmes calculs d'ensembles à fournir pour les récursion suivantes.
*/
void BronKerboschPivot(vector<int> &P, vector<int> &R, vector<int> &X,vector<vector<int>> &cliques, Graph &G){
    	
	int sizeIntersectionVoisins;

	if(P.size() + X.size() == 0){
		cliques.push_back(R);
		return;
	}

	//Choisir Pivot afin de maximiser P inter voisins u dans P U X
	vector<int> unionPetX;
	std::set_union(P.begin(), P.end(),
                          X.begin(), X.end(),
                          std::back_inserter(unionPetX));

	vector<int> interPVoisinsU;
	int maxPinterVoisinsU = 0;
	int pivot = unionPetX[0];
	
	for(int u : unionPetX){

		
		vector<int> &voisinsU = *G.GetVoisins(u);

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

		intersection(P,voisinsV,interPVoisinsV);

		std::set_union(R.begin(), R.end(),
                          ensembleV.begin(), ensembleV.end(),
                          std::back_inserter(unionRetV));

		intersection(X,voisinsV,interXVoisinsV);


		BronKerboschPivot(interPVoisinsV, unionRetV, interXVoisinsV,cliques,G);
		
		X.push_back(v);
		P.erase(std::remove(P.begin(), P.end(), v), P.end());
		
		
	}
	
}
/*
Cette fonction représente le 3ème algorithme de Bron-Kerbosch.
Elle appelle le tout premier appel à la récursion de l'algorithme avec pivot afin de mettre en jeu l'ordre de dégénérescnec.
Elle appelle donc la fonction ordreDegenerescence afin de recuperer l'ordre de dégénérescence des sommets sous forme de tableau (accès direct à la position d'un sommet dans l'ordre)
et le vecteur (sommets dans l'ordre de degenerescence). 
On parcours ensuite les sommets dans l'ordre de dégénérescence.
Cependant les calculs des ensembles faits pour appeler la récursion changent:
P devient l'intersection des voisins du sommet parcouru et des sommets qui viennent après dans l'ordre de dégénérescence et X l'intersection des voisins du sommet avec les sommets venant avant dans l'ordre de dégénérescence.
*/
void BronKerboschDegeneracy(vector<vector<int>> &cliques,Graph &G){
    
	int positionSommetOrdreDege[G.GetNbSommets()];
	vector<int> vectOrdreDegenerescence;
	Graph* copieGraphe = G.CreerCopie();
	ordreDegenerescence(copieGraphe,vectOrdreDegenerescence,positionSommetOrdreDege);
	vector<int> P;
	vector<int> R;
	vector<int> X;

	for(int v : vectOrdreDegenerescence){
	
		int posVDansOrdre = positionSommetOrdreDege[v];

		vector<int> &voisinsV = *G.GetVoisins(v);

		int nbVoisinsV = voisinsV.size();
		vector<int> ensembleV = {v};
		if(voisinsV.empty() == true){
			for(int i = 0; i < nbVoisinsV; i++){
				if(positionSommetOrdreDege[voisinsV[i]] > posVDansOrdre){
	    				P.push_back(voisinsV[i]);
	  			}
				else{
	    				X.push_back(voisinsV[i]);
				}
			} 
		}
		
		BronKerboschPivot(P,ensembleV,X,cliques,G);
		P.clear();
		X.clear();
		ensembleV.clear();
	
	}
	
	
}
