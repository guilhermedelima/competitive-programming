#include <iostream>
#include <string.h>
#include <queue>
#include <limits.h>

#define MAX_VERTEX 100

using namespace std;

int cap[MAX_VERTEX][MAX_VERTEX];
int flow[MAX_VERTEX][MAX_VERTEX];
int parent[MAX_VERTEX];

int bfs(int N, int source, int sink);
int ford_fulkerson(int N, int source, int sink);

int main(void){

	ios::sync_with_stdio(false);
	int N, M, A, B, C;

	while( cin >> N >> M ){

		memset(cap, 0, sizeof(cap));
		memset(flow, 0, sizeof(flow));

		for(int i=0; i<M; i++){
			cin >> A >> B >> C;

			cap[A][B] = C;
		}

		cout << "Max Flow = " << ford_fulkerson(N, 0, N-1) << endl;
	}

	return 0;
}


int bfs(int N, int source, int sink){

	bool visited[MAX_VERTEX];
	int min_flow[MAX_VERTEX];
	queue<int> Q;
	int v;

	for(int i=0; i<N; i++){
		visited[i] = false;
		parent[i] = -1;
		min_flow[i] = INT_MAX;
	}

	visited[source] = true;
	Q.push( source );

	while( !Q.empty() ){

		v = Q.front();
		Q.pop();

		for(int u=0; u<N; u++){
			if( !visited[u] && cap[v][u] - flow[v][u] > 0 ){
				visited[u] = true;
				parent[u] = v;
				min_flow[u] = min(min_flow[v], cap[v][u] - flow[v][u]);
				
				Q.push(u);
			}
		}
	}

	return min_flow[sink];
}


int ford_fulkerson(int N, int source, int sink){

	int aug_flow, f;

	f = 0;

	while( (aug_flow=bfs(N, source, sink)) != INT_MAX ){
		for(int i=sink; parent[i] != -1; i = parent[i]){
			flow[parent[i]][i] += aug_flow;
			flow[i][parent[i]] -= aug_flow;
		}

		f += aug_flow;
	}

	return f;
}
