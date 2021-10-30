#include <iostream>
#include <vector>
#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Graph
{
    public:
        Graph();
        virtual ~Graph();
        void printDab();
        void ajouterSommet(int nb);
        void supprimerSommet(int index);
        void ajouterArete(int s1, int s2);
        void supprimerArete(int s1, int s2);
        void rafraichirAretes();

    protected:

    private:
        int indexSommetMax;
        int nbSommets;
        vector<int8_t> listeSommets;
        vector<vector<int>> listeAdjacence;
};

#endif // GRAPH_H
