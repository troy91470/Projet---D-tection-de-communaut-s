#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

/**
Renvoie une copie du vecteur donne en entree, triee selon les numeros de sommet
*/
vector<int> trierVecteurSelonNum(vector<int> v);


/**
Classe representant un Graphe non-oriente.
Supporte l'ajout et la suppression de sommets et d'aretes.
*/
class Graph
{
    public:
        /*
        Constructeur.
        nbS est le nombre de sommets du Graph créé instantanement.
        */
        Graph(int nbS);
        virtual ~Graph();
        /*
        Permet d'afficher la liste d'adjacence du Graph.
        */
        void PrintDab();
        /*
        Renvoie le nombre de voisins du sommet index
        */
        int GetDegres(int index);
        /*
        Explicite.
        */
        int GetNbSommets();
        /*
        Renvoie un pointeur vers la liste des sommets.
        */
        vector<int8_t>* GetListeSommets();
        /*
        Renvoie un pointeur vers la liste des voisins du sommet indexSommet.
        */
        vector<int>* GetVoisins(int indexSommet);
        /*
        Utilisé pour creer une copie d'un Graph.
        */
        void SetGraph(int indexMax,int nbS, vector<int8_t>* listeS,vector<vector<int>>* listeA);
        /*
        Ajoute un nombre de sommet egal a nb.
        2 sommets sont ajoutes si nb=2.
        nb ne represente pas le nom/indice d'un sommet a ajouter.
        */
        void AjouterSommets(int nb=1);
        /*
        Supprime un sommet et les aretes liees a ce sommet.
        */
        void SupprimerSommet(int index);
        /*
        Explicite.
        Ajoute a deux endroits dans la liste d'adjacence.
        */
        void AjouterArete(int s1, int s2);
        /*
        Marque l'arete concernee pour la suppression.
        */
        void SupprimerArete(int s1, int s2);
        /*
        Supprime toutes les aretes marquees.
        */
        void RafraichirAretes();
        /*
        Genere un Graph aleatoire avec un nombre de sommets nbS, et une chance de liaison entre sommet p.
        */
        static Graph* GenerateRandomGraph(int nbS, int p);
        /*
        Genere un Graph avec un nombre de sommets nbS qui suit le modele Barabasi-Albert de parametre m.
        */
        static Graph* GenerateBarabasiAlbertGraph(int nbS,int m);
        /*
        Renvoie un pointeur vers une copie du Graph appelant.
        */
        Graph* CreerCopie();
        /*
        Tri un vecteur selon la liste de degenerescence
        */
	void triVecteurSelonOrdreDege(int* posOrdreDegenerescence);
        /*
        Renvoie le sous graphe d'un sommet
        */
	Graph* TrouveSousGraphe(int* posOrdreDegenerescence, int numSommet);

    protected:

    private:
        /*
        Pour une description imagee, voir la documentations.
        */

        /*
        Index maximum du vecteur listeSommets et de la premiere dimension de la liste d'adjacence.
        Correspond plus grand "nom de sommet".
        */
        int indexSommetMax;
        /*
        Explicite.
        */
        int nbSommets;
        /*
        Vector contenant des booleens representant l'existence du sommet dans le graphe.
        Si le sommet i renvoie 1, il est dans le graphe. Apres suppression d'un sommet, il est mis a 0 et n'est plus pris en compte dans les calculs.
        */
        vector<int8_t> listeSommets;
        /*
        Explicite.
        */
        vector<vector<int>> listeAdjacence;
};

#endif // GRAPH_H
