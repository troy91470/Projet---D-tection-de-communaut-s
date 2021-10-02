#include <iostream>
#include <list>
#ifndef GRAPH_H
#define GRAPH_H


class Graph
{
    public:
        Graph();
        virtual ~Graph();
        void printDab();
        void addVertex();
        void addEdge();
        void deleteEdge();

    protected:

    private:
        int countVertices;
        std::list<int> adjacencyList;
};

#endif // GRAPH_H
