#include "Graph.h"

Graph::Graph()
{
    nbSommets=0;
    indexSommetMax=-1;
    listeSommets={};
    listeAdjacence={};
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::printDab() {
    for (int i=0;i<indexSommetMax+1;i++) {
            if (listeSommets[i]==1) {
            cout << i << " ";
            int siz = listeAdjacence[i].size();
            for (int j=0;j<siz;j++) {
                cout << listeAdjacence[i][j];
            }
            cout << "\n";
        }
    }
}

void Graph::ajouterSommet(int nb=1) {
    for (int i=0;i<nb;i++) {
        if (indexSommetMax == nbSommets-1) {
            indexSommetMax++;
            nbSommets++;
            listeSommets.push_back(1);
            vector<int> newL;
            listeAdjacence.push_back(newL);
        }
        else {
            int out=0;
            for (int j=0;j<indexSommetMax && out==0;j++) {
                if (listeSommets[j]==0) {
                    nbSommets++;
                    listeSommets[j]=1;
                    out=1;
                }
            }
        }
        cout << "Sommet ajout�\n";
    }
}

void Graph::supprimerSommet(int index) {
    if (index > indexSommetMax) {
        cout << "Le sommet n'existe pas\n";
        return;
    }
    else if (index == indexSommetMax) {
        listeSommets[index]=0;
        for (int i=index;i>-1 && listeSommets[i];i--) {
            indexSommetMax--;
            nbSommets--;
            listeSommets.pop_back();
            listeAdjacence.pop_back();
        }
    }
    else {
        nbSommets--;
        listeSommets[index]=0;
        listeAdjacence[index].resize(1);
        listeAdjacence[index][0]=-1;
    }
    cout << "Sommet supprim�\n";
}

void Graph::ajouterArete(int v1, int v2) {
    if (v1>indexSommetMax || v2>indexSommetMax) {
        cout << "L'ar�te ne peut pas �tre ajout�e\n";
        return;
    }
    int taille=listeAdjacence[v1].size();
    for (int i=0;i<taille;i++) {
        if (listeAdjacence[v1][i]==v2) {
            cout << "L'ar�te existe d�j�\n";
            return;
        }
    }
    listeAdjacence[v1].push_back(v2);
    listeAdjacence[v2].push_back(v1);
    cout << "Ar�te ajout�e\n";
}

void Graph::supprimerArete(int v1, int v2) {
    if (v1>indexSommetMax || v2>indexSommetMax) {
        cout << "L'ar�te "<< v1 << " " << v2 <<" ne peut pas �tre supprim�e\n";
        return;
    }
    int out=0;
    int taille=listeAdjacence[v1].size();
    for (int i=0;i<taille && out==0;i++) {
        if (listeAdjacence[v1][i]==v2) {
            listeAdjacence[v1][i]=-1;
            cout << "Ar�te supprim�e d'un c�t�\n";
            out=1;
        }
    }
    out=0;
    taille=listeAdjacence[v2].size();
    for (int i=0;i<taille && out==0;i++) {
        if (listeAdjacence[v2][i]==v1) {
            listeAdjacence[v2][i]=-1;
            cout << "Ar�te supprim�e de l'autre\n";
            out=1;
        }
    }
    cout << "Ar�te supprim�e\n";
}

void Graph::rafraichirAretes() {
    int tailleListe=listeAdjacence.size();
    int tailleSousListe;
    for (int j=0;j<tailleListe;j++) {
        tailleSousListe=listeAdjacence[j].size();
        for (int i=tailleSousListe;i>-1;i--) {
            vector<int>::iterator start=listeAdjacence[j].begin();
            if (listeAdjacence[j][i]==-1) {
                listeAdjacence[j].erase(start+i);
            }
        }
    }
    cout << "Liste d'adjacence nettoy�e\n";
}

int main() {
    Graph* g = new Graph();

    g->ajouterSommet(2);
    g->ajouterSommet();
    g->ajouterSommet(2);
    g->ajouterArete(0,1);
    g->ajouterArete(0,1);
    g->ajouterArete(0,2);
    g->ajouterArete(4,3);
    g->ajouterArete(7,6);

    g->supprimerArete(0,1);

    g->supprimerSommet(2);
    g->supprimerSommet(4);
    g->supprimerSommet(3);
    g->supprimerSommet(2);
    g->supprimerSommet(1);
    g->supprimerSommet(0);
    g->rafraichirAretes();

    g->printDab();cout << "\n";

    g->ajouterSommet(3);

    g->ajouterArete(0,1);
    g->ajouterArete(0,1);
    g->ajouterArete(0,2);

    g->printDab();cout << "\n";
    return 0;
}
