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
    std::cout << "V added\n";

}

void Graph::addEdge() {
    std::cout << "EDGE added\n";
}

void Graph::deleteEdge() {
    std::cout << "EDGE deleted\n";
}

int main() {
    Graph* g = new Graph();
    g->printDab();
    return 0;
}
