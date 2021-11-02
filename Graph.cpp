#include "Graph.h"

Graph::Graph(int nbS=0)
{
    nbSommets=0;
    indexSommetMax=-1;
    listeSommets={};
    listeAdjacence={};
    AjouterSommet(nbS);
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::PrintDab() {
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

int Graph::getDegres(int index) {
    return listeAdjacence[index].size();
}

int Graph::getNbSommets() {
    return nbSommets;
}

vector<int8_t>* Graph::getListeSommets() {
    return &listeSommets;
}

vector<int>* Graph::getVoisins(int indexSommet) {
    return &listeAdjacence[indexSommet];
}

void Graph::AjouterSommet(int nb=1) {
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
        cout << "Sommet ajouté\n";
    }
}

void Graph::SupprimerSommet(int index) {
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
    cout << "Sommet supprimé\n";
}

void Graph::AjouterArete(int v1, int v2) {
    if (v1>indexSommetMax || v2>indexSommetMax || v1==v2) {
        cout << "L'arète ne peut pas être ajoutée\n";
        return;
    }
    int taille=listeAdjacence[v1].size();
    for (int i=0;i<taille;i++) {
        if (listeAdjacence[v1][i]==v2) {
            cout << "L'arète existe déjà\n";
            return;
        }
    }
    listeAdjacence[v1].push_back(v2);
    listeAdjacence[v2].push_back(v1);
    cout << "Arète ajoutée\n";
}

void Graph::SupprimerArete(int v1, int v2) {
    if (v1>indexSommetMax || v2>indexSommetMax) {
        cout << "L'arète "<< v1 << " " << v2 <<" ne peut pas être supprimée\n";
        return;
    }
    int out=0;
    int taille=listeAdjacence[v1].size();
    for (int i=0;i<taille && out==0;i++) {
        if (listeAdjacence[v1][i]==v2) {
            listeAdjacence[v1][i]=-1;
            cout << "Arète supprimée d'un côté\n";
            out=1;
        }
    }
    out=0;
    taille=listeAdjacence[v2].size();
    for (int i=0;i<taille && out==0;i++) {
        if (listeAdjacence[v2][i]==v1) {
            listeAdjacence[v2][i]=-1;
            cout << "Arète supprimée de l'autre\n";
            out=1;
        }
    }
    cout << "Arète supprimée\n";
}

void Graph::RafraichirAretes() {
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
    cout << "Liste d'adjacence nettoyée\n";
}

Graph* Graph::GenerateRandomGraph(int nbS, int p) {
    Graph* g = new Graph(nbS);
    std::mt19937 mt(time(nullptr));
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    double r;int realr;
    for (int i=0;i<nbS;i++) {
        for (int j=i+1;j<nbS;j++) {
            r=dist(mt);r=r+0.5-(r<0);
            realr=(int)r;
            if (realr<p) {
                g->AjouterArete(i,j);
            }
        }
    }
    return g;
}

Graph* Graph::GenerateBarabasiAlbertGraph(int nbS=3, int m=0) {
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
    int compteurM=0;
    int dMax=6;int d=2;
    Graph* g = new Graph();
    g->AjouterSommet(nbS);
    g->AjouterArete(0,1);
    g->AjouterArete(0,2);
    g->AjouterArete(1,2);
    std::mt19937 mt(time(nullptr));
    std::uniform_real_distribution<double> dist(1.0, 100.0);
    double r;
    for (int i=3;i<nbS;i++) {
        for (int j=0;j<nbS&&compteurM<m;j++) {
            if (j==i) {j++;}
            d=g->getDegres(j);
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

int main() {
    Graph* g = new Graph();

    g->AjouterSommet(2);
    g->AjouterSommet();
    g->AjouterSommet(2);
    g->AjouterArete(0,1);
    g->AjouterArete(0,1);
    g->AjouterArete(0,2);
    g->AjouterArete(4,3);
    g->AjouterArete(7,6);

    g->SupprimerArete(0,1);

    g->SupprimerSommet(2);
    g->SupprimerSommet(4);
    g->SupprimerSommet(3);
    g->SupprimerSommet(2);
    g->SupprimerSommet(1);
    g->SupprimerSommet(0);
    g->RafraichirAretes();

    g->PrintDab();cout << "\n";

    g->AjouterSommet(3);

    g->AjouterArete(0,1);
    g->AjouterArete(0,1);
    g->AjouterArete(0,2);

    g->PrintDab();cout << "\n";

    Graph* h = Graph::GenerateRandomGraph(4,45);
    h->PrintDab();

    cout<<"\n\n";
    Graph* t = Graph::GenerateBarabasiAlbertGraph(8,1);
    t->PrintDab();
    return 0;
}
