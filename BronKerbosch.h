#include <algorithm>
#include <iterator>
#include <map>
#include <typeinfo>
#include "Graph.h"

void intersection(vector<int> &v1, vector<int> &v2, vector<int> &vectorIntersection);
void v1PriveDeV2(vector<int> &v1, vector<int> &v2, vector<int> &vectorV1PriveDeV2);
void BronKerbosch(vector<int> &P, vector<int> &R, vector<int> &X, vector<vector<int>> &cliques, Graph &G);
void ordreDegenerescence(Graph *graphe, vector<int> &tabOrdreDege, int posSommetOrdreDege[]);
void BronKerboschPivot(vector<int> &P, vector<int> &R, vector<int> &X,vector<vector<int>> &cliques, Graph &G);
void BronKerboschDegeneracy(vector<vector<int>> &cliques,Graph &G);
