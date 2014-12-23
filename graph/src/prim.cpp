/*
Algoritmo guloso para arvore geradora minima
Parecido com dijkstra, A unica diferenca eh o uso apenas do custo da aresta
e nao o custo desde o vertice inicial ate o vizinho
OBS: Apenas para grafos conectados
OBS: Indicado para grafos densos, ao contrario do kruskal
*/

#include <iostream>
#include <vector>
#include <limits.h>
#include <queue>

#define MAX_VERTEX 1000

using namespace std;

struct edge{
	int neighbor;
	int cost;
	edge(int n, int c) : neighbor(n), cost(c){
	}
};

struct vertex{
	vector<edge> adjacencyList;
};

struct prim_node{
	int index;
	int cost;
	prim_node(int i, int c) : index(i), cost(c){
	}
	bool operator < (const prim_node& b) const{
		return this->cost > b.cost;
	}
};

int prim_sparse(vertex *graph, int N);
int prim_dense(vertex *graph, int N);
int getSmaller(int *cost, bool *visited, int N);

int main(void){

	ios::sync_with_stdio(false);

	int N, M;
	int A, B, C;
	vertex graph[MAX_VERTEX];
	
	while( cin >> N >> M ){

		for(int i=0; i<N; i++){
			graph[i].adjacencyList.clear();
		}

		for(int i=0; i<M; i++){
			cin >> A >> B >> C;

			graph[A].adjacencyList.push_back( edge(B, C) );
			graph[B].adjacencyList.push_back( edge(A, C) );
		}

		cout << "New Test" << endl;
		cout << "Prim (Dense Graphs) = " << prim_dense(graph, N) << endl;
		cout << "Prim (Sparse Graph) = " << prim_sparse(graph, N) << endl;
	}

	return 0;
}

/*
Iniciar busca a partir de qualquer vertice
*/
int prim_sparse(vertex *graph, int N){

	int cost[MAX_VERTEX];
	bool visited[MAX_VERTEX];
	int v, u, du, minLength;
	priority_queue<prim_node> Q;

	for(int i=0; i<N; i++){
		cost[i] = INT_MAX;
		visited[i] = false;
	}

	cost[0] = 0;
	Q.push( prim_node(0, 0) );
	minLength = 0;

	while( !Q.empty() ){

		v = Q.top().index;
		Q.pop();

		if( !visited[v] ){
			
			visited[v] = true;
			minLength += cost[v];

			for(unsigned int i=0; i<graph[v].adjacencyList.size(); i++){
				u = graph[v].adjacencyList[i].neighbor;
				du = graph[v].adjacencyList[i].cost;

				if( !visited[u] && cost[u] > du ){
					cost[u] = du;
					Q.push( prim_node(u, cost[u]) );
				}
			}
		}
	}

	return minLength;
}

int getSmaller(int *cost, bool *visited, int N){

	int index, smaller;

	index = -1;
	smaller = INT_MAX;

	for(int i=0; i<N; i++){
		if( !visited[i] && cost[i] < smaller ){
			smaller = cost[i];
			index = i;
		}
	}

	return index;
}

int prim_dense(vertex *graph, int N){

	int cost[MAX_VERTEX];
	bool visited[MAX_VERTEX];
	int v, u, du, minLength;

	for(int i=0; i<N; i++){
		cost[i] = INT_MAX;
		visited[i] = false;
	}

	cost[0] = 0;
	minLength = 0;

	while( (v=getSmaller(cost, visited, N))!=-1 ){
		
		visited[v] = true;
		minLength += cost[v];

		for(unsigned int i=0; i<graph[v].adjacencyList.size(); i++){
			u = graph[v].adjacencyList[i].neighbor;
			du = graph[v].adjacencyList[i].cost;

			if( !visited[u] && cost[u] > du ){
				cost[u] = du;
			}
		}
	}

	return minLength;
}
