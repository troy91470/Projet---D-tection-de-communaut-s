#include <iostream>
#include <vector>
#include <random>
#include <time.h>
#ifndef GRAPH_H
#define GRAPH_H

using namespace std;

class Graph
{
    public:
        Graph(int nbS);
        virtual ~Graph();
        void PrintDab();
        int getDegres(int index);
        void AjouterSommet(int nb);
        void SupprimerSommet(int index);
        void AjouterArete(int s1, int s2);
        void SupprimerArete(int s1, int s2);
        void RafraichirAretes();
        static Graph* GenerateRandomGraph(int nbS, int p);
        static Graph* GenerateBarabasiAlbertGraph(int nbS,int m);

    protected:

    private:
        int indexSommetMax;
        int nbSommets;
        vector<int8_t> listeSommets;
        vector<vector<int>> listeAdjacence;
};

#endif // GRAPH_H
