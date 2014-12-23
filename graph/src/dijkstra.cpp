#include <iostream>
#include <vector>
#include <queue>
#include <limits.h>
#include <limits.h>

#define MAX_VERTEX 100

using namespace std;

struct edge{
	int neighbor;
	int distance;
	edge(int n, int d) : neighbor(n), distance(d){
	}
};

struct vertex{
	vector<edge> adjacencyList;
};

struct dijkstra_node{
	int index;
	int distanceFromSource;
	dijkstra_node(int i, int d) : index(i), distanceFromSource(d){
	}
	bool operator < (const dijkstra_node& b) const{
		return this->distanceFromSource > b.distanceFromSource;
	}
};

int dijkstra_sparse(vertex *graph, int N, int source, int target);
int dijkstra_dense(vertex *graph, int N, int source, int target);
int getSmaller(int *distance, bool *visited, int N);

int main(){

	ios::sync_with_stdio(false);

	int N, E;
	int a, b, cost;
	int source, target;
	vertex graph[MAX_VERTEX];

	while( cin >> N >> E && N ){

		for(int i=0; i<N; i++){
			graph[i].adjacencyList.clear();
		}

		for(int i=0; i<E; i++){
			cin >> a >> b >> cost;	

			graph[a-1].adjacencyList.push_back( edge(b-1, cost) );
		}

		cin >> source >> target;

		cout << "New Test" << endl;
		cout << "Dijkstra (Sparse Graphs) Distance = " << dijkstra_sparse(graph, N, source-1, target-1) << endl;
		cout << "Dijkstra (Dense  Graphs) Distance = " << dijkstra_dense(graph, N, source-1, target-1) << endl;

		cout << endl;
	}

	return 0;
}

/*
Algoritmo dijkstra para grafos esparsos ("Poucas Arestas")
Utiliza Heap para sempre visitar os vértices com a menor distancia da fonte
*/
int dijkstra_sparse(vertex *graph, int N, int source, int target){

	priority_queue<dijkstra_node> Q;
	int v, u, d, du;
	int distance[MAX_VERTEX];
	
	for(int i=0; i<N; i++)
		distance[i] = INT_MAX;

	distance[source] = 0;
	Q.push( dijkstra_node(source, 0) );

	while( !Q.empty() ){

		v = Q.top().index;
		d = Q.top().distanceFromSource;

		Q.pop();

		if( d == distance[v] ){

			if( v == target )
				return d;

			for(unsigned int i=0; i<graph[v].adjacencyList.size(); i++){
				u = graph[v].adjacencyList[i].neighbor;
				du = graph[v].adjacencyList[i].distance;
				
				if( distance[u] > d + du ){
					distance[u] = d + du;
					Q.push( dijkstra_node(u, distance[u]) );
				}
			}
		}
	}

	return -1;
}

int getSmaller(int *distance, bool *visited, int N){

	int smaller, index;

	smaller = INT_MAX; 
	index = -1;

	for(int i=0; i<N; i++){
		if( !visited[i] && distance[i] < smaller ){
			smaller = distance[i];
			index = i;
		}
	}

	return index;
}


/*
Algoritmo dijkstra para grafos densos ("Muitas Arestas")
Com muitas arestas um Heap pode se tornar muito grande, com isso as buscas ficam demoradas
Por isso substitui-se o Heap por uma busca linear a cada rodada
Obs: Para grafos completos usar matriz de adjacencia!
*/
int dijkstra_dense(vertex *graph, int N, int source, int target){

	int v, u, du;
	int distance[MAX_VERTEX];
	bool visited[MAX_VERTEX];

	for(int i=0; i<N; i++){
		visited[i] = false;
		distance[i] = INT_MAX;
	}

	distance[source] = 0;

	while( !visited[target] && (v=getSmaller(distance, visited, N)) != -1 ){

		visited[v] = true;

		for(unsigned int i=0; i<graph[v].adjacencyList.size(); i++){
			u = graph[v].adjacencyList[i].neighbor;
			du = graph[v].adjacencyList[i].distance;

			if( !visited[u] && distance[u] > distance[v] + du ){
				distance[u] = distance[v] + du;
			}
		}
	}

	return distance[target] == INT_MAX ? -1 : distance[target];
}
