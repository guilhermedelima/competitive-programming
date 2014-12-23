#include <iostream>
#include <vector>
#include <string.h>

#define MAX_VERTEX 100

#define WHITE -1
#define BLACK 0
#define GRAY 1

using namespace std;

struct vertex{
	vector<int> adjacencyList;
};

bool dfsCycle(vertex *graph, int N);
bool dfsVisit(vertex *graph, int *color, int v);

int main(void){

	ios::sync_with_stdio(false);

	vertex graph[MAX_VERTEX];
	int N, M, A, B;

	while( cin >> N >> M ){

		for(int i=0; i<N; i++){
			graph[i].adjacencyList.clear();
		}

		for(int i=0; i<M; i++){
			cin >> A >> B;

			graph[B-1].adjacencyList.push_back(A-1);
		}

		cout << (dfsCycle(graph, N) ? "Graph has cycle" : "This is a DAG" ) << endl;
	}

	return 0;
}


bool dfsCycle(vertex *graph, int N){

	int color[MAX_VERTEX];

	memset(color, -1, sizeof(color));

	for(int i=0; i<N; i++){
		if( color[i] == WHITE && dfsVisit(graph, color, i) )
			return true;
	}

	return false;
}

/*
Para grafos não direcionados basta verificar se o vértice vizinho
não é o pai do atual e se este já foi visitado
*/
bool dfsVisit(vertex *graph, int *color, int v){

	int u;

	color[v] = GRAY;

	for(unsigned int i=0; i<graph[v].adjacencyList.size(); i++){
		u = graph[v].adjacencyList[i];

		if( color[u] == WHITE && dfsVisit(graph, color, u) )
			return true;
		else if( color[u] == GRAY )
			return true;
	}

	color[v] = BLACK;

	return false;
}
