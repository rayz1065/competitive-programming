#include <stdio.h>
#include <assert.h>
#define MAXM 3000000

static int i, N, M, T;
static int S[MAXM], E[MAXM];


using namespace std;
#include <bits/stdc++.h>

int solve(int N, int M, int T, int* S, int* E){
    vector<pair<int, bool> > grafo[N];
    queue<int> FF;
    int dist[N];
    fill(dist, dist + N, INT_MAX);
    for(int i = 0; i < M; i++){
        grafo[S[i]].push_back({E[i], 0});
        grafo[E[i]].push_back({S[i], 1});
    }
    FF.push(0);
    dist[0] = 0;
    while(!FF.empty()){
        int node = FF.front();
        bool marea = (dist[node] >= T);
        FF.pop();
        for(auto i:grafo[node]){
            if(i.second == marea && dist[node] + 1 < dist[i.first]){
                FF.push(i.first);
                dist[i.first] = dist[node] + 1;
            }
        }
    }
    for(int i = 0; i < N - 1; i++){
        if(dist[i] < T){
            FF.push(i);
            dist[i] = T;
        }
    }
    while(!FF.empty()){
        int node = FF.front();
        FF.pop();
        for(auto i:grafo[node]){
            if(i.second && dist[node] + 1 < dist[i.first]){
                FF.push(i.first);
                dist[i.first] = dist[node] + 1;
            }
        }
    }
    if(dist[N - 1] == INT_MAX)
        return -1;
    return dist[N - 1];
}

static FILE *fin, *fout;

int main(){
    fin = fopen("input.txt", "r");
    fout = fopen("output.txt", "w");
    assert(3 == fscanf(fin, "%d%d%d", &N, &M, &T));
    for(i=0; i<M; i++) assert(2 == fscanf(fin, "%d%d", S+i, E+i));
    fprintf(fout, "%d\n", solve(N, M, T, S, E));
    fclose(fin);
    fclose(fout);
    return 0;
}
