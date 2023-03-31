#include <cstdio>
#include <cassert>
#include <cstdlib>

static FILE *fr, *fw;

// Declaring variables
static int N;
static int* C;
static int* L;
static int* P;

// Declaring functions

#include <bits/stdc++.h>
#define MAXN 1000005
using namespace std;

inline int fastMod(int num, int N){
    return ((num < N)?num:num-N);
}

void valuta(int N, int C[], int L[], int P[]){
    for(int i = 0; i < N; i++){
        C[i] = C[i] - L[i];
        P[i] = false;
    }
    int i = 0;
    while(i < N){
        if(C[i] >= 0 && C[fastMod(i + N - 1, N)] <= 0){
            int benzina = 0, j = i;
            while(benzina >= 0 && j < i + N)
                benzina+= C[fastMod(j, N)], j++;
            if(benzina < 0)
                i = j;
            else{
                int benzina = 0, j = i;
                while(j <= i + N){
                    if(benzina == 0)
                        P[fastMod(j, N)] = true;
                    benzina+= C[fastMod(j, N)], j++;
                }
                return;
            }
        }
        else
            i++;
    }
	return ;
}


int main() {
    fr = fopen("input.txt", "r");
    fw = fopen("output.txt", "w");

	// Reading input
	fscanf(fr, " %d", &N);
	C = (int*)malloc((N) * sizeof(int));
	L = (int*)malloc((N) * sizeof(int));
	for (int i0 = 0; i0 < N; i0++) {
		fscanf(fr, " %d %d", &C[i0], &L[i0]);
	}

	// Calling functions
	P = (int*)malloc((N) * sizeof(int));
	valuta(N, C, L, P);

	// Writing output
	for (int i0 = 0; i0 < N; i0++) {
		fprintf(fw, "%c", P[i0]);
	}
	fprintf(fw, "\n");

    fclose(fr);
    fclose(fw);
    return 0;
}
