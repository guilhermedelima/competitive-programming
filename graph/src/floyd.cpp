#include <iostream>

#define MAX_VERTEX 100
#define INF 10000

using namespace std;

void floyd(int distance[][MAX_VERTEX], int next[][MAX_VERTEX], int N);

int main(void){

	int distance[MAX_VERTEX][MAX_VERTEX];
	int next[MAX_VERTEX][MAX_VERTEX];
	int N, E, source, target;
	int A, B, D;

	while( cin >> N >> E && N ){

		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				distance[i][j] = i!=j ? INF : 0;
				next[i][j] = j;
			}
		}

		for(int i=0; i<E; i++){
			cin >> A >> B >> D;

			distance[A-1][B-1] = D;
		}

		cin >> source >> target;

		floyd(distance, next, N);

		cout << "New Test" << endl;

		if( distance[source-1][target-1] != INF ){
			cout << "Distance Floyd = " <<  distance[source-1][target-1] << endl;

			cout << source << " ";

			for(int u=next[source-1][target-1]; u!=target-1; u=next[u][target-1]){
				cout << u+1 << " ";
			}

			cout << target << endl;

		}else{
			cout << "Distance Floyd = -1" << endl;
			cout << "There's no Path from " << source << " to " << target << endl;
		}

		cout << endl;
	}

	return 0;
}

/*
Algoritmo Floyd Warshall para calcular menor distancia entre todos os vértices do grafo
Utilizar em questões com muitas consultas e poucos vértces
*/
void floyd(int distance[][MAX_VERTEX], int next[][MAX_VERTEX], int N){

	for(int k=0; k<N; k++){
		for(int i=0; i<N; i++){
			for(int j=0; j<N; j++){
				if( distance[i][j] > distance[i][k] + distance[k][j] ){						
					distance[i][j] = distance[i][k] + distance[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
}
