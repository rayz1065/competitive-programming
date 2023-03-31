#include <stdio.h>
#include <assert.h>
#define MAXN 10000000

static int N, i;
static int M[MAXN], P[MAXN];


#include <bits/stdc++.h>
using namespace std;

long long solve(int N, int* M, int* P){
    pair<int, int> comp[N];
    for(int i = 0; i < N; i++){
        comp[i] = {M[i] - P[i], i};
    }
    nth_element(comp, comp + N/2, comp + N);
    long long S = 0;
    for(int i = 0; i < N; i++){
        if(i < N/2){
            S+= P[comp[i].second];
        }
        else{
            S+= M[comp[i].second];
        }
    }
    return S;
}

static FILE *fin, *fout;

int main(){
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    assert(1 == fscanf(fin, "%d", &N));
    for(i=0; i<N; i++) assert(2 == fscanf(fin, "%d%d", M+i, P+i));
    fprintf(fout, "%lld\n", solve(N, M, P));
    fclose(fin);
    fclose(fout);
    return 0;
}
