#include "BronKerbosch.h"
#include "TableauSuffixes.h"
/*
Renvoie le vecteur contenant toutes les cliques maximales du graphe donne en entree
Algorithme n°1 du papier "A new decomposition technique for maximal clique enumeration for sparse graphs"
*/
vector<vector<int>> listeCliquesEnumAlgo1(Graph &graph);
/*
Renvoie le vecteur contenant toutes les cliques maximales du graphe donne en entree
Algorithme n°2 du papier "A new decomposition technique for maximal clique enumeration for sparse graphs"
*/
vector<vector<int>> listeCliquesEnumAlgo2(Graph &graph);
/*
Renvoie un booleen selon si la clique est acceptable ou non
*/
bool verifClique(Graph* graph,vector<int> K,int ordreDegenerescence[],int sommetSousGraphe,int sommetEtude);
/**
Renvoie une copie du vecteur donne en entree, triee selon l'ordre donne en entree
*/
vector<int> trierVecteurSelonOrdre(vector<int> v,int* ordre,int taille);
