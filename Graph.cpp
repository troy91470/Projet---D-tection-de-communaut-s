#include "Graph.h"

Graph::Graph()
{
    countVertices=0;
    adjacencyList={};
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::printDab() {
    for (int i=0;i<countVertices;i++) {
        int siz = adjacencyList[i].size();
        for (int j=0;j<siz;j++) {
            cout << adjacencyList[i][j];
        }
        cout << "\n";
    }
}

void Graph::addVertex(int num=1) {
    for (int i=0;i<num;i++) {
        countVertices++;
        vector<int> newL;
        adjacencyList.push_back(newL);
        cout << "V added\n";
    }
}

void Graph::addEdge(int v1, int v2) {
    adjacencyList[v1].push_back(v2);
    adjacencyList[v2].push_back(v1);
    cout << "EDGE added\n";
}

int main() {
    Graph* g = new Graph();
    g->addVertex(2);
    g->addEdge(0,1);
    g->printDab();
    return 0;
}
