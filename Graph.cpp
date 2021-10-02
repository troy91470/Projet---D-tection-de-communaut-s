#include "Graph.h"

Graph::Graph()
{
    adjacencyList = {};
    //ctor
}

Graph::~Graph()
{
    //dtor
}

void Graph::printDab() {
    std::cout << "dab\n";
}

void Graph::addVertex() {
    std::cout << "dab\n";
}

void Graph::addEdge() {
    std::cout << "dab\n";
}

void Graph::deleteEdge() {
    std::cout << "dab\n";
}

int main() {
    Graph* g = new Graph();
    g->printDab();
    std::cout << "prout";
    return 0;
}
