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

		cout << i << ": ";
		for (int j=0;j<siz;j++) {
            		cout << adjacencyList[i][j] << " ";	
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


void Graph::sortDegenerativeList(){
	int i;
	int j;
	int iterator;

	//tableau d'exemple d'ordre de dégénrescence -> plus tard en entrée de fonction
	int tab[3];
	tab[0] = 1;
	tab[1] = 0;
	tab[2] = 2;
	tab[3] = 3;

	printf("APRES LA FONCTION SORT:\n");

	for(i=0;i<countVertices;i++) {
		int size = adjacencyList[i].size();
		iterator = 0;

		for(j=0;j<size;j++){
			if(tab[adjacencyList[i][iterator]] < tab[i])
			{
				int tmp = adjacencyList[i][size-1];
				//printf("----> i:%d | j:%d | %d<=>%d\n", i,j,adjacencyList[i][iterator],tmp);
				adjacencyList[i][size-1] = adjacencyList[i][iterator];
				adjacencyList[i][iterator] = tmp;
			}
			else
			{
				iterator++;
			}
		}


	}
}


int main() {
	Graph* g = new Graph();
    	g->addVertex(3);
    	g->addEdge(0,1);
    	g->addEdge(0,2);
    	g->addEdge(2,3);
    	g->addEdge(1,2);
    	g->printDab();
	g->sortDegenerativeList();
    	g->printDab();
    	return 0;
}




