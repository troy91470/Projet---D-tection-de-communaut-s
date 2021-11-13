#include "Graph.h"

/**
Initialise tous les elements du graphe et ajoute nbS sommets au Graph.
*/
Graph::Graph(int nbS=0)
{
    nbSommets=0;
    indexSommetMax=-1;
    listeSommets={};
    listeAdjacence={};
    AjouterSommets(nbS);
    //ctor
}

Graph::~Graph()
{
    //dtor
}

/**
Ecrit dans la console la liste d'adjacence en explorant chaque element.
Utilisee pour Debug et nom a revoir.
*/
void Graph::PrintDab() {
    for (int i=0;i<indexSommetMax+1;i++) {
        if (listeSommets[i]==1) {
            cout << i << ": ";
            int siz = listeAdjacence[i].size();
            for (int j=0;j<siz;j++) {
                cout << listeAdjacence[i][j] << " ";
            }
            cout << "\n";
        }
    }
    cout << "\n";
}

/**
Renvoie le nombre de voisins d'un sommet.
*/
int Graph::GetDegres(int index) {
    return listeAdjacence[index].size();
}

/**
Explicite.
*/
int Graph::GetNbSommets() {
    return nbSommets;
}

/**
Renvoie un pointeur vers listeSommets.
*/
vector<int8_t>* Graph::GetListeSommets() {
    return &listeSommets;
}

/**
Renvoie un pointeur vers la liste des voisins du sommet indexSommet.
*/
vector<int>* Graph::GetVoisins(int indexSommet) {
    return &listeAdjacence[indexSommet];
}

/**
Deep copy d'un Graph. Ne passe pas par des fonctions de Graph.
Utilisee exclusivement pour la creation de copie d'un Graph.
*/
void Graph::SetGraph(int indexMax,int nbS, vector<int8_t>* listeS,vector<vector<int>>* listeA) {
    indexSommetMax=indexMax;
    nbSommets=nbS;
    listeSommets.resize(indexMax+1);
    listeAdjacence.resize(indexMax+1);
    for (int i=0;i<indexSommetMax+1;i++) {
        listeSommets[i]=listeS->operator[](i);
        int taille=listeA->operator[](i).size();
        for (int j=0;j<taille;j++) {
            listeAdjacence[i].push_back(listeA->operator[](i)[j]);
        }
    }
}

/**
Ajoute un sommet dans la liste d'adjacence.
2 cas:
Si aucun sommet n'a ete supprime auparavant, il faut push_back.
Sinon, nous remplacons un sommet "vide" par un sommet.
*/
void Graph::AjouterSommets(int nb) {
    for (int i=0;i<nb;i++) {
        //ajout a la fin de la liste
        if (indexSommetMax == nbSommets-1) {
            indexSommetMax++;
            nbSommets++;
            listeSommets.push_back(1);
            vector<int> newL;
            listeAdjacence.push_back(newL);
        }
        else {
            //ajout au milieu de la liste sans rien deplacer
            int out=0;
            for (int j=0;j<indexSommetMax && out==0;j++) {
                if (listeSommets[j]==0) {
                    nbSommets++;
                    listeSommets[j]=1;
                    out=1;
                }
            }
        }
    }
}

/**
Supprime un sommet.
Gere l'impossibilite de supprimer.
Supprime d'abord les aretes liees a ce sommet.
2 cas:
Si c'est le dernier sommet de la liste, on reduit la liste: on reduit jusqu'a trouver un sommet non vide. Optimisation possible: calculer le nombre d'element a supprimer et utiliser resize au lieu de pop_back.
Sinon, on remplace le sommet par un sommet "vide".

*/
void Graph::SupprimerSommet(int index) {
    //gestion des erreurs d'entrees
    if (index > indexSommetMax || listeSommets[index]==0) {
        cout << "Le sommet n'existe pas\n";
        return;
    }
    //Suppression des aretes
    int taille=GetDegres(index);
    for (int i=0;i<taille;i++) {
        if (listeAdjacence[index][i]!=-1) {
            SupprimerArete(index,listeAdjacence[index][i]);
        }
    }
    //suppression des derniers de la liste
    if (index == indexSommetMax) {
        listeSommets[index]=0;
        for (int i=index;i>-1 && listeSommets[i]==0;i--) {
            if (i==index) {
                nbSommets--;
            }
            indexSommetMax--;
            listeSommets.pop_back();
            listeAdjacence.pop_back();
        }
    }
    else {
        //suppression au milieu de la liste
        nbSommets--;
        listeSommets[index]=0;
        listeAdjacence[index].resize(1);
        listeAdjacence[index][0]=-1;
    }
    //cout << "Sommet supprim�\n";
}

/**
Ajoute une arete aux deux endroits concernes de la liste d'adjacence.
Gere si l'arete existe deja.
*/
void Graph::AjouterArete(int v1, int v2) {
    if (v1>indexSommetMax || v2>indexSommetMax || v1==v2) {
        cout << "L'arete ne peut pas etre ajoutee\n";
        return;
    }
    int taille=listeAdjacence[v1].size();
    for (int i=0;i<taille;i++) {
        if (listeAdjacence[v1][i]==v2) {
            cout << "L'arete existe deja\n";
            return;
        }
    }
    listeAdjacence[v1].push_back(v2);
    listeAdjacence[v2].push_back(v1);
}

/**
Marque l'arete v1,v2 a la suppression.
Gere les erreurs d'entrees.
Dans la liste d'adjacence, les index concernes sont remplaces par -1.
0: 1 2
1: 0 2
2: 0 1

deviens, apres SupprimerArete(1,2):
0: 1 2
1: 0 -1
2: 0 -1
*/
void Graph::SupprimerArete(int v1, int v2) {
    //gestion erreurs d'entrees
    if (v1>indexSommetMax || v2>indexSommetMax || v1<0 || v2<0) {
        cout << "L'arete "<< v1 << " " << v2 <<" ne peut pas etre supprimee\n";
        return;
    }
    int out=0;
    int taille=listeAdjacence[v1].size();
    for (int i=0;i<taille && out==0;i++) {
        if (listeAdjacence[v1][i]==v2) {
            listeAdjacence[v1][i]=-1;
            //cout << "Arete supprimee d'un cote\n";
            out=1;
        }
    }
    out=0;
    taille=listeAdjacence[v2].size();
    for (int i=0;i<taille && out==0;i++) {
        if (listeAdjacence[v2][i]==v1) {
            listeAdjacence[v2][i]=-1;
            //cout << "Arete supprimee de l'autre\n";
            out=1;
        }
    }
    //cout << "Arete supprimee\n";
}

/**
Supprime les aretes marquees.
Parcours toute la liste d'adjacence pour reduire les sous-listes en commencant par la fin pour optimiser les decalages.
Optimisation possible: nous pouvons garder en memoire les sous-listes conernees pour eviter d'explorer toute la liste d'adjacence.
*/
void Graph::RafraichirAretes() {
    int tailleListe=listeAdjacence.size();
    int tailleSousListe;
    for (int j=0;j<tailleListe;j++) {
        tailleSousListe=GetDegres(j);
        for (int i=tailleSousListe-1;i>-1;i--) {
            vector<int>::iterator start=listeAdjacence[j].begin();
            if (listeAdjacence[j][i]==-1) {
                listeAdjacence[j].erase(start+i);
            }
        }
    }
    //cout << "Liste d'adjacence nettoy�e\n";
}

/**
Generation de Graph aleatoire.
Utilise une loi uniforme pour choisir son aleatoire.
*/
Graph* Graph::GenerateRandomGraph(int nbS, int p) {
    Graph* g = new Graph(nbS);
    std::mt19937 mt(time(nullptr));
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    double r;int realr;
    for (int i=0;i<nbS;i++) {
        for (int j=i+1;j<nbS;j++) {
            //permet d'arondir
            r=dist(mt);r=r+0.5-(r<0);
            realr=(int)r;
            if (realr<p) {
                g->AjouterArete(i,j);
            }
        }
    }
    return g;
}

/**
Generation de Graph aleatoire.
Utilise le modele Barabasi-Albert et une loi uniforme pour l'aleatoire.
Gere le cas d'un Graph de taille inferieur a 3 sommets.
*/
Graph* Graph::GenerateBarabasiAlbertGraph(int nbS=3, int m=0) {
    //Graphe plus petit que 3 sommets
    if (nbS<3) {
        Graph* g = new Graph(nbS);
        for (int i=0;i<nbS;i++) {
            for (int j=0;j<nbS;j++) {
                g->AjouterArete(i,j);
            }
        }
        return g;
    }
    else if (nbS<1) {
        return new Graph();
    }
    //initailisation d'un graphe triangle
    int compteurM=0;
    int dMax=6;int d=2;
    Graph* g = new Graph();
    g->AjouterSommets(nbS);
    g->AjouterArete(0,1);
    g->AjouterArete(0,2);
    g->AjouterArete(1,2);
    std::mt19937 mt(time(nullptr));
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    double r;
    //modele barabasi-albert
    for (int i=3;i<nbS;i++) {
        for (int j=0;j<nbS&&compteurM<m;j++) {
            if (j==i) {j++;}
            d=g->GetDegres(j);
            r=dist(mt);
            if (r<(((double)d/(double)dMax)*100)) {
                g->AjouterArete(i,j);
                compteurM++;
                dMax++;
            }
        }
        compteurM=0;
    }
    return g;
}

/**
Renvoie un pointeur d'un nouveau Graph.
Utilise SetGraph qui permet une Deep Copy.
*/
Graph* Graph::CreerCopie() {
    Graph* g = new Graph();
    g->SetGraph(indexSommetMax,nbSommets,&listeSommets,&listeAdjacence);
    return g;
}


void Graph::triVecteurSelonOrdreDege(int* posOrdreDegenerescence){
	int tmp;
	int startIterator;
	int endIterator;

	for(int i=0;i<indexSommetMax+1;i++) //on parcourt la liste des sommets
	{
		int size = listeAdjacence[i].size();
		startIterator = 0;
		endIterator = size-1;

		while(startIterator != endIterator) //on parcourt les voisins du sommet actuel tant que nos 2 iterateurs sont differents
		{
			if(posOrdreDegenerescence[listeAdjacence[i][startIterator]] < posOrdreDegenerescence[i])
			{
				//on change la valeur placee a l'iterateur de debut, avec celle de l'iterateur de fin
				tmp = listeAdjacence[i][endIterator];
				listeAdjacence[i][endIterator] = listeAdjacence[i][startIterator];
				listeAdjacence[i][startIterator] = tmp;
				endIterator--; //on recule l'iterateur de fin
			}
			else
			{
				startIterator++; //sinon on avance l'iterateur de debut
			}
		}


	}
}



vector<int> trierVecteurSelonNum(vector<int> v) //Implementation du tri fusion
{
	if (v.size()>1) 
	{
		int mid = v.size()/2;

		vector<int> gauche(v.begin(),v.begin()+mid); //on divise le vecteur pour prendre sa partie gauche
		vector<int> droite(v.begin()+mid,v.begin()+v.size()); //on divise le vecteur pour prendre sa partie droite

		gauche = trierVecteurSelonNum(gauche); //on appelle la fonction sur la partie gauche du vecteur
		droite = trierVecteurSelonNum(droite); //on appelle la fonction sur la partie droite du vecteur

		unsigned i = 0;
		unsigned j = 0;
		unsigned k = 0;
	
		//tant que i est plus petit que le taille du vecteur gauche et j plus petit que la taille du vecteur droite
		while (i < gauche.size() && j < droite.size()) 
		{
			//si la valeur de gauche en position i est inferieure à celle du vecteur droit en position j, le vecteur final prendra en k la valeur du vecteur droit
		   	if (gauche[i] < droite[j]) 
			{
				v[k]=gauche[i];
		        	i++;
		   	}
			//sinon le vecteur final prendra en position k la valeur du vecteur de droite a la position j
			else 
			{
		        	v[k] = droite[j];
				j++;
		    	}
			k++;
		}
		
		//tant que i est plus petit que le vecteur gauche, on place la valeur du vecteur a la position i dans le vecteur final a la position k
		while (i<gauche.size()) 
		{
			v[k] = gauche[i];
		   	i++;
		    	k++;
		}

		//tant que j est plus petit que le vecteur droite, on place la valeur du vecteur a la position j dans le vecteur final a la position k
		while (j<droite.size()) 
		{
		    	v[k]=droite[j];
			j++;
		    	k++;
        	}

    }
    return v;
}


Graph* Graph::TrouveSousGraphe(int* posOrdreDegenerescence, int numSommet){
	int i;
	int j=0;
	Graph* copieGraphe = CreerCopie();
	int size = copieGraphe->listeAdjacence[numSommet].size();
	vector<int> listeAdjTrieeParNum;

	//on redimensionne le vecteur selon la taille de la liste d'adjacence de numSommet
	listeAdjTrieeParNum.resize(size);

	//on copie la liste d'adjacence de numSommet dans le nouveau vecteur
	copy(copieGraphe->listeAdjacence[numSommet].begin(),copieGraphe->listeAdjacence[numSommet].end(),listeAdjTrieeParNum.begin());

	listeAdjTrieeParNum = trierVecteurSelonNum(listeAdjTrieeParNum);

	for(i=size-1;i>=0;i--) //on parcourt en sens inverse les voisins de numSommet
	{
		//si le voisin de numSommet est degenere avant numSommet, alors on supprime ce voisin
		if(posOrdreDegenerescence[listeAdjacence[numSommet][i]] < posOrdreDegenerescence[numSommet])
			copieGraphe->SupprimerSommet(copieGraphe->listeAdjacence[numSommet][i]);
		else  //sinon on a plus d'operation a faire, donc on quitte la boucle
        	{
            		break;
		}
    	}

	for(i=0;i<indexSommetMax+1;i++) //on parcourt la liste des sommets
	{
		//si le sommet parcouru n'est pas voisin de numSommet et n'est pas numSommet, alors on le supprime
		if(i != listeAdjTrieeParNum[j] && i!=numSommet)
		{
			copieGraphe->SupprimerSommet(i);
		}
		else if(i != numSommet)
		{
			j++;
		}
    	}

	copieGraphe->RafraichirAretes(); //on met a jour les aretes du sous graphe
	return copieGraphe;
}

/*int main() {
    Graph* g = new Graph();

	g->AjouterSommets(6);
	g->AjouterArete(0,1);
	g->AjouterArete(0,2);
	g->AjouterArete(0,3);
	g->AjouterArete(1,4);
	g->AjouterArete(1,5);
	g->AjouterArete(2,5);
	g->AjouterArete(2,4);
	g->AjouterArete(3,4);

	g->PrintDab();

	int tab[6];
	tab[0] = 5;
	tab[1] = 3;
	tab[2] = 2;
	tab[3] = 1;
	tab[4] = 4;
	tab[5] = 0;
	g->sortDegenerativeList(tab);

	g->PrintDab();

	Graph* g2 = g->TrouveSousGraphe(tab,1);
	g2->PrintDab();


    g->AjouterSommets(2);
    g->AjouterSommets();
    g->AjouterSommets(2);
    g->AjouterArete(0,1);
    g->AjouterArete(0,1);
    g->AjouterArete(0,2);
    g->AjouterArete(4,3);
    g->AjouterArete(7,6);
    g->SupprimerArete(0,1);
    g->SupprimerSommet(2);
    g->RafraichirAretes();
    g->PrintDab();
    cout<<"\n";
    g->SupprimerSommet(4);
    g->RafraichirAretes();
    g->AjouterSommets();
    g->PrintDab();
    cout<<"\n";
    g->SupprimerSommet(3);
    g->SupprimerSommet(2);
    g->SupprimerSommet(1);
    g->SupprimerSommet(0);
    g->RafraichirAretes();
    g->PrintDab();
    g->AjouterSommets(3);
    g->AjouterArete(0,1);
    g->AjouterArete(0,1);
    g->AjouterArete(0,2);
    g->PrintDab();cout << "\n";
    Graph* h = Graph::GenerateRandomGraph(4,45);
    h->PrintDab();
    cout<<"\n\n";
    Graph* t = Graph::GenerateBarabasiAlbertGraph(8,1);
    t->PrintDab();
    cout<<"\n\n";
    t->SupprimerSommet(0);
    t->SupprimerSommet(1);
    t->RafraichirAretes();
    t->PrintDab();
    cout<<"\n\n";
    Graph* a = t->CreerCopie();
    a->PrintDab();


    return 0;
}
*/
