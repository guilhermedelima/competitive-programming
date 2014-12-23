#include <iostream>

#define MAX_VERTEX 100
#define MAX_EDGE 1000
#define INF 10000

using namespace std;

struct edge{
	int src;
	int dest;
	int cost;
};

int bellman_ford(edge *list, int N, int M, int source, int target);

int main(void){

	ios::sync_with_stdio(false);

	int N, M, A, B, source, target;
	edge list[MAX_EDGE];

	while( cin >> N >> M && N ){

		for(int i=0; i<M; i++){
			cin >> A >> B >> list[i].cost;

			list[i].src = A-1;
			list[i].dest = B-1;
		}

		cin >> source >> target;

		cout << bellman_ford(list, N, M, source-1, target-1) << endl;
	}

}

int bellman_ford(edge *list, int N, int M, int source, int target){

	int distance[MAX_VERTEX];
	int index, neighbor, cost;

	for(int i=0; i<N; i++){
		distance[i] = INF;
	}

	distance[source] = 0;

	for(int i=0; i<N-1; i++){
		for(int j=0; j<M; j++){
			index = list[j].src;
			neighbor = list[j].dest;
			cost = 	list[j].cost;

			distance[neighbor] = min(distance[neighbor], distance[index] + cost);
		}
	}

	for(int i=0; i<M; i++){
		index = list[i].src;
		neighbor = list[i].dest;
		cost = 	list[i].cost;

		if( distance[neighbor] > distance[index] + cost ){
			cout << "Found negative cycle: ";
			return -2;
		}
	}

	return distance[target] == INF ? -1 : distance[target];
}
