#include "Graph.h"

Graph::Graph()
{
	countVertices=0;
	adjacencyList={};
	vertexPresent={};
	//ctor
}

Graph::~Graph()
{
	//dtor
}

void Graph::printDab() {
	for (int i=0;i<countVertices;i++) {
		int siz = adjacencyList[i].size();

		if(vertexPresent[i] == 1)
		{
			cout << i << ": ";

			for (int j=0;j<siz;j++)
		    		cout << adjacencyList[i][j] << " ";

        		cout << "\n";
		}
    	}
}

void Graph::addVertex(int num=1) {
	for (int i=0;i<num;i++) {
        	countVertices++;
       	 	vector<int> newL;
		adjacencyList.push_back(newL);
		vertexPresent.push_back(1);
       		cout << "V added\n";
	}
}

void Graph::addEdge(int v1, int v2) {
	adjacencyList[v1].push_back(v2);
    	adjacencyList[v2].push_back(v1);
    	cout << "EDGE added\n";
}




// partie à bouger + à commenter
void Graph::sortDegenerativeList(){
	int tmp;
	int startIterator;
	int endIterator;

	//tableau d'exemple d'ordre de dégénrescence -> plus tard en entrée de fonction
	int tab[4];
	tab[0] = 1;
	tab[1] = 2;
	tab[2] = 3;
	tab[3] = 0;
	tab[4] = 4;

	cout << "APRES LA FONCTION SORT:\n";

	for(int i=0;i<countVertices;i++) 
	{
		int size = adjacencyList[i].size();
		startIterator = 0;
		endIterator = size-1;

		for(int j=0;j<size;j++)
		{
			if(tab[adjacencyList[i][startIterator]] < tab[i])
			{
				tmp = adjacencyList[i][endIterator];
				adjacencyList[i][endIterator] = adjacencyList[i][startIterator];
				adjacencyList[i][startIterator] = tmp;
				endIterator--;
			}
			else
			{
				startIterator++;
			}
		}


	}
}

Graph* copyGraph(Graph* mainGraph)
{
	Graph* subGraph = new Graph();

	subGraph->countVertices = mainGraph->countVertices;

	subGraph->adjacencyList.resize(mainGraph->adjacencyList.size());
	copy(mainGraph->adjacencyList.begin(), mainGraph->adjacencyList.end(), subGraph->adjacencyList.begin());

	for(int i=0;i<(subGraph->countVertices);i++)
	{
		subGraph->adjacencyList[i].resize(mainGraph->adjacencyList[i].size());
		copy(mainGraph->adjacencyList[i].begin(), mainGraph->adjacencyList[i].end(), subGraph->adjacencyList[i].begin());
	}

	(subGraph->vertexPresent).resize(mainGraph->vertexPresent.size());
	copy(mainGraph->vertexPresent.begin(), mainGraph->vertexPresent.end(), subGraph->vertexPresent.begin());

	return subGraph;
}


Graph* giveSubGraph(Graph* mainGraph, int vertexRemoved){

	Graph* subGraph = copyGraph(mainGraph);

	for(int i=0;i<(subGraph->countVertices);i++)
	{
		if(i == vertexRemoved)
			subGraph->vertexPresent[i] = 0;
		else
		{
			int size = subGraph->adjacencyList[i].size();

			for(int j=0;j<size;j++)
			{
				if(subGraph->adjacencyList[i][j] == vertexRemoved)
				{
					subGraph->adjacencyList[i].erase(subGraph->adjacencyList[i].begin() + j);
					if(size == 1)
						subGraph = giveSubGraph(subGraph, i);
				}
			}
		}
	}

	return subGraph;
}



int main() {
	Graph* mainGraph = new Graph();
    	mainGraph->addVertex(5);
    	mainGraph->addEdge(0,1);
    	mainGraph->addEdge(0,2);
    	mainGraph->addEdge(2,3);
    	mainGraph->addEdge(1,2);
    	mainGraph->addEdge(1,4);
    	mainGraph->addEdge(0,4);
    	mainGraph->printDab();
	//printf("-------------------------------\n");
	//mainGraph->sortDegenerativeList();
	Graph* subGraph = giveSubGraph(mainGraph, 2);
    	subGraph->printDab();
    	return 0;
}




