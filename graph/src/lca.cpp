/*
Exemplo para menor caminho caminho em árvores
Utilizando o algoritmo LCA.
Casos de teste tirados do Problema colonias de formigas
*/
#include <iostream>
#include <vector>
#include <cmath>

#define MAX_VERTEX 100000

using namespace std;

struct vertex{
	long parent;
	long secParent;
	long level;
	long distanceFromRoot;
	vector<long> kidList;
	vertex() : parent(0), level(0), distanceFromRoot(0){
	}
};

long lca(vertex *graph, long A, long B);
void dfsBuildTree(vertex *graph, int index, int SQH);

int main(void){

	ios::sync_with_stdio(false);

	long N, A, B, D, Q;
	long deep, lcaIndex, path;
	vertex graph[MAX_VERTEX];

	while( cin >> N && N ){

		for(long i=0; i<N; i++){
			graph[i].kidList.clear();
		}

		deep = 0;

		for(long i=1; i<=N-1; i++){
			cin >> A >> D;

			graph[i].parent = A;
			graph[i].level = graph[A].level+1;
			graph[i].distanceFromRoot = graph[A].distanceFromRoot + D;


			graph[A].kidList.push_back(i);
			deep = max(deep, graph[i].level);
		}

		dfsBuildTree(graph, 0, sqrt(deep+1));

		cin >> Q;

		for(int i=0; i<Q; i++){
			cin >> A >> B;

			lcaIndex = lca(graph, A, B);
			path = graph[A].distanceFromRoot + graph[B].distanceFromRoot - 2*graph[lcaIndex].distanceFromRoot;

			cout << (i ? " " : "") << path;
		}

		cout << endl;
	}

	return 0;
}

void dfsBuildTree(vertex *graph, int index, int SQH){

	graph[index].secParent = graph[index].level%SQH ? graph[ graph[index].parent ].secParent : graph[index].parent;

	for(unsigned int i=0; i<graph[index].kidList.size(); i++){
		dfsBuildTree(graph, graph[index].kidList[i], SQH);
	}
}

long lca(vertex *graph, long A, long B){

	while( graph[A].secParent != graph[B].secParent ){
		if( graph[A].level > graph[B].level )
			A = graph[A].secParent;
		else
			B = graph[B].secParent;
	}

	while( A != B ){
		if( graph[A].level > graph[B].level )
			A = graph[A].parent;
		else
			B = graph[B].parent;
	}

	return A;
}
