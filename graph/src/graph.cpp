#include <iostream>
#include <vector>
#include <queue>
#include <string.h>

#define MAX_VERTEX 100

using namespace std;

struct vertex{
	vector<int> adjacencyList;
};

int bfs(vertex *graph, int N);
int getUnvisited(bool *visitedArray, int N);
void dfsVisit(vertex *graph, bool *visited, int v);
int dfsCC(vertex *graph, int N);

int main(void){

	ios::sync_with_stdio(false);

	int N, M, A, B, cc;
	vertex graph[MAX_VERTEX];

	while( cin >> N >> M && N ){

		for(int i=0; i<N; i++){
			graph[i].adjacencyList.clear();
		}

		for(int i=0; i<M; i++){
			cin >> A >> B;

			graph[A-1].adjacencyList.push_back(B-1);
			graph[B-1].adjacencyList.push_back(A-1);
		}

		cout << "DFS" << endl;
		
		cc = dfsCC(graph, N);

		cout << "Total of Connected Components = " << cc << endl;

		cout << endl << "BFS" << endl;

		cc = bfs(graph, N);
		
		cout << "Total of Connected Components = " << cc << endl;
	}

	return 0;
}

int dfsCC(vertex *graph, int N){

	bool visited[MAX_VERTEX];
	int cc;

	memset(visited, false, sizeof(visited));

	cc = 0;

	for(int i=0; i<N; i++){
		if( !visited[i] ){
			dfsVisit(graph, visited, i);
			cc++;
		}
	}

	return cc;
}

void dfsVisit(vertex *graph, bool *visited, int v){

	int u;

	visited[v] = true;

	for(unsigned int i=0; i<graph[v].adjacencyList.size(); i++){
		u = graph[v].adjacencyList[i];
	
		if( !visited[u] ){
			cout << "Edge: " << v+1 << " -> " << u+1 << endl;
			dfsVisit(graph, visited, u);
		}
	}
}

int bfs(vertex *graph, int N){

	int v, u, cc;
	bool visited[MAX_VERTEX];
	queue<int> Q;

	memset(visited, false, sizeof(visited));

	cc = 0;

	for(int i=0; i<N; i++){

		if( !visited[i] ){
			cc++;

			visited[i] = true;
			Q.push( i );

			while( !Q.empty() ){
			
				v = Q.front();
				Q.pop();

				for(unsigned int i=0; i<graph[v].adjacencyList.size(); i++){
					u = graph[v].adjacencyList[i];

					if( !visited[u] ){
						cout << "Edge: " << v+1 << " -> " << u+1 << endl;
						visited[u] = true;
						Q.push(u);
					}
				}
			}
		}
	}

	return cc;
}
