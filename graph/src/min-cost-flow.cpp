#include <iostream>
#include <string.h>
#include <queue>
#include <limits.h>

#define INF INT_MAX/2
#define MAX 102

using namespace std;

int cost[MAX][MAX];
int cap[MAX][MAX];
int flow[MAX][MAX];
int pi[MAX];
int parent[MAX];
int minFlow[MAX];
int distanceArray[MAX];

struct vertex{
	int index;
	int distance;
	vertex(int i, int d) : index(i), distance(d){
	}
	bool operator < (const vertex& b) const{
		return this->distance > b.distance;
	}
};

void relax(priority_queue<vertex>& Q, int v, int u, int capacity, int distance);
int dijkstra(int N, int source, int sink);
void min_cost_flow(int N, int source, int sink, int& max_flow, int& f_cost);

int main(void){

	ios::sync_with_stdio(false);

	int N, M;
	int A, B, capacity, edge_cost;
	int f_cost, max_flow;

	while( cin >> N >> M ){

		memset(cost, 0, sizeof(cost));
		memset(cap, 0, sizeof(cap));
		memset(flow, 0, sizeof(flow));
		memset(pi, 0, sizeof(pi));

		cost[0][1] = 0;
		cost[N][N+1] = 0;

		cap[0][1] = INF;
		cap[N][N+1] = INF;

		for(int i=0; i<M; i++){
			cin >> A >> B >> capacity >> edge_cost;

			cap[A][B] = capacity;
			cap[B][A] = capacity;

			cost[A][B] = edge_cost;
			cost[B][A] = edge_cost;
		}

		min_cost_flow(N+2, 0, N+1, max_flow, f_cost);

		cout << "Max flow " << max_flow << " with cost " << f_cost << endl;
	}

	return 0;
}

void relax(priority_queue<vertex>& Q, int v, int u, int capacity, int distance){
	if( capacity > 0 && distanceArray[u] > distance ){
		distanceArray[u] = distance;
		parent[u] = v;
		minFlow[u] = min(minFlow[v], capacity);
		Q.push( vertex(u, distance) );
	}
}

int dijkstra(int N, int source, int sink){

	priority_queue<vertex> Q;
	int v, distance, potential;

	for(int i=0; i<N; i++){
		parent[i] = -1;
		minFlow[i] = INT_MAX;
		distanceArray[i] = INF;
	}

	distanceArray[source] = 0;
	Q.push( vertex(source, 0) );

	while( !Q.empty() ){

		v = Q.top().index;
		distance = Q.top().distance;

		Q.pop();

		if( distance == distanceArray[v] ){
			for(int u=0; u<N; u++){
				potential = distance + pi[v] - pi[u];

				relax(Q, v, u, cap[v][u]-flow[v][u], potential + cost[v][u]);
				relax(Q, v, u, flow[u][v], potential - cost[u][v]);
			}
		}
	}

	for(int i=0; i<N; i++)
		pi[i] = min(pi[i] + distanceArray[i], INF);

	return minFlow[sink];
}

void min_cost_flow(int N, int source, int sink, int& max_flow, int& f_cost){

	int shortestFlow;

	f_cost = 0;
	max_flow = 0;

	while( (shortestFlow=dijkstra(N, source, sink)) != INT_MAX ){
		for(int i=sink; parent[i]!=-1; i=parent[i]){
			if( flow[i][ parent[i] ] ){
				flow[i][ parent[i] ] -= shortestFlow;
				f_cost -= shortestFlow * cost[i][ parent[i] ];
			}else{
				flow[ parent[i] ][i] += shortestFlow;
				f_cost += shortestFlow * cost[ parent[i] ][i];
			}
		}

		max_flow += shortestFlow;		
	}
}
