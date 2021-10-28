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




void Graph::sortDegenerativeList(int* tab){
	int tmp;
	int startIterator;
	int endIterator;


	for(int i=0;i<countVertices;i++) //on parcourt la liste des sommets
	{
		int size = adjacencyList[i].size();
		startIterator = 0;
		endIterator = size-1;

		for(int j=0;j<size;j++) //on parcourt les voisins du sommet actuel
		{
			if(tab[adjacencyList[i][startIterator]] < tab[i])
			{
				//on échange la valeur placée à l'itérateur de début, avec celle de l'itérateur de fin
				tmp = adjacencyList[i][endIterator];
				adjacencyList[i][endIterator] = adjacencyList[i][startIterator];
				adjacencyList[i][startIterator] = tmp;
				endIterator--; //on recule l'itérateur de fin
			}
			else
			{
				startIterator++; //sinon on avance l'itérateur de début
			}
		}


	}
}

Graph* copyGraph(Graph* mainGraph)
{
	Graph* subGraph = new Graph();

	subGraph->countVertices = mainGraph->countVertices;

	subGraph->adjacencyList.resize(mainGraph->adjacencyList.size()); //on redimensionne le vecteur des sommets de la liste d'adj du nouveau graphe, selon le vecteur de l'ancien graphe
	copy(mainGraph->adjacencyList.begin(), mainGraph->adjacencyList.end(), subGraph->adjacencyList.begin()); //on copie le vecteur des sommets de la liste d'adj de l'ancien graphe sur le nouveau graphe

	for(int i=0;i<subGraph->countVertices;i++) //on parcourt les sommets de la liste d'adj du nouveau graphe afin de redimensionner et remplacer le vecteur des voisins du sommet parcouru selon l'ancien graphe
	{
		subGraph->adjacencyList[i].resize(mainGraph->adjacencyList[i].size());
		copy(mainGraph->adjacencyList[i].begin(), mainGraph->adjacencyList[i].end(), subGraph->adjacencyList[i].begin());
	}

	(subGraph->vertexPresent).resize(mainGraph->vertexPresent.size());
	copy(mainGraph->vertexPresent.begin(), mainGraph->vertexPresent.end(), subGraph->vertexPresent.begin());

	return subGraph;
}


Graph* giveSubGraph(Graph* mainGraph, int vertexRemoved){

	Graph* subGraph = copyGraph(mainGraph); //on crée une copie du graphe que l'on renverra une fois modifiée

	for(int i=0;i<subGraph->countVertices;i++)  //on parcourt les sommets du nouveau graphe
	{
		if(i == vertexRemoved) //si le sommet actuel est le sommet que l'on souhaite supprimé
			subGraph->vertexPresent[i] = 0; //on met un 0 à sa position dans vertexPresent pour indiquer qu'il est supprimé
		else
		{
			if(subGraph->vertexPresent[i] == 1){ //on vérifie que le sommet parcouru existe bien afin d'éviter d'éxecuter du code inutiliement
 
				int size = subGraph->adjacencyList[i].size();

				for(int j=0;j<size;j++) //on parcourt les voisins du sommet actuel
				{
					if(subGraph->adjacencyList[i][j] == vertexRemoved) //si le voisin parcouru est le sommet que l'on souhaite supprimer
					{
						subGraph->adjacencyList[i].erase(subGraph->adjacencyList[i].begin() + j); //on supprime ce voisin de la liste d'adj
						if(size == 1) //si le sommet supprimé est le seul voisin du sommet parcouru
							subGraph = giveSubGraph(subGraph, i); //on utilise de la récurrence sur ce sommet
					}
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

	//Graph* subGraph = giveSubGraph(mainGraph, 2);
    	mainGraph->printDab();
    	return 0;
}




