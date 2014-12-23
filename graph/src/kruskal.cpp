#include <iostream>
#include <algorithm>

#define MAX_VERTEX 1000

using namespace std;

struct edge{
	int a;
	int b;
	int cost;
};

bool compare(const edge& a, const edge& b);
int UFfind(int A, int *boss);
void UFunion(int A, int B, int *boss, int *size);
int kruskal(edge *list, int N, int M);

int main(void){

	ios::sync_with_stdio(false);

	int N, M;
	edge list[MAX_VERTEX];

	while( cin >> N >> M ){

		for(int i=0; i<M; i++){
			cin >> list[i].a >> list[i].b >> list[i].cost;
		}

		cout << "New Test - Kruskal" << endl << kruskal(list, N, M) << endl;
	}	

	return 0;
}

bool compare(const edge& a, const edge& b){
	return a.cost < b.cost;
}

int UFfind(int A, int *boss){

	int b;

	for(b=A; boss[b]!=-1; b=boss[b]);

	return b;
}

void UFunion(int A, int B, int *boss, int *size){

	if( size[A] > size[B] ){
		boss[B] = A;
		size[A] += size[B];
	}else{
		boss[A] = B;
		size[B] += size[A];
	}
}

int kruskal(edge *list, int N, int M){

	int boss[MAX_VERTEX];
	int size[MAX_VERTEX];
	int A, B, minLength;

	for(int i=0; i<N; i++){
		boss[i] = -1;
		size[i] = 1;
	}

	sort(list, list+M, compare);

	minLength = 0;

	for(int i=0; i<M; i++){
		A = UFfind(list[i].a, boss);
		B = UFfind(list[i].b, boss);

		if( A != B ){
			UFunion(A, B, boss, size);
			minLength += list[i].cost;
		}
	}

	return minLength;
}
