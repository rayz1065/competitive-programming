#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int M;
static int* A;
static int* B;
static int* inizio;
static int* fine;
static int tempo;

// Declaring functions
#include <climits>
#include <vector>
#include <set>
#include <iostream>
using namespace std;
int raggiungi(int N, int M, int A[], int B[], int inizio[], int fine[]){
    set<pair<int,int> > FF;
    vector<vector<int> > scuola(N);
    vector<int> aule(N,INT_MAX);
    for(int i=0; i<M; i++){
        scuola[A[i]].push_back(i);
        scuola[B[i]].push_back(i);
    }
    FF.insert({0,0});
    aule[0]=0;
    int posizione(0);
    while(!FF.empty()&&FF.begin()->first<aule[N-1]){
        posizione=FF.begin()->second;
        FF.erase(FF.begin());
        for(int i=0; i<scuola[posizione].size(); i++){
            int scala=scuola[posizione][i];
            if(aule[posizione]<fine[scala]){
                if(posizione==A[scala]){
                    if(inizio[scala]<=aule[posizione]&&aule[posizione]+1<aule[B[scala]]){
                        FF.insert({aule[posizione]+1,B[scala]});
                        aule[B[scala]]=aule[posizione]+1;
                    }
                    else if(inizio[scala]>=aule[posizione]&&inizio[scala]+1<aule[B[scala]]){
                        FF.insert({inizio[scala]+1,B[scala]});
                        aule[B[scala]]=inizio[scala]+1;
                    }
                }
                else{
                    if(inizio[scala]<=aule[posizione]&&aule[posizione]+1<aule[A[scala]]){
                        FF.insert({aule[posizione]+1,A[scala]});
                        aule[A[scala]]=aule[posizione]+1;
                    }
                    else if(inizio[scala]>=aule[posizione]&&inizio[scala]+1<aule[A[scala]]){
                        FF.insert({inizio[scala]+1,A[scala]});
                        aule[A[scala]]=inizio[scala]+1;
                    }
                }
            }
        }
    }
    if(aule[N-1]!=INT_MAX)
        return aule[N-1];
    return -1;
}

int main() {
	fr = stdin;
	fw = stdout;
	// Reading input
	fscanf(fr, " %d %d", &N, &M);
	A = (int*)malloc((M) * sizeof(int));
	B = (int*)malloc((M) * sizeof(int));
	inizio = (int*)malloc((M) * sizeof(int));
	fine = (int*)malloc((M) * sizeof(int));
	for (int i0 = 0; i0 < M; i0++) {
		fscanf(fr, " %d %d %d %d", &A[i0], &B[i0], &inizio[i0], &fine[i0]);
	}

	// Calling functions
	tempo = raggiungi(N, M, A, B, inizio, fine);

	// Writing output
	fprintf(fw, "%d\n", tempo);

	fclose(fr);
	fclose(fw);
	return 0;
}
