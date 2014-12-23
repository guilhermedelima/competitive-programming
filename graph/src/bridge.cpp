#include <iostream>
#include <vector>
#include <string.h>

#define MAX_VERTEX 100

using namespace std;

struct vertex{
	vector<int> adjacencyList;
};

int dfsFindBridges(vertex *graph, int N);
int dfsBridge(vertex *graph, int *parent, int *pre, int *low, int& id, int index);

int main(void){

	ios::sync_with_stdio(false);

	int N, E, A, B, bridges;
	vertex graph[MAX_VERTEX];

	while( cin >> N >> E && N ){

		for(int i=0; i<N; i++){
			graph[i].adjacencyList.clear();
		}

		for(int i=0; i<E; i++){
			cin >> A >> B;

			graph[A-1].adjacencyList.push_back(B-1);
			graph[B-1].adjacencyList.push_back(A-1);
		}

		cout << "New Test" << endl;
		
		bridges = dfsFindBridges(graph, N);

		cout << "Total of Bridges = " << bridges << endl << endl;
	}

	return 0;
}

int dfsFindBridges(vertex *graph, int N){

	int parent[MAX_VERTEX];
	int pre[MAX_VERTEX];
	int low[MAX_VERTEX];
	int id, bridges;

	memset(parent, -1, sizeof(parent));
	memset(pre, -1, sizeof(pre));
	memset(low, -1, sizeof(low));

	id = -1;
	bridges = 0;

	for(int i=0; i<N; i++){
		if( parent[i] == -1 ){
			parent[i] = i;
			bridges += dfsBridge(graph, parent, pre, low, id, i);
		}
	}

	return bridges;
}


int dfsBridge(vertex *graph, int *parent, int *pre, int *low, int& id, int index){

	int neighbor, bridges;

	pre[index] = ++id;
	low[index] = id;

	bridges = 0;

	for(unsigned int i=0; i<graph[index].adjacencyList.size(); i++){
		neighbor = graph[index].adjacencyList[i];

		if( parent[neighbor] == -1 ){
			parent[neighbor] = index;
			bridges += dfsBridge(graph, parent, pre, low, id, neighbor);

			low[index] = min(low[index], low[neighbor]);

			if( pre[neighbor] == low[neighbor] ){
				bridges++;
				cout << "Bridge: " << index+1 << " -> " << neighbor+1 << endl;
			}

		}else if( neighbor != parent[index] ){
			low[index] = min(low[index], low[neighbor]);
		}
	}

	return bridges;
}
