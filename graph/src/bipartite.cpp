/*
Algoritmo para emparelhamento bipartido maximo
dos vertices do conjunto A com os vertices do conjunto B
*/

#include <iostream>
#include <vector>
#include <string.h>

#define MAX_A 100
#define MAX_B 100

using namespace std;

struct vertex{
	vector<int> adjList;
};

int matching(vertex *graph, int N);
bool dfsBPM(vertex *graph, int *match, bool *seen, int v);

int main(void){

	ios::sync_with_stdio(false);

	int A, B, M, X, Y, result;
	vertex graph[MAX_A];

	while( cin >> A >> B >> M && A ){

		for(int i=0; i<A; i++){
			graph[i].adjList.clear();
		}

		for(int i=0; i<M; i++){
			cin >> X >> Y;
		
			graph[X-1].adjList.push_back(Y-1);
		}

		cout << "Set A = " << A << endl;
		cout << "Set B = " << B << endl;
		cout << "Max Matching = " << matching(graph, A) << endl << endl;
	}

	return 0;
}


int matching(vertex *graph, int N){

	bool seen[MAX_B];
	int match[MAX_B];
	int max_matching;

	memset(match, -1, sizeof(match));

	max_matching = 0;

	for(int i=0; i<N; i++){
		memset(seen, false, sizeof(seen));
		max_matching += dfsBPM(graph, match, seen, i);
	}

	return max_matching;
}

bool dfsBPM(vertex *graph, int *match, bool *seen, int v){

	int B;

	for(unsigned int i=0; i<graph[v].adjList.size(); i++){
		B = graph[v].adjList[i];

		if( !seen[B] ){
			seen[B] = true;

			if( match[B] == -1 || dfsBPM(graph, match, seen, match[B]) ){
				match[B] = v;
				return true;
			}
		}
	}

	return false;
}
