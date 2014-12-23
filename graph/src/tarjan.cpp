#include <iostream>
#include <vector>
#include <stack>
#include <limits.h>
#include <string.h>

#define MAX_VERTEX 100

using namespace std;

struct vertex{
	vector<int> adjacencyList;
};

int dfsVisit(vertex *graph, stack<int>& stack_scc, int *pre, int *low, int& id, int v);
int dfsSCC(vertex *graph, int N);

int main(void){

	ios::sync_with_stdio(false);

	int N, E, A, B, scc;
	vertex graph[MAX_VERTEX];

	while( cin >> N >> E && N ){

		for(int i=0; i<N; i++){
			graph[i].adjacencyList.clear();
		}

		for(int i=0; i<E; i++){
			cin >> A >> B;

			graph[A-1].adjacencyList.push_back(B-1);
		}

		cout << "New Test - Strongly Connected Components" << endl;

		scc = dfsSCC(graph, N);

		cout << "Total of SCC = " << scc << endl << endl;
	}

	return 0;
}

int dfsSCC(vertex *graph, int N){

	stack<int> stack_scc;
	int pre[MAX_VERTEX];
	int low[MAX_VERTEX];
	int id, scc;

	memset(pre, -1, sizeof(pre));
	memset(low, -1, sizeof(low));

	id = -1;
	scc = 0;

	for(int i=0; i<N; i++){
		if( pre[i] == -1 ){
			scc += dfsVisit(graph, stack_scc, pre, low, id, i);
		}
	}

	return scc;
}


int dfsVisit(vertex *graph, stack<int>& stack_scc, int *pre, int *low, int& id, int v){

	int u, stackIndex, scc;

	pre[v] = ++id;
	low[v] = id;
	stack_scc.push( v );

	scc = 0;

	for(unsigned int i=0; i<graph[v].adjacencyList.size(); i++){
		u = graph[v].adjacencyList[i];

		if( pre[u] == -1 )
			scc += dfsVisit(graph, stack_scc, pre, low, id, u);

		low[v] = min(low[v], low[u]);
	}

	if( low[v] == pre[v] ){

		scc++;
		cout << "SCC:";

		do{
			stackIndex = stack_scc.top();
			stack_scc.pop();

			low[stackIndex] = INT_MAX;

			cout << " " << stackIndex+1;
			
		}while( stackIndex != v );

		cout << endl;
	}

	return scc;
}
